#include <fstream>
#include "sort_strings.h"

using namespace myNameSpace;
using namespace std;

int main(){
    ifstream in("in.txt");
    ofstream out("out.txt");
    list<string> list_to_sort;

    string tmp_str;
    while (getline(in, tmp_str))
    {
        list_to_sort.push_back(tmp_str);
    }

    sort_strings(list_to_sort);

    for(const auto& a: list_to_sort)
    {
        out << a << endl;
    }

    return 0;
}