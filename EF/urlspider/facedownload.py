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

myheaders= [
    'Mozilla/5.0 (Windows NT 5.2) AppleWebKit/534.30 (KHTML, like Gecko) Chrome/12.0.742.122 Safari/534.30',
    'Mozilla/5.0 (Windows NT 5.1; rv:5.0) Gecko/20100101 Firefox/5.0',
    'Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 5.2; Trident/4.0; .NET CLR 1.1.4322; .NET CLR 2.0.50727; .NET4.0E; .NET CLR 3.0.4506.2152; .NET CLR 3.5.30729; .NET4.0C)',
    'Opera/9.80 (Windows NT 5.1; U; zh-cn) Presto/2.9.168 Version/11.50',
    'Mozilla/5.0 (Windows; U; Windows NT 5.1; zh-CN) AppleWebKit/533.21.1 (KHTML, like Gecko) Version/5.0.5 Safari/533.21.1',
    'Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 5.1; Trident/4.0; .NET CLR 2.0.50727; .NET CLR 3.0.04506.648; .NET CLR 3.5.21022; .NET4.0E; .NET CLR 3.0.4506.2152; .NET CLR 3.5.30729; .NET4.0C)']

siteURL = "http://www.7dapei.com/men.html"
sitebaseURL = "http://www.7dapei.com/"
#================================spider thread======================

#===============================spider================================

#==============================get page================================
#获取索引页面的内容
def getPage():
    global myheaders
    #url = siteURL + str(pageIndex)+".html"
    url = siteURL 
    print "url is "+ url
    header={"User-Agent":random.choice(myheaders)}
    try:
        request = urllib2.Request(url,headers=header)
        response = urllib2.urlopen(request)
        #page =  response.read().decode('utf-8')
        page =  response.read().decode('utf-8')
        response.close()
        return page 
    except:
        print "Open pageIndex Error,skip this" 
    return 

#获取索引界面所有MM的信息，list格式
def saveImg(imgurl,filename):
    print "imgurl==="+imgurl
    fend = imgurl.split('.')[-1]
    print "img end of "+fend
    filenm = filename+'.'+fend
    try:
        u = urllib.urlopen(imgurl)
        data = u.read()
        f = open(filenm,'wb')
        f.write(data)
        f.close
        print "OK,save the img\n"
    except:
        print "this img is error,can not be sava\n"

def rwurls():
    page = getPage()
    print "ok,get the page"
    if page == None:
        return 
    pattern = re.compile('<a.?href=".*?".?target=.?"_blank">.?<img.?class=".*?".?data-src="(.*?)".*?>.*?</a>',re.S)
    urls = re.findall(pattern,page)
    if len(urls) >=2:
        del urls[0]
    print "get this page of all the imgs urls"+str(len(urls))
    rwfile(urls)

#read and write the file
def rwfile(urls):
    j = 0
    for i in urls:
        saveImg(sitebaseURL+i,"facedata/face_"+str(j))
        j+=1

#========================================tool for get imgs==================================	
def main():
    rwurls()

if __name__ == '__main__':
    main()
