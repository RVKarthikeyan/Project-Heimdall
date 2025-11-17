#include "LiveImageProvider.h"
#include <QDebug>

// Global video capture object (Simple approach for Day 1)
cv::VideoCapture cap;

LiveImageProvider::LiveImageProvider() : QQuickImageProvider(QQuickImageProvider::Image)
{
    // Open the default camera (ID 0)
    // If you don't have a webcam, change 0 to a file path: "/home/user/video.mp4"
    cap.open(0); 
    
    if (!cap.isOpened()) {
        qWarning() << "Error: Could not open camera 0";
    }
}

QImage LiveImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    cv::Mat frame;
    
    if (cap.isOpened()) {
        cap >> frame; // Capture a frame
    }

    if (frame.empty()) {
        // If camera fails, return Red Error screen
        QImage error(640, 480, QImage::Format_RGB888);
        error.fill(Qt::red);
        if (size) *size = error.size();
        return error;
    }

    // Convert BGR (OpenCV) to RGB (Qt)
    cv::Mat rgb;
    cv::cvtColor(frame, rgb, cv::COLOR_BGR2RGB);
    
    // Resize if requested (Performance optimization)
    if (requestedSize.isValid()) {
        cv::resize(rgb, rgb, cv::Size(requestedSize.width(), requestedSize.height()));
    }

    QImage img((const unsigned char*)(rgb.data), 
               rgb.cols, rgb.rows, 
               rgb.step, 
               QImage::Format_RGB888);
               
    // We must deep copy because 'rgb' mat will be destroyed when function ends
    QImage result = img.copy();

    if (size) *size = result.size();
    return result;
}

void LiveImageProvider::updateFrame(const QString &id, const cv::Mat &frame) {
    // Not used in this simple polling version yet
}

QImage LiveImageProvider::matToQImage(const cv::Mat &mat) {
    return QImage(); // Helper not used in this version
}
