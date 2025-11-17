#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "backend/LiveImageProvider.h" // Import our new class

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    
    // --- THIS IS THE FIX ---
    // Create and Register the Image Provider
    LiveImageProvider *liveProvider = new LiveImageProvider();
    // This connects C++ "liveProvider" to QML "image://live"
    engine.addImageProvider("live", liveProvider);
    // ------------------------

    const QUrl url(u"qrc:/Main/content/App.qml"_qs);
    
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}
