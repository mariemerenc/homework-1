import cv2
import numpy as np
import matplotlib.pyplot as plt
import sys

def histograma(img, bins=256):
    hist = np.zeros(bins)

    for px in img.flatten():
        hist[px] += 1
    
    return hist

def cumsum(hist):
    cdf = np.zeros_like(hist)
    cdf[0] = hist[0]

    for i in range(1, len(hist)):
        cdf[i] = cdf[i-1] + hist[i]
    
    return cdf

def equalizacao(img):
    hist = histograma(img)
    cdf = cumsum(hist)

    total_pxs = img.size
    cdf_min = np.min(cdf[cdf>0])

    cdf_norm = (cdf-cdf_min)/(total_pxs-cdf_min) #normalização para [0,1]
    cdf_norm = (cdf_norm*255).astype(np.uint8) #normalização para [0,255]

    img_eq = np.zeros_like(img)

    for x in range(img.shape[0]):
        for y in range(img.shape[1]):
            img_eq[x,y] = cdf_norm[img[x,y]]

    return img_eq, hist, cdf



def main():
    img = cv2.imread(sys.argv[1],cv2.IMREAD_GRAYSCALE)
    img_eq, hist, cdf = equalizacao(img)

    # Histograma original
    plt.subplot(2,3,1)
    plt.bar(range(256), hist)
    plt.title('Histograma Original')

    # Imagem original
    plt.subplot(2,3,2)
    plt.imshow(img, cmap='gray')
    plt.title('Imagem Original')
    plt.axis('Off')

    # Cumsum original
    plt.subplot(2,3,3)
    plt.plot(cdf)
    plt.title('Cumsum Original')

    # Histograma após equalização
    hist_eq = histograma(img_eq)
    plt.subplot(2,3,4)
    plt.bar(range(256), hist_eq)
    plt.title('Histograma após Equalização')

    # Imagem após equalização
    plt.subplot(2,3,5)
    plt.imshow(img_eq, cmap='gray')
    plt.title('Imagem após Equalização')
    plt.axis('off')

    # Cumsum após equalização
    cumsum_eq = cumsum(hist_eq)
    plt.subplot(2,3,6)
    plt.plot(cumsum_eq)
    plt.title('Cumsum após Equalização')


    plt.show()

if __name__ == "__main__":
    main()