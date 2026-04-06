# para executar esse script, rodar o comando "python q4.py ../images/<nome_da_foto>.pgm NUM" sendo NUM o tamanho da vizinhança que o filtro da mediana vai processar (ex: 3, o filtro da mediana vai pegar a mediana dos 3x3 pixels ao redor do pixel central (ele incluso))
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

    for y in range(altura):
        for x in range(largura):
            vizinhanca = img_pad[y:y+m, x:x+n]
            img_filtrada[y,x] = np.median(vizinhanca)

    return np.clip(img_filtrada, 0, 255).astype(np.uint8)


def main():
    # Imagem original
    img = cv2.imread(sys.argv[1],cv2.IMREAD_GRAYSCALE)
    plt.subplot(1, 2, 1)
    plt.imshow(img, cmap='gray')
    plt.title('Original')
    plt.axis('Off')

    # Imagem filtrada
    tam = int(sys.argv[2])
    img_filtrada = median_filter(img, (tam,tam))
    plt.subplot(1, 2, 2)
    plt.imshow(img_filtrada, cmap='gray')
    plt.title(f'Filtro da Mediana ({tam}x{tam})')
    plt.axis('Off')

    plt.show()
    plt.savefig('saida_plot.png')

if __name__ == "__main__":
    main()