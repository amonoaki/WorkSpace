# -*- coding: utf-8 -*-
'''
Created on Wed Jan 31 19:24:05 2018

@author: 23755
'''
import sys
import math
from PyQt5.QtWidgets import QWidget, QApplication, QGridLayout, QLabel, QPushButton
from PyQt5.QtGui import QIcon

class Calculator(QWidget):
    
    flag = False
    num = []
    
    def __init__(self):
        super().__init__()
        self.main()
        
    def main(self):
        self.setWindowTitle("Calculator")
        self.setGeometry(300, 300, 350, 250)
        self.setWindowIcon(QIcon("calculator.ico"))
        
        root = QGridLayout(self)
        self.label = QLabel()
        self.label.setFixedHeight(30)
        self.label.setText("Hey, there...")
        self.label.resize(self.sizeHint())
        root.addWidget(self.label, 0, 0, 1, 4)
        
        for i in range(1, 10):
            button = QPushButton(str(i))
            button.resize(self.sizeHint())
            root.addWidget(button, (i - 1) // 3 + 1, (i - 1) % 3)
            button.clicked.connect(self.process)
        button_list = ['+', '-', '*']
        for i in range(1, 4):
            button = QPushButton(button_list[i - 1])
            root.addWidget(button, i, 3)
            button.clicked.connect(self.process)
        button_list = ['(', '0', ')', '/', 'C', "n!", '.', '=']
        count = 0
        for i in range(4, 6):
            for j in range(0, 4):
                button = QPushButton(button_list[count])
                root.addWidget(button, i, j)
                button.clicked.connect(self.process)
                count += 1
        self.show()
        
    def process(self):
        
        clear_flag = False
        
        self.charactor = ['(', ')', '.', '+', '-', '*', '/']
        sender = self.sender()
        
        
        if (sender.text() in self.charactor ) and (Calculator.flag == True):
            Calculator.num.append(sender.text())
            Calculator.flag = False
        elif sender.text() == "C":
            clear_flag = True
        elif sender.text() == "n!":
            index = self.numFind(Calculator.num)
            if index != -1:
                the_num = ''.join( Calculator.num[index+1:] ) 
                Calculator.num[index+1] = ( str( math.factorial(int(the_num) ) ) )
                if index+2 < 0:
                    for i in Calculator.num[index+2:]:
                        Calculator.num.pop()
                Calculator.flag = True
        elif sender.text() == "=":
            num_result = str( eval(''.join(Calculator.num)) )
            Calculator.num.append(sender.text())
            Calculator.num.append(num_result)
            clear_flag = True
        elif int( sender.text() ) in range(10):
            Calculator.num.append(sender.text())
            Calculator.flag = True
        self.label.setText(''.join(Calculator.num))
        if clear_flag:
            Calculator.num = []
            
    def numFind(self, num):
        i = -1
        while i >= -len(num):
            if num[i] in self.charactor:
                return i
            i -= 1
        
if __name__ == "__main__":
    app = 0
    app = QApplication(sys.argv)
    cal = Calculator()
    sys.exit(app.exec_())
