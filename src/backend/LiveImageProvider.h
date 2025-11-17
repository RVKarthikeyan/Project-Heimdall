#ifndef LIVEIMAGEPROVIDER_H
#define LIVEIMAGEPROVIDER_H

#include <QQuickImageProvider>
#include <QImage>
#include <QMutex>
#include <opencv2/opencv.hpp>

class LiveImageProvider : public QQuickImageProvider
{
public:
    LiveImageProvider();
    
    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize) override;
    void updateFrame(const QString &id, const cv::Mat &frame);

private:
    QImage matToQImage(const cv::Mat &mat);
    QMap<QString, QImage> m_frames;
    QMutex m_mutex;
};

#endif // LIVEIMAGEPROVIDER_H
