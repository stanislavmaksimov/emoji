#include "emojimodel.h"

EmojiModel::EmojiModel(QObject *parent)
    : QAbstractListModel(parent)
    , _emojiData()
{
}

EmojiModel::~EmojiModel()
{
}

QHash<int,QByteArray> EmojiModel::roleNames() const
{
    auto result = QAbstractListModel::roleNames();
    result.insert(CodeRole, "code_role");
    result.insert(NameRole, "name_role");
    result.insert(CharacterRole, "character_role");
    return result;
}

int EmojiModel::rowCount(const QModelIndex& parent) const
{
    if (!parent.isValid()) {
        return this->_emojiData.size();
    }
    return 0;
}

QVariant EmojiModel::data(const QModelIndex& index, int role) const
{
    if (index.isValid() && index.row() >= 0 && index.row() < this->_emojiData.size()) {
        switch (role) {
        case CodeRole:
            return this->_emojiData.at(index.row()).code;
        case NameRole:
            return this->_emojiData.at(index.row()).name;
        case Qt::DisplayRole:
        case CharacterRole:
            return this->_emojiData.at(index.row()).character;
        default:
            break;
        }
    }
    return QVariant();
}

const QVector<Emoji>& EmojiModel::emojiData() const
{
    return this->_emojiData;
}

void EmojiModel::setEmojiData(const QVector<Emoji>& value)
{
    if (this->_emojiData != value) {
        this->beginResetModel();
        this->_emojiData = value;
        this->endResetModel();
        emit this->emojiDataChanged(this->_emojiData);
    }
}
