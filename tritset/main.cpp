#include "trit_pointer.h"
#include "tritset.h"


int main() {
    Tritset set(10);
    int allocLength = set.capacity();
    set[16] = True;
    cout << allocLength << endl;
    cout << set.capacity() << endl;
    set.printSet();
    return 0;
}