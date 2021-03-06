# -*- coding: UTF-8 -*-
import requests
import time

# Change username and password below
username = 'USERNAME'
password = 'PASSWORD'

f = open('CUPWiFiLogin.log', 'a', encoding='utf-8')
t = time.strftime("%Y-%m-%d %H:%M:%S", time.localtime())
f.write(t)
r = requests.get('http://login.cup.edu.cn/ac_detect.php?ac_id=1&', timeout=10)
if 'srun_portal_pc_succeed.php' not in r.text:
    payload = {
        'action': 'login',
        'ac_id': '1',
        'user_ip': '',
        'nas_ip': '',
        'user_mac': '',
        'url': '',
        'username': username,
        'password': password,
        'save_me': '1'
    }
    headers = {
        'user-agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) \
                      AppleWebKit/537.36 (KHTML, like Gecko) \
                      Chrome/75.0.3770.100 Safari/537.36'
    }
    requests.post('http://login.cup.edu.cn/srun_portal_pc.php', data=payload, headers=headers, timeout=10)
    f.write(' 检测到未登录，已自动登录。\n')
else:
    f.write(' 已登录。\n')
f.close()
exit(0)
