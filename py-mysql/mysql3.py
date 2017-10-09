#!/usr/bin/python
# -*- coding: UTF-8 -*-

import MySQLdb
import datetime as dt
import xlrd
import random


__s_date = dt.date(1899, 12, 31).toordinal() - 1


class Problem:

    db = None

    def __init__(self):
        self.db = MySQLdb.connect("localhost", "root", "123", "pro", charset="utf8")
        print 'connection ok!!'

    def get_id(self,problem):
        # print type(problem)
        # print type(u'本地业务节点故障')
        if problem==u'产品内容或增值业务类故障':
            return 4
        if problem==u'本地业务节点故障':
            return 3
        if problem==u'业务鉴权类故障':
            return 2
        if problem==u'带宽接入故障':
            return 1
        if problem==u'终端故障':
            return 0
        return -1
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

    def xls_to_db(self,file_name):
        time_string = '2012-03-09'
        date_time = dt.datetime.strptime(time_string,'%Y-%m-%d')
        before_date = date_time - dt.timedelta(7)
        last_date = date_time + dt.timedelta(7)
        data = xlrd.open_workbook(file_name)
        table = data.sheets()[0]
        n_rows = table.nrows
        num = 0
        okn = 0
        cursor = self.db.cursor()
        for i in xrange(1, n_rows):
            num += 1
            # print '%d--' % num
            i_row = table.row_values(i)
            # get user
            user = i_row[1]
            if not user:
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
                time1 = dt.datetime(time1.year, time1.month, time1.day, 0, 0)
            if time1<before_date or time1>last_date:
                okn += 1
                continue
            problem = i_row[11]
            pro_id = self.get_id(problem)
            # print '%d'%pro_id
            if pro_id == -1:
                continue
            # out = [user, time1.strftime("%Y-%m-%d"), problem]
            sql = "INSERT INTO problem(username,proid) VALUES ('%s',%d)" % (user,pro_id)
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
        print '%d-----okn'%okn

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


def getdate(date):
    if isinstance(date, float):
        date = int(date)
    d = dt.date.fromordinal(__s_date + date)
    return d

if __name__ == '__main__':
    # read_xls('all.xls')
    pro = Problem()
    # pro.file_to_db('hw2.txt')
    pro.xls_to_db('all.xls')
    pro.close_db()
    # pro.add_ms('2017-03-03 00:00:00', 'ww', 0, 1, 2, 3, 4, '故障')
    # pro.random_to_pro()
