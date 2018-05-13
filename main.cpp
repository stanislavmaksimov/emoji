#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "chat.h"
#include "emojiloader.h"
#include "emojimodel.h"
#include "messagesmodel.h"

int main(int argc, char *argv[])
{
    //QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qRegisterMetaType<Emoji>("Emoji");
    qRegisterMetaType<QVector<Emoji>>("QVector<Emoji>");

    qmlRegisterType<Chat>("Emoji", 1, 0, "Chat");
    qmlRegisterType<EmojiLoader>("Emoji", 1, 0, "EmojiLoader");
    qmlRegisterType<EmojiModel>("Emoji", 1, 0, "EmojiModel");
    qmlRegisterType<MessagesModel>("Emoji", 1, 0, "MessagesModel");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
