#!/usr/bin/python3
# -*- "coding: utf-8" -*

# 绘制小猪佩琪，小课堂备用

from turtle import *

def moveTo(x, y):
    penup()
    goto(x, y)
    pendown()

x, y = -200, 200

# speed(0)
colormode(255)

# 头
pensize(5)
pencolor((236,142,195))
fillcolor((255,176,223))
moveTo(x, y)
begin_fill()
seth(-40)
circle(200,25)
right(110)
circle(60, 70)
circle(90, 130)
circle(80, 20)
circle(110, 20)
circle(90, 30)
circle(265, 40)
seth(-111)
fd(70)
end_fill()
pensize(1)

# 鼻
pensize(5)
# pensize(1)
pencolor((236,142,195))
fillcolor((255,176,223))
moveTo(x, y)
begin_fill()
seth(-40)
circle(30, 30)
circle(30, 30)
circle(50, 60)
circle(30, 60)
circle(30, 60)
circle(50, 60)
circle(30, 60)
end_fill()

#鼻孔
fillcolor((236,142,195))
moveTo(x+15, y+35)
begin_fill()
circle(5, 360)
end_fill()
begin_fill()
moveTo(x+30, y+30)
circle(5, 360)
end_fill()

# 眼
pensize(5)
moveTo(x+110, y+35)
fillcolor((255,255,255))
begin_fill()
seth(10)
circle(-15, 120)
circle(-10, 60)
circle(-15, 120)
circle(-10, 60)
end_fill()

moveTo(x+150, y+20)
begin_fill()
seth(-10)
circle(-15, 120)
circle(-10, 60)
circle(-15, 120)
circle(-10, 60)
end_fill()
pensize(1)

# 眼珠
pencolor((0,0,0))
fillcolor((0,0,0))
moveTo(x+105, y+30)
begin_fill()
seth(80)
circle(-5, 360)
end_fill()

moveTo(x+140, y+15)
begin_fill()
seth(60)
circle(-5, 360)
end_fill()

# 不高兴
# pencolor((215,70,145))
# pensize(5)
# moveTo(x+100, y-100)
# circle(-20, 100)
# pensize(1)

# 微笑
pencolor((215,70,145))
pensize(5)
moveTo(x+90, y-70)
seth(-70)
circle(40, 120)
pensize(1)

# 胎记
pencolor((255,140,209))
fillcolor((255,140,209))
moveTo(x+175, y-65)
begin_fill()
seth(-90)
circle(25, 360)
end_fill()

# 耳朵
pensize(5)
pencolor((236,142,195))
fillcolor((255,176,223))
moveTo(x+150, y+48)
begin_fill()
seth(100)
circle(-80, 25)
circle(-15, 180)
circle(-80, 28)
pencolor((255,176,223))
seth(153)
fd(11)
end_fill()

pencolor((236,142,195))
moveTo(x+182, y+30)
begin_fill()
seth(70)
circle(-80, 25)
circle(-15, 180)
circle(-80, 21)
pencolor((255,176,223))
seth(150)
fd(14)
end_fill()
pensize(1)

# 衣服 
pensize(5)
pencolor((225,54,63))
fillcolor((233,86,94))
moveTo(x+84, y-118)
begin_fill()
seth(-140)
circle(100, 20)
circle(80, 5)
circle(280, 15)
fd(30)
circle(280, 10)
seth(0)

fd(250)

seth(90)
circle(280, 10)
fd(30)
circle(280, 15)
circle(80, 5)
circle(100, 22)

pencolor((236,142,195))
seth(-130)
circle(-80, 20)
circle(-90, 78)
end_fill()
pensize(1)

# 腿
pencolor((255,176,223))
pensize(10)
moveTo(x+110, y-305)
seth(-90)
fd(40)

moveTo(x+210, y-305)
seth(-90)
fd(40)
pensize(1)

# 鞋
pencolor((0,0,0))
fillcolor((0,0,0))
moveTo(x+110, y-340)
begin_fill()
seth(170)
circle(200, 10)
circle(6, 180)
fd(33)
circle(4, 180)
end_fill()

moveTo(x+210, y-340)
begin_fill()
seth(170)
circle(200, 10)
circle(6, 180)
fd(33)
circle(4, 180)
end_fill()

# 手
pencolor((255,176,223))
pensize(10)
moveTo(x+58, y-155)
seth(-170)
circle(300, 15)
moveTo(x-15, y-165)
seth(10)
circle(-12, 150)

moveTo(x+250, y-165)
seth(-10)
circle(-300, 15)
moveTo(x+320, y-170)
seth(170)
circle(12, 150)

# 尾巴
pencolor((255,176,223))
moveTo(x+274, y-250)
seth(-30)
circle(20, 100)
circle(7, 270)
circle(20, 100)

moveTo(500,-500)

done()
