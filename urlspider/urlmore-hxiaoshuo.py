#!/usr/bin/env python
# -*- coding:utf-8 -*-
"""
һ���򵥵�Python����, ʹ���˶��߳�, 
��ȡ����Topǰ250�����е�Ӱ
Anthor: Andrew Liu
Version: 0.0.2
Date: 2014-12-14
Language: Python2.7.8
Editor: Sublime Text2
Operate: ��������뿴README.md����
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
SHARE_Q = Queue.Queue()  #����һ�������ƴ�С�ĵĶ���
_WORKER_THREAD_NUM = 3  #�����̵߳ĸ���
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
        super(MyThread, self).__init__()  #���ø���Ĺ��캯��
        self.func = func
    def run(self) :
        self.func()

#===============================spider================================

#==============================get page================================
#��ȡ����ҳ�������
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

#��ȡ������������MM����Ϣ��list��ʽ
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
        url = SHARE_Q.get() #�������
        rwurls(url)
        time.sleep(3)
        SHARE_Q.task_done()

def StartMask() :
    global SHARE_Q
    threads = []
    for i in xrange(_WORKER_THREAD_NUM) :
        thread = MyThread(worker)
        thread.start()  #�߳̿�ʼ��������
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
