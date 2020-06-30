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
    throw std::exception("test");
}

int main(){
    
}