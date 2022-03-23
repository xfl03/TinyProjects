/*
 * 相关讨论：https://bbs.mihoyo.com/ys/article/19277924
 * 《mys99%的人不会做这题，特别是双暴魔怔人！》
 * 作者：番茄香蕉酸奶
 * 1。已知角色攻击力2200，双暴40/200，问：提升7.8的爆伤带来的期望收益和提升多少攻击力带来的期望收益等价？
 * 2。攻冰暴神里雾切基础攻击力为1016，圣遗物副词条提供攻击力，双暴为a.b.c，现给你37个词条分配双暴大公鸡，问：如何分配词条使得期望伤害最高？(提示：假设吃满双冰冰套+自身暴击率为60暴击率，雾切爆伤44.1%，神里突破+38.4爆伤，爆伤头62.2%，自身带50爆伤，攻击沙漏46.6%，羽毛311攻击力)
 * 词条成长均为最大值5.8/3.9/7.8
 * 3。同问2，但给你攻击拐40%，求重新分配abc。
 * 期望公式：总攻击力×(1+爆×暴)，其中总攻击力＝白字+绿字，白字受武器，人物等级影响，绿字受圣遗物影响
 */

/*
 * 攻击相关信息
 */
const baseAttack = 1016;
const bonusAttack = 311;
const bonusAttackPercent = 46.6 + 40;

/*
 * 暴击相关信息
 */
const criticalRate = 60;
const criticalDamageRate = 44.1 + 38.4 + 62.2 + 50;

/*
 * 圣遗物词条信息
 */
const extraCount = 37;
const extraAttackPercent = 5.8;
const extraCriticalRate = 3.9;
const extraCriticalDamageRate = 7.8;

function getDamage(attack, critical, criticalDamage) {
    return attack * (1 + Math.min(critical, 100) * criticalDamage);
}

function getAttack(attackPercent) {
    return baseAttack + baseAttack * (attackPercent + bonusAttackPercent) / 100 + bonusAttack;
}

function getCritical(criticalPercent) {
    return criticalRate + criticalPercent;
}

function getCriticalDamage(criticalDamagePercent) {
    return criticalDamageRate + criticalDamagePercent;
}

let maxDamage = 0;

function judgeDamage(arr) {
    let info = [
        getAttack(arr[0] * extraAttackPercent),
        getCritical(arr[1] * extraCriticalRate),
        getCriticalDamage(arr[2] * extraCriticalDamageRate)
    ];
    let damage = getDamage(info[0], info[1], info[2]);
    if (damage < maxDamage) return;
    maxDamage = damage;
    console.log(`${damage} ${arr} ${info}`)
}

function dfs(arr, pos) {
    let sum = arr.slice(0, pos).reduce((p, v) => p + v, 0);
    if (pos === arr.length - 1) {
        arr[pos] = extraCount - sum;
        judgeDamage(arr);
        return;
    }

    Array.from({ length: extraCount - sum + 1 }, (_, i) => i).forEach(i => {
        arr[pos] = i;
        dfs(arr, pos + 1);
    })
}
judgeDamage([17, 10, 10])
dfs([0, 0, 0], 0);