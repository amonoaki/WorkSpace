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
            indices = np.argsort(np.sum(np.power(train - rows, 2), axis=1))  #距离从小到大排序对应的索引
            count_dict={}
            for i in range(self.K):  #对最近的标签计数
                label = train_label[indices[i]]
                value = count_dict.setdefault(label, 0)
                count_dict[label] = value+1
            # print('count_dict:', count_dict)
            predict.append(sorted(count_dict.items(), key = lambda kv: kv[1])[-1][0])  #记录预测值，注意：从小到大排列，所以这里应该取最后一个键
        
        cnt = 0
        for i in range(len(test)):
            if test_label[i] == predict[i]:
                cnt += 1
        rate = cnt/len(test_label)
        # print(test_label[:20])
        # print(predict[:20])
        # print('rate:', rate)
        return rate

    def predict(self, train, train_label, test):
        '''
        train, test: 计算欧氏距离
        train_label: 得出二分类结果并返回
        '''
        pass

def findK():
    '''寻找最佳的K值'''
    X, Y = Tools.loadMnist('../data/mnist.pkl.gz')
    # train, train_label, test, test_label = X[:1000], Y[:1000], X[1000:1500], Y[1000:1500]
    train, train_label, test, test_label = X[:500], Y[:500], X[500:750], Y[500:750]
    for i in range(1, 50, 2):
        knn = Knn(i)
        rate = knn.predictBatch(train, train_label.tolist(), test, test_label.tolist())
        print('k=', i, "rate=", rate)

def main():
    '''主方法'''
    X, Y = Tools.loadMnist('../data/mnist.pkl.gz')
    train, train_label, test, test_label = X[:1000], Y[:1000], X[1000:1500], Y[1000:1500]
    knn = Knn(10)
    rate = knn.predictBatch(train, train_label.tolist(), test, test_label.tolist())
    print('rate:', rate)

if __name__ == '__main__':
    # findK()
    main()
