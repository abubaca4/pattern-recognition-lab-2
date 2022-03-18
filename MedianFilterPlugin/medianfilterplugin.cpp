#include "medianfilterplugin.h"

QString MedianFilterPlugin::name()
{
    return "MedianFilter";
}

void MedianFilterPlugin::edit(const cv::Mat &input, cv::Mat &output)
{
    cv::Mat result(input.rows, input.cols, CV_8UC3);

    std::array<std::array<uint8_t, 9>, 3> temp;
    int pixelInd = 0;
    // border rows
    for (int col: {0, input.cols - 1}){
        for (int row = 0; row < input.rows; row++)
        {
            pixelInd = 0;
            for (int k = row - 1; k <= row + 1; k++){
                for (int l = col - 1; l <= col + 1; l++){
                    cv::Vec3b pixel = input.at<cv::Vec3b>(row, col);
                    if ((k >= 0 && k < input.rows) && (l >= 0 && l < input.cols))
                    {
                        pixel = input.at<cv::Vec3b>(k, l);
                    }
                    for (auto i = 0; i < temp.size(); i++){
                        temp[i][pixelInd] = pixel[i];
                    }
                    pixelInd++;
                }
            }
            cv::Vec3b &resultPixel = result.at<cv::Vec3b>(row, col);
            for (auto i = 0; i < temp.size(); i++){
                uint8_3x3_core_sort(temp[i]);
                resultPixel[i] = temp[i][4];
            }
        }
    }
    // border cols
    for (int row: {0, input.rows - 1}){
        for (int col = 0; col < input.cols; col++)
        {
            pixelInd = 0;
            for (int k = row - 1; k <= row + 1; k++){
                for (int l = col - 1; l <= col + 1; l++){
                    cv::Vec3b pixel = input.at<cv::Vec3b>(row, col);
                    if ((k >= 0 && k < input.rows) && (l >= 0 && l < input.cols))
                    {
                        pixel = input.at<cv::Vec3b>(k, l);
                    }
                    for (auto i = 0; i < temp.size(); i++){
                        temp[i][pixelInd] = pixel[i];
                    }
                    pixelInd++;
                }
            }
            cv::Vec3b &resultPixel = result.at<cv::Vec3b>(row, col);
            for (auto i = 0; i < temp.size(); i++){
                uint8_3x3_core_sort(temp[i]);
                resultPixel[i] = temp[i][4];
            }
        }
    }
    // main part
    for (int row = 1; row < input.rows - 1; row++){
        for (int col = 1; col < input.cols - 1; col++){
            pixelInd = 0;
            for (int k = row - 1; k <= row + 1; k++){
                for (int l = col - 1; l <= col + 1; l++){
                    cv::Vec3b pixel = input.at<cv::Vec3b>(k, l);
                    for (auto i = 0; i < temp.size(); i++){
                        temp[i][pixelInd] = pixel[i];
                    }
                    pixelInd++;
                }
            }
            cv::Vec3b &resultPixel = result.at<cv::Vec3b>(row, col);
            for (auto i = 0; i < temp.size(); i++){
                uint8_3x3_core_sort(temp[i]);
                resultPixel[i] = temp[i][4];
            }
        }
    }

    result.copyTo(output);
}

void MedianFilterPlugin::uint8_sort(uint8_t &a, uint8_t &b){ //not found code for uint8_t without if for int is: int d = a - b; int m = ~(d >> 8); b += d&m; a -= d&m;
    if(a > b)
    {
        uint8_t t = a;
        a = b;
        b = t;
    }
}

void MedianFilterPlugin::uint8_3x3_core_sort(std::array<uint8_t, 9> &a){
    uint8_sort(a[1], a[2]); uint8_sort(a[4], a[5]); uint8_sort(a[7], a[8]);
    uint8_sort(a[0], a[1]); uint8_sort(a[3], a[4]); uint8_sort(a[6], a[7]);
    uint8_sort(a[1], a[2]); uint8_sort(a[4], a[5]); uint8_sort(a[7], a[8]);
    uint8_sort(a[0], a[3]); uint8_sort(a[5], a[8]); uint8_sort(a[4], a[7]);
    uint8_sort(a[3], a[6]); uint8_sort(a[1], a[4]); uint8_sort(a[2], a[5]);
    uint8_sort(a[4], a[7]); uint8_sort(a[4], a[2]); uint8_sort(a[6], a[4]);
    uint8_sort(a[4], a[2]);
}
