// ==UserScript==
// @name         USC jwzx
// @namespace    https://github.com/xfl03
// @version      0.1.1
// @description  USC jwzx
// @author       xfl03
// @match        http://jwzx.usc.edu.cn/Student/ScoreReview
// @grant        none
// ==/UserScript==

(function() {
    'use strict';

    $('#StuScore').datagrid({
            columns: [[
                 { field: 'Id', title: '成绩ID', width: 80, hidden: true },
                 { field: 'CourseId', title: '课程Id', width: 100, hidden: true },
                 { field: 'ScoreKind', title: '类别', width: 60 },
                 { field: 'CourseCode', title: '课程代码', width: 100, hidden: true },
                 { field: 'CourseName', title: '课程名称', width: 180 },
                 { field: 'Credit', title: '学分', width: 60 },
                 { field: 'ExamMethod', title: '考核', width: 60 },
                 { field: 'TeachingClassCode', title: '教学班号', width: 80, hidden: true },
                 { field: 'RTeacherName', title: '报送教师', width: 87 },
                 { field: 'ScoreType', title: '类型', width: 60 },
                 { field: 'GeneralScore', title: '平时成绩', width: 87 },
                 { field: 'ExamScore', title: '考试成绩', width: 87 },
                 { field: 'FinalScore', title: '成绩', width: 87 }
            ]]
        });

})();
