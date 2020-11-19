const P = 0.4;
const N = 3;
const T = 1000000;
const J = 1;
const EXCHANGE = true;
const SURE = J >= 10;

function getRandom(max: number) {
    return Math.random() * Math.floor(max);
}

let sum = 0;

for (let t = 0; t < T; ++t) {
    let set = new Set();
    for (let i = 1; ; ++i) {
        let star2 = 0;
        for (let j = 0; j < J; ++j) {
            let ran = getRandom(100);
            if (ran >= 11.5) star2++;
            let n = Math.floor(ran / P);
            if (n >= N) continue;
            set.add(n);
            //console.log("Get:"+n);
        }

        if (SURE && star2 == 10) {
            let n = Math.floor(getRandom(100) / P);
            if (n >= N) continue;
            set.add(n);
        }

        if (EXCHANGE && set.size >= N - Math.floor(i * J / 300)) {
            sum += i;
            break;
        }
        if (set.size >= N) {
            //console.log(i);
            sum += i;
            break;
        }
    }
}

console.log(sum / T);