#include <iostream>
using namespace std;
class problema {
    int i;

public:
    problema(int j = 5) { i = j; }
    void schimba() { i++; }
    void afiseaza() const { cout << "starea curenta " << i << "\n"; }


    ~problema() {
        cout << "Dest\n";
    }
};

const problema& mister1() { return problema(6); }

void mister2(const problema& o)
{
    o.afiseaza();
    // o.schimba();
    o.afiseaza();
}
int main()
{
    // cout << b.i;
    mister2(mister1()); //(1)


    return 0;
}