#include "messagesmodel.h"

MessagesModel::MessagesModel(QObject *parent)
    : QStringListModel(parent)
{
}

MessagesModel::~MessagesModel()
{
}

QStringList MessagesModel::messagesData() const
{
    return this->stringList();
}

void MessagesModel::setMessagesData(const QStringList& data)
{
    QStringListModel::setStringList(data);
}
