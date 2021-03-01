#include "camara.h"

#include <QDateTime>

Camara::Camara()
{
    moveToThread(&m_thread);

    connect(&m_thread, &QThread::started,  this, &Camara::tbegin);
    connect(&m_thread, &QThread::finished, this, &Camara::tend);

    m_thread.start(QThread::HighPriority);
}

Camara::~Camara()
{
    m_thread.quit();
    m_thread.wait();
}

void Camara::tbegin()
{
    m_capture.reset(new cv::VideoCapture);
    m_writer.reset(new cv::VideoWriter);
    m_timer = new QTimer(this);

    m_timer->setTimerType(Qt::PreciseTimer);

    connect(m_timer, &QTimer::timeout, this, &Camara::captureCamara);
}

void Camara::tend()
{
    closeCamara();
}

void Camara::openCamara(const QString &url)
{
    if (!m_capture->isOpened() && m_capture->open(url.toLatin1().data()))
    {
        m_isflip = false;

        m_timer->start(33);

        emit statusChanged(true);
    }
    else
    {
       emit statusChanged(false);
    }
}

void Camara::openCamara(int index)
{
    if (!m_capture->isOpened() && m_capture->open(index))
    {
        m_isflip = true;

        m_timer->start(33);

        emit statusChanged(true);
    }
    else
    {
        emit statusChanged(false);
    }
}

void Camara::closeCamara()
{
    m_timer->stop();

    if (m_writer->isOpened())
        m_writer->release();

    if (m_capture->isOpened())
        m_capture->release();
}

void Camara::captureCamara()
{
    cv::Mat originalframe;
    cv::Mat flipframe;

    *m_capture >> originalframe;

    if (m_isflip)
        cv::flip(originalframe, flipframe, 1);
    else
        flipframe = originalframe;

    QImage img = QImage(flipframe.data, flipframe.cols, flipframe.rows, QImage::Format_RGB888).rgbSwapped();

    if (!img.isNull())
    {
        if (m_isTakepicture)
        {
            m_isTakepicture = !m_isTakepicture;

            QString name = m_savepath + QDateTime::currentDateTime().toString("yyyy-MM-hh hh_mm_ss") + ".jpeg";

            img.save(name, "jpeg");
        }

        if (m_isTakevideo)
        {
            *m_writer << flipframe;
        }

        updateImage(img);
    }

    originalframe.release();
    flipframe.release();
}

void Camara::takePicture()
{
    m_isTakepicture = true;
}

void Camara::takeVideo()
{
    if (!m_isTakevideo)
    {
        QString name =  m_savepath + QDateTime::currentDateTime().toString("yyyy-MM-hh hh_mm_ss") + ".avi";

        if (m_writer->open(name.toLatin1().data(), cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 30.0, cv::Size(m_capture->get(cv::CAP_PROP_FRAME_WIDTH), m_capture->get(cv::CAP_PROP_FRAME_HEIGHT)), true))
        {
            m_isTakevideo = true;
        }
    }
    else
    {
        m_isTakevideo = false;

        m_writer->release();
    }
}

void Camara::setSavePath(const QString &path)
{
    m_savepath = path + '/';
}

void Camara::setResolutions(const QSize &size)
{
    if (m_capture->isOpened())
    {
        m_capture->set(cv::CAP_PROP_FRAME_WIDTH, size.width());
        m_capture->set(cv::CAP_PROP_FRAME_HEIGHT, size.height());
    }
}

QString Camara::getSavePath() const
{
    return m_savepath;
}

bool Camara::isOpened() const
{
    return m_capture->isOpened();
}

bool Camara::isTakevideoed() const
{
    return m_isTakevideo;
}

QSize Camara::getResolutions()  const
{
    QSize ret;

    ret.setWidth(m_capture->get(cv::CAP_PROP_FRAME_WIDTH));
    ret.setHeight(m_capture->get(cv::CAP_PROP_FRAME_HEIGHT));

    return ret;
}

bool Camara::isTakeVideo() const
{
    return m_writer->isOpened();
}
