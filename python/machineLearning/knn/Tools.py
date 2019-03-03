#!/usr/bin/python3
# -*- "coding: utf-8" -*-

import pickle
import gzip
import numpy
from PIL import Image
import os

class Tools(object):
    def __init__(self):
        pass

    @staticmethod
    def loadMnist(path="mnist.pkl.gz"):
        print('load mnist from', path)
        f = gzip.open(path, 'rb')  #加载数据
        train, valid, test = pickle.load(f, encoding='bytes')
        f.close()
        X, Y = train
        return X, Y

    @staticmethod
    def loadLocalImageSet(opt, path='/media/ubuntu/DT/BISTU/请转至onedrive/TeamWater/water项目-手写密码锁/第二周/0_1/'):
        '''
        opt = "train": 读取训练集
        opt = "test": 读取测试集
        '''
        cur_dir = os.getcwd()  #保留原始路径，以便返回
        if opt == 'train':
            os.chdir(path+'0_1_train')
        else:
            os.chdir(path+'0_1_test')

        imgs = os.listdir('.')
        X = numpy.zeros((len(imgs), 28*28))
        Y = []  #标签
        row = 0
        for img in imgs:
            Y.append(int(img[-5]))
            img_arr = numpy.array(Image.open(img, 'r'))
            X[row] = img_arr.reshape(1, 28*28)[0]
            row += 1
        X = numpy.where(X<127, 0, 1)
        os.chdir(cur_dir)

        return X, Y


