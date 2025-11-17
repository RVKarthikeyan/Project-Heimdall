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

private:
    QImage matToQImage(const cv::Mat &mat);
    
    cv::Mat prevFrame; // To store the last frame for comparison
    QMutex m_mutex;
};

#endif // LIVEIMAGEPROVIDER_H
