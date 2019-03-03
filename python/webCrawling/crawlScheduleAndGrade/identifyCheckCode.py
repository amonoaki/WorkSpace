#!/usr/bin/python3
#! -*- "coding: utf-8" -*-

from PIL import Image
import requests
import os
import pytesseract

url = 'http://jwgl.bistu.edu.cn/(0hn1iorbybwvx1v4nrmpit45)/CheckCode.aspx'

def printImage(pixdata, size):
    x, y = size
    for i in range(x):
        for j in range(y):
            print("%3d" % pixdata[i,j], end=' ')
        print()

def binarization(pixdata, size):
    x, y = size
    for i in range(x):  # binarization
        for j in range(y):
            if pixdata[i,j] > 127:
                pixdata[i,j] = 255
            else:
                pixdata[i,j] = 0

def noiseReduction(pixdata, size, cycle):  # 8邻域，0像素值(黑)个数小于3视为噪点
    x, y = size
    for cnt in range(cycle):
        for j in range(1, y-1):
            for i in range(1, x-1):

                '''1'''
                # near = 0
                # if (pixdata[i-1,j-1] == 255): near += 1
                # if (pixdata[i,j-1] == 255): near += 1
                # if (pixdata[i+1,j-1] == 255): near += 1
                # if (pixdata[i-1,j] == 255): near += 1
                # if (pixdata[i+1,j] == 255): near += 1
                # if (pixdata[i-1,j+1] == 255): near += 1
                # if (pixdata[i,j+1] == 255): near += 1
                # if (pixdata[i+1,j+1] == 255): near += 1
                # if near >= 6: pixdata[i,j] = 255

                '''2'''
                # near = pixdata[i-1,j-1] + pixdata[i,j-1] + pixdata[i+1,j-1] + pixdata[i-1,j] + \
                # pixdata[i+1,j] + pixdata[i-1,j+1] + pixdata[i,j+1] + pixdata[i+1,j+1]
                # if near >= 6*255: pixdata[i,j] = 255

                '''3'''
                # pixdata[i,j] = 255 if (sum([pixdata[i+ox,j+oy] for ox in range(-1,2) for oy in range(-1,2)]) - pixdata[i,j]) >= 255*6  else  0  # (没搞懂为啥这句不对)正确姿势看下面一句
                pixdata[i,j] = 255 if (sum([pixdata[i+ox,j+oy] for ox in range(-1,2) for oy in range(-1,2)]) - pixdata[i,j]) >= 255*6  else pixdata[i,j]  # 不增加0的数量


image = requests.get(url)  # get image
with open('./checkcode.png', 'wb') as img_handle:  # download image
    img_handle.write(image.content)
with Image.open('./checkcode.png') as img:  # open image with Image model
    img = img.convert('L')  # convert image to grayscale
    pixdata = img.load()
    binarization(pixdata, img.size)
    # img.show()
    # printImage(pixdata, img.size)
    noiseReduction(pixdata, img.size, 1)
    # printImage(pixdata, img.size)
    print(pytesseract.image_to_string(img))  # identify the image and print the result
    img.show()  # show image on screen
os.system('rm ./checkcode.png')  # delete the image file
