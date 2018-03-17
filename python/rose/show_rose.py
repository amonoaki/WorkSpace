from PIL import Image
import numpy as np
import matplotlib.pyplot as plt
img = Image.open('rose_p.png')
img_array = np.array(img)

plt.figure("picture")
plt.imshow(img_array)
plt.axis("on")

print(img.format, img.size, img.mode)

plt.show()

"""
1、增加input("Enter any key to quit...")
2、使用write()增加文字的绘制
3、尝试裁去斜右下方的文字说明(使用show()展示坐标，找出端点坐标，将该段坐标排除在数列之外)
"""
