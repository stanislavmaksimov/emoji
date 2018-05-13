#ifndef EMOJI_H
#define EMOJI_H

#include <QString>

struct Emoji
{
    QString code;
    QString name;
    QString character;
};

bool operator <(const Emoji&, const Emoji&);
bool operator !=(const Emoji&, const Emoji&);
bool operator ==(const Emoji&, const Emoji&);

#endif // EMOJI_H
