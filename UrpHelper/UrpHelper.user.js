// ==UserScript==
// @name         URP教务系统助手
// @namespace    https://github.com/xfl03
// @version      0.1.3
// @description  URP教务系统助手，用于辅助URP教务系统的使用
// @author       xfl03
// @match        http://urp.cup.edu.cn/student/teachingEvaluation/teachingEvaluation/evaluationPage
// @grant        none
// ==/UserScript==

(function() {
    'use strict';

    $(document).ready(function () {
        //解决提交时间限制问题，允许提前提交
        //修改：已加入后端时间检测，无法提前提交
        //$("#RemainM").html(0);
        //$("#RemainS").html(1);

        //提交倒计时结束自动提交
        function autoSubmit(){
            var m = parseInt($("#RemainM").html());
            var s = parseInt($("#RemainS").html());
            var t = (m * 60 + s) * 1000;
            console.log(t);
            if (t == 0) {
                console.log("Submit");
                $("#buttonSubmit").click();
                return;
            }
            setTimeout(function(){
               autoSubmit();
            }, t);
        }
        autoSubmit();

        //自动选择最优选项
        var keyWord=["优","很大进步","总是","个别最好的"];
        $(".ace").each(function(){
            var self=$(this);
            var text=$(this).next().next().html();
            keyWord.forEach(function(value){
                if(text.indexOf(value)!=-1)
                    self.click();
            });
            console.log(text);
        })

        //自动填写主观评价
        var content="";//自行填写
        $("textarea").val(content);
    });
})();
