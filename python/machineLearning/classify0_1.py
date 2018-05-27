# myLock.py

'''
注意 numpy.where(condition, x, y) 有返回值，为处理后的数组
    array.resize((x, y)) 无返回值，调用则直接改变，即将指针传入
'''

import os
import numpy as np
from PIL import Image

def dataPreparation(dir_path):
    '''数据准备：获取图片名、获取训练数组的维度'''
    #获取图片名
    trainimage_name = os.listdir('E:\\BISTU\\TeamWater\\water项目-手写密码锁\\第二周\\0_1\\%s' % dir_path)
    #获取训练数组的维度
    image_count = len(trainimage_name)
    pixel_count = 28 * 28
    #更改执行位置
    os.chdir('E:\\BISTU\\TeamWater\\water项目-手写密码锁\\第二周\\0_1\\%s' % dir_path)
    #按维度初始化训练数组
    trainimage = np.zeros([image_count, pixel_count])
    trainlabel = np.zeros([image_count, 1])

    return (trainimage_name, image_count, pixel_count, trainimage, trainlabel)


def getArray(trainimage_name, image_count, pixel_count, trainimage, trainlabel):
    '''获得训练数组和标签数组'''
    for i in range(image_count):
        img = Image.open(trainimage_name[i])
        trainimage[i] = np.array(img).reshape((1, pixel_count))  #trainimage.shape = (image_count, pixel_count)
        trainlabel[i] = int(trainimage_name[i][-5])  #trainlabel.shape = (image_count, 1)
    trainimage = np.where(trainimage >= 127, 1, 0)

    return (trainimage, trainlabel)


if __name__ == '__main__':

    ##监督学习，训练参数##
    (trainimage_name, image_count, pixel_count, trainimage, trainlabel) = dataPreparation("0_1_train")
    (trainimage, trainlabel) = getArray(trainimage_name, image_count, pixel_count, trainimage, trainlabel)
    #设置权重数组和偏置量(随机数)
    W = np.random.random((pixel_count, 1))  #W.shape = (pixel_count, 1)
    b = np.random.random((1, 1))  #b.shape = (1, 1)
    #计算
    for i in range(image_count):
        Z = np.dot(trainimage, W) + b  #Z.shape = (image_count, 1)
        A = 1 / (1 + np.exp(-Z))  #a.shape = (image_count, 1)

        dW = np.dot(trainimage.T, (A-trainlabel))  #dW.shape = (pixel_count, 1)
        db = np.sum((A-trainlabel), 0)  #db.shape = (1, 1)  0-按列求和；1-按行求和
        #修改权重和偏置量
        r = 0.01
        W -= r * dW
        b -= r * db

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

    ##统计识别率##
    count = 0
    for i in range(image_count):
        if A[i] == trainlabel[i]:
            count += 1
    print("识别率:%s" % (count/image_count))

