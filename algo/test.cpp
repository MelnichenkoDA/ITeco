#include <iostream>
#include <map>

class A{
    A() = delete;
public:
    template<typename T>
    static void sort(int a, int b, T comp);
};

template<typename T>
void A::sort(int a, int b, T comp){
    std::cout << comp(a, b);
}

int main(){
    std::map<double, int> buff{{10.5, 3}, {3, 1}, {23, 1}};
    auto it = buff.lower_bound(0);
    std::cout << (it == buff.begin());

}