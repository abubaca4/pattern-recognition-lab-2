#ifndef RESIZEPLUGINX2_H
#define RESIZEPLUGINX2_H

#include <QGenericPlugin>

#include "editor_plugin_interface.h"

class ResizePluginX2 : public QObject, public EditorPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QGenericPluginFactoryInterface_iid)
    Q_INTERFACES(EditorPluginInterface);

public:
    QString name();
    void edit(const cv::Mat &input, cv::Mat &output);
};

#endif // RESIZEPLUGINX2_H
