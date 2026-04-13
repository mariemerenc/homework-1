import cv2
import numpy as np
import matplotlib.pyplot as plt
import sys
from math import sqrt

def distancia(pt1, pt2):
    return sqrt((pt1[0] - pt2[0])**2 + (pt1[1] - pt2[1])**2)

def gaussianFilter(shape):
    d0 = 5
    base = np.zeros(shape[:2])
    rows, cols = shape[:2]
    center_row, center_col = rows // 2, cols // 2
    
    for i in range(rows):
        for j in range(cols):
            base[i, j] = np.exp(-distancia((i, j), (center_row, center_col))**2 / d0**2)
            
    return 1-base


def main():
    img = cv2.imread(sys.argv[1], cv2.IMREAD_GRAYSCALE)
    k1 = float(sys.argv[2])
    k2 = float(sys.argv[3])

    fft = np.fft.fft2(img)
    shift_fft = np.fft.fftshift(fft)

    filter = k1 + k2*gaussianFilter(img.shape)

    gx = shift_fft * filter

    gx_shift = np.fft.ifftshift(gx)

    gx_final = np.fft.ifft2(gx_shift)

    gx_final = np.abs(gx_final)

    plt.subplot(1,2,1)
    plt.imshow(img, cmap='gray')
    plt.title("Imagem Original")
    plt.axis('Off')

    plt.subplot(1,2,2)
    plt.imshow(gx_final, cmap='gray')
    plt.title(f'Imagem Filtrada (k1={k1}, k2={k2})')
    plt.axis('Off')

    plt.show()
    plt.savefig('saida_q5.png')
    

if __name__ == "__main__":
    main()