#pre_rose.py

from PIL import Image

img = Image.open('rose.jpg')

print(img.format, img.size, img.mode)
img.show()
img_p = img.convert('P')
img_p.show()
img_p.save("rose_p.png")

