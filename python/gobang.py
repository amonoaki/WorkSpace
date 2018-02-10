# -*- coding: utf-8 -*-
"""
Created on Thu Feb  1 14:23:53 2018

@author: 23755
"""
"""

边界棋子显示不全

"""
import tkinter as tk

PIECE_SIZE = 10

click_x = 0
click_y = 0

pieces_x = [i for i in range(22, 513, 35)]
pieces_y = [i for i in range(28, 519, 35)]

coor_black = []
coor_white = []

person_flag = 1
piece_color = "black"

def showChange(color):
    global piece_color
    piece_color = color
    side_canvas.delete("show_piece")
    side_canvas.create_oval(110 - PIECE_SIZE, 25 - PIECE_SIZE,
                        110 + PIECE_SIZE, 25 + PIECE_SIZE,
                        fill = piece_color, tags = ("show_piece"))

def pushMessage():
    if person_flag == -1:
        var1.set("白棋赢")
    elif person_flag == 1:
        var1.set("黑棋赢")

def piecesCount(coor, pieces_count, t1, t2):
    for i in range(1, 5):
        (x, y) = (click_x + t1 * 35 * i, click_y + t2 * 35 * i)
        if (x, y) in coor:
            pieces_count += 1
        else:
            break
    return pieces_count

def preJudge(piece_color):
    if piece_color == "black":
        realJudge0(coor_black)
    elif piece_color == "white":
        realJudge0(coor_white)
        

def realJudge0(coor):
    global person_flag

    if realJudge1(coor) == 1 or realJudge2(coor) == 1:
        var.set("游戏结束")
        pushMessage()
        person_flag = 0

def realJudge1(coor):
    pieces_count = 0
    pieces_count = piecesCount(coor, pieces_count, 1, 0) #右边
    pieces_count = piecesCount(coor, pieces_count, -1, 0)#左边
    if pieces_count >= 4:
        return 1
    else:
        pieces_count = 0
        pieces_count = piecesCount(coor, pieces_count, 0, -1)#上边
        pieces_count = piecesCount(coor, pieces_count, 0, 1) #下边
        if pieces_count >= 4:
            return 1
        else:
            return 0

def realJudge2(coor):
    pieces_count = 0
    pieces_count = piecesCount(coor, pieces_count, 1, 1)  #右下角
    pieces_count = piecesCount(coor, pieces_count, -1, -1)#左上角
    if pieces_count >= 4:
        return 1
    else:
        pieces_count = 0
        pieces_count = piecesCount(coor, pieces_count, 1, -1) #右上角
        pieces_count = piecesCount(coor, pieces_count, -1, 1) #左下角
        if pieces_count >= 4:
            return 1
        else:
            return 0

#放置棋子
def putPiece(piece_color):
    global coor_black, coor_white
    canvas.create_oval(click_x - PIECE_SIZE, click_y - PIECE_SIZE,
                       click_x + PIECE_SIZE, click_y + PIECE_SIZE, 
                       fill = piece_color, tags = ("piece"))
    if piece_color == "white":
        coor_white.append( (click_x, click_y) )
    elif piece_color == "black":
        coor_black.append( (click_x, click_y) )
    preJudge(piece_color)

def coorJudge():
    coor = coor_black + coor_white
    global person_flag, show_piece
    #print("x = %s, y = %s" % (click_x, click_y))
    if ( (click_x, click_y) not in coor )and( click_x in pieces_x )and( click_y in pieces_y ):
        #print("True")
        if person_flag != 0:
            if person_flag == 1:
                putPiece("black")
                showChange("white")
                var.set("执白棋")
            elif person_flag == -1:
                putPiece("white")
                showChange("black")
                var.set("执黑棋")
            person_flag *= -1
        else:
            var.set("游戏结束")
    #else:
        #print("False")

def coorBack(event):  #return coordinates of cursor 返回光标坐标
    global click_x, click_y
    click_x = event.x
    click_y = event.y
    coorJudge()
    
def gameReset():
    global person_flag, coor_black, coor_white, piece_color
    person_flag = 1
    var.set("执黑棋")
    var1.set("")
    piece_color = "black"
    canvas.delete("piece")
    coor_black = []
    coor_white = []
    
"""窗口主体"""
root = tk.Tk()

root.title("Gobang")
root.geometry("750x550")

"""棋子提示"""
side_canvas = tk.Canvas(root, width = 220, height = 50)
side_canvas.grid(row = 0, column = 1)
side_canvas.create_oval(110 - PIECE_SIZE, 25 - PIECE_SIZE,
                        110 + PIECE_SIZE, 25 + PIECE_SIZE,
                        fill = piece_color, tags = ("show_piece") )
"""棋子提示标签"""
var = tk.StringVar()
var.set("执黑棋")
person_label = tk.Label(root, textvariable = var, width = 12, anchor = tk.CENTER, 
                        font = ("Arial", 20) )
person_label.grid(row = 1, column = 1)

"""输赢提示标签"""
var1 = tk.StringVar()
var1.set("")
result_label = tk.Label(root, textvariable = var1, width = 12, height = 4, 
                        anchor = tk.CENTER, fg = "red", font = ("Arial", 25) )
result_label.grid(row = 2, column = 1, rowspan = 3)

"""重置按钮"""
reset_button = tk.Button(root, text = "重新开始", font = 20, 
                          width = 8, command = gameReset)
reset_button.grid(row = 5, column = 1)

"""棋盘绘制"""
#背景
canvas = tk.Canvas(root, bg = "saddlebrown", width = 530, height = 530)
canvas.bind("<Button-1>", coorBack)
canvas.grid(row = 0, column = 0, rowspan = 6)
#线条
for i in range(15):
    canvas.create_line(22, (35 * i + 28), 512, (35 * i + 28))
    canvas.create_line((35 * i + 22), 28, (35 * i + 22), 518)
#点
point_x = [3, 3, 11, 11, 7]
point_y = [3, 11, 3, 11, 7]
for i in range(5):
    canvas.create_oval(35 * point_x[i] + 18, 35 * point_y[i] + 23, 
                       35 * point_x[i] + 26, 35 * point_y[i] + 31, fill = "black")

#数字坐标
for i in range(15):
    label = tk.Label(canvas, text = str(i + 1), fg = "black", bg = "saddlebrown",
                     width = 2, anchor = tk.E)
    label.place(x = 2, y = 35 * i + 18)
#字母坐标
count = 0
for i in range(65, 81):
    label = tk.Label(canvas, text = chr(i), fg = "black", bg = "saddlebrown")
    label.place(x = 35 * count + 15, y = 2)
    count += 1

"""窗口循环"""
root.mainloop()