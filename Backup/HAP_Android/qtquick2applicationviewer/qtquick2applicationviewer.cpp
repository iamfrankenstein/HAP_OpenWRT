#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"
#include <QSettings>
#include <QDebug>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QCoreApplication::setOrganizationName("ani mtakhnet");
    QCoreApplication::setOrganizationDomain("animtakhnet");
    QCoreApplication::setApplicationName("HAPAndroid");

    QSettings settings;
    bool QML = settings.value("QML/custom", false).toBool();
    QtQuick2ApplicationViewer viewer;
    QString QMLadress;
    QMLadress = "qrc:/resources/qml/HAP_Android/main.qml";
    if (QML)
           QMLadress = (settings.value("QML/Location", "").toString());
    viewer.setSource(QUrl(QMLadress.toLocal8Bit()));
    viewer.showExpanded();

    return app.exec();
}
//#EOF main.cpp
#include "qtquick2applicationviewer.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QDir>
#include <QtQml/QQmlEngine>
#include <QtNetwork>

class QtQuick2ApplicationViewerPrivate
{
    QString mainQmlFile;
    friend class QtQuick2ApplicationViewer;
    static QString adjustPath(const QString &path);
};

QString QtQuick2ApplicationViewerPrivate::adjustPath(const QString &path)
{
#if defined(Q_OS_MAC)
    if (!QDir::isAbsolutePath(path))
        return QString::fromLatin1("%1/../Resources/%2")
                .arg(QCoreApplication::applicationDirPath(), path);
#elif defined(Q_OS_BLACKBERRY)
    if (!QDir::isAbsolutePath(path))
        return QString::fromLatin1("app/native/%1").arg(path);
#elif !defined(Q_OS_ANDROID)
    QString pathInInstallDir =
            QString::fromLatin1("%1/../%2").arg(QCoreApplication::applicationDirPath(), path);
    if (QFileInfo(pathInInstallDir).exists())
        return pathInInstallDir;
    pathInInstallDir =
            QString::fromLatin1("%1/%2").arg(QCoreApplication::applicationDirPath(), path);
    if (QFileInfo(pathInInstallDir).exists())
        return pathInInstallDir;
#endif
    return path;
}

QtQuick2ApplicationViewer::QtQuick2ApplicationViewer(QWindow *parent)
    : QQuickView(parent)
    , d(new QtQuick2ApplicationViewerPrivate())
{
    connect(engine(), SIGNAL(quit()), SLOT(close()));
    setResizeMode(QQuickView::SizeRootObjectToView);
    udpSocket = new QUdpSocket(this);

}

QtQuick2ApplicationViewer::~QtQuick2ApplicationViewer()
{
    delete d;
}

void QtQuick2ApplicationViewer::setMainQmlFile(const QString &file)
{
    d->mainQmlFile = QtQuick2ApplicationViewerPrivate::adjustPath(file);
#ifdef Q_OS_ANDROID
    setSource(QUrl(QLatin1String("assets:/")+d->mainQmlFile));
#else
    setSource(QUrl::fromLocalFile(d->mainQmlFile));
#endif
}

void QtQuick2ApplicationViewer::addImportPath(const QString &path)
{
    engine()->addImportPath(QtQuick2ApplicationViewerPrivate::adjustPath(path));
}

void QtQuick2ApplicationViewer::showExpanded()
{
#if defined(Q_WS_SIMULATOR) || defined(Q_OS_QNX)
    showFullScreen();
#else
    show();
#endif
    connect((QObject*)rootObject(),SIGNAL(broadencryptedmessage(QString)),
                        this,SLOT(broadcast_encryptedmessage(QString)));
    connect((QObject*)rootObject(),SIGNAL(broadmessage(QString)),
                        this,SLOT(broadcast_message(QString)));
}

void QtQuick2ApplicationViewer::broadcast_encryptedmessage(QString Message)
{
    SimpleCrypt crypto(Q_UINT64_C(0x0c2ad4a4acb9f023)); //some random number
    QString encrypted_Message = crypto.encryptToString(Message.toLocal8Bit());

    QByteArray datagram = encrypted_Message.toLocal8Bit();
    qDebug()<<encrypted_Message;
    udpSocket->writeDatagram(datagram.data(), datagram.size(),
                             QHostAddress::Broadcast, 45454);
}


void QtQuick2ApplicationViewer::broadcast_message(QString Message)
{
    qDebug()<<Message;
    QByteArray datagram = Message.toLocal8Bit();
    udpSocket->writeDatagram(datagram.data(), datagram.size(),
                             QHostAddress::Broadcast, 45454);
}
