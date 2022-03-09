#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QFileDialog>
#include <QMessageBox>
#include <QRegularExpression>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_open_triggered();
    void on_save_as_triggered();
    void on_exit_triggered();
    void on_zome_in_triggered();
    void on_zome_out_triggered();
    void on_prev_triggered();
    void on_next_triggered();
    void on_rotate_triggered();

private:
    Ui::MainWindow *ui;

    QString currentImagePath;
    QGraphicsScene imageScene;
    QGraphicsView imageView;
    QGraphicsPixmapItem *currentImage;

    void showImage(QString path);
};
#endif // MAINWINDOW_H
