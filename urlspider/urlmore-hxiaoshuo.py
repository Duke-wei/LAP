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
import sys 

con = threading.Condition()
FILE_LOCK = threading.Lock()
socket.setdefaulttimeout(3)
SHARE_Q = Queue.Queue()  #构造一个不限制大小的的队列
_WORKER_THREAD_NUM = 3  #设置线程的个数
myheaders= [
    'Mozilla/5.0 (Windows NT 5.2) AppleWebKit/534.30 (KHTML, like Gecko) Chrome/12.0.742.122 Safari/534.30',
    'Mozilla/5.0 (Windows NT 5.1; rv:5.0) Gecko/20100101 Firefox/5.0',
    'Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 5.2; Trident/4.0; .NET CLR 1.1.4322; .NET CLR 2.0.50727; .NET4.0E; .NET CLR 3.0.4506.2152; .NET CLR 3.5.30729; .NET4.0C)',
    'Opera/9.80 (Windows NT 5.1; U; zh-cn) Presto/2.9.168 Version/11.50',
    'Mozilla/5.0 (Windows; U; Windows NT 5.1; zh-CN) AppleWebKit/533.21.1 (KHTML, like Gecko) Version/5.0.5 Safari/533.21.1',
    'Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 5.1; Trident/4.0; .NET CLR 2.0.50727; .NET CLR 3.0.04506.648; .NET CLR 3.5.21022; .NET4.0E; .NET CLR 3.0.4506.2152; .NET CLR 3.5.30729; .NET4.0C)']

siteURL = "http://www.hxiaoshuo.top/?m=art-type-id-11"
sitebaseURL = "http://www.hxiaoshuo.top"
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
    url = siteURL + "-pg-" + str(pageIndex)+".html"
    print "url is "+ url
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

#获取索引界面所有MM的信息，list格式
def rwurls(pageIndex):
    page = getPage(pageIndex)
    print "ok,get the page"
    if page == None:
        return 
    pattern = re.compile('<a.?href="(.*?)".?target=.?"_black".?style=".*?">',re.S)
    urls = re.findall(pattern,page)
    if len(urls) >=2:
        del urls[0]
    print "get this page of all the imgs urls"+str(len(urls))
    rwfile(urls)

#read and write the file
def rwfile(urls):
    FILE_LOCK.acquire()
    output = open('url.log','a+')
    for i in urls:
        output.write(sitebaseURL+i)
        output.write("\n")
    output.close()
    FILE_LOCK.release()

#========================================tool for get imgs==================================	

def worker() :
    global SHARE_Q
    while not SHARE_Q.empty():
        url = SHARE_Q.get() #获得任务
        rwurls(url)
        time.sleep(3)
        SHARE_Q.task_done()

def StartMask() :
    global SHARE_Q
    threads = []
    for i in xrange(_WORKER_THREAD_NUM) :
        thread = MyThread(worker)
        thread.start()  #线程开始处理任务
        threads.append(thread)
    for thread in threads :
        thread.join()
    SHARE_Q.join()

def main():
    for index in range(int(sys.argv[1]),int(sys.argv[2])):
        SHARE_Q.put(index)
    StartMask()
	
if __name__ == '__main__':
    main()
