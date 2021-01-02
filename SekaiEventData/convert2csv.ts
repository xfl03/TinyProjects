import {readFileSync, writeFileSync} from 'fs';
import {EventData, EventRanking, SimpleRanking} from "./Struct";
import dateFormat from "dateFormat";

let dataFile = "data.json";
let csvFile = "out.csv";
let jsonFile = "out.json";

//Choose event
if (process.argv.length > 3) {
    const event = parseInt(process.argv[2]);
    const rank = parseInt(process.argv[3]);
    dataFile = `data/data_${event}_${rank}.json`;
    csvFile = `out/out_${event}_${rank}.csv`;
    jsonFile = `out/out_${event}_${rank}.json`;
}

let day = 0;
let lastDay = 0;

function dateToString(date: Date): string {
    if (date.getDay() !== lastDay) day++;
    lastDay = date.getDay();
    return "D" + day + dateFormat(date, " HH:MM");
}

let eventData = JSON.parse(readFileSync(dataFile, 'utf8')) as EventData;
let data = eventData.data.eventRankings;
console.log(data.length);
data.forEach(it => {
    it.timestamp = new Date(it.timestamp.valueOf());
})

//Add begin data
let begin = {} as EventRanking;
begin.timestamp = new Date(data[0].timestamp.valueOf());
begin.timestamp.setHours(14);
begin.timestamp.setMinutes(0);
begin.score = 0;
data.push(begin);

data = data.sort((a, b) => a.timestamp.valueOf() - b.timestamp.valueOf());
lastDay = data[0].timestamp.getDay();

//Process last data
let dt = data[data.length - 1].timestamp.getTime() - data[data.length - 2].timestamp.getTime()
if (dt > 32 * 60 * 1000) {
    //Correct end data time
    data[data.length - 1].timestamp.setHours(20);
    data[data.length - 1].timestamp.setMinutes(0);
    data[data.length - 1].timestamp.setSeconds(0, 0);
}

let outObj: SimpleRanking[] = [];
data.forEach((it, i) => {
    //Skip illegal data
    if (it.timestamp.getMinutes() !== 0 && it.timestamp.getMinutes() !== 30) return

    if (i > 0) {
        let pre = data[i - 1];
        let delta = Math.round((it.timestamp.valueOf() - pre.timestamp.valueOf()) / 1000 / 1800);
        if (delta !== 1) {
            console.log("MISS " + (delta - 1) + " between " + dateToString(pre.timestamp) + " and " + dateToString(it.timestamp));

            let deltaPT = Math.round((it.score - pre.score) / delta);
            for (let d = 1; d < delta; ++d) {
                let midTime = new Date(pre.timestamp.getTime() + d * 30 * 60 * 1000);
                outObj.push({
                    time: midTime,
                    pt: delta > 3 ? 0 : pre.score + d * deltaPT
                });
            }
        }
    }
    outObj.push({
        time: it.timestamp,
        pt: it.score
    });
});

//Save CSV
let outCSV = "T,PT\r\n";
outObj.forEach(it => {
    outCSV += dateToString(it.time) + "," + it.pt + "\r\n"
})
writeFileSync(csvFile, outCSV);

//Gen day PT
let dayPT: number[] = [];
let PT: number[] = [];
outObj.forEach(it => {
    if (it.time.getHours() === 0 && it.time.getMinutes() === 0) dayPT.push(it.pt);
    PT.push(it.pt);
})
let outJson = {
    beginTime: outObj[0].time,
    lastTime: outObj[outObj.length - 1].time,
    lastScore: outObj[outObj.length - 1].pt,
    dayScores: dayPT,
    halfHourScores: PT
}
writeFileSync(jsonFile, JSON.stringify(outJson, null, 4));
