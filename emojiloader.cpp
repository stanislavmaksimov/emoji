#include "emojiloader.h"
#include <QBuffer>
#include <QNetworkAccessManager>
#include <QNetworkReply>

QVector<Emoji> parse(const QByteArray& value);

EmojiLoader::EmojiLoader(QObject *parent)
    : QObject(parent)
    , _source()
    , _emojiData()
{
}

EmojiLoader::~EmojiLoader()
{
}

const QVector<Emoji>& EmojiLoader::emojiData() const
{
    return this->_emojiData;
}

void EmojiLoader::setEmojiData(const QVector<Emoji>& value)
{
    if (this->_emojiData != value) {
        this->_emojiData = value;
        emit this->emojiDataChanged(this->_emojiData);
    }
}

const QUrl& EmojiLoader::source() const
{
    return this->_source;
}

void EmojiLoader::setSource(const QUrl& value)
{
    if (this->_source != value) {
        this->_source = value;
        if (this->_source.isValid()) {
            if (auto networkAccessManager = new QNetworkAccessManager(this)) {
                if (auto reply = networkAccessManager->get(QNetworkRequest(this->_source))) {
                    connect(reply, &QNetworkReply::finished, [this, reply, networkAccessManager](){
                        this->setEmojiData(parse(reply->readAll()));
                        reply->deleteLater();
                        networkAccessManager->deleteLater();
                    });
                } else {
                    delete networkAccessManager;
                }
            }
        }
        emit this->sourceChanged(this->_source);
    }
}

QVector<Emoji> parse(const QByteArray& value)
{
    QVector<Emoji> result;
    QBuffer buffer(const_cast<QByteArray*>(&value));
    if (buffer.open(QIODevice::ReadOnly)) {
        while(!buffer.atEnd()) {
            const auto line = buffer.readLine();
            if (!line.startsWith('#')) {
                QList<QByteArray> parts = line.split(';');
                if (parts.size() >= 4) {
                    const auto type = parts.at(1).trimmed();
                    if (type == "emoji") {
                        const auto codes = parts.first().trimmed().split(' ');
                        if (codes.size() == 1) {
                            Emoji emoji;
                            emoji.code = codes.first().trimmed().toLower();
                            const auto charBegin = parts.last().indexOf('(');
                            if (charBegin >= 0) {
                                const auto charEnd = parts.last().indexOf(')', charBegin);
                                emoji.character = parts.last().mid(charBegin + 1, charEnd - charBegin - 1);
                                emoji.name = parts.last().mid(charEnd + 1).trimmed().toLower();
                                emoji.name.replace(' ', '_');
                                emoji.name.prepend(':');
                                emoji.name.append(':');
                            }
                            result.push_back(emoji);
                        }
                    }
                }
            }
        }
        buffer.close();
    }
    return result;
}
