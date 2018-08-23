import java.io.*

val usedClasses = setOf(
        "net/minecraft/client/Minecraft",
        "net/minecraft/client/multiplayer/ServerData",
        "net/minecraft/client/renderer/IImageBuffer",
        "net/minecraft/client/renderer/ImageBufferDownload",
        "net/minecraft/client/renderer/ThreadDownloadImageData",
        "net/minecraft/client/renderer/texture/ITextureObject",
        "net/minecraft/client/renderer/texture/NativeImage",
        "net/minecraft/client/renderer/texture/SimpleTexture",
        "net/minecraft/client/renderer/texture/TextureManager",
        "net/minecraft/client/renderer/texture/ThreadDownloadImageData",//1.13
        "net/minecraft/client/resources/DefaultPlayerSkin",
        "net/minecraft/client/resources/SkinManager",
        "net/minecraft/util/ResourceLocation",
        "net/minecraft/util/StringUtils"
)

val br = BufferedReader(InputStreamReader(FileInputStream(File("in.srg"))))
val bw = BufferedWriter(OutputStreamWriter(FileOutputStream(File("out.srg"))))

var str = br.readLine()
while (str != null) {
    var t = str.split(" ").toMutableList()
    val qwq = (t.size + 1) / 2
    var className = if (t[0] == "CL:") t[qwq] else t[qwq].substring(0, t[qwq].lastIndexOf('/'))
    if (className.contains("$")) className = className.substring(0, className.lastIndexOf('$'))

    if (usedClasses.contains(className)) {
        //1.13 Fix
        if (t[qwq].contains("onSkinTextureAvailable"))
            t[qwq] = t[qwq].replace("onSkinTextureAvailable", "func_180521_a")
        if (str.contains("net/minecraft/client/renderer/texture/ThreadDownloadImageData")) {
            str = str.replace("net/minecraft/client/renderer/texture/ThreadDownloadImageData", "net/minecraft/client/renderer/ThreadDownloadImageData")
            t = str.split(" ").toMutableList()
        }

        val sb = StringBuilder(t[0]).append(" ");
        (qwq until t.size).forEach { sb.append(t[it]).append(" ") }
        (1 until qwq).forEach { sb.append(t[it]).append(" ") }
        val strs = sb.trim().toString() + "\n"
        bw.write(strs)
    }
    str = br.readLine()
}

br.close()
bw.flush()
bw.close()