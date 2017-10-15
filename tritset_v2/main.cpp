#include <iostream>
#include "Tritset.h"

int main() {
    Tritset set1(10);
    set1[1] = True;
    set1[5] = False;
    set1[2] = False;
    set1[6] = True;
    set1.printSet();
    Tritset set2(15);
    set2[1] = True;
    set2[2] = False;
    set2[3] = True;
    set2[4] = Unknown;
    set2[6] = False;
    set2.printSet();
    Tritset set3 = set1 & set2;
    set3.printSet();
    Tritset set4 = set1 | set2;
    set4.printSet();
    Tritset set5 = ~set1;
    set5.printSet();
    Tritset set6 = set5;
    std::cout << (set6 == set5) << " " << (set6 != set5) << std::endl;
    Tritset set7 = ~set6;
    std::cout << (set7 == set6) << " " << (set7 != set6) << std::endl;
    std::cout << set2[2] << std::endl;
    std::cout << set1 << std::endl;
    return 0;
}