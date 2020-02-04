import SimpleCTokenizer.Status.*
import java.io.*
import java.util.*


class SimpleCTokenizer(code: InputStream) {
    private var br = BufferedReader(InputStreamReader(code))

    enum class Type {
        TYPE, //类型
        IDENTIFIER, //标识符
        CONSTANT,//常量
        OPERATOR, //操作符
        ARGUMENT //参数
    }

    private enum class Status {
        INIT, //初态
        READING_TYPE, //正在读取类型
        WAIT_NAME, //已知类型，等待标识符
        READING_NAME, //正在读取标识符
        WAIT_NAME1,//已知标识符，等待';'或'('
        IN_ARGUMENT, //读取到'('，在参数中
        IN_ARGUMENT_NEWLINE, //读取到换行，在参数中的新行
        WAIT_FUNCTION,//等待'{'
        IN_FUNCTION, //读取到'{'，在函数中
        WAIT_COMMENT, //读取到'/'，等待第二个'/'或'*'
        IN_SINGLE_COMMENT, //在单行注释中
        IN_MULTI_COMMENT, //在多行注释中
        IN_MULTI_COMMENT1 //在多行注释中读取到'*'，等待'/'
    }

    private var status = INIT
    private var statusAfterComment = INIT

    var result = LinkedList<Pair<Type, String>>()

    fun process() {
        var c: Int
        while (br.read().also { c = it } != -1) {
            processChar(c.toChar())
        }
    }

    var buffer = StringBuilder()
    private fun processChar(c: Char) {
        var next = -1

        when (status) {
            INIT -> {
                when {
                    isBlank(c) -> {
                        //空白字符，无操作
                    }
                    c == '/' -> {
                        //注释
                        status = WAIT_COMMENT
                        statusAfterComment = INIT
                    }
                    c == '#' -> {
                        //预编译指令，跳过此行
                        br.readLine()
                    }
                    isName(c) -> {
                        //读取类型
                        status = READING_TYPE
                        buffer.append(c)
                    }
                    else -> error(c)
                }
            }
            READING_TYPE -> {
                when {
                    c == '/' -> {
                        //注释，注释后应接标识符
                        status = WAIT_COMMENT
                        statusAfterComment = WAIT_NAME
                    }
                    isName(c) -> {
                        //继续读取类型
                        buffer.append(c)
                    }
                    isBlank(c) -> {
                        //类型读取完成，等待标识符
                        status = WAIT_NAME
                    }
                    else -> error(c)
                }

                if (status != READING_TYPE) {
                    //已经读完类型，将类型存入结果
                    result.add(Pair(Type.TYPE, buffer.toString()))
                    buffer.clear()
                }
            }
            WAIT_NAME -> {
                when {
                    c == '/' -> {
                        //注释
                        status = WAIT_COMMENT
                        statusAfterComment = WAIT_NAME
                    }
                    isBlank(c) -> {
                        //空白符号，什么都不做
                    }
                    isName(c) -> {
                        //开始读取名称
                        status = READING_NAME
                        buffer.append(c)
                    }
                    else -> error(c)
                }
            }
            READING_NAME -> {
                when {
                    c == '/' -> {
                        //注释，等待语句结束
                        status = WAIT_COMMENT
                        statusAfterComment = WAIT_NAME1
                    }
                    isBlank(c) -> {
                        //空白字符，名称读取完毕
                        status = WAIT_NAME1
                    }
                    c == ';' -> {
                        //语句结束
                        status = INIT
                    }
                    c == '(' -> {
                        //进入参数
                        status = IN_ARGUMENT
                    }
                    isName(c) -> {
                        //继续读取名称
                        buffer.append(c)
                    }
                    else -> error(c)
                }

                if (status != READING_NAME) {
                    //已经读完名称，将类型存入结果
                    result.add(Pair(Type.IDENTIFIER, buffer.toString()))
                    buffer.clear()
                }
            }
            WAIT_NAME1 -> {
                when (c) {
                    ';' -> {
                        //语句结束
                        status = INIT
                    }
                    '(' -> {
                        //进入参数
                        status = IN_ARGUMENT
                    }
                }
            }
            IN_ARGUMENT -> {
                when {
                    isCRLF(c) -> {
                        //忽略行首空格
                        status = IN_ARGUMENT_NEWLINE
                    }
                    c == ')' -> {
                        //参数读取完毕
                        result.add(Pair(Type.ARGUMENT, buffer.toString()))
                        status = WAIT_FUNCTION
                    }
                    else -> {
                        //继续读取参数
                        buffer.append(c)
                    }
                }
            }
            IN_ARGUMENT_NEWLINE -> {
                when {
                    isBlank(c) -> {
                        //忽略行首空格
                    }
                    c == ')' -> {
                        //参数读取完毕
                        result.add(Pair(Type.ARGUMENT, buffer.toString()))
                        status = WAIT_FUNCTION
                    }
                    else -> {
                        //继续读取参数
                        buffer.append(c)
                        status = IN_ARGUMENT
                    }
                }
            }
            WAIT_FUNCTION -> {
                if (c == '{') {
                    //进入函数
                    status = IN_FUNCTION
                }
            }
            IN_FUNCTION -> {
                if (c == '}') {
                    //离开函数
                    status = INIT
                }
            }
            WAIT_COMMENT -> {
                when (c) {
                    '*' -> {
                        //多行注释
                        status = IN_MULTI_COMMENT
                    }
                    '/' -> {
                        //单行注释
                        status = IN_SINGLE_COMMENT
                    }
                    else -> error(c)
                }
            }
            IN_SINGLE_COMMENT -> {
                if (isCRLF(c)) {
                    //单行注释结束
                    status = statusAfterComment
                }
            }
            IN_MULTI_COMMENT -> {
                if (c == '*') {
                    //读取到'*'，等待'/'
                    status = IN_MULTI_COMMENT1
                }
            }
            IN_MULTI_COMMENT1 -> {
                if (c == '/') {
                    //多行注释结束
                    status = statusAfterComment
                } else {
                    //仍在多行注释中
                    status = IN_MULTI_COMMENT
                }
            }
        }

        if (next != -1) {
            processChar(next.toChar())
        }
    }

    private fun isCRLF(c: Char) = (c == '\n' || c == '\r')
    private fun isBlank(c: Char) = (c == ' ' || c == '\n' || c == '\r')
    private fun isName(c: Char) = ((c in 'a'..'z' || c in 'A'..'Z' || c in '0'..'9' || c == '_' || c.toInt() > 256))
    private fun error(c: Char) {
        throw RuntimeException("Status:$status Char:$c ${c.toInt()}")
    }
}