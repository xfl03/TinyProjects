// ==UserScript==
// @name         蓝墨云班课（Moso Tech）资源下载
// @namespace    https://github.com/xfl03/
// @version      0.2
// @description  增加下载按钮，以便于直接在线下载蓝墨云班课（Moso Tech）中的资源
// @author       xfl03
// @match        https://www.mosoteach.cn/web/index.php*
// @grant        none
// ==/UserScript==

(function() {
    'use strict';

    $(".res-row-open-enable").each(function() {
        if ($(this).find(".download-res-button").length > 0) return;//如果已经存在下载按钮（例如mp3），则不再添加
        $(this).find("ul").html('<li class="download-ress download-res-button">下载</li>' + $(this).find("ul").html());
    });

    $(document).on('click', '.download-ress', function() {
            var resHref = $(this).parents(".res-row-open-enable").attr('data-href');
            window.open(resHref);
    });
})();