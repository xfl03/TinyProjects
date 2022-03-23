/**
 * 同时作用的方块
 * 打击时会影响其他哪些方块
 * 空数组表示打了没反应
 */
const infer = [[1,2], [1,2,3], [2,3,4], [3,4,5], [4,5]];

/**
 * 当前方块状态
 * 状态为旋转次数/叶子数量
 */
const state = [1, 2, 3, 3, 2];

/**
 * 余数
 * 旋转方块为4、循环叶子为3
 */
 const moder = 3;

const results = [];

for (let i = 0; i < Math.pow(moder, state.length); ++i) {
    let working = i;
    let ptr = state.length;
    let times = new Array(state.length).fill(0);
    while (working > 0) {
        times[--ptr] = working % moder;
        working = Math.floor(working / moder);
    }
    let stateNew = Array.from(state);
    infer.forEach((v, i) => {
        for (let j = 1; j <= times[i]; ++j) {
            v.forEach((vv => {
                //if (vv - 1 == i) return;
                stateNew[vv - 1]++;
            }))
            //stateNew[i]++;
        }
    })
    let ans = stateNew[0];
    let flag = true;
    stateNew.forEach(v => {
        if (v % moder != ans % moder){
            flag = false;
        }
    })
    if (flag) {
        results.push(times);
    }
}

const reducer = (previousValue, currentValue) => previousValue + currentValue;

results.sort((a,b) => {
    return a.reduce(reducer) - b.reduce(reducer);
})

results.forEach(it => {
    console.log(it.reduce(reducer))
    console.log(it)
})