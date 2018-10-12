// ==UserScript==
// @name         淡化萌娘百科黑幕
// @namespace    http://github.com/xfl03
// @version      0.1
// @description  淡化萌娘百科黑幕
// @author       xfl03
// @match        https://zh.moegirl.org/*
// @grant        none
// ==/UserScript==

(function() {
    'use strict';

    //$(".heimu, .heimu a, .heimu a.new").css("background-color","#CCCCCC");
    //$(".heimu").removeClass("heimu");
    var heimus=document.querySelectorAll(".heimu, .heimu a, .heimu a.new");
    heimus.forEach(
        function(a){
            a.style.backgroundColor="#D0D0D0";
            a.classList.remove("heimu");
        }
    );
})();