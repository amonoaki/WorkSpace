#mylock.py
#手写数字识别密码锁-神经网络-机器学习

import os
import numpy as np
import cv2
from PIL import Image


PIXEL_COUNT = 28 * 28
NUMBER_COUNT = 10
TRY_TIMES = 5
PASSWARD = [2, 3, 5, 7]
drawing=False


def drawCircle(event,x,y,flags,param):
    global drawing
    if event==cv2.EVENT_LBUTTONDOWN:
        drawing=True
    if event==cv2.EVENT_MOUSEMOVE and flags==cv2.EVENT_FLAG_LBUTTON:
        if drawing == True:
            cv2.circle(img,(x,y),10,(0, 0, 0),-1)  #画笔
        elif event==cv2.EVENT_LBUTTONUP:
            drawing=False


def arrayInitialize(dir_path):
    '''数据准备：获取图片名、获取训练数组的维度'''
    #获取图片名
    image_name = os.listdir('E:\\BISTU\\TeamWater\\water项目-手写密码锁\\第三周\\%s' % dir_path)
    #获取训练数组的维度
    image_count = len(image_name)
    #更改执行位置
    os.chdir('E:\\BISTU\\TeamWater\\water项目-手写密码锁\\第三周\\%s' % dir_path)
    #按维度初始化训练数组
    image = np.zeros([image_count, PIXEL_COUNT])
    label = np.zeros([image_count, 1])

    return (image_name, image_count, image, label)


def getArray(image_name, image_count, image, label):
    '''获得训练数组和标签数组'''
    for i in range(image_count):
        img = Image.open(image_name[i])
        img = img.convert('1')  #黑色为0，白色为1
        img = img.resize((28,28))
        image[i] = np.array(img).reshape((1, PIXEL_COUNT))  #trainimage.shape = (image_count, PIXEL_COUNT)
        label[i] = int(image_name[i][-5])  #trainlabel.shape = (image_count, 1)
    image = np.where(image == 1, 0, 1)

    return (image, label)


def learning():
    ##监督学习，训练参数##
    (trainimage_name, image_count, trainimage, trainlabel) = arrayInitialize("0-5999")
    (trainimage, trainlabel) = getArray(trainimage_name, image_count, trainimage, trainlabel)
    #初始化权重数组和偏置量(随机数)
    W = np.random.random((PIXEL_COUNT, NUMBER_COUNT))  #W.shape = (PIXEL_COUNT, NUMBER_COUNT)
    b = np.random.random((1, NUMBER_COUNT))  #b.shape = (1, NUMBER_COUNT)
    #计算
    for i in range(400):
        Z = np.dot(trainimage, W) + b  #Z.shape = (image_count, NUMBER_COUNT)
        temp0 = np.exp(Z)  #暂存各项exp()的结果 #temp0.shape = (image_count, NUMBER_COUNT)
        temp1 = np.sum(np.exp(Z), 1).reshape(image_count, 1)  #暂存各行的和 #temp1.shape = (image_count, 1)
        A = temp0 / temp1  #a.shape = (image_count, NUMBER_COUNT)

        #处理损失函数的一个参数
        Yij = np.zeros([image_count, NUMBER_COUNT])  #Yij.shape = (image_count, NUMBER_COUNT)
        for i in range(image_count):
            temp2 = int(trainlabel[i][0])  #暂存每行对应的正确数字
            Yij[i][temp2] = 1

        sum_dW = np.zeros([PIXEL_COUNT, NUMBER_COUNT])
        sum_db = np.zeros([1, NUMBER_COUNT])
        for i in range(image_count):
            temp1 = trainimage[i].reshape(PIXEL_COUNT, 1)
            temp2 = (A[i]-Yij[i]).reshape(1, NUMBER_COUNT)
            sum_dW += np.dot(temp1, temp2)
            sum_db += temp2
        dW = sum_dW / image_count  #dW.shape = (PIXEL_COUNT, NUMBER_COUNT)
        db = sum_db / image_count  #db.shape = (1, 1)  0-按列求和；1-按行求和

        #修改权重和偏置量
        r = 0.6
        W -= r * dW
        b -= r * db

    return (W, b)


if __name__ == '__main__':

    #获得学习后的参数并加以存储
    #(W, b) = learning()
    #np.save("E:\\BISTU\\TeamWater\\water项目-手写密码锁\\第三周\\W", W)
    #np.save("E:\\BISTU\\TeamWater\\water项目-手写密码锁\\第三周\\b", b)
    #读取学习过的参数
    W = np.load("E:\\BISTU\\TeamWater\\water项目-手写密码锁\\第三周\\W.npy")
    b = np.load("E:\\BISTU\\TeamWater\\water项目-手写密码锁\\第三周\\b.npy")

    #准备窗口与提示
    img=np.zeros((280,280),np.uint8) + 255
    cv2.namedWindow('Image')
    cv2.setMouseCallback('Image',drawCircle)
    print("c->clear  s->save  q->quit")

    #开始写数字
    for i in range(TRY_TIMES):
        inputnumber_count = 0
        passward = []
        print("Draw your passward...")
        while(True):
            cv2.imshow('Image',img)
            key=cv2.waitKey(1)&0xFF
            if key==ord('s'):
                img = cv2.resize(img, (28, 28))

                #开始识别
                img = np.array(img).reshape((1, PIXEL_COUNT))
                img = np.where(img >= 127, 0, 1)
                Z = np.dot(img, W) + b
                temp0 = np.exp(Z)
                temp1 = np.sum(np.exp(Z), 1)
                A = temp0 / temp1
                #每行概率最大的对应位置即为结果
                predictlabel = A.argmax(1)
                passward.append(predictlabel[0])

                #完毕，初始化窗口，准备下一次循环
                inputnumber_count += 1
                print("%s number saved..." % (inputnumber_count))
                img=np.zeros((280,280),np.uint8) + 255
            elif key==ord('q'):
                break
            elif key==ord('c'):
                img = np.zeros((280, 280), np.uint8) + 255
            else:
                pass

        #print(passward)
        #print(PASSWARD)
        if (len(passward) == len(PASSWARD)):
            count = 0
            for i in range(len(PASSWARD)):
                if (PASSWARD[i] == passward[i]):
                    count += 1
                else:
                    break
            if (count == len(PASSWARD)):
                print("Correct! Enjoy your game!")
                os.system("python E:\\WorkSpace\\python\\gobang\\gobang.py")
                break
            else:
                print("Passwards do not match, try again.(%s chance(s) left)" % (TRY_TIMES-1 - i))
        else:
            print("Bad passwards, try again.(%s chance(s) left)" % (TRY_TIMES-1 - i))

    print("Bye!")
#end



'''
if __name__ == '__main__':
    ##批量数据测试##
    (testimage_name, image_count, testimage, testlabel) = arrayInitialize("6000-6999")
    (testimage, testlabel) = getArray(testimage_name, image_count, testimage, testlabel)
    (W, b) = learning()

    #计算
    Z = np.dot(testimage, W) + b  #Z.shape = (image_count, 1)
    temp0 = np.exp(Z)  #暂存各项exp()的结果 #temp0.shape = (image_count, NUMBER_COUNT)
    temp1 = np.sum(np.exp(Z), 1).reshape(image_count, 1)  #暂存各行的和 #temp1.shape = (image_count, 1)
    A = temp0 / temp1  #a.shape = (image_count, NUMBER_COUNT)

    #每行概率最大的对应位置即为结果
    predictlabel = A.argmax(1)  #predictlabel存储每行最大值的索引(即预测结果)
    print("正确值")
    print(testlabel.T)
    print("预测值")
    print(predictlabel)

    #计算识别率
    right_count = 0
    for i in range(image_count):
        if testlabel[i][0] == predictlabel[i]:
            right_count += 1
    print("识别率:%s" % (right_count/image_count))
'''