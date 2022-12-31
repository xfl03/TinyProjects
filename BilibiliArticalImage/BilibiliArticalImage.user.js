// ==UserScript==
// @name         bilibili 专栏高清图片
// @namespace    https://github.com/xfl03
// @version      0.1
// @license      GPL-v3.0
// @description  在 bilibili 专栏中显示高清图片
// @author       xfl03
// @match        https://www.bilibili.com/read/cv*
// @icon         https://static.hdslb.com/images/favicon.ico
// @grant        none
// ==/UserScript==

(function() {
    'use strict';

    const imageRegex = /\/\/i0.hdslb.com\/bfs\/article\/(\w+)\.png@(\w+)\.webp/;
    const targetNode = document.getElementById('article-content');
    const callback = function(mutationsList, observer) {
        for(let mutation of mutationsList){
            if (mutation.type === "attributes") {
                const image = mutation.target;

                const src = image.getAttribute('src');
                if (!src) continue;
                const m = src.match(imageRegex);
                if (m) {
                    const newSrc = `//i0.hdslb.com/bfs/article/${m[1]}.png`;
                    //console.log(`图片地址替换: ${newSrc}`);
                    image.setAttribute('src', newSrc);
                }
            }
        }
    };
    //https://developer.mozilla.org/zh-CN/docs/Web/API/MutationObserver/observe
    const option = {subtree: true, childList: false, attributes: true, attributeFilter: ["src"]};
    new MutationObserver(callback).observe(targetNode, option);
})();