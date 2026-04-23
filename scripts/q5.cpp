#include <cmath>
#include <opencv2/core.hpp>
#include <opencv2/core/base.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>
#include <glm/glm.hpp>

cv::Mat gaussian_filter(cv::Size shape){
    float d0{5.0f};
    cv::Mat base = cv::Mat::zeros(shape, CV_32FC1);
    int center_row{shape.height/2}, center_col{shape.width/2};

    for(int i{0}; i < shape.height; ++i){
        for(int j{0}; j < shape.width; ++j){   
            auto d2 = std::pow(i - center_row, 2) + std::pow(j - center_col, 2);
            base.at<float>(i, j) = std::exp(-d2/(2*std::pow(d0, 2)));
        }
    }
    return 1.0f - base;
}

cv::Mat ideal_filter(cv::Size shape){
    float d0{5.0f};
    cv::Mat base = cv::Mat::zeros(shape, CV_32FC1);
    int center_row{shape.height/2}, center_col{shape.width/2};

    for(int i{0}; i < shape.height; ++i){
        for(int j{0}; j < shape.width; ++j){
            auto d = std::sqrt(std::pow(i - center_row, 2) + std::pow(j - center_col, 2));
            if(d <= d0){
                base.at<float>(i, j) = 0.0f;
            }
            else{
                base.at<float>(i, j) = 1.0f;
            }
        }
    }

    return base;
}

//como to com preguiça de procurar outra biblioteca q implemente a fft com shift, eu msm irei fzr o shift :)

void preProcessarShift(cv::Mat& imagem) { // Basicamente uma função que aplica o que foi visto na questão 6 para otimizar o shift.
    
    for (int y = 0; y < imagem.rows; y++) {
        for (int x = 0; x < imagem.cols; x++) {
            if ((x + y) % 2) {
                imagem.at<float>(y, x) *= -1.0f;    //> f (x, y)(−1)x+y ⇔ F(u − M/2, v − N/2)
            }

        }
    }
}
int main(int argc, char* argv[]){

    cv::Mat img = cv::imread(argv[1], cv::IMREAD_GRAYSCALE); //Lê a imagem original e coloca em img.
    cv::Mat img_float;
    img.convertTo(img_float, CV_32F);

    preProcessarShift(img_float);

    cv::Mat planes[] = {img_float, cv::Mat::zeros(img_float.size(), CV_32F)};
    cv::Mat complexImg;
    cv::merge(planes, 2, complexImg);
    cv::dft(complexImg, complexImg);

    float k1 = std::stof(argv[2]);
    float k2 = std::stof(argv[3]);

    cv::Mat filter = k1 + k2 * gaussian_filter(img.size());

    cv::Mat dft_planes[2];
    cv::split(complexImg, dft_planes);
    cv::multiply(dft_planes[0], filter, dft_planes[0]);
    cv::multiply(dft_planes[1], filter, dft_planes[1]);
    cv::merge(dft_planes, 2, complexImg);

    cv::Mat inversa_complexa;
    cv::dft(complexImg, inversa_complexa, cv::DFT_INVERSE | cv::DFT_SCALE);

    cv::Mat inversa_planes[2];
    cv::split(inversa_complexa, inversa_planes);

    cv::Mat img_filtrada_float = inversa_planes[0];

    preProcessarShift(img_filtrada_float);

    img_filtrada_float = cv::abs(img_filtrada_float);

    cv::Mat img_normalizada;
    cv::normalize(img_filtrada_float, img_normalizada, 0, 255, cv::NORM_MINMAX);
    
    cv::Mat img_final;
    img_normalizada.convertTo(img_final, CV_8UC1);

    cv::imshow("Imagem Original", img);
    cv::imshow("Imagem Filtrada", img_final);
    cv::waitKey(0);

    return 0;
}