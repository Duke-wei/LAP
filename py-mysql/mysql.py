#!/usr/bin/python
# -*- coding: UTF-8 -*-

import MySQLdb
import datetime as dt
import xlrd
import random

problems = {
    0:'(211)用户软件问题',
    1:'(212)用户硬件问题',
    2:'(223)局域网影响',
    3:'FTTB障碍原因',
    4:'查中自复',
    5:'数据配置',
    6:'用户硬件问题',
    7:'交接箱跳线坏',
    8:'传输设备故障',
    9:'无线信号受干扰',
    10:'用户预埋线室内故障',
    11:'设备割接影响',
    12:'硬件故障',
    13:'传输资源',
    14:'用户自建局域网故障影响',
    15:'软件故障',
    16:'计算机软件问题',
    17:'用户线问题',
    18:'其他',
    19:'用户软件(不包括拨号软件)问题',
    20:'用户操作不当',
    21:'其他特殊原因',
    22:'产品内容或增值业务类故障',
    23:'本地业务节点故障',
    24:'业务鉴权类故障',
    25:'带宽接入故障',
    26:'终端故障'
}
__s_date = dt.date(1899, 12, 31).toordinal() - 1


def get_index(num):
    if num >= 24354:
        return 26
    elif num >= 13329:
        return 25
    elif num >= 7569:
        return 24
    elif num >= 2554:
        return 23
    elif num >= 255:
        return 22
    if num <= 7:
        return num
    elif num <= 9:
        return 8
    elif num <= 11:
        return 9
    elif num <= 12:
        return 10
    elif num <= 15:
        return 11
    elif num <= 19:
        return 12
    elif num <= 24:
        return 13
    elif num <= 29:
        return 14
    elif num <= 37:
        return 15
    elif num <= 46:
        return 16
    elif num <= 55:
        return 17
    elif num <= 88:
        return 18
    elif num <= 121:
        return 19
    elif num <= 170:
        return 20
    else:
        return 21


class Problem:

    db = None

    def __init__(self):
        self.db = MySQLdb.connect("localhost", "root", "123", "pro", charset="utf8")
        print 'connection ok!!'

    def file_to_db(self, file_name):
        file1 = open(file_name, 'r')
        done = 0
        num = 0
        cursor = self.db.cursor()
        while not done:
            num += 1
            if num%500 == 0:
                print '%d\n' % num
            line = file1.readline()
            line = line[:-1]
            if line == '':
                done = 1
            dump = line.split('|')
            if len(dump) != 18:
                continue
            datelist = []
            # print user_name
            datelist.append(dump[0])
            datelist.append(dump[1].split('@')[0])
            datelist.append(int(dump[3]))
            datelist.append(int(dump[4]))
            datelist.append(int(dump[5]))
            datelist.append(int(dump[6]))
            datelist.append(int(dump[7]))
            datelist.append(int(dump[8]))
            datelist.append(int(dump[9]))
            datelist.append(int(dump[10]))
            datelist.append(int(dump[11]))
            datelist.append(int(dump[12]))
            datelist.append(int(dump[13]))
            datelist.append(int(dump[14]))
            datelist.append(int(dump[15]))
            datelist.append(int(dump[16]))
            datelist.append(int(dump[17]))
            sql = "INSERT INTO message(savetime,username,f1,f2,f3,f4,f5,f6,f7,f8,f9,f10,f11,f12,f13,f14,f15) VALUES ('%s','%s',%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d)" % tuple(datelist)
            # print sql
            try:
                cursor.execute(sql)
                if(num%2000 == 0):
                    self.db.commit()
                    print 'add 2000-----'
            except MySQLdb.Error, e:
                self.db.rollback()
                print("Mysql Error %d: %s" % (e.args[0], e.args[1]))
        self.db.commit()

    def random_to_pro(self):
        cursor = self.db.cursor()
        for i in xrange(6020, 1724444):
            print i
            num = random.randint(0, 55237)
            sql = "update message set problem='%s' where id=%d" % (problems[get_index(num)], i)
            try:
                cursor.execute(sql)
                if i%2000 == 0:
                    print 'commit--'
                    self.db.commit()
            except MySQLdb.Error, e:
                self.db.rollback()
                print("Mysql Error %d: %s" % (e.args[0], e.args[1]))
        self.db.commit()

    def find_and_set(self, date, user, pro):
        cursor = self.db.cursor()
        before_date = date - dt.timedelta(30)
        last_date = date + dt.timedelta(30)
        # print '-------'
        # print last_date.strftime("%Y-%m-%d")+'----------'+before_date.strftime("%Y-%m-%d")
        # print '-------'
        # date = dt.datetime(date.year, date.month, date.day, 0, 0)
        # print type(date)
        b_time = dt.datetime(before_date.year, before_date.month, before_date.day, 0, 0)
        l_time = dt.datetime(last_date.year, last_date.month, last_date.day, 0, 0)
        sql = "select * from message where username='%s' and savetime between '%s' and '%s'" % (user, b_time, l_time)
        # print sql
        try:
            cursor.execute(sql)
            results = cursor.fetchall()
            if not results:
                # print 'no results'
                return
            # print len(results)
            for row in results:
                # print row
                # print row[0]
                self.set_pro(pro, row[0])
        except MySQLdb.Error, e:
            self.db.rollback()
            print("Mysql Error %d: %s" % (e.args[0], e.args[1]))

    def set_pro(self, prob, idx):
        cursor = self.db.cursor()
        sql = "update message set problem='%s' where id=%d" % (prob, idx)
        # print sql
        try:
            cursor.execute(sql)
            self.db.commit()
            # print 'ok,add one'
        except MySQLdb.Error, e:
            self.db.rollback()
            print("Mysql Error %d: %s" % (e.args[0], e.args[1]))

    def close_db(self):
        self.db.close()


def read_xls(filename):
    data = xlrd.open_workbook(filename)
    table = data.sheets()[0]
    deal_rows(table)


def deal_rows(table):
    n_rows = table.nrows
    pro = Problem()
    # print str(n_rows)
    num = 0
    for i in xrange(7166, n_rows):
        num += 1
        print '%d--' % num
        i_row = table.row_values(i)
        # get user
        user = i_row[1]
        if not user:
            # print 'no user'
            continue
        else:
            user = user.split('@')[0]
        # get time report
        time1 = i_row[5]
        if not time1:
            # print 'no time'
            continue
        else:
            time1 = getdate(time1)
        # get time solve
        # time2 = i_row[6]
        # if time2 == '':
        #     continue
        # else:
        #     time2 = getdate(time2).strftime("%Y-%m-%d")
        # get problem
        problem = i_row[11]
        # out = [user, time1.strftime("%Y-%m-%d"), problem]
        # print ' '.join(out)
        # print str(num)
        pro.find_and_set(time1, user, problem)
        # print '-------------------\n'


def getdate(date):
    if isinstance(date, float):
        date = int(date)
    d = dt.date.fromordinal(__s_date + date)
    return d

if __name__ == '__main__':
    # read_xls('all.xls')
    pro = Problem()
    pro.file_to_db('hw2.txt')
    pro.close_db()
    # pro.add_ms('2017-03-03 00:00:00', 'ww', 0, 1, 2, 3, 4, '故障')
    # pro.random_to_pro()
