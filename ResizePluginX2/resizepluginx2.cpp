#include "resizepluginx2.h"

QString ResizePluginX2::name()
{
    return "Resize(X2)";
}

void ResizePluginX2::edit(const cv::Mat &input, cv::Mat &output)
{
    int scale = 2;
    cv::Mat result;
    cv::resize(input, result, input.size() * scale);
    result.copyTo(output);
}
