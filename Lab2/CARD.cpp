#include "CARD.h"
#include <cassert>

card::card(suit st, int r)
{
    assert(1<=r&&r<=13);
    s=st;
    rank=r;
}

suit card::get_suit() const
{
    return s;
}

int card::get_rank() const
{
    return rank;
}
