#include <cstdlib>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/saturate.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>

const int d = 3; // Dimensão

cv::Mat convolucao(const cv::Mat& img, const cv::Mat& kernel, const int& d){
    int altura{img.rows}, largura{img.cols}, pad{d/2};

    cv::Mat img_filtrada = cv::Mat(img).clone();

    for(int y{pad}; y < altura - pad; y++){
        for(int x{pad}; x < largura - pad; x++){
            float soma{0.0};

            for(int i{0}; i < d; i++){
                for(int j{0}; j < d; j++){
                    soma += static_cast<float>(img.at<uchar>(y + i - pad, x + j - pad)) * kernel.at<float>(i, j);
                }
            }
            img_filtrada.at<uchar>(y, x) = cv::saturate_cast<uchar>(soma);
        }
    }
    return img_filtrada;
}


int main(int argc, char* argv[]) {
   
    cv::Mat img = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);
    cv::Mat kernel = cv::Mat::zeros(d, d, CV_32FC1);
    switch(*argv[2]){
        case 'h':
            kernel = (cv::Mat_<float>(3,3) << 
                      0.0f, 1.0f, 0.0f, 
                      1.0f, -4.0f, 1.0f, 
                      0.0f, 1.0f, 0.0f
                     );
            break;
        case 'l':
            kernel = (cv::Mat_<float>(3, 3) << 
                      1.0f, 1.0f, 1.0f,
                      1.0f, 1.0f, 1.0f, 
                      1.0f, 1.0f, 1.0f
                     );
            kernel /= 9.0f;
            break;
        default:
            std::cerr << "Error: invalid arguments " + std::string(argv[2]) << '\n';
            return EXIT_FAILURE;
    }

    cv::Mat img_filtrada = convolucao(img, kernel ,d);

    cv::imwrite("peppers_original.png", img);

    bool sucesso = cv::imwrite("peppers_filtrado.png", img_filtrada);
    
    if (sucesso) {
        std::cout << "Imagem salva com sucesso como 'resultado_filtrado.png'!\n";
    } else {
        std::cerr << "Erro ao salvar a imagem.\n";
    }
    
    return 0;
}