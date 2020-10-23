import org.objectweb.asm.ClassReader
import org.objectweb.asm.tree.AnnotationNode
import org.objectweb.asm.tree.ClassNode
import java.io.File
import java.io.InputStream
import java.util.zip.ZipFile

fun main(args: Array<String>) {
    val file = File(if (args.isNotEmpty()) args[0] else "./mods")
    file.listFiles()?.forEach { processJar(it) }
}

fun processJar(jar: File) {
    if (!jar.isFile || !jar.name.endsWith(".jar")) {
        return
    }
    var side = Side.DEFAULT

    val zip = ZipFile(jar)
    val zes = zip.entries()
    while (zes.hasMoreElements()) {
        val ze = zes.nextElement()
        if (ze.name.endsWith(".class")) {
            side = side.max(processClass(zip.getInputStream(ze)))
        }
    }

    println("${jar.name}: $side")
}

fun processClass(clazz: InputStream): Side {
    val cr = ClassReader(clazz)
    val cn = ClassNode()
    cr.accept(cn, ClassReader.SKIP_DEBUG)

    if (cn.name == "org/spongepowered/mod/SpongeMod") {
        return Side.SERVER_ONLY
    }

    var side = Side.DEFAULT

    cn.visibleAnnotations?.forEach { side = side.max(processAnnotation(cn.name, it)) }

    return side
}

fun processAnnotation(name: String, an: AnnotationNode): Side {
    if (an.desc == "Lorg/spongepowered/api/plugin/Plugin;") {
        return Side.SERVER_ONLY
    }
    if (an.desc != "Lnet/minecraftforge/fml/common/Mod;") {
        return Side.DEFAULT
    }
    //println(name)
    var flag = true
    var key = ""

    an.values.forEach {
        if (flag) {
            key = it.toString()
        } else {
            //println("$key = $it")
            val side = judgeSide(key, it.toString())
            if (side != Side.DEFAULT) {
                return side
            }
        }
        flag = !flag

    }
    //println()
    return Side.BOTH
}

fun judgeSide(key: String, value: String): Side {
    if (key == "clientSideOnly" && value == "true") {
        return Side.CLIENT_ONLY
    }
    if (key == "serverSideOnly" && value == "true") {
        return Side.SERVER_ONLY
    }
    if (key == "acceptableRemoteVersions" && value == "*") {
        return Side.UNIVERSAL
    }
    return Side.DEFAULT
}

enum class Side {
    DEFAULT, BOTH, SERVER_ONLY, CLIENT_ONLY, UNIVERSAL;

    fun max(s1: Side): Side {
        return if (this.ordinal < s1.ordinal) s1 else this
    }
}