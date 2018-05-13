#include "emoji.h"

bool operator <(const Emoji& l, const Emoji& r)
{
    if (&l == &r) return false;
    if (l.code < r.code) return true;
    if (l.name < r.name) return true;
    if (l.character < r.character) return true;
    return false;
}

bool operator !=(const Emoji& l, const Emoji& r)
{
    return (l < r) || (r < l);
}

bool operator ==(const Emoji& l, const Emoji& r)
{
    return !(l != r);
}
