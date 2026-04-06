#include <iostream>
#include <string>
#include <vector>


class BankAccount 
{
private:
    std::string owner;
    float balance;

public:
    BankAccount(std::string owner = "", float balance = 100):owner(owner), balance(balance)
    {
        // logica
    }

    std::string getOwner() const
    {
        return owner;
    }

    float getBalance() const
    {
        return balance; 
    }

    void print()
    {
       std::cout << this->getOwner() << "\n" << this->getBalance() << "\n";
    }

    friend std::ostream& operator<<(std::ostream& os, const BankAccount& b)
    {
        os << b.owner << "\n" << b.balance << "\n";
        return os;
    }
};


int main()
{
    BankAccount b("raluca", 100);
    b.print();

    //  cout

    std::cout << 3 << "petru" << "\n" << b;

    return 0;
}