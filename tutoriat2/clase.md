# Clase

In C++ folosim clasele pentru a crea propriile noastre tipuri de date abstracte.

La baza claselor stau doua principii OOP importante: 
- **abstractizare (data abstraction)** = separare intre interfata si implementare
- **incapsularea** = ascunderea implementarii unei clase, utilizatorii au acces la interfata, dar nu la implementarea din spate.

## Ce faceam in C pana acum? - Enum
Enum-ul reprezinta, asa cum ii spune numele, o enumerare. O multime fixa de valori. Toate valorile sunt defapt intregi 0, 1, 2, ..

```c
enum Day 
{
    MONDAY = 5, // putem sa renumerotam
    TUESDAY,
    WEDNESDAY
};

enum Day myDay = MONDAY;
```

Enum-ul exista si in C++ in forma asta, dar exista si Enum Class introdus in C++11.

```cpp
enum class Color {
    RED,
    GREEN
};

int x = Color::RED; // ok
int x = RED; // not ok


enum Color { RED, GREEN };
enum Status { OK, ERROR };

if (RED == OK) {}   // allowed

enum class Color { RED, GREEN };
enum class Status { OK, ERROR };

// if (Color::RED == Status::OK) {} // not allowed
```

## Ce faceam in C pana acum? - Struct

```c
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
```

Ce probleme sunt:
- Nu avem incapsulare: `acc.balance = -999999;`
- Functiile sunt separate, trebuie sa pasam `*acc` mereu


## Cum ne ajuta C++? - Clase
```cpp
class BankAccount
{
private:
    std::string owner;
    double balance;

public:
    BankAccount(std::string name, double initial)
    {
        owner = name;
        balance = initial;
    }

    void deposit(double amount)
    {
        balance += amount;
    }
};

```
Deci avem: incapsulare + date si functii grupate

## Diferentele intre clase si struct-uri in C++

In C++, struct-urile au fost extinse sa fie la fel de puternice ca si clasele, dar cu cateva diferente:
- In struct, atributele sunt `public` by default, iar in clasa sunt `private` by default 
- In struct, mostenirea este `public` by default, iar in clasa este `private` by default.
- Structurile se folosesc pentru: tipuri de date simple, logica minimala, etc. Clasele se folosesc pentru tipuri de date complexe unde datele trebuie ascunse, iar comportamentul este expus prin metode.


## Pointer-ul this

Functiile membre acceseaza obiectul prin care au fost apelate prin intermediul unui parametru implicit, pointerul `this`.

```cpp
int main()
{
    BankAccount acc("Alice", 1000);
    acc.deposit(200); // Compilatorul o transforma in BankAccount::deposit(&acc, 200);

    return 0;
}
```
```cpp
class BankAccount
{
private:
    std::string owner;
    double balance;

public:

    const std::string& getOwner() const
    {
        return this->owner;
    }

};
```

Observatie: Nu putem modifica valoare pointer-ului this. Este un pointer **const**.


## Specificatori de acces
In functie de ce vizibilitate(scope) vrem sa dam membrilor, avem diferiti specificatori de acces: `public`, `protected`, `private`.

Adica: 
- Membrii public sunt vizibili oriunde.
- Membrii protected sunt vizibili doar in clasele derivate.
- Membrii private nu sunt vizibili in clasele derivate.


```cpp
class BankAccount 
{
private:
    double balance;   // only accessible inside the class

protected:
    int accountId;    // accessible in derived classes

public:
    std::string owner;     // accessible from anywhere

}
```


## Constructori 

Fiecare clasa defineste cum obiectele sale trebuie instantiate. Constructorii sunt functii membre "speciale", adica:

- Sunt apelati automat cand obiectul e creat.
- Nu au return type.
- Trebuie sa aiba acelasi nume cu numele clasei.

```cpp
BankAccount(std::string name, double initial)
{
    owner = name;
    balance = initial;
}
```


Daca o clasa nu are un constructor definit, compilatorul foloseste un constructor special `default constructor`, care functioneaza in felul urmator:
- Foloseste valoarea de initializare din clasa (in-class initializer) 
- Foloseste valoarea default
```cpp
class BankAccount 
{
private:
    std::string name; // default
    double balance = 1000;   // in-class initializer
}
```

In C++ avem urmatorii constructori:
- Default
- Parametrizat
- Copy Constructor
- Move Constructor (din C++11)
- Explicit 
- *Delegating constructor

Pe langa constructori, clasa se ocupa si de **copierea**, **atribuirea** si **distrugerea** obiectelor.

Mai multe detalii despre constructori, destructori, operatori de atribuire, etc in tutoriatele viitoare.

# Friend 
Friend este un specificator care permite altor functii sau clase care nu sunt membre in clasa sa acceseze membrii ei non-publici.

Exemplu de functie friend:
```cpp
class MyClass {
private:
    int secret;
public:
    MyClass(int val) : secret(val) {}
    friend void showSecret(const MyClass& obj);
};

void showSecret(const MyClass& obj) {
    std::cout << obj.secret << std::endl; // ok
}
```


Exemplu de clasa friend:
```cpp
class B; // forward declaration

class A {
private:
    int data = 42;
    friend class B; // B poate accesa membrii privati
};

class B {
public:
    void showData(A& a) {
        std::cout << a.data << std::endl; // ok
    }
};
```

# Operatori
## Supraincarcarea Operatorilor

Exemplu: o clasa care implementeaza numerele complexe

Operatorii sunt functii:

Avem operatori:
- aritmetici
```cpp
// 1. Complex + Complex
Complex operator+(const Complex &c) const {
    return Complex(real + c.real, imag + c.imag);
}

// 2. Complex + int (member function: Complex on left)
Complex operator+(int val) const {
    return Complex(real + val, imag);
}

// Optional: friend function to allow int + Complex
friend Complex operator+(int val, const Complex &c) {
    return Complex(c.real + val, c.imag);
}
```
- relationali
```cpp
bool operator==(const Complex &c) const;
```
- de atribuire
- unari
```cpp
// unary
Complex operator-() const {
    return Complex(-real, -imag);
}
```
- stream insertion
```cpp
// my friends:
friend ostream& operator<<(ostream &out, const Complex &c);
friend istream& operator>>(istream &in, Complex &c);
```
- subscript 
```cpp
class MyArray {
    int data[10];
public:
    int& operator[](int index) { return data[index]; }
};
```
- function call
```cpp
class Adder {
public:
    int operator()(int a, int b) { return a + b; }
};
```
Supraincarcarea operatorilor face obiectul sa se comporte precum ar fi un tip de date obisnuit.


## Spaceship operator
https://en.cppreference.com/w/cpp/language/default_comparisons.html

Ofera un singur operator pentru a defini toate cele 6 comparatii (<, <=, >, >=, ==, !=).

```cpp
auto operator<=>(const ClassName&) const = default;
```


