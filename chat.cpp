#include "chat.h"
#include <QFile>
#include <QFileSystemWatcher>

constexpr const char* filename = "messages.txt";
constexpr const char  separator = 0xFF;

Chat::Chat(QObject *parent)
    : QObject(parent)
    , _messagesData()
    , _fileSystemWatcher(new QFileSystemWatcher(this))
{
    connect(this->_fileSystemWatcher, SIGNAL(fileChanged(QString)), this, SLOT(receiveMessages()));
    this->receiveMessages();
}

Chat::~Chat()
{
}

const QStringList& Chat::messagesData() const
{
    return this->_messagesData;
}

void Chat::setMessagesData(const QStringList& value)
{
    if (this->_messagesData != value) {
        this->_messagesData = value;
        emit this->messagesDataChanged(this->_messagesData);
    }
}

bool Chat::sendMessage(const QString& value)
{
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly | QIODevice::Append)) {
        file.write(value.toUtf8());
        file.write(QByteArray::fromRawData(&separator, 1));
        file.close();
        this->receiveMessages();
        return true;
    }
    return false;
}

void Chat::receiveMessages()
{
    if (!this->_fileSystemWatcher->files().contains(filename)) {
        this->_fileSystemWatcher->addPath(filename);
    }
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly)) {
        this->setMessagesData(QString(file.readAll()).split(QByteArray::fromRawData(&separator, 1), QString::SkipEmptyParts));
        file.close();
    }
}
