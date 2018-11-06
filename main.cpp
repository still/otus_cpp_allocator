#include "lib.h"
#include <iostream>
#include <map>

using namespace std;

#define N 10

using Map   = map<int, int>;
using AMap  = map<int, int, less<int>, Allocator<pair<const int, int>, N > >;

template <typename T>
void fillMap(T& m) {
    for(size_t i = 0; i < N; ++i)
        m[i] = factorial(i);
}

template <typename T>
void fillList(T& l) {
    for(size_t i = 0; i < N; ++i)
        l.append(i);
}

template <typename T>
void outputMap(const T& m) {
    for(const auto& i: m)
        cout << i.first << " " << i.second << endl;
}

template <typename T>
void outputList(const T& l) {
    for(const auto& i: l)
        cout << i << endl;
}

int main()
{
    Map         map1;
    fillMap(map1);

    AMap        map2;
    fillMap(map2);

    outputMap(map2);

    List<int>   list1;
    fillList(list1);

    List<int, Allocator<int, N> > list2;
    fillList(list2);
    outputList(list2);

    return 0;
}
