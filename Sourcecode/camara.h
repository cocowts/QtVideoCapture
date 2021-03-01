#ifndef CAMARA_H
#define CAMARA_H

#include <QImage>
#include <QObject>
#include <QThread>
#include <QTimer>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

Q_DECLARE_METATYPE(QImage);

/*
 *@brief Camara 在单独线程中完成视频抽帧、拍照及录像功能
 *@brief open、close 等是耗时操作，请保证在 Camara 线程时间中完成调用 （可考虑异步槽函数、QMetaObject::invokeMethod）
 */

class Camara : public QObject
{
    Q_OBJECT

public:
    Camara();
    ~Camara();

    bool isOpened()        const;
    bool isTakevideoed()   const;
    QString getSavePath()  const;
    QSize getResolutions() const;
    bool isTakeVideo()     const;

signals:
    void updateImage(QImage);
    void statusChanged(bool isOpen);

public slots:
    void openCamara(const QString &url);
    void openCamara(int index);
    void closeCamara();
    void takePicture();
    void takeVideo();
    void setSavePath(const QString &path);
    void setResolutions(const QSize &size);

private slots:
    void tbegin();
    void tend();
    void captureCamara();

private:
    QString m_savepath;
    QAtomicInteger<bool> m_isTakepicture = false;
    QAtomicInteger<bool> m_isTakevideo   = false;
    QAtomicInteger<bool> m_isflip        = false;

    QScopedPointer<cv::VideoCapture> m_capture;
    QScopedPointer<cv::VideoWriter>  m_writer;

    QTimer  *m_timer = nullptr;
    QThread m_thread;
};

#endif // CAMARA_H
