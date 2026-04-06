#include <bits/stdc++.h>

class Base {
public:
    Base() { f(); }
    virtual void f() = 0;
};

class Derived : public Base {
public:
    void f() override { std::cout << "Derived"; }
};

int main()
{
    Derived d;
    return 0;
}