#ifndef CARD_H
#define CARD_H

enum suit {CLUBS,DIAMONDS,HEARTS,SPADES};
class card
{
public:
    //precondition:1<=r<=13
    //postcondition:card with given properties has been created
    card(suit st, int r);
    //postcondition: suit has been returned
    suit get_suit() const;
    //postcondition: rank has been returned
    int get_rank() const;
private:
    suit s;
    int rank;
};

#endif // CARD_H