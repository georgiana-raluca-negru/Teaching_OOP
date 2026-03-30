# Functiile Inline in C++

## 1. Ce este o functie `inline`
In C++, o functie `inline` este o cerere facuta compilatorului de a inlocui apelul functiei cu insusi corpul (codul) functiei in etapa de compilare. 

In general, la apelul unei functii, programul executa un salt la adresa de memorie unde se afla instructiunile functiei, salveaza starea curenta pe stiva si dupa terminare se intoarce la punctul de plecare. Acest proces necesita timp (overhead) -> functiile `inline` elimina acest lucru.

---

## 2. Implicit vs. Explicit in Clase

In ceea ce priveste programarea orientata pe obiecte,  functiile `inline` se pot defini in doua moduri:

### 2.1. Inline Implicit
Pentru o metoda definita direct **in interiorul corpului clasei**, compilatorul o va trata automat ca pe o functie `inline`. Nu este nevoie in mod explicit de cuvantul cheie `inline`.

```cpp
class Punct {
private:
    int x, y;
public:
    Punct(int x, int y) : x(x), y(y) {}

    // inline implicit - functia este definita in interiorul classei
    int getX() const { 
        return x; 
    }
};
```

### 2.2. Inline Explicit
Daca o functei este declarata in interiorul clasei, dar definita **in afara ei**, trebuie folosit explicit cuvantul cheie `inline` inainte de definirea functiei.

```cpp
class Punct {
private:
    int x, y;
public:
    Punct(int x, int y) : x(x), y(y) {}

    // aici doar declaratia
    int getY() const; 
};

// inline explicit - functia este definita in afara clasei
inline int Punct::getY() const {
    return y;
}
```

## 3. Pros & Cons


| Avantaje | Dezavantaje  |
| :--- | :--- |
| **Viteza mai mare de executie:** elimina timpul consumat cu apelul functiei (salvarea registrilor, plasarea argumentelor pe stiva, saltul la adresa). | **Dimensiunea executabilului :** daca o functie mare este marcata `inline` si apelata des, codul ei este duplicat, ducand la un executabil mult mai mare. |
| **Ideale pentru functii scurte:** funcții de tip *getter* sau *setter* si operatii matematice simple (1-3 linii). | **Timp de compilare mai lung:** modificarea unei functii `inline` dintr-un fisier header forteaza recompilarea tuturor fisierelor `.cpp` care includ acel header. |