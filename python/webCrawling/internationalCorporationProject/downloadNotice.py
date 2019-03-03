#!/usr/bin/python3
# -*- "coding: utf-8" -*-

import requests
from bs4 import BeautifulSoup
import os

url = 'http://icd.bistu.edu.cn/hwxx/'
selector_string = 'body > div.main > div.mainrig > div > div.mainrig > div.mainrigbar > div.mainrig > div > div.newslist > ul > li'

r = requests.get(url)
r.encoding = 'utf-8'  #更改编码类型为 utf-8
soup = BeautifulSoup(r.text, 'lxml')
links = soup.select(selector_string)
infos = []
update = False
for li in links:
    ele = li.find_all('a', href=True)[0]
    infos.append({'filename':ele.text, 'href':ele['href']})
for info in infos:
    if os.path.isfile('downloads/{}.html'.format(info['filename'])):
        continue
    link = url + info['href']
    r = requests.get(link)
    r.encoding = 'utf-8'
    with open('downloads/{}.html'.format(info['filename']), 'w') as f:
        f.write(r.text)
    update = True
if update:
    os.system('python3 /home/ubuntu/bin/alarm.py 有新的交流项目啦')
