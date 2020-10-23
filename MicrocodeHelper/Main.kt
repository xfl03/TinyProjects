import java.util.*

fun main(args: Array<String>) {
    while (true) {
        run()
    }
}

var ins = LinkedList<String>()

fun run() {
    ins.clear()
    println("MRW I2-0 I8-6 I5-3 B口 A口 SST SSH、SCI DC2 DC1")
    val sc = Scanner(System.`in`)

    val mrv = sc.next().toInt(2)
    var target = ""
    var source = ""
    when (mrv) {
        0 -> target = "MEM"
        1 -> source = "MEM"
        2 -> target = "IO"
        3 -> source = "IO"
    }

    val i20 = sc.next().toInt(2)
    val i86 = sc.next().toInt(2)
    val i53 = sc.next().toInt(2)
    val b = sc.next().toInt(2)
    val a = sc.next().toInt(2)
    sc.next()
    val sshsci = sc.next().toInt(2)

    val dc2 = sc.next().toInt(2)
    val dc1 = sc.next().toInt(2)

    when (dc2) {
        1 -> target = "IR"
        3 -> target = "AR"
    }

    when (dc1) {
        2 -> source = "IR"
        3 -> source = "FLAG"
    }

    alu(i20, i86, i53, b, a, sshsci, target, source)
    println(ins.joinToString(", "))
    println()
}

fun alu(I20: Int, I86: Int, I53: Int, B: Int, A: Int, sshsci: Int, target: String, source: String): String {
    val r: String
    val s: String
    val a = getR(A, true)
    val b = getR(B, false)
    when (I20) {
        0 -> {
            r = a;s = "Q"
        }
        1 -> {
            r = a;s = b
        }
        2 -> {
            r = "0";s = "Q"
        }
        3 -> {
            r = "0";s = b
        }
        4 -> {
            r = "0";s = a
        }
        5 -> {
            r = source;s = a
        }
        6 -> {
            r = source;s = "Q"
        }
        else -> {
            r = source;s = "0"
        }
    }
    val op = when (I53) {
        0 -> formatAdd(r, s, sshsci)
        1 -> formatSub(s, r, sshsci)
        2 -> formatSub(r, s, sshsci)
        3 -> "$r|$s"
        4 -> "$r&$s"
        5 -> "~$r&$s"
        6 -> "$r^$s"
        else -> ""
    }

    var cr = ""
    var cq = ""
    var cy = ""
    var t = target
    when (I86) {
        0 -> {
            cq = "$op->Q"
        }
        1 -> {
            cy = if (source != "" && I20 == 0) {
                if (target == "") t = "FLAG"
                source
            } else op
        }
        2 -> {
            cr = "$op->$b"
            cy = a
        }
        3 -> {
            cr = "$op->$b"
        }
    }
    if (cy != "") if (t != "") printI("$cy->$t") else printI(cy)
    printI(cr)
    printI(cq)
    if (t != "" && cy == "") printI(t)
    return cy
}

fun formatAdd(R: String, S: String, sshsci: Int): String {
    var ret = when {
        R == "0" -> S
        S == "0" -> R
        else -> "$R+$S"
    }

    when (sshsci) {
        1 -> ret += "+1"
        2 -> ret += "+CF"
    }
    return ret
}

fun formatSub(R: String, S: String, sshsci: Int): String {
    var ret = when {
        R == "0" -> "-$S"
        S == "0" -> R
        else -> "$R-$S"
    }

    when (sshsci) {
        0 -> ret += "-1"
        2 -> ret += "-CF"
    }
    return ret
}

fun getR(R: Int, SD: Boolean): String {
    return when (R) {
        4 -> "SP"
        5 -> "PC"
        else -> if (SD) "SR" else "DR"
    }
}

var flag = false
fun printI(I: String) {
    if (I.isEmpty()) return
    ins.add(I)
}