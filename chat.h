#ifndef CHAT_H
#define CHAT_H

#include <QObject>

class QFileSystemWatcher;

class Chat : public QObject
{
    Q_OBJECT

    QStringList _messagesData;
    QFileSystemWatcher* _fileSystemWatcher;

    Q_PROPERTY(QStringList messagesData READ messagesData WRITE setMessagesData NOTIFY messagesDataChanged)

signals:
    void messagesDataChanged(const QStringList&);

public:
    explicit Chat(QObject *parent = nullptr);
    virtual ~Chat();

    const QStringList& messagesData() const;

private slots:
    void setMessagesData(const QStringList&);

public slots:
    Q_INVOKABLE bool sendMessage(const QString&);
    Q_INVOKABLE void receiveMessages();
};

#endif // CHAT_H
