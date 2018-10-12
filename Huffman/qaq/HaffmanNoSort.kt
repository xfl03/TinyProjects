package qaq

import java.util.*

/**
 * 权值数组大小，会在每次合并后减一
 */
var size = 0

/**
 * 权值数组数据，无效数据会被标记为2^31-1
 */
var data = ArrayList<Int>()

/**
 * 主函数 程序入口
 */
fun main(args: Array<String>) {
    val scanner = Scanner(System.`in`)

    println("请输入权值个数：")
    val n = scanner.nextInt()//权值个数，下面运行过程中不改变
    size = n//将数组大小赋值为权值个数

    println("请输入权值：")
    (0 until n).forEach {
        data.add(scanner.nextInt())//读入所有权值
    }
    data.sort()//排序读入的权值
    print()//输出排序后的数组

    while (size > 1) {//不断查找两个最小权值并合并，直至数组内仅剩一个有效元素
        select()//进行合并
        print()//输出合并后的数组
    }
}

/**
 * 查找最小的两个权值并合并
 */
fun select() {

    var min = Int.MAX_VALUE//最小值
    var minPos = -1//最小值所在的位置
    var min2 = Int.MAX_VALUE//次小值
    var min2Pos = -1//次小值所在地位置

    (0 until data.size).forEach {
        //遍历数组
        val e = data[it]//当前元素的值
        if (e < min) {//e比最小值还小
            min2 = min;min2Pos = minPos//将次小值设定为原先的最小值
            min = e;minPos = it//将最小值设定为e
        } else if (e < min2) {//e在最小值和次小值中间
            min2 = e;min2Pos = it//将次小值设置为e
        }
    }

    data[min2Pos] = min + min2//将两个数合并放入次小的位置
    data[minPos] = Int.MAX_VALUE//将最小的位置标记为无效数据（已经被合并）
    size--//减小数组大小
}

/**
 * 格式化输出数据数组中的有效内容
 */
fun print() {
    data.forEach {
        if (it != Int.MAX_VALUE) print("$it"); //输出每一个有效数据
        print("\t") //用制表符分割
    }
    println()//输出换行
}