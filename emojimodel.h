#ifndef EMOJIMODEL_H
#define EMOJIMODEL_H

#include <QAbstractListModel>
#include "emoji.h"

class EmojiModel : public QAbstractListModel
{
    Q_OBJECT

    QVector<Emoji> _emojiData;

    enum Roles
    {
        CodeRole = Qt::UserRole + 1,
        NameRole,
        CharacterRole
    };

    Q_PROPERTY(QVector<Emoji> emojiData READ emojiData WRITE setEmojiData NOTIFY emojiDataChanged)

signals:
    void emojiDataChanged(const QVector<Emoji>&);

public:
    explicit EmojiModel(QObject *parent = nullptr);
    virtual ~EmojiModel();

    QHash<int,QByteArray> roleNames() const;
    int rowCount(const QModelIndex& parent) const;
    QVariant data(const QModelIndex& index, int role) const;

    const QVector<Emoji>& emojiData() const;

public slots:
    void setEmojiData(const QVector<Emoji>&);
};


#endif // EMOJIMODEL_H
