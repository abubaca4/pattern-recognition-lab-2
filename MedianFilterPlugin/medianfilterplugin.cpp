#include "medianfilterplugin.h"

QString MedianFilterPlugin::name()
{
    return "MedianFilter";
}

void MedianFilterPlugin::edit(const cv::Mat &input, cv::Mat &output)
{
    cv::Mat result(input.size(), input.type());

    //copy coners
    result.at<cv::Vec3b>(0, 0) = input.at<cv::Vec3b>(0, 0);
    result.at<cv::Vec3b>(input.rows - 1, 0) = input.at<cv::Vec3b>(input.rows - 1, 0);
    result.at<cv::Vec3b>(0, input.cols - 1) = input.at<cv::Vec3b>(0, input.cols - 1);
    result.at<cv::Vec3b>(input.rows - 1, input.cols - 1) = input.at<cv::Vec3b>(input.rows - 1, input.cols - 1);

    // border rows
    for (std::pair<int, int> col: {std::make_pair(0, 1), std::make_pair(input.cols - 1, -1)}){
        for (int row = 1; row < input.rows - 1; row++)
        {
            cv::Vec3b &resultPixel = result.at<cv::Vec3b>(row, col.first);
            for (auto i = 0; i < 3; i++){
                std::array<uint8_t, 9> temp = {input.at<cv::Vec3b>(row, col.first)[i], input.at<cv::Vec3b>(row - 1, col.first)[i], input.at<cv::Vec3b>(row - 1, col.first + col.second)[i],
                                           input.at<cv::Vec3b>(row, col.first)[i], input.at<cv::Vec3b>(row, col.first)[i], input.at<cv::Vec3b>(row, col.first + col.second)[i],
                                           input.at<cv::Vec3b>(row, col.first)[i], input.at<cv::Vec3b>(row + 1, col.first)[i], input.at<cv::Vec3b>(row + 1, col.first + col.second)[i]};
                uint8_3x3_core_sort(temp);
                resultPixel[i] = temp[4];
            }
        }
    }
    // border cols
    for (std::pair<int, int> row: {std::make_pair(0, 1), std::make_pair(input.rows - 1, -1)}){
        for (int col = 1; col < input.cols - 1; col++)
        {
            cv::Vec3b &resultPixel = result.at<cv::Vec3b>(row.first, col);
            for (auto i = 0; i < 3; i++){
                std::array<uint8_t, 9> temp = {input.at<cv::Vec3b>(row.first, col)[i], input.at<cv::Vec3b>(row.first, col)[i], input.at<cv::Vec3b>(row.first, col)[i],
                                           input.at<cv::Vec3b>(row.first, col - 1)[i], input.at<cv::Vec3b>(row.first, col)[i], input.at<cv::Vec3b>(row.first, col + 1)[i],
                                           input.at<cv::Vec3b>(row.first + row.second, col - 1)[i], input.at<cv::Vec3b>(row.first + row.second, col)[i], input.at<cv::Vec3b>(row.first + row.second, col + 1)[i]};
                uint8_3x3_core_sort(temp);
                resultPixel[i] = temp[4];
            }
        }
    }
    // main part
    cv::parallel_for_(cv::Range(1, input.rows - 1), [&](const cv::Range& range){
        for (int row = range.start; row < range.end; row++){
            for (int col = 1; col < input.cols - 1; col++){
                cv::Vec3b &resultPixel = result.at<cv::Vec3b>(row, col);
                for (auto i = 0; i < 3; i++){
                    std::array<uint8_t, 9> temp = {input.at<cv::Vec3b>(row - 1, col - 1)[i], input.at<cv::Vec3b>(row - 1, col)[i], input.at<cv::Vec3b>(row - 1, col + 1)[i],
                                               input.at<cv::Vec3b>(row, col - 1)[i], input.at<cv::Vec3b>(row, col)[i], input.at<cv::Vec3b>(row, col + 1)[i],
                                               input.at<cv::Vec3b>(row + 1, col - 1)[i], input.at<cv::Vec3b>(row + 1, col)[i], input.at<cv::Vec3b>(row + 1, col + 1)[i]};
                    uint8_3x3_core_sort(temp);
                    resultPixel[i] = temp[4];
                }
            }
        }
    });

    result.copyTo(output);
}

inline void MedianFilterPlugin::uint8_sort(uint8_t &a, uint8_t &b){
    uint8_t t = a;
    a = std::min(t, b);
    b = std::max(t, b);
}

inline void MedianFilterPlugin::uint8_3x3_core_sort(std::array<uint8_t, 9> &a){
    uint8_sort(a[1], a[2]); uint8_sort(a[4], a[5]); uint8_sort(a[7], a[8]);
    uint8_sort(a[0], a[1]); uint8_sort(a[3], a[4]); uint8_sort(a[6], a[7]);
    uint8_sort(a[1], a[2]); uint8_sort(a[4], a[5]); uint8_sort(a[7], a[8]);
    uint8_sort(a[0], a[3]); uint8_sort(a[5], a[8]); uint8_sort(a[4], a[7]);
    uint8_sort(a[3], a[6]); uint8_sort(a[1], a[4]); uint8_sort(a[2], a[5]);
    uint8_sort(a[4], a[7]); uint8_sort(a[4], a[2]); uint8_sort(a[6], a[4]);
    uint8_sort(a[4], a[2]);
}
