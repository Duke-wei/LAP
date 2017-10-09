import os
num = 16471;
def rename2(filepath):
    for filei in os.listdir(filepath):
        os.chdir(filepath)
        print filei
        if os.path.isdir(filei):
            print "ok ,we will open the file "+filei
            print os.path.abspath(filei)
            re2(os.path.abspath(filei))

def re2(filepath):
    global num #print filei
    for filei in os.listdir(filepath):
        if os.path.splitext(filei)[1]==".jpg":
            newname = "Y"+str(num) + ".jpg"
            #print "change to "+filei+" with name "+newname
            os.chdir(filepath)
            os.rename(filei,newname)
            num += 1
        print "OK,kill this one!!! num become "+str(num)
def main():
    rename2("E:\\DataSet")	
if __name__ == '__main__':
    main()
