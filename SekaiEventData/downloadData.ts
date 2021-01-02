import axios from 'axios';
import {writeFileSync, existsSync} from 'fs';
import {execSync} from 'child_process';

async function downloadData(eventId: number, rankId: number) {
    const response = await axios.get(`https://api.sekai.best/event/${eventId}/rankings/graph?rank=${rankId}`);
    writeFileSync(`data/data_${eventId}_${rankId}.json`, JSON.stringify(response.data), 'utf-8');
    console.log(`Download ${eventId} ${rankId}`)
}

const events = 8;
const ranks = [100, 500, 1000, 5000, 10000];

async function downloadAllData() {
    ranks.forEach(it => {
        for (let i = 1; i <= events; ++i) {
            if (!existsSync(`data/data_${i}_${it}.json`))
                downloadData(i, it).catch(e => console.log(`Failed to download: ${i} ${it}`))
        }
    })
}

function processAllData() {
    ranks.forEach(it => {
        for (let i = 1; i <= events; ++i) {
            if (existsSync(`data/data_${i}_${it}.json`) && !existsSync(`out/out_${i}_${it}.json`)) {
                execSync(`ts-node convert2csv.ts ${i} ${it}`)
                console.log(`Processed ${i} ${it}`)
            }
        }
    })
}

if (process.argv.length > 3) {
    const event = parseInt(process.argv[2]);
    const rank = parseInt(process.argv[3]);
    downloadData(event, rank).then(it=>execSync(`ts-node convert2csv.ts ${event} ${rank}`))
} else {
    downloadAllData().then(it => processAllData())
}