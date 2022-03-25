#ifndef ROTATEPLUGIN_H
#define ROTATEPLUGIN_H

#include <QGenericPlugin>

#include "editor_plugin_interface.h"

#include <array>
#include <utility>
#include <algorithm>

class MedianFilterPlugin : public QObject, public EditorPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QGenericPluginFactoryInterface_iid)
    Q_INTERFACES(EditorPluginInterface);

public:
    QString name();
    void edit(const cv::Mat &input, cv::Mat &output);

private:
    static void uint8_sort(uint8_t  &a, uint8_t  &b);
    static void uint8_3x3_core_sort(std::array<uint8_t , 9> &a);
};

#endif // ROTATEPLUGIN_H
