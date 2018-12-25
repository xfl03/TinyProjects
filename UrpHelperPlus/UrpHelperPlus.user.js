// ==UserScript==
// @name         URP Helper Plus
// @namespace    https://github.com/xfl03
// @version      0.1
// @description  URP Helper Plus
// @author       xfl03
// @match        http://urp.cup.edu.cn/student/courseSelect/freeCourse/*
// @grant        none
// ==/UserScript==

(function() {
    'use strict';

    //在此修改默认设置
    var autopost = false;//是否开启自动提交，默认关闭
    var timeout = 30;//刷新时间，默认30秒
    var logtime = 1;//几次刷新输出一次日志，默认1次

    var t0 = 0;//上一次设置TimeOut的时间
    var lt0 = 0;//刷新次数

    //检查变量是否存在
    function isset(o){return typeof o !== 'undefined'}
    //输出日志
    function log(msg){var date = new Date();console.log(`[${date.toTimeString().split(' ')[0]}] ${msg}`);}

    //更新设置
    function updateConfig(r){
        if(isset(window.parent.autopost) && window.parent.autopost!=autopost){
            autopost=window.parent.autopost;
            if(r) log(autopost?"自动提交已开启":"自动提交已关闭");
        }
        if(isset(window.parent.timeout) && window.parent.timeout!=timeout){
            timeout=window.parent.timeout;
            if(r) log(`刷新时间修改为${timeout}秒`)
        }
    }
    //刷新课程
    function refreshList(){
        lt0=(lt0+1)%logtime;
        updateConfig(true);
        guolv(1);//调用查询按钮的事件
        if(lt0==0) log(`已刷新${logtime}次`);
    }
    //Watch Dog
    function watchDog(){
        var timestamp = new Date().getTime();
        if(timestamp>t0+2*timeout*1000){//检查上一次的Timeout时间是否已超过2倍延时
            log("Watch Dog已尝试重连")
            setTimeout(refreshList,2000);//设置刷新时间
            t0=timestamp;
        }
    }
    setInterval(watchDog,5*timeout*1000);//定时检查Timeout状态

    log("脚本正在运行");
    updateConfig(false);
    log(autopost?"已开启自动提交":"未开启自动提交");
    log(`刷新时间为${timeout}秒`)

    //课程刷新事件
    $("body").on('DOMSubtreeModified', "#xirxkxkbody", function() {
        var count=$(".ace-checkbox-2").size();
        if(count==0){
            var timestamp = new Date().getTime();
            if(timestamp>t0+1000){//每隔一段时间再设置新的Timeout
                setTimeout(refreshList,timeout*1000);//设置刷新时间
                t0=timestamp;
            }
        }else{
            if(!$(".ace-checkbox-2")[0].checked){
                $(".ace-checkbox-2")[0].click();//选择CheckBox
                log("检测到有课余量，已自动选择课程");
                if(autopost){
                    log("已自动提交选课");
                    window.parent.tijiao();//调用提交按钮（在父窗口）的事件
                }
            }
        }
    });
})();