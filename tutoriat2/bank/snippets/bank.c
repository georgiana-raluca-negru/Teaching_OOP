#include <stdio.h>
#include <string.h>

struct BankAccount
{
    char owner[50];
    double balance;
};

void initAccount(struct BankAccount *acc, const char *name, double initial)
{
    strcpy(acc->owner, name);
    acc->balance = initial;
}

void deposit(struct BankAccount *acc, double amount)
{
    acc->balance += amount;
}

int withdraw(struct BankAccount *acc, double amount)
{
    if (amount > acc->balance)
    {
        return 0;
    }
    acc->balance -= amount;
    return 1;
}

void printAccount(struct BankAccount *acc)
{
    printf("Owner: %s, Balance: %.2f\n", acc->owner, acc->balance);
}

int main()
{
    struct BankAccount acc;

    initAccount(&acc, "Ana", 1000);
    deposit(&acc, 200);
    withdraw(&acc, 500);

    printAccount(&acc);

    return 0;
}