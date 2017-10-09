import datetime as dt
import xlrd


__s_date = dt.date(1899, 12, 31).toordinal() -1


def read_xls(filename):
    data = xlrd.open_workbook(filename)
    table = data.sheets()[0]
    deal_rows(table)


def deal_rows(table):
    n_rows = table.nrows
    print str(n_rows)
    # num = 0
    for i in xrange(2, n_rows):
        # num += 1
        i_row = table.row_values(i)
        # get user
        user = i_row[1]
        if user == '':
            continue
        else:
            user = user.split('@')[0]
        # get time report
        time1 = i_row[5]
        if time1 == '':
            continue
        else:
            time1 = getdate(time1).strftime("%Y-%m-%d")
        # get time solve
        time2 = i_row[6]
        if time2 == '':
            continue
        else:
            time2 = getdate(time2).strftime("%Y-%m-%d")
        # get problem
        problem = i_row[11]
        # out = [user, time1, time2, problem]
        # print ' '.join(out)
        # print str(num)


def getdate(date):
    if isinstance(date, float):
        date = int(date)
    d = dt.date.fromordinal(__s_date + date)
    return d

if __name__ == '__main__':
    read_xls('test.xls')
