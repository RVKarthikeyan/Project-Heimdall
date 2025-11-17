#include "LiveImageProvider.h"

LiveImageProvider::LiveImageProvider() : QQuickImageProvider(QQuickImageProvider::Image)
{
    // Default GREEN frame to prove connection works
    QImage placeholder(640, 480, QImage::Format_RGB888);
    placeholder.fill(Qt::green);
    m_frames.insert("cam1", placeholder);
}

QImage LiveImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    QMutexLocker locker(&m_mutex);
    
    if (!m_frames.contains(id)) {
        QImage error(640, 480, QImage::Format_RGB888);
        error.fill(Qt::red); // Red means ID not found
        return error;
    }

    QImage img = m_frames[id];
    if (size) *size = img.size();
    
    if (requestedSize.isValid()) {
        img = img.scaled(requestedSize, Qt::KeepAspectRatio);
    }
    
    return img;
}

void LiveImageProvider::updateFrame(const QString &id, const cv::Mat &frame)
{
    QMutexLocker locker(&m_mutex);
    m_frames.insert(id, matToQImage(frame));
}

QImage LiveImageProvider::matToQImage(const cv::Mat &mat)
{
    if (mat.empty()) return QImage();
    cv::Mat rgb;
    cv::cvtColor(mat, rgb, cv::COLOR_BGR2RGB);
    return QImage((const unsigned char*)(rgb.data), rgb.cols, rgb.rows, rgb.step, QImage::Format_RGB888).copy();
}
