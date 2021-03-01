#include "mainwindow.h"

#include <QCameraInfo>
#include <QFileDialog>
#include <QImage>
#include <QMetaObject>
#include <QPixmap>
#include <QThread>
#include <QTimer>
#include <QUrl>

void MainWindow::initControl()
{
    scanCamDevs();

    m_camara.setSavePath(QDir::currentPath());

    connect(&m_camara, &Camara::updateImage, this, [&](QImage image){
        m_videoLabel.setPixmap(QPixmap::fromImage(std::move(image)));
    });

    connect(&m_videoResolutionBox, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), &m_camara, [&](){
        m_camara.setResolutions(m_videoResolutionBox.currentData().toSize());
    });

    connect(&m_switchBtn, &QPushButton::clicked, &m_camara, [&](){
        if (m_switchBtn.text() == QStringLiteral("打开"))
        {
            m_switchBtn.setEnabled(false);
            m_scanDevBtn.setEnabled(false);

            if (m_videosListBox.currentText().contains("rtsp") || m_videosListBox.currentText().contains("http"))
                m_camara.openCamara(m_videosListBox.currentText());
            else
                m_camara.openCamara(m_videosListBox.currentIndex());

            m_switchBtn.setEnabled(true);
            if (m_camara.isOpened())
            {
                if (m_camara.getResolutions() != m_videoResolutionBox.currentData().toSize())
                    m_camara.setResolutions(m_videoResolutionBox.currentData().toSize());

                m_switchBtn.setText(QStringLiteral("关闭"));
                m_takePictureBtn.setEnabled(true);
                m_takeVideoBtn.setEnabled(true);
                m_videosListBox.setEnabled(false);
            }
            else
            {
                m_scanDevBtn.setEnabled(true);
                m_videoLabel.setText(QStringLiteral("相机打开失败\n\n"
                                                    "请检查相机是否存在或网络摄像头URL已失效\n\n"
                                                    "请检查相机是否被其它应用占用\n\n"
                                                    "请在相机列表选择其它相机或重启软件"));
            }
        }
        else if (m_switchBtn.text() == QStringLiteral("关闭"))
        {
            m_videoLabel.setPixmap(QPixmap(":/img/src/camera.jpg"));
            m_switchBtn.setText(QStringLiteral("打开"));
            m_takePictureBtn.setEnabled(false);
            m_takeVideoBtn.setEnabled(false);
            m_scanDevBtn.setEnabled(true);
            m_videosListBox.setEnabled(true);

            m_camara.closeCamara();
        }
    });

    connect(&m_takePictureBtn, &QPushButton::clicked, &m_camara, &Camara::takePicture);

    connect(&m_takeVideoBtn, &QPushButton::clicked, &m_camara, [&](){
        if (!m_camara.isTakevideoed())
            m_takeVideoBtn.setText(QStringLiteral("结束录像"));
        else
            m_takeVideoBtn.setText(QStringLiteral("开始录像"));

        m_camara.takeVideo();
    });

    connect(&m_pathBtn, &QPushButton::clicked, this, [&](){
        QString path = QFileDialog::getExistingDirectory(this, QStringLiteral("选择保存路径"), m_camara.getSavePath(), QFileDialog::ShowDirsOnly);
        if (!path.isEmpty())
        {
            m_pathEdit.setText(path);
            m_camara.setSavePath(path);
        }
    });

    connect(&m_scanDevBtn, &QPushButton::clicked, this, [&](){
        scanCamDevs();
        m_videosListBox.showPopup();
    });
}

void MainWindow::scanCamDevs()
{
    m_videosListBox.clear();

    const QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
    for (const QCameraInfo &cameraInfo : cameras)
        m_videosListBox.addItem(cameraInfo.description());

    m_videosListBox.lineEdit()->setPlaceholderText(QStringLiteral("可解析的视频流"));
    m_videosListBox.setCurrentIndex(-1);

    m_videoResolutionBox.addItem("160 x 120", QSize(160, 120));
    m_videoResolutionBox.addItem("320 x 180", QSize(320, 180));
    m_videoResolutionBox.addItem("320 x 240", QSize(320, 240));
    m_videoResolutionBox.addItem("424 x 240", QSize(424, 240));
    m_videoResolutionBox.addItem("640 x 360", QSize(640, 360));
    m_videoResolutionBox.addItem("640 x 480", QSize(640, 480));
    m_videoResolutionBox.addItem("848 x 480", QSize(848, 480));
    m_videoResolutionBox.addItem("960 x 540", QSize(960, 540));
    m_videoResolutionBox.addItem("1280 x 720", QSize(1280, 720));

    m_videoResolutionBox.setCurrentIndex(5);
}
