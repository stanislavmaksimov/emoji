#ifndef EMOJILOADER_H
#define EMOJILOADER_H

#include <QObject>
#include <QUrl>
#include <QVector>
#include "emoji.h"

class EmojiLoader : public QObject
{
    Q_OBJECT

    QUrl _source;
    QVector<Emoji> _emojiData;

    Q_PROPERTY(QUrl source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(QVector<Emoji> emojiData READ emojiData WRITE setEmojiData NOTIFY emojiDataChanged)

signals:
    void sourceChanged(const QUrl&);
    void emojiDataChanged(const QVector<Emoji>&);

public:
    explicit EmojiLoader(QObject *parent = nullptr);
    virtual ~EmojiLoader();

    const QUrl& source() const;
    const QVector<Emoji>& emojiData() const;

public slots:
    void setSource(const QUrl&);
    void setEmojiData(const QVector<Emoji>&);
};

#endif // EMOJILOADER_H
