#include "head.h"
typedef enum {CLUBS,DIAMONDS,HEARTS,SPADES} Suit ;
const string suit_name[] = {"clubs","diamonds","hearts","spades"};
void show(Suit suit){
    cout<<suit_name[suit];
}

int main() {
    int x = 1;
    int y = 2;
    (y = x) += 2;
    cout<<x<<endl<<y<<endl;
    return 0;
}