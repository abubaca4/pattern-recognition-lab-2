#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , imageScene(this)
    , imageView(&imageScene)
{
    ui->setupUi(this);
    setCentralWidget(&imageView);
    currentImage = nullptr;
    currentImagePath = "";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_open_triggered()
{
    QFileDialog dialog(this);
    dialog.setWindowTitle("Открыть изображение");
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter("Изображения (*.png *.bmp *.jpg)");
    QStringList filePaths;
    if (dialog.exec()){
        filePaths = dialog.selectedFiles();
        showImage(filePaths[0]);
    }
}

void MainWindow::on_save_as_triggered()
{
    if (image_check_null()) {
        return;
    }
    QFileDialog dialog(this);
    dialog.setWindowTitle("Сохранить изображение как ...");
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setNameFilter("Изображения (*.png *.bmp *.jpg)");
    QStringList fileNames;
    if (dialog.exec()){
        fileNames = dialog.selectedFiles();
        if(QRegularExpression(".+\\.(png|bmp|jpg)").match(fileNames.at(0)).hasMatch()) {
            currentImage->pixmap().save(fileNames.at(0));
        } else {
            QMessageBox::information(this, "Сообщение", "Ошибка сохранения: неверный формат или имя файла");
        }
    }
}

void MainWindow::on_exit_triggered()
{
    QCoreApplication::quit();
}

void MainWindow::on_zome_in_triggered()
{
    imageView.scale(1.2, 1.2);
}

void MainWindow::on_zome_out_triggered()
{
    imageView.scale(1/1.2, 1/1.2);
}

void MainWindow::on_prev_triggered()
{
    if (currentImagePath == "")
        return;
    QFileInfo current(currentImagePath);
    QDir dir = current.absoluteDir();
    QStringList nameFilters;
    nameFilters << "*.png" << "*.bmp" << "*.jpg";
    QStringList fileNames = dir.entryList(nameFilters, QDir::Files, QDir::Name);
    int idx = fileNames.indexOf(QRegularExpression(QRegularExpression::escape(current.fileName())));
    if (idx > 0) {
        showImage(dir.absoluteFilePath(fileNames.at(idx - 1)));
    } else {
        showImage(dir.absoluteFilePath(fileNames.at(fileNames.length() - 1)));
    }
}

void MainWindow::on_next_triggered()
{
    if (currentImagePath == "")
        return;
    QFileInfo current(currentImagePath);
    QDir dir = current.absoluteDir();
    QStringList nameFilters;
    nameFilters << "*.png" << "*.bmp" << "*.jpg";
    QStringList fileNames = dir.entryList(nameFilters, QDir::Files, QDir::Name);
    int idx = fileNames.indexOf(QRegularExpression(QRegularExpression::escape(current.fileName())));
    if (idx <= fileNames.length() - 2) {
        showImage(dir.absoluteFilePath(fileNames.at(idx + 1)));
    } else {
        showImage(dir.absoluteFilePath(fileNames.at(0)));
    }
}

void MainWindow::on_rotate_triggered()
{
    imageView.rotate(-90);
}

void MainWindow::showImage(QString path){
    currentImagePath = path;
    imageScene.clear();
    imageView.resetTransform();
    QPixmap image(path);
    currentImage = imageScene.addPixmap(image);
    imageScene.update();
    imageView.setSceneRect(image.rect());
    QString status = QString("%1, %2x%3, %4 Байт").arg(path).arg(image.width())
            .arg(image.height()).arg(QFile(path).size());
    ui->statusbar->showMessage(status);

    ui->prev->setEnabled(true);
    ui->next->setEnabled(true);
    QFileInfo current(currentImagePath);
    QDir dir = current.absoluteDir();
    QStringList nameFilters;
    nameFilters << "*.png" << "*.bmp" << "*.jpg";
    QStringList fileNames = dir.entryList(nameFilters, QDir::Files, QDir::Name);
    auto idx = fileNames.indexOf(QRegularExpression(QRegularExpression::escape(current.fileName())));
    if (idx == 0)
        ui->prev->setEnabled(false);
    if (idx == fileNames.length() - 1)
        ui->next->setEnabled(false);
}

cv::Mat MainWindow::mat_from_pixmap(const QPixmap &in){
    QImage image = in.toImage();
    image = image.convertToFormat(QImage::Format_RGB888);
    return cv::Mat(
                image.height(),
                image.width(),
                CV_8UC3,
                image.bits(),
                image.bytesPerLine()).clone();
}

QPixmap MainWindow::pixmap_from_mat(const cv::Mat &in){
    QImage image(
                in.data,
                in.cols,
                in.rows,
                in.step,
                QImage::Format_RGB888);
    return QPixmap::fromImage(image);
}

bool MainWindow::image_check_null(){
    if (currentImage == nullptr) {
        QMessageBox::information(this, "Сообщение", "Изображение отсутствует");
    }
    return currentImage == nullptr;
}

void MainWindow::on_actionBlur_triggered()
{
    if (image_check_null())
        return;
    cv::Mat mat = mat_from_pixmap(currentImage->pixmap());
    cv::Mat tmp(mat.size(), mat.type());
    cv::blur(mat, tmp, cv::Size(8, 8));
    tmp.copyTo(mat);
    QPixmap pixmap = pixmap_from_mat(mat);
    imageScene.clear();
    imageView.resetTransform();
    currentImage = imageScene.addPixmap(pixmap);
    imageScene.update();
    imageView.setSceneRect(pixmap.rect());
}
