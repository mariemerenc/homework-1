// para executar esse script, basta compilar com o cmake (entra na pasta build e digite "make" no terminal). Após isso, basta
// rodar o comando "./question4 ../images/<nome_da_foto>.pgm NUM" sendo NUM o tamanho da vizinhança que o filtro da mediana vai processar 
// (ex: 3, o filtro da mediana vai pegar a mediana dos 3x3 pixels ao redor do pixel central (ele incluso))

#include <opencv2/opencv.hpp>

cv::Mat median_filter(cv::Mat img, std::pair<int, int> tamanho_janela){
    int m{tamanho_janela.first}, n{tamanho_janela.second};
    int altura{img.rows}, largura{img.cols};

    cv::Mat img_filtrada = cv::Mat(img).clone();

    int pad_alt = m/2;
    int pad_larg = n/2;

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

    for(int y{0}; y < altura; ++y){
        for(int x{0}; x < largura; ++x){
            cv::Rect roi(x, y,n,m);
            cv::Mat vizinhanca = img_pad(roi);
            std::vector<uchar> pixels;
            pixels.reserve(m * n);

            for(int i{0}; i < m; ++i){
                for(int j{0}; j < n; ++j){
                    pixels.push_back(vizinhanca.at<uchar>(i, j));
                }
            }
            int meio = pixels.size()/2;
            std::nth_element(pixels.begin(), pixels.begin() + meio, pixels.end());
            img_filtrada.at<uchar>(y, x) = pixels[meio];
        }
    }


    return img_filtrada;
}

int main(int argc, char* argv[]) {
   
    cv::Mat img = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);

    cv::Mat img_filtrada = median_filter(img, {std::stoi(argv[2]), std::stoi(argv[2])});

    cv::imshow("Imagem filtrada",img_filtrada);
    cv::waitKey(0); // Espera você apertar uma tecla
    
    cv::destroyAllWindows();

    return 0;
}