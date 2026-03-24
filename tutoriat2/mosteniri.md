# Mosteniri

Mecanismul prin care o clasa poate prelua membrii ai altei clase. Mostenirea permite reutilizarea codului.

Principii OOP relevante:
- **reutilizare cod** = putem folosi functionalitati fara sa le rescriem

- **polimorfism** = o clasa derivata poate sa fie trata ca o clasa de baza si invers.

Sintaxa de baza:
```cpp
class Base {
public:
    void greet() { std::cout << "Hello from Base\n"; }
};

class Derived : public Base {
    // mosteneste greet() de la Base
};

int main() {
    Derived d;
    d.greet();  // Hello from Base
}
```

## Tipuri de mostenire
- **public**: 
    - Membrii public raman public
    - Membrii protected raman protected
    - Membrii private raman private
- **protected**
    - Membrii publici devin protected
    - Membrii protected raman protected
    - Membrii private devin private
- **private**:
    - Membri publici devin private
    - Membrii protected devin private
    - Membrii private raman private

Exemplu:
```cpp
class Base {
public:
    int pub = 1;
protected:
    int prot = 2;
private:
    int priv = 3;
};

class Derived1 : public Base {
    // pub = public, prot = protected, priv = inaccesibil
};

class Derived2 : protected Base {
    // pub = protected, prot = protected, priv = inaccesibil
};

class Derived3 : private Base {
    // pub = private, prot = private, priv = inaccesibil
};

```

## Mostenire multipla si diamant
```cpp
class A { public: void showA() { std::cout << "A\n"; } };
class B { public: void showB() { std::cout << "B\n"; } };

class C : public A, public B {};

int main() {
    C obj;
    obj.showA();
    obj.showB();
}
```

> Daca mai multe clase au membrii cu aceeasi nume, vom avea ambiguitati si se folosesc specificatori de acces: `A::member` pentru a clarifica.

Daca clasele au acelasi membru putem folosi keyword-ul `virtual` pentru a evita duplicarea:

```cpp

// The diamond: 

class A { };
class B : virtual public A { };
class C : virtual public A { };
class D : public B, public C { };
```

