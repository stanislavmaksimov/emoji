#ifndef MESSAGESMODEL_H
#define MESSAGESMODEL_H

#include <QStringListModel>

class MessagesModel : public QStringListModel
{
    Q_OBJECT

    Q_PROPERTY(QStringList messagesData READ messagesData WRITE setMessagesData)

public:
    explicit MessagesModel(QObject *parent = nullptr);
    virtual ~MessagesModel();

    QStringList messagesData() const;

public slots:
    void setMessagesData(const QStringList& data);
};

#endif // MESSAGESMODEL_H
