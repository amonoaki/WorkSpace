#!/usr/bin/python3
# -*- coding: utf-8 -*-

from Crypto.Cipher import AES  #使用 AES 的 EAX 模式加密账号密码数据
import os.path
import getpass  #用来输入不可见密码
from prettytable import PrettyTable  #用来打印整齐的表格
import re
import requests
import os
from bs4 import BeautifulSoup
from PIL import Image

class Account(object):
    '''创建账户'''
    def __init__(self):
        self.key = b'aGVsbG93b3JsZA=='
        if os.path.isfile('./username.bin') and os.path.isfile('./passward.bin'):
            self.loadAccount()
            option = input('已加载账户{}，是否继续？[y/n]'.format(self.userName))
            if option == 'n':
                self.newAccount()
        else:
            self.newAccount()
    
    def newAccount(self):
        #询问私人数据
        self.userName = input('请输入用户名: ')
        self.passward = getpass.getpass('请输入密码(输入过程字符不可见,输入完成按下回车即可): ')
        option = input('账户信息是否保存到本地？[y/n]')
        if option == 'y':
            self.saveAccount()

    def loadAccount(self):
        self.userName = self.loadData('username.bin')
        self.passward = self.loadData('passward.bin')
    
    def saveAccount(self):
        self.saveData('username.bin', self.userName)
        self.saveData('passward.bin', self.passward)

    def loadData(self, filename):
        # 加载并解密数据
        file_in = open(filename, "rb")
        nonce, tag, ciphertext = [ file_in.read(x) for x in (16, 16, -1) ]
        # let's assume that the key is somehow available again
        cipher = AES.new(self.key, AES.MODE_EAX, nonce)
        data = cipher.decrypt_and_verify(ciphertext, tag)
        return data.decode()
    
    def saveData(self, filename, data):
        # 加密并保存数据
        cipher = AES.new(self.key, AES.MODE_EAX)
        ciphertext, tag = cipher.encrypt_and_digest(data.encode())
        file_out = open(filename, "wb")
        [ file_out.write(x) for x in (cipher.nonce, tag, ciphertext) ]

class Crawling(object):
    '''爬取网页数据'''
    def __init__(self, userName, passward):
        # public data
        self.originURL = 'http://jwgl.bistu.edu.cn/(0hn1iorbybwvx1v4nrmpit45)/'
        self.originHeaders = {'User-Agent': 'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/69.0.3497.81 Safari/537.36', 'Connection': 'keep-alive'}  #记录headers, 伪装成浏览器访问. 'referer'的值要依据网页添加
        self.checkcodePath = './code.png'  #验证码保存路径
        self.checkcodeURL = self.originURL+'CheckCode.aspx'  #验证码网址
        # personal data
        self.__originData = {'Button1':'', 'txtUserName':userName, 'TextBox2':passward}  #登录时要提交的数据: 用户名, 密码, '__VIEWSTATE'的值要从登录页源码中提取, 'txtSecretCode'(验证码)的值要手工输入
        # new session
        self.session = requests.session()  #一个会话, 让cookie得以保存传递. 后面都使用这个session进行post和get

    def getName(self):
        return self.__name

    def setLoginData(self, URL, headers):
        data = self.__originData
        data['__VIEWSTATE'] = BeautifulSoup(self.session.get(URL, headers=headers).text, 'lxml').find('input', type='hidden', id=False).get('value')  #解析得到'__VIEWSTATE'的值, 将'__VIEWDATE'的值加入字典
        checkcode = self.session.get(self.checkcodeURL, headers=headers)  #获得验证码网页
        with open(self.checkcodePath, 'wb') as fp:  #保存验证码图片
            fp.write(checkcode.content)
        with Image.open(self.checkcodePath) as checkcodeImg:
            checkcodeImg.show()  #展示验证码
            data['txtSecretCode'] = input("请输入图片中的验证码(ESC关闭图片): ")  #获得手工输入的验证码, 将验证码加入数据字典中.  数据准备完毕
        
        return data
    
    def setSwitchToGradeData(self, URL, headers, year, semester):
        data = self.__originData
        data['ddlXN'] = year
        data['ddlXQ'] = semester

        data['__VIEWSTATE'] = BeautifulSoup(self.session.get(URL, headers=headers).text, 'lxml').find('input', type='hidden', id=False).get('value')  #解析得到'__VIEWSTATE'的值, 将'__VIEWDATE'的值加入字典

        return data

    def setHeaders(self, refererURL):
        headers = self.originHeaders
        headers['Referer'] = refererURL
        return headers

    def login(self):
        loginPageURL = self.originURL+'default2.aspx'  #登录的网址(post请求网址, 同时也是referer网址)

        loginHeaders = self.setHeaders(loginPageURL)  #得到post需要的headers
        loginData = self.setLoginData(loginPageURL, loginHeaders)  #得到post需要的data
        homePage = self.session.post(loginPageURL, data=loginData, headers=loginHeaders)  #发出post请求(登录), 进入个人教务系统主页

        homePageSoup = BeautifulSoup(homePage.text, 'lxml')  #解析主页源码
        targetURL = homePageSoup.find(onclick="GetMc('课表查询');").get('href')  #得到课表页网址, 其中有中文待处理
        self.__name = re.search(r'[\u4e00-\u9fa5]{2,}', targetURL).group()  #正则匹配到中文
        self.__nameInURL = str(self.__name.encode('gb2312')).replace('\\x', '%').upper()[2:-1]  #将中文转换为地址
    
        return homePage

    def switchToSchedule(self):
        homePageURL = self.originURL+'xs_main.aspx?xh='+self.__originData['txtUserName']  #主页网址(referer网址)
        classPageURL = self.originURL+'xskbcx.aspx?xh='+self.__originData['txtUserName']+'&xm='+self.__nameInURL+'&gnmkdm=N121603'  #得到课表页数据来源网址(get请求网址)
        classPageHeaders = self.setHeaders(homePageURL)  #得到get需要的headers
        classPage = self.session.get(classPageURL, headers=classPageHeaders)  #发出get请求,得到课表页数据
        
        return classPage

    def switchToGrade(self, year, semester):
        gradePageURL = self.originURL+'xscj_gc.aspx?xh='+self.__originData['txtUserName']+'&xm='+self.__nameInURL+'&gnmkdm=N121623'  #取得post网址, post请求网址, 同时也是referer网址
        switchToGradeHeaders = self.setHeaders(gradePageURL)  #取得headers
        switchToGradeData = self.setSwitchToGradeData(gradePageURL, switchToGradeHeaders, year, semester)  #取得data:
        gradePage = self.session.post(gradePageURL, data=switchToGradeData, headers=switchToGradeHeaders)

        return gradePage




class ResolvePage(object):
    '''解析网页数据'''
    def __init__(self, pageCode):  #pageCode可以是爬取的源码也可以是源码的文件句柄
        self.soup = BeautifulSoup(pageCode, 'lxml')

    def resolveScheduleTime(self):  #获得课表所在学年与学期
        scheduleTime = []
        for option in self.soup.findAll('option'):
            if option.get('selected') == 'selected':
                scheduleTime.append(option.get('value'))

        return scheduleTime

    def resolveScheduleContent(self):
        
        subject = []
        schedule = []

        list_table = self.soup.findAll('table')[1].findAll('td', rowspan=True, align=True)
        for sub in list_table:
            for item in sub.strings:
                subject.append(str(item))  #注意要强制转换
                if len(subject) == 5:
                    schedule.append(subject)
                    subject = []
                    
        return schedule

    def resolveSchedule(self):
        schedule = resolver.resolveScheduleContent()  #存放课表
        scheduleTime = resolver.resolveScheduleTime()  #存放当前学年学期, 索引0为学年, 索引1为学期

        return (scheduleTime[0], scheduleTime[1], schedule)
    
    def resolveGradeContent(self):
        
        #total
        total = []
        total_data = self.soup.findAll('table')[1].findAll(height='13')[:-1]
        for i in total_data:
            total.append(i.string)

        #garde
        grade_data = self.soup.findAll('table')[0].findAll('td')
        grade_data1 = str(grade_data).replace('<td>', '').replace('</td>', '').replace(' ', '').replace('[', '').replace(']', '').split(',')

        #按科目拆开
        item = []
        grades = []
        for i in range(len(grade_data1)):
            if (i+1)%20 == 0:
                grades.append(item)
                item = []
            else:
                item.append(grade_data1[i])

        return (grades, total)


if __name__ == '__main__':
    print("将登录你的教务系统......")
    user = Account()
    try:
        #登录
        spider = Crawling(user.userName, user.passward)
        homePage = spider.login()
        #拿到你的姓名
        name = spider.getName()

        option = input("\n选项: 查课表输入1, 查成绩输入2, 输入q退出: ")

        while option != 'q':
            if option == '1':
                #爬取课表
                classPage = spider.switchToSchedule()
                #解析课表
                resolver = ResolvePage(classPage.text)
                # resolver = ResolvePage(open('./source.html'))
                schedule = resolver.resolveSchedule()
                #显示课表
                print("\n%s的课表:" % name)
                print('第%s学年 第%s学期' % (schedule[0], schedule[1]))
                scheduleTable = PrettyTable(['课名', '类型', '时间', '地点', '教师'])
                scheduleTable.align='l'
                for i in schedule[2]:
                    scheduleTable.add_row([i[0],i[1],i[2],i[4],i[3]])
                print(scheduleTable)
                # print("课名\t\t\t类型\t\t时间\t\t\t地点\t教师")
                # for i in schedule[2]:
                #    print("%s\t\t%s\t%s\t%s\t%s" % (i[0],i[1],i[2],i[4],i[3]))
            elif option == '2':
                year = input("请输入要查询的学年(如2017-2018): ")
                semester = input("请输入是%s学年的第几学期(如2): " % year)
                #爬取成绩
                gradePage = spider.switchToGrade(year, semester)
                #解析成绩
                resolver = ResolvePage(gradePage.text)
                (grades, total) = resolver.resolveGradeContent()
                #显示成绩
                print("\n%s的成绩:" % name)
                print('第%s学年 第%s学期' % (year, semester))
                gradeTable = PrettyTable(['课名', '类型', '绩点', '平时', '期末', '实验', '总评'])
                gradeTable.align='l'
                for i in grades[1:]:
                    gradeTable.add_row([i[3],i[4],i[7],i[8],i[10],i[11],i[12]])
                print(gradeTable)
                # print("课名\t\t\t类型\t\t\t绩点\t平时\t期末\t实验\t总评")
                # for i in grades:
                #     print("%s\t\t%s\t%s \t%s\t%s\t%s\t%s" % (i[3],i[4],i[7],i[8],i[10],i[11],i[12]))
                print("综合情况:  %s,  %s,  %s" % (total[0],total[1],total[2]))
            else:
                print("无效选项")
            
            option = input("\n选项: 查课表输入1, 查成绩输入2, 输入q退出: ")
       
        print("\n已退出. 欢迎使用, 再见")
    except:
        print("\n网络开了点小差，已退出，请重试")
    try:
        os.system('rm %s' % spider.checkcodePath)
    except:
        pass
