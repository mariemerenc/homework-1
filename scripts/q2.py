# para executar esse script, rodar o comando "python q2.py ../images/chaewon-2.png P" sendo P ou a letra 'h' ou a letra 'l', representando, respectivamente, filtro de passa alta ou baixa
import cv2
import numpy as np
import matplotlib.pyplot as plt
import sys

def convolucao(img, p):
    m = n = 3
    altura, largura, = img.shape
    img_filtrada = np.zeros_like(img, dtype=np.float64)

    pad_alt = m // 2
    pad_larg = n // 2

    kernel = []

    if p == 'h':
        kernel = np.array([
            [0, -1, 0],
            [-1, 4, -1],
            [0, -1, 0]
        ])
    elif p == 'l':
        kernel = np.ones((3,3)) / 9

    #EM TESE, precisamos inverter o kernel!!
    kernel = np.flip(kernel, axis=(0,1))

    img_pad = np.pad(img, ((pad_alt, pad_alt), (pad_larg, pad_larg)), mode='reflect')

    for y in range(altura):
        for x in range(largura):
            soma = 0.0
            
            for i in range(m):
                for j in range(n):
                    soma += img_pad[y+1,x+j] * kernel[i,j]
            
            img_filtrada[y,x] = soma

    return np.clip(img_filtrada, 0, 255).astype(np.uint8)


def main():
    # Imagem original
    img = cv2.imread(sys.argv[1],cv2.IMREAD_GRAYSCALE)
    plt.subplot(1, 2, 1)
    plt.imshow(img, cmap='gray')
    plt.title('Original')
    plt.axis('Off')

    # Imagem filtrada
    p = sys.argv[2]
    img_filtrada = convolucao(img, p)
    plt.subplot(1, 2, 2)
    plt.imshow(img_filtrada, cmap='gray')
    plt.title(f'Convolução passa-{'alta' if p == 'h' else 'baixa'} (3x3)')
    plt.axis('Off')

    plt.show()
    plt.savefig('saida_plot.png')

if __name__ == "__main__":
    main()