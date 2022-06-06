#include <QApplication>
#include <QtWebEngineWidgets>
#include <QWebEngineSettings>
#include <qfileinfo.h>
#include <qdir.h>

QUrl commandLineUrlArgument()
{
    const QStringList args = QCoreApplication::arguments();
    for (const QString& arg : args.mid(1)) {
        if (!arg.startsWith(QLatin1Char('-')))
            return QUrl::fromUserInput(arg);
    }
    return QUrl(QStringLiteral("http://192.168.1.12"));
}

int main(int argc, char* argv[])
{
    QDir dir = QFileInfo(argv[0]).absoluteDir();
    std::string path = QString("--ppapi-flash-path=%1/plugins/pepflashplayer32_32_0_0_344.dll").arg(dir.absolutePath()).toStdString();
    std::vector<char*> list;
    for (int i = 0; i < argc; i++) {
        list.push_back(argv[i]); // add all arguments to the vector
    }
    list.push_back((char*)path.c_str());
    list.push_back((char*)"--ppapi-flash-version=32_0_0_344");
    list.push_back(nullptr);
    argv = list.data();
    argc = list.size();

    QCoreApplication::setOrganizationName("Gunny Mien Phi");
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setApplicationName("Gunny Client");

    QApplication app(argc, argv);

    QWebEngineSettings::defaultSettings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);

    QWebEngineView view;
    view.setUrl(commandLineUrlArgument());
    view.resize(1024, 600);
    view.show();

    return app.exec();
}
