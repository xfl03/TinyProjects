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
 * 结构体（数据类），用于存储值和值对应的位置
 */
data class E(val value: Int, val pos: Int)

/**
 * 优先队列，用于快速寻找最小值和次小值
 */
val queue = PriorityQueue<E> { o1, o2 ->
    if (o1.value == o2.value)
        o1.pos - o2.pos
    else
        o1.value - o2.value
}

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

    (0 until n).forEach {
        queue.add(E(data[it], it))//将数组中的所有内容加入优先队列
    }

    while (size > 1) {//不断查找两个最小权值并合并，直至数组内仅剩一个有效元素
        select()//进行合并
        print()//输出合并后的数组
    }
}

/**
 * 查找最小的两个权值并合并
 */
fun select() {
    val min = queue.poll()//最小值
    val min2 = queue.poll()//次小值

    data[min2.pos] = min.value + min2.value//将两个数合并放入次小的位置
    data[min.pos] = Int.MAX_VALUE//将最小的位置标记为无效数据（已经被合并）

    queue.add(E(data[min2.pos], min2.pos))//将合并后的元素再次加入优先队列
    size--//减小数组大小
}

/**
 * 格式化输出数据数组中的有效内容
 */
fun print() {
    data.forEach {
        if (it != Int.MAX_VALUE) print("$it") //输出每一个有效数据
        print("\t") //用制表符分割
    }
    println()//输出换行
}