print("Please wait...")
import os
import numpy as np
import cv2
drawing=False
def drawCircle(event,x,y,flags,param):
    global drawing
    if event==cv2.EVENT_LBUTTONDOWN:
        drawing=True
    if event==cv2.EVENT_MOUSEMOVE and flags==cv2.EVENT_FLAG_LBUTTON:
        if drawing == True:
            cv2.circle(img,(x,y),10,(225,225,225),-1)
        elif event==cv2.EVENT_LBUTTONUP:
            drawing=False

def function(n):
    if (n % 2 == 0):
        n = n - (n % 10)
        n += 1
    else:
        n = n - (n % 10) + 1
        n += 9
    return n

os.chdir("0_1_test1")
img=np.zeros((280,280),np.uint8)
cv2.namedWindow('Image')
cv2.setMouseCallback('Image',drawCircle)
n=int(input("Input n:"))###############
print("c->clear  s->save  q->quit")
while(True):
    cv2.imshow('Image',img)
    key=cv2.waitKey(1)&0xFF
    if key==ord('s'):
        print("Saving...",end='')
        img = cv2.resize(img, (28, 28))
        cv2.imwrite(r"img"+str(n)+".jpg",img)
        print("img"+str(n)+".jpg")
        img=np.zeros((280,280),np.uint8)
        n = function(n)
    elif key==ord('q'):
        break
    elif key==ord('c'):
        img = np.zeros((280, 280), np.uint8)
    else:
        pass
