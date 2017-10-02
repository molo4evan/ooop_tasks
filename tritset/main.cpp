#include "trit_pointer.h"
#include "tritset.h"


int main() {
    Tritset set(10);
    int allocLength = set.capacity();
    set[5] = True;
    set[7] = False;
    set[19] = True;
    set[21] = False;
    set[40] = True;
    set.printSet();
    set[40] = Unknown;
    set.printSet();
    set.shrink();
    set.printSet();
    cout << allocLength << endl;
    cout << set.capacity() << endl;
    return 0;
}