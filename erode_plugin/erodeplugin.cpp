#include "erodeplugin.h"

QString ErodePlugin::name()
{
    return "Erode";
}

void ErodePlugin::edit(const cv::Mat &input, cv::Mat &output)
{
    cv::Mat tmp(input.size(), input.type());
    cv::erode(input, tmp, cv::Mat());
    tmp.copyTo(output);
}
