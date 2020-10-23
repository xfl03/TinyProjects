import java.io.*

fun main(args: Array<String>) {
    val tokenizer = SimpleCTokenizer(FileInputStream("demo.c"))
    tokenizer.process()

    println("File 'demo.c' has functions below:")
    val it = tokenizer.result.listIterator()
    while (it.hasNext()) {
        val p = it.next()
        if (p.first == SimpleCTokenizer.Type.ARGUMENT) {
            it.previous()
            it.previous()
            val type = it.previous().second
            it.next()
            val id = it.next().second
            val arg = it.next().second
            println("$type $id($arg)")
        }
    }
}

