#classify0_1.py

print("Please wait...")

import os
import numpy as np
import cv2
from PIL import Image

drawing=False
PIXEL_COUNT = 28 * 28

def drawCircle(event,x,y,flags,param):
    global drawing
    if event==cv2.EVENT_LBUTTONDOWN:
        drawing=True
    if event==cv2.EVENT_MOUSEMOVE and flags==cv2.EVENT_FLAG_LBUTTON:
        if drawing == True:
            cv2.circle(img,(x,y),10,(225,225,225),-1)
        elif event==cv2.EVENT_LBUTTONUP:
            drawing=False

def dataPreparation(dir_path):
    '''数据准备：获取图片名、获取训练数组的维度'''
    #获取图片名
    trainimage_name = os.listdir('E:\\BISTU\\TeamWater\\water项目-手写密码锁\\第二周\\0_1\\%s' % dir_path)
    #获取训练数组的维度
    image_count = len(trainimage_name)
    #更改执行位置
    os.chdir('E:\\BISTU\\TeamWater\\water项目-手写密码锁\\第二周\\0_1\\%s' % dir_path)
    #按维度初始化训练数组
    trainimage = np.zeros([image_count, PIXEL_COUNT])
    trainlabel = np.zeros([image_count, 1])

    return (trainimage_name, image_count, trainimage, trainlabel)

def getArray(trainimage_name, image_count, trainimage, trainlabel):
    '''获得训练数组和标签数组'''
    for i in range(image_count):
        img = Image.open(trainimage_name[i])
        trainimage[i] = np.array(img).reshape((1, PIXEL_COUNT))  #trainimage.shape = (image_count, PIXEL_COUNT)
        trainlabel[i] = int(trainimage_name[i][-5])  #trainlabel.shape = (image_count, 1)
    trainimage = np.where(trainimage >= 127, 1, 0)

    return (trainimage, trainlabel)

def learning():
    ##监督学习，训练参数##
    (trainimage_name, image_count, trainimage, trainlabel) = dataPreparation("0_1_train")
    (trainimage, trainlabel) = getArray(trainimage_name, image_count, trainimage, trainlabel)
    #设置权重数组和偏置量(随机数)
    W = np.random.random((PIXEL_COUNT, 1))  #W.shape = (PIXEL_COUNT, 1)
    b = np.random.random((1, 1))  #b.shape = (1, 1)
    #计算
    for i in range(image_count):
        Z = np.dot(trainimage, W) + b  #Z.shape = (image_count, 1)
        A = 1 / (1 + np.exp(-Z))  #a.shape = (image_count, 1)

        dW = np.dot(trainimage.T, (A-trainlabel))  #dW.shape = (PIXEL_COUNT, 1)
        db = np.sum((A-trainlabel), 0)  #db.shape = (1, 1)  0-按列求和；1-按行求和
        #修改权重和偏置量
        r = 0.01
        W -= r * dW
        b -= r * db

<<<<<<< HEAD
    ##数据测试##
    (trainimage_name, image_count, pixel_count, trainimage, trainlabel) = dataPreparation("0_1_test1")
    (trainimage, trainlabel) = getArray(trainimage_name, image_count, pixel_count, trainimage, trainlabel)
    #计算
    Z = np.dot(trainimage, W) + b  #Z.shape = (image_count, 1)
    A = 1 / (1 + np.exp(-Z))  #a.shape = (image_count, 1)
    #两极化即为结果
    A = np.where(A >= 0.5, 1, 0)  #另一种方法是  A = [1 for i in A if i >= 0.5 else 0]
    print("正确值")
    print(trainlabel.T)
    print("预测值")
    print(A.T)
=======
    return (W, b)
>>>>>>> mylock0

if __name__ == '__main__':

    #获得学习后的参数
    (W, b) = learning()
    #准备窗口与提示
    img=np.zeros((280,280),np.uint8)
    cv2.namedWindow('Image')
    cv2.setMouseCallback('Image',drawCircle)
    print("c->clear  s->save  q->quit")
    #开始写数字
    image_count = 0
    right_count = 0
    print("Draw your number...")
    while(True):   
        cv2.imshow('Image',img)
        key=cv2.waitKey(1)&0xFF
        if key==ord('s'):
            print("Recognizing...",end='')
            img = cv2.resize(img, (28, 28))
            #开始识别
            testimage = np.array(img).reshape((1, PIXEL_COUNT))
            testimage = np.where(testimage >= 127, 1, 0)
            Z = np.dot(testimage, W) + b  #Z.shape = (image_count, 1)
            A = 1 / (1 + np.exp(-Z))  #a.shape = (image_count, 1)
            #两极化即为结果
            A = np.where(A >= 0.5, 1, 0)  #另一种方法是  A = [1 for i in A if i >= 0.5 else 0]
            #输出识别结果
            print("It's ", end='')
            print(A.T)
            image_count += 1
            if (int(input("right?(1-Yes/0-No): "))):
                right_count += 1
            #完毕，初始化窗口，准备下一次循环
            img=np.zeros((280,280),np.uint8)
            print("Draw your number...")
        elif key==ord('q'):
            break
        elif key==ord('c'):
            img = np.zeros((280, 280), np.uint8)
        else:
            pass

    print("识别率:%s" % (right_count/image_count))
