#!/usr/bin/env python

import sys
import shutil 
import os.path

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print "usage:xxx"
        sys.exit(1)
    num = 0
    BASE_PATH = sys.argv[1]
    for dirname,dirnames,filenames in os.walk(BASE_PATH):
        #print dirname
        #print dirnames
        for oldfile in filenames:
            newname = "data_"+str(num)
            newfile = newname+'.'+oldfile.split('.')[-1]
            print "oldfile is "+oldfile+" newfile is "+newfile
            os.rename(dirname+oldfile,dirname+newfile)
            print "=====ok,rename over======num is "+str(num)+"=========="
            os.mkdir(dirname+newname)
            shutil.move(dirname+newfile,dirname+newname)
            num+=1
