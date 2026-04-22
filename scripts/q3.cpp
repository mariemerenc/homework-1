#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace cv;
using namespace std;

vector<int> histograma(const Mat& img) {
    vector<int> hist(256, 0);
    for (int r=0; r<img.rows; r++) {
        for (int c=0; c<img.cols; c++) {
            int pixel_val = img.at<uchar>(r, c);
            hist[pixel_val]++;
        }
    }
    return hist;
}

vector<int> cumsum(const vector<int>& hist) {
    vector<int> cdf(256, 0);
    cdf[0] = hist[0];
    for (int i=1; i<256; i++) {
        cdf[i] = cdf[i-1] + hist[i];
    }
    return cdf;
}

void equalizacao(const Mat& img, Mat& img_eq, vector<int>& hist, vector<int>& cdf) {
    hist = histograma(img);
    cdf = cumsum(hist);

    int total_pxs = img.rows * img.cols;
    
    int cdf_min = 0;
    for (int i=0; i<256; i++) {
        if (cdf[i] > 0) {
            cdf_min = cdf[i];
            break;
        }
    }

    vector<uchar> cdf_norm(256, 0);
    for (int i=0; i<256; i++) {
        float valor = (float)(cdf[i] - cdf_min) / (total_pxs - cdf_min); //normalização para [0,1]
        cdf_norm[i] = saturate_cast<uchar>(round(valor * 255.0f)); //normalização para [0,255]
    }

    img_eq = Mat::zeros(img.size(), img.type());
    for (int r=0; r<img.rows; r++) {
        for (int c=0; c<img.cols; c++) {
            img_eq.at<uchar>(r, c) = cdf_norm[img.at<uchar>(r, c)];
        }
    }
}

int main(int argc, char** argv) {

    Mat img = imread(argv[1], IMREAD_GRAYSCALE);

    Mat img_eq;
    vector<int> hist_orig, cdf_orig;
    
    equalizacao(img, img_eq, hist_orig, cdf_orig);

    imshow("Imagem Original", img);
    imshow("Imagem Equalizada", img_eq);
    waitKey(0);

    cv::destroyAllWindows();
    return 0;
}