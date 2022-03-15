#ifndef ERODEPLUGIN_H
#define ERODEPLUGIN_H

#include <QGenericPlugin>

#include "editor_plugin_interface.h"

class ErodePlugin : public QObject, public EditorPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QGenericPluginFactoryInterface_iid)
    Q_INTERFACES(EditorPluginInterface);

public:
    QString name();
    void edit(const cv::Mat &input, cv::Mat &output);
};

#endif // ERODEPLUGIN_H
