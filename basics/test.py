import cv2
import numpy as np
im = np.array([[0, 0, 1], [0, 0, 2], [0, 0, 1]], dtype='uint8')
print(im)
grad_x = cv2.Sobel(im.T, cv2.CV_16S, 0, 1, ksize=3, scale=1, delta=0, borderType=cv2.BORDER_CONSTANT)
print(grad_x)