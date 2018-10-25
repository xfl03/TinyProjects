import java.util.*
import kotlin.collections.ArrayList

/**
 * 存储边信息的数据类
 */
data class Edge(
        var v1: Int,//边的顶点1
        var v2: Int, //边的顶点2
        var weight: Int//边的权值
)

var u = 0//顶点个数
var v = 0//边个数
var edges = ArrayList<Edge>()//存储边信息的数组

fun main(args: Array<String>) {
    var scanner = Scanner(System.`in`);
    print("请输入顶点数：")
    u = scanner.nextInt();//读入顶点个数
    print("请输入边数：")
    v = scanner.nextInt();//读入边个数
    println("请分别输入每条边：")
    for (i in 0 until v) {
        edges.add(Edge(scanner.nextInt(), scanner.nextInt(), scanner.nextInt()));//分别读入每条边的信息
    }

    var tree = kruskal(edges, u);//计算最小生成树
    var weight = 0//记录总权值
    println("最小生成树为：")
    tree.forEach {
        println("${it.v1} ${it.v2} ${it.weight}")//输出每条边的信息
        weight += it.weight//记录总权值
    }
    println("最小权值为：$weight")
}

/**
 * 克鲁斯克尔算法
 * @param e 边的集合
 * @param n 顶点个数
 * @return 最小生成树的边的集合
 */
fun kruskal(e: List<Edge>, n: Int): List<Edge> {
    var set = IntArray(n + 1) { it }//记录每个元素属于哪个集合
    var t = ArrayList<Edge>()//最小生成树边的集合T，初始为空
    var pos = 0//工作指针，指向原集合的下一个位置
    while (t.size < n - 1) {
        var next = e[pos++];//获得E中下一条边
        if (set[next.v1] != set[next.v2]) {//如果x、y不在一个集合中
            t.add(next);//将边加入T
            set[next.v2] = set[next.v1];//将集合合并
        }
    }
    return t//返回生成后的边集合
}