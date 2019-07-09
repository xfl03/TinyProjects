import requests

# Change username and password below
username = 'username'
password = 'password'

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
