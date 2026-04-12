#include <cstddef>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/saturate.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>
#include "glm/glm.hpp"
#include "glm/matrix.hpp"
#include <iostream>


cv::Mat convolucao(cv::Mat img, char p){
    int m{3}, n{3};
    int altura{img.rows}, largura{img.cols};

    cv::Mat img_filtrada = cv::Mat(img).clone();

    int pad_alt{m/2}, pad_larg{n/2};

    glm::mat3x3 kernel;

    switch(p){
        case 'h':
            kernel = {0.0f, -1.0f, 0.0f, -1.0f, 4.0f, -1.0f, 0.0f, -1.0f, 0.0f};
            break;
        case 'l':
            kernel = {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f};
            kernel /= 9;
            break;
        default:
            return img;
        }

    // kernel = glm::inverse(kernel);
    cv::Mat img_pad;

    cv::copyMakeBorder(
    img,               
    img_pad,           
    pad_alt,           
    pad_alt,           
    pad_larg,          
    pad_larg,          
    cv::BORDER_REFLECT 
    );

    for(int y{0}; y < altura; y++){
        for(int x{0}; x < largura; x++){
            float soma{0.0};

            for(int i{0}; i < m; i++){
                for(int j{0}; j < n; j++){
                    soma += ((float)img_pad.at<uchar>(y + i, x + j)) * kernel[i][j];
                }
            }
            img_filtrada.at<uchar>(y, x) = cv::saturate_cast<uchar>(soma);
        }
    }
    return img_filtrada;
}


int main(int argc, char* argv[]) {
   
    cv::Mat img = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);

    cv::Mat img_filtrada = convolucao(img, *argv[2]);

    cv::imshow("Imagem filtrada",img_filtrada);
    cv::waitKey(0); // Espera você apertar uma tecla
    
    cv::destroyAllWindows();
    return 0;
}