#!/usr/bin/env python
import cv2
import sys
import shutil 
import os.path
import numpy as np
from PIL import Image,ImageDraw
from cv2 import *

def detectFaces(img):
    imgd = cv2.imread(img)
    img_gray = cv2.imread(img,CV_LOAD_IMAGE_GRAYSCALE)
    face_cascade = cv2.CascadeClassifier("model/haarcascade_frontalface_alt.xml")
    #if imgd.ndim == 3:
    #    gray = cv2.cvtColor(imgd,cv2.COLOR_BGR2GRAY)
    #else:
    #    gray = img
    gray = np.array(img_gray,dtype='uint8')
    faces = face_cascade.detectMultiScale(gray,1.1,6,0)
    result = []
    for(x,y,width,height) in faces:
        result.append((x,y,x+width,y+height))
    return result

def saveFaces(image_name):
    faces = detectFaces(image_name)
    print "step 2 ok,get the face area"
    if faces:
        filetype = '.'+image_name.split('.')[-1]
        save_dir = image_name.split('.')[0]+"_faces"
        count = 0
        for (x1,y1,x2,y2) in faces:
            file_name = save_dir+str(count)+filetype
            print "step 3 "+file_name
            srcimg = cv2.imread(image_name)
            srcimgROI = srcimg[y1:y2,x1:x2]
            #Image.open(image_name).crop((x1,y1,x2,y2))
            saveimg = cv2.resize(srcimgROI,(32,32),interpolation=cv2.INTER_CUBIC)
            cv2.imwrite(file_name,saveimg)
            #saveimg.save(file_name)
            count += 1


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print "usage:xxx"
        sys.exit(1)
    num = 0
    BASE_PATH = sys.argv[1]
    for dirname,dirnames,filenames in os.walk(BASE_PATH):
        for subdirname in dirnames:
            subject_path = os.path.join(dirname,subdirname)
            print "step 0"+subject_path
            for filename in os.listdir(subject_path):
                abs_path = "%s/%s"%(subject_path,filename)
                print "step 1"+abs_path
                saveFaces(abs_path)
                print "step 4================clear one=========="+str(num)
                num += 1
