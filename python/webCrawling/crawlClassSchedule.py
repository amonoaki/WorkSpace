#!/usr/bin/python3
# -*- coding: utf-8 -*-

import getpass  #用来输入不可见密码
import re
import requests
from bs4 import BeautifulSoup
from PIL import Image

class Crawling:
    #public data
    originURL = 'http://jwgl.bistu.edu.cn/(0hn1iorbybwvx1v4nrmpit45)/'
    originHeaders = {'User-Agent': 'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/69.0.3497.81 Safari/537.36',
            'Connection': 'keep-alive'}  #记录headers, 伪装成浏览器访问. 'referer'的值要依据网页添加
    checkcodePath = './code.png'  #验证码保存路径
    checkcodeURL = originURL+'CheckCode.aspx'  #验证码网址
    session = None #一个会话, 让cookie得以保存传递. 后面都使用这个session进行post和get.

    #personal data
    __originData = {'Button1':''} #登录时要提交的数据: 用户名, 密码, '__VIEWSTATE'的值要从登录页源码中提取, 'txtSecretCode'(验证码)的值要手工输入


    def __init__(self, userName, passward):
        self.__originData['txtUserName'] = userName
        self.__originData['TextBox2'] = passward
        self.session = requests.session() 

    def setData(self, pageSoup, headers):
        data = self.__originData
        data['__VIEWSTATE'] = pageSoup.findAll('input')[0].get('value')  #解析得到'__VIEWSTATE'的值, 将'__VIEWDATE'的值加入字典
        checkcode = self.session.get(self.checkcodeURL, headers=headers)  #获得验证码网页
        with open(self.checkcodePath, 'wb') as fp:  #保存验证码图片
            fp.write(checkcode.content)
        checkcodeImg = Image.open(self.checkcodePath)
        checkcodeImg.show()  #展示验证码
        data['txtSecretCode'] = input("请输入图片中的验证码: ")  #获得手工输入的验证码, 将验证码加入数据字典中.  数据准备完毕
        return data

    def setHeaders(self, refererURL):
        headers = self.originHeaders
        headers['Referer'] = refererURL
        return headers

    def login(self):
        loginPageURL = self.originURL+'default2.aspx'  #登录的网址(post请求网址, 同时也是referer网址)

        loginPageCode = self.session.get(loginPageURL, headers=self.originHeaders).text  #进入登录页, 保存登录页源码
        loginPageSoup = BeautifulSoup(loginPageCode, 'lxml')  #登录页源码传入解析器解析

        loginData = self.setData(loginPageSoup, self.originHeaders)  #得到post需要的data
        loginHeaders = self.setHeaders(loginPageURL)  #得到post需要的headers
        homePage = self.session.post(loginPageURL, data=loginData, headers=loginHeaders)  #发出post请求(登录), 进入个人教务系统主页
    
        return homePage

    def switchToSchedule(self, homePage):
        homePageURL = self.originURL+'xs_main.aspx?xh='+self.__originData['txtUserName']  #主页网址(referer网址)

        homePageSoup = BeautifulSoup(homePage.text, 'lxml')  #解析主页源码
        targetURL = homePageSoup.findAll('a')[18].get('href')  #得到课表页网址, 其中有中文待处理
        name = re.search(r'[\u4e00-\u9fa5]{2,}', targetURL).group()  #正则匹配到中文
        nameInURL = str(name.encode('gb2312')).replace('\\x', '%').upper()[2:-1]  #将中文转换为地址
        classPageURL = self.originURL+'xskbcx.aspx?xh='+self.__originData['txtUserName']+'&xm='+nameInURL+'&gnmkdm=N121603'  #得到课表页数据来源网址(get请求网址)

        classPageHeaders = self.setHeaders(homePageURL)  #得到get需要的headers
        classPage = self.session.get(classPageURL, headers=classPageHeaders)  #发出get请求,得到课表页数据
        
        return classPage

class ResolvePage:
    soup = None
    schedule = []  #存放课表
    scheduleTime = []  #存放当前学年学期, 索引0为学年, 索引1为学期

    def __init__(self, pageCode):  #pageCode可以是爬取的源码也可以是源码的文件句柄
        self.soup = BeautifulSoup(pageCode, 'lxml')

    def getSchedule(self):
        return self.schedule
    def getScheduleYear(self):
        return self.scheduleTime[0]
    def getScheduleSemester(self):
        return self.scheduleTime[1]

    def resolveScheduleTime(self):  #获得课表所在学年与学期
        for option in self.soup.findAll('option'):
            if option.get('selected') == 'selected':
                self.scheduleTime.append(option.get('value'))

    def resolveScheduleContent(self):
        classes = []

        #取下包含了课表内容的源码
        rows = self.soup.findAll('tr')[4:17]
        for row in rows:
            columns = row.findAll('td')
            for column in columns:
                if column.get('align') == 'Center' and column.text != '\xa0':
                    classes.append(str(column))

        #去除无用部分,留下<\br>用来分隔各项
        for i in range(len(classes)):
            index = classes[i].find('>')+1
            classes[i] = classes[i][index:-5]
        #合为一个字符串
        classes = '<br/>'.join(classes)
        #按分隔符拆开为列表
        classes =re.split(r'<br/><br/>|<br/>', classes)  #按正则表达式分割, | 为或, 遵循短路原则, 所以 | 两边顺序不可变换

        #按科目拆开
        subject = []
        for i in range(len(classes)):
            subject.append(classes[i])
            if (i+1)%5 == 0:
                self.schedule.append(subject)
                subject = []

if __name__ == '__main__':
    #询问私人数据
    userName = input('请输入用户名: ')
    passward = getpass.getpass('请输入密码: ')
    #爬取
    spider = Crawling(userName, passward)
    homePage = spider.login()
    classPage = spider.switchToSchedule(homePage)
    #解析
    resolver = ResolvePage(classPage.text)
    resolver.resolveScheduleTime()
    resolver.resolveScheduleContent()
    #显示
    print('第%s学年 第%s学期' % (resolver.getScheduleYear(), resolver.getScheduleSemester()))
    schedule = resolver.getSchedule()
    for i in schedule:
        print(i)
