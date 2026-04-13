# para executar esse script, rodar o comando "python q4.py"
import cv2
import numpy as np
import matplotlib.pyplot as plt
import sys

def median_filter(img, tam_janela):
    m, n = tam_janela
    altura, largura, = img.shape
    img_filtrada = np.zeros_like(img, dtype=np.float64)

    pad_alt = m // 2
    pad_larg = n // 2

    img_pad = np.pad(img, ((pad_alt, pad_alt), (pad_larg, pad_larg)), mode='reflect')

    idx_central = (m * n) // 2

    for y in range(altura):
        for x in range(largura):
            vizinhanca = img_pad[y:y+m, x:x+n].flatten()
            vizinhanca_ordenada = np.sort(vizinhanca)
            img_filtrada[y, x] = vizinhanca_ordenada[idx_central]

    return np.clip(img_filtrada, 0, 255).astype(np.uint8)

def gerando_imgs(tam):
    # Primeira imagem
    # glass_s_and_p.pgm
    plt.subplot(2, 3, 1)
    img1 = cv2.imread('../images/glass_s_and_p.pgm', cv2.IMREAD_GRAYSCALE)
    plt.imshow(img1, cmap='gray')
    plt.axis('Off')

    # Imagem filtrada
    img_filtrada1 = median_filter(img1, (tam,tam))
    plt.subplot(2, 3, 4)
    plt.imshow(img_filtrada1, cmap='gray')
    plt.axis('Off')

    # bear_s_and_p.pgm
    img2 = cv2.imread('../images/bear_s_and_p.pgm',cv2.IMREAD_GRAYSCALE)
    plt.subplot(2, 3, 2)
    plt.imshow(img2, cmap='gray')
    plt.axis('Off')

    # Imagem filtrada
    img_filtrada2 = median_filter(img2, (tam,tam))
    plt.subplot(2, 3, 5)
    plt.imshow(img_filtrada2, cmap='gray')
    plt.axis('Off')

    # boat_s_and_p.pgm
    img3 = cv2.imread('../images/boat_s_and_p.pgm',cv2.IMREAD_GRAYSCALE)
    plt.subplot(2, 3, 3)
    plt.imshow(img3, cmap='gray')
    plt.axis('Off')

    # Imagem filtrada
    img_filtrada3 = median_filter(img3, (tam,tam))
    plt.subplot(2, 3, 6)
    plt.imshow(img_filtrada3, cmap='gray')
    plt.axis('Off')

    plt.subplots_adjust(wspace=0.05, hspace=0.05, left=0.01, right=0.99, bottom=0.01, top=0.99)
    plt.show()
    plt.savefig(f'../output_images/saida_q4_plot1_{tam}x{tam}.png')


    # ----------------------------------------------------------------------------

    # Segunda imagem
    # lungs_s_and_p_10.pgm
    plt.subplot(2, 3, 1)
    img4 = cv2.imread('../images/lungs_s_and_p_10.pgm', cv2.IMREAD_GRAYSCALE)
    plt.imshow(img4, cmap='gray')
    plt.axis('Off')

    # Imagem filtrada
    img_filtrada4 = median_filter(img4, (tam,tam))
    plt.subplot(2, 3, 4)
    plt.imshow(img_filtrada4, cmap='gray')
    plt.axis('Off')

    # lungs_s_and_p_30.pgm
    img5 = cv2.imread('../images/lungs_s_and_p_30.pgm',cv2.IMREAD_GRAYSCALE)
    plt.subplot(2, 3, 2)
    plt.imshow(img5, cmap='gray')
    plt.axis('Off')

    # Imagem filtrada
    img_filtrada5 = median_filter(img5, (tam,tam))
    plt.subplot(2, 3, 5)
    plt.imshow(img_filtrada5, cmap='gray')
    plt.axis('Off')

    # lungs_s_and_p_50.pgm
    img6 = cv2.imread('../images/lungs_s_and_p_50.pgm',cv2.IMREAD_GRAYSCALE)
    plt.subplot(2, 3, 3)
    plt.imshow(img6, cmap='gray')
    plt.axis('Off')

    # Imagem filtrada
    img_filtrada6 = median_filter(img6, (tam,tam))
    plt.subplot(2, 3, 6)
    plt.imshow(img_filtrada6, cmap='gray')
    plt.axis('Off')

    plt.subplots_adjust(wspace=0.05, hspace=0.05, left=0.01, right=0.99, bottom=0.01, top=0.99)
    plt.show()
    plt.savefig(f'../output_images/saida_q4_plot2_{tam}x{tam}.png')
    

def main():
    tams = [3, 5, 7]
    for t in tams:
        gerando_imgs(t)
    

if __name__ == "__main__":
    main()