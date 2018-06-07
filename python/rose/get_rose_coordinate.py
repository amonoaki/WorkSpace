from PIL import Image
import numpy as np
import matplotlib.pyplot as plt
img = Image.open('rose_p.png')
img_array = np.array(img)

img_rose = []
img_leaf = []

count1 = 0
count2 = 0

for i in range(600):
    for j in range(607):
        if i < 297 or j < 360:
            if img_array[j, i] == 182:
                if j > 245:
                    img_rose.append([i - 300,(-1) * j + 300])
                    count1 += 1
                else:
                    img_leaf.append([i - 300,(-1) * j + 300])
                    count2 += 1

print(img_rose, end = '')
print(count1)
print(img_leaf, end = '')
print(count2)
