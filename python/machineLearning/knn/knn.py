#!/usr/bin/python3
# -*- "coding: utf-8" -*-

from Tools import Tools
import numpy as np
import os

'''
knn实现
'''

class Knn(object):
    def __init__(self, K):
        '''K应该为奇数'''
        self.K = K

    def predictBatch(self, train, train_label, test, test_label):
        '''
        train, test: 计算欧氏距离
        train_label: 得出二分类结果
        test_label: 计算准确率
        '''
        predict = []
        for row in test:
            rows = np.repeat(np.expand_dims(row, axis=0), train.shape[0], axis=0)
            indices = np.argsort(np.sum(np.power(train - rows, 2), axis=1))  #有小到大的索引
            s = 0
            for i in range(self.K):  #得出预测值
                s += train_label[indices[i]]
            predict.append(1 if s > self.K//2 else 0)
        rate = 1 - sum(abs(test_label-predict))/len(test)
        return rate

    def predict(self, train, train_label, test):
        '''
        train, test: 计算欧氏距离
        train_label: 得出二分类结果并返回
        '''
        pass
    
def loadData(path='data.npz'):
    '''加载自制数据集'''
    if not os.path.isfile(path):
        train, train_label = Tools.loadLocalImageSet('train')
        test, test_label = Tools.loadLocalImageSet('test')
        np.savez(path, train=train, train_label=np.array(train_label), test=test, test_label=np.array(test_label))
        return train, train_label, test, test_label
    else:
        data = np.load(path)
        return data['train'], data['train_label'], data['test'], data['test_label']

def findK():
    '''寻找最佳的K值'''
    train, train_label, test, test_label = loadData()
    for i in range(1, 200, 2):
        knn = Knn(i)
        rate = knn.predictBatch(train, train_label, test, test_label)
        print('k=', i, "rate=", rate)

if __name__ == "__main__":
    train, train_label, test, test_label = loadData()
    knn = Knn(11)  #通过findK()找到
    rate = knn.predictBatch(train, train_label, test, test_label)
    print("rate=", rate)
