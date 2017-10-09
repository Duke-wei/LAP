#!/usr/bin/env python
# -*- coding:utf-8 -*-
"""
一个简单的Python爬虫, 使用了多线程, 
爬取豆瓣Top前250的所有电影
Anthor: Andrew Liu
Version: 0.0.2
Date: 2014-12-14
Language: Python2.7.8
Editor: Sublime Text2
Operate: 具体操作请看README.md介绍
"""

import urllib2
import urllib
import string
import re 
import threading, Queue, time
import os
import random 
import socket

con = threading.Condition()
FILE_LOCK = threading.Lock()
socket.setdefaulttimeout(3)
SHARE_Q = Queue.Queue()  #构造一个不限制大小的的队列
_WORKER_THREAD_NUM = 3  #设置线程的个数
number = 0
path = "."
myheaders= [
    'Mozilla/5.0 (Windows NT 5.2) AppleWebKit/534.30 (KHTML, like Gecko) Chrome/12.0.742.122 Safari/534.30',
    'Mozilla/5.0 (Windows NT 5.1; rv:5.0) Gecko/20100101 Firefox/5.0',
    'Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 5.2; Trident/4.0; .NET CLR 1.1.4322; .NET CLR 2.0.50727; .NET4.0E; .NET CLR 3.0.4506.2152; .NET CLR 3.5.30729; .NET4.0C)',
    'Opera/9.80 (Windows NT 5.1; U; zh-cn) Presto/2.9.168 Version/11.50',
    'Mozilla/5.0 (Windows; U; Windows NT 5.1; zh-CN) AppleWebKit/533.21.1 (KHTML, like Gecko) Version/5.0.5 Safari/533.21.1',
    'Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 5.1; Trident/4.0; .NET CLR 2.0.50727; .NET CLR 3.0.04506.648; .NET CLR 3.5.21022; .NET4.0E; .NET CLR 3.0.4506.2152; .NET CLR 3.5.30729; .NET4.0C)']

siteURL = 'http://www.husewang88.com/meitu'
sitebaseURL = 'http://www.husewang88.com'
#================================spider thread======================
class MyThread(threading.Thread) :
    def __init__(self,func) :
        super(MyThread, self).__init__()  #调用父类的构造函数
        self.func = func
    def run(self) :
        self.func()

#===============================spider================================

#==============================get page================================
#获取索引页面的内容
def getPage(pageIndex):
    global myheaders
    print "start get page....."
    url = siteURL + "/index_" + str(pageIndex)+".html"
    header={"User-Agent":random.choice(myheaders)}
    try:
        request = urllib2.Request(url,headers=header)
        response = urllib2.urlopen(request)
        page =  response.read().decode('utf-8')
        response.close()
        return page 
    except:
        print "Open pageIndex Error,skip this with pageIndex = " + str(pageIndex)
    return 

def getOnlyPage(url):
    global myheaders
    url = sitebaseURL+url
    print "start get the img page ...url="+url
    header={"User-Agent":random.choice(myheaders)}
    try:
        request = urllib2.Request(url,headers=header)
        response = urllib2.urlopen(request)
        page =  response.read().decode('utf-8')
        response.close()
        return page 
    except:
        print "Open Imgsurl Error,skip this One!!!"

#获取索引界面所有MM的信息，list格式
def getContents(pageIndex):
    print "get the imgs url....."
    page = getPage(pageIndex)
    if page == None:
        return 
    pattern = re.compile('<li><a.?href="(.*?)".?target=.?_blank.?>.*?</a><span>.*?</span></li>',re.S)
    imgsurl = re.findall(pattern,page)
    if len(imgsurl) >= 2:
        del imgsurl[0]
    print "get this page of all the imgs urls"+str(len(imgsurl))
    return imgsurl 

#========================================tool for dir=====================		
#use rar to get xx.rar
def rardir():
    global path
    path = path.strip()
    isExists = os.path.exists(path)
    if isExists:
        target = path+'.rar'
        rar_command = "rar a %s %s" % (target,path)
        if os.system(rar_command) == 0:
            deldir()
            print "successful rar !!!"
        else:
            print "rar fail !!!"

#mkdir for a page of img
def mkimgdir():
    global path
    path = path.strip()
    isExists = os.path.exists(path)
    if not isExists:
        os.makedirs(path)
        print "OK,create the dir"
    else:
        print "Error,fail to create the dir"
#mkdir for a page of img
def deldir():
    global path
    path = path.strip()
    isExists = os.path.exists(path)
    if isExists:
        rm_command = "rm -rf %s" % (path)
        os.system(rm_command)
        print "del the dir......" 
#========================================tool for dir=====================

#传入图片地址，文件名，保存单张图片
def saveImg(imageURL,filename):
    print "imageURL==========="+imageURL
    try:
        u = urllib.urlopen(imageURL)
        data = u.read()
        print "get image data=======then save it!!!"
        print "filename======"+filename
        f = open(filename, 'wb')
        f.write(data)
        f.close()
        print "ok, sava the mag!!!"
    except :
        print "this img is break,skip it!!!"

#保存多张写真图片
def saveImgs(images):
    global number
    global path
    print "get the imgs...."
    for imageURL in images:
        if con.acquire():
            pathi = path + "/" + str(number) + ".jpg"
            print "number :==========" + str(number)
            saveImg(imageURL,pathi)
            number += 1
            con.release()
            time.sleep(1)


#获取页面所有图片
def getAllImg(imgurl):
    page = getOnlyPage(imgurl)
    if page == None:
        print "the imgurl return None!!!"
        return 
    #从代码中提取图片
#    print page
    patternImg = re.compile('<img.*?src="(.*?)".*?><br>',re.S)
    images = re.findall(patternImg,page)
    if len(images) >= 2:
        del images[0]
    print "get the img url ....care it is img...."
    return images
	 
def savePageInfo(imgurl):
    images = getAllImg(imgurl)
    if images == None:
        print "images is None!!!!"
        return 
    if len(images) > 1:
        saveImgs(images)
    else:
        print "this page has no imgs!!!"

#========================================tool for get imgs==================================	

def worker() :
    global SHARE_Q
    while not SHARE_Q.empty():
        imgurl = SHARE_Q.get() #获得任务
        savePageInfo(imgurl)
        time.sleep(3)
        SHARE_Q.task_done()

def GetOneMask(Index) :
    global SHARE_Q
    global path
    threads = []
    imgsurl  = getContents(Index)
    if imgsurl == None:
        deldir()
        return 1 #return 1 mean try again
    if len(imgsurl) == 0:
        return 1 #return 2 mean over the index
    for imgurl in imgsurl:
        SHARE_Q.put(imgurl)
    for i in xrange(_WORKER_THREAD_NUM) :
        thread = MyThread(worker)
        thread.start()  #线程开始处理任务
        threads.append(thread)
    for thread in threads :
        thread.join()
    SHARE_Q.join()

def main():
    global path
    for index in range(85,182):
        path = "./" + str(index)
        mkimgdir()
        try:
            t = GetOneMask(index)
            if t == 1:
                print "try again ,a ha ha !!!!!!"
                GetOneMask(index)
        except urllib2.URLError,e:
            deldir()
            print "get URLerror !! with index = "+str(index)
        rardir()
        deldir()
        time.sleep(1)
	
if __name__ == '__main__':
    main()
