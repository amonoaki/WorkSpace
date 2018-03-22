# -*- coding: utf-8 -*-
"""
Created on Thu Mar 22 16:33:46 2018

@author: 23755
"""

import cv2

"""
img = cv2.imread("test.jpg")
cv2.namedWindow("image")
cv2.imshow("image", img)
cv2.waitKey(0)
cv2.destroyAllWindows()
"""

def callBack(x):
  pass

capture = cv2.VideoCapture(0)

while(True):
  ret, frame = capture.read()
  cv2.namedWindow("frame")
  cv2.createTrackbar("Tracbar", "frame", 0, 10, callBack)
  cv2.imshow("frame", frame)
  if cv2.waitKey(1) == ord('q'):
    break
capture.release()
cv2.destroyAllWindows()
  
