import numpy as np
import cv2 as cv
from matplotlib import pyplot as plt
imgL = cv.imread('cube0_8x6_40cm.png',0)
imgR = cv.imread('cube1_8x6_40cm.png',0)


window_size = 3
min_disp = 16
num_disp = 112-min_disp
stereo = cv.StereoSGBM_create(minDisparity = min_disp,
        numDisparities = num_disp,
        blockSize = 15,
        P1 = 8*3*window_size**2,
        P2 = 32*3*window_size**2,
        disp12MaxDiff = 1,
        uniquenessRatio = 15,
        speckleWindowSize = 100,
        speckleRange = 16)

disparity = stereo.compute(imgL,imgR).astype(np.float32) / 16.0
plt.imshow(disparity,'gray')
plt.show()
