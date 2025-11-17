#include "LiveImageProvider.h"
#include <QDebug>

// Global video capture
cv::VideoCapture cap;

LiveImageProvider::LiveImageProvider() : QQuickImageProvider(QQuickImageProvider::Image)
{
    // Open webcam 0
    cap.open(0); 
}

QImage LiveImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    QMutexLocker locker(&m_mutex);
    cv::Mat frame, gray, diff, thresh;
    
    if (cap.isOpened()) {
        cap >> frame;
    }

    if (frame.empty()) {
        QImage error(640, 480, QImage::Format_RGB888);
        error.fill(Qt::red);
        if (size) *size = error.size();
        return error;
    }

    // --- MOTION DETECTION ALGORITHM ---
    
    // 1. Resize for consistency (and speed)
    cv::resize(frame, frame, cv::Size(640, 480));

    // 2. Convert to Grayscale
    cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(gray, gray, cv::Size(21, 21), 0); // Blur to remove noise

    // 3. Compare with previous frame
    if (!prevFrame.empty()) {
        // Calculate absolute difference
        cv::absdiff(prevFrame, gray, diff);
        
        // Threshold to binary (Black/White)
        cv::threshold(diff, thresh, 25, 255, cv::THRESH_BINARY);
        
        // Count changed pixels
        int changedPixels = cv::countNonZero(thresh);
        
        // 4. Trigger Alert if significant motion (> 500 pixels changed)
        if (changedPixels > 500) {
            // Draw "MOTION DETECTED" on the original frame
            cv::putText(frame, "MOTION DETECTED", cv::Point(20, 50), 
                        cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255), 2);
            cv::rectangle(frame, cv::Point(0,0), cv::Point(640,480), cv::Scalar(0,0,255), 5);
        }
    }

    // Store current frame as "previous" for next loop
    gray.copyTo(prevFrame);
    
    // ----------------------------------

    // Convert for QML display
    cv::Mat rgb;
    cv::cvtColor(frame, rgb, cv::COLOR_BGR2RGB);
    
    if (requestedSize.isValid()) {
        cv::resize(rgb, rgb, cv::Size(requestedSize.width(), requestedSize.height()));
    }

    QImage img((const unsigned char*)(rgb.data), 
               rgb.cols, rgb.rows, 
               rgb.step, 
               QImage::Format_RGB888);
               
    QImage result = img.copy();

    if (size) *size = result.size();
    return result;
}

QImage LiveImageProvider::matToQImage(const cv::Mat &mat) { return QImage(); }
