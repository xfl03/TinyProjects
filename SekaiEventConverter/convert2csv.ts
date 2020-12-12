import {readFileSync, writeFileSync} from 'fs';
import {EventData, EventRanking} from "./Struct";
import dateFormat from "dateFormat";

let day = 0;
let lastDay = 0;

function dateToString(date: Date): string {
    if (date.getDay() !== lastDay) day++;
    lastDay = date.getDay();
    return "D" + day + dateFormat(date, " HH:MM");
}

let eventData = JSON.parse(readFileSync('data.json', 'utf8')) as EventData;
let data = eventData.data.eventRankings;
console.log(data.length);
data.forEach(it => {
    it.timestamp = new Date(it.timestamp.valueOf());
})
data = data.sort((a, b) => a.timestamp.valueOf() - b.timestamp.valueOf());
if (process.argv.length > 2) {
    let final = {} as EventRanking;
    final.timestamp = new Date(data[data.length - 1].timestamp.valueOf());
    final.timestamp.setHours(20);
    final.timestamp.setMinutes(0);
    final.score = parseInt(process.argv[2]);
    data.push(final);
}
lastDay = data[0].timestamp.getDay();

let out = "T,PT\r\n";
data.forEach((it, i) => {
    if (i > 0) {
        let pre = data[i - 1];
        let delta = Math.round((it.timestamp.valueOf() - pre.timestamp.valueOf()) / 1000 / 1800);
        if (delta !== 1) {
            console.log(delta + " " + dateToString(pre.timestamp) + " " + dateToString(it.timestamp));
        }
        if (delta === 2) {
            out +=  "MISS," + Math.round((it.score+pre.score)/2);
            out += "\r\n";
        } else if(delta>2) {
            for(let d = 0;d<delta - 1;++d){
                out +=  "MISS,0\r\n";
            }
        }
    }
    out += dateToString(it.timestamp) + "," + it.score;
    out += "\r\n";
});
writeFileSync("out.csv", out);