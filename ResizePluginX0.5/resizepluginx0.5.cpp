#include "resizepluginx0.5.h"

QString  ResizePluginX0_5::name()
{
    return "Resize(X0.5)";
}

void  ResizePluginX0_5::edit(const cv::Mat &input, cv::Mat &output)
{
    int scale = 2;
    cv::Mat result;
    cv::resize(input, result, input.size() / scale);
    result.copyTo(output);
}
