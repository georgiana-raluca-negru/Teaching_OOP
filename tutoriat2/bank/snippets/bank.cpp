#include <iostream>
#include <string>

class BankAccount
{
private:
    std::string owner;
    double balance;

public:
    // Constructor
    BankAccount(std::string name, double initial)
    {
        owner = name;
        balance = initial;
    }

    void deposit(double amount)
    {
        balance += amount;
    }

    bool withdraw(double amount)
    {
        if (amount > balance)
            return false;
        balance -= amount;
        return true;
    }

    void print()
    {
        std::cout << "Owner: " << owner << ", Balance: " << balance << std::endl;
    }

    // getters and setters
    const std::string& getOwner() const
    {
        return this->owner;
    }
    
};

int main()
{
    BankAccount acc("Alice", 1000);

    acc.deposit(200);
    acc.withdraw(500);
    acc.print();

    std::cout << acc.getOwner() << '\n';
    


    return 0;
}