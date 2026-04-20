# Type Casting în C++

In C++, casting-ul se imparte in doua categorii: implicit (automat) si explicit (cerut de programator). Deci, cele mai importante sunt:

- **Upcasting**: Trecerea de la o clasa derivata la una de baza (este sigur pentru ca derivata poate fi vazuta,in esenta, drept baza).
- **Downcasting**: Trecerea de la o clasa de baza la una derivata (nesigur, necesita `dynamic_cast`).
- **C++ Casts**(`static`, `dynamic`, `const`, `reinterpret`): Inlocuiesc vechiul cast din C, oferind siguranta la compilare sau la executie.

## 1. Upcasting si Downcasting

Acestea sunt conceptele de bază în contextul moștenirii.

### 1.1. Upcasting
* **Ce este:** Conversia unui pointer sau a unei referinte de la o clasa derivata la o clasa de baza.
* **Siguranta:** Este intotdeauna sigur si se face implicit de catre compilator.
* **Utilizare:** Permite polimorfismul (tratarea obiectelor diferite printr-o interfata comuna).

```cpp
#include <iostream>

class Animal { 
    public: 
    virtual void sunet() { 
        std::cout << "Sunet generic"; 
    } 
};

class Caine : public Animal 
{ 
    public: 
    void sunet() override { 
        std::cout << "Ham!"; 
    } 
};

int main(){
    Caine rex;
    Animal* animalPtr = &rex; // upcasting implicit

    return 0;
}
```

### 2.1. Downcasting
* **Ce este**: Conversia de la o clasa de baza la o clasa derivata.

* **Siguranta**: Este riscant deoarece obiectul de baza ar putea sa nu fie de fapt tipul derivat dorit.

* **Utilizare**: Se face obligatoriu prin casting explicit, preferabil `dynamic_cast`.

```cpp
#include <iostream>

class Animal {
public:
    // functie viruala pentru a aputea avea polimorfism la runtime
    virtual ~Animal() {}
};

class Caine : public Animal {
public:
    void latra() { std::cout << "Ham!\n"; }
};

class Pisica : public Animal {
public:
    void miauna() { std::cout << "Miau!\n"; }
};

int main() {
    // upcasting implicit -> este sigur
    Animal* animalPtr = new Caine(); 

    // conversia va reusi intrucat animalPtr arata spre un Caine
    Caine* cainePtr = dynamic_cast<Caine*>(animaPtr);
    if (cainePtr) {
        cainePtr->latra(); 
    }

    // aiai dynamic_cast va returna nullptr, animalPtr nu pointeaza
    //catre o pisica
    Pisica* pisicaPtr = dynamic_cast<Pisica*>(animalPtr);
    if (pisicaPtr == nullptr) {
        std::cout << "Eroare la executie\n";
    }

    delete animalPtr;
    return 0;
}
```

## 2. Operatorii de Casting Specifici C++
În C++, folosirea cast-ului de tip C (tip)valoare este descurajată în favoarea celor patru operatori specifici.

### 2.1. `static_cast`
* **Utilizare**: Conversii intre tipuri inrudite (ex: int la float) sau upcasting/downcasting simplu fara verificari la runtime.

> !! Se foloseste cand se stie sigur ca tipurile sunt compatibile (la compilare), intrucat nu se fac verificari la executie.


```cpp
#include <iostream>

class Vehicul {
public:
    virtual ~Vehicul() {}
};

class Masina : public Vehicul {
public:
    void claxoneaza() { std::cout << "Tit tiiit!\n"; }
};

class Bicicleta : public Vehicul {
public:
    void sunaClopotel() { std::cout << "Ding ding!\n"; }
};

int main() {
    // upcasting implicit (-> este sigur
    Vehicul* vehiculPtr = new Masina();

    // conversia se realizeaza la compilare, nu executie 
    // prin urmare functia va fi apelata cu succes
    Masina* masinaPtr = static_cast<Masina*>(vehiculPtr);
    masinaPtr->claxoneaza(); 

    
    Bicicleta* bicicletaPtr = static_cast<Bicicleta>(vehiculPtr);
    
    // bicicletaPtr NU va fi nullptr! 
    // va conține o adresa de memorie, dar pe care programul o va interpreta gresit ca fiind o Bicicleta.
    
    if (bicicletaPtr != nullptr) {
        std::cout << "Conversia a 'reusit' (aparent) cu static_cast!\n";
        
        // bicicletaPtr->sunaClopotel -> vom avea comportament nedefinit, nu stim ce se intampla
    }

    delete vehiculPtr;
    return 0;
}
```

### 2.2 `const_cast`

Rolul sau exclusiv este de a **elimina sau adauga modificatorul** `const`. Este folosit cel mai des atunci cand avem cod "legacy" (vechi) din C, unde functiile nu au fost scrise folosind `const` pentru parametri, chiar daca nu modifica datele.

> Folosirea `const_cast` pentru a modifica efectiv o variabila care a fost declarată initial constanta duce la un **comportament nedefinit** (undefined behavior).

```cpp
#include <iostream>

void afiseazaMesaj(char* text) {
    std::cout << "Mesaj: " << text << "\n";
}

int main() {
    const char* salut = "Salutare, lume!";

    // afiseazaMesaj(salut); 
    // eroare de compilare -> nu se poate trimite direct const char* unei funcții ce cere char*

    // cast away constness
    afiseazaMesaj(const_cast<char*>(salut)); 

    return 0;
}
```

More on [`const_cast`](https://en.cppreference.com/cpp/language/const_cast)

### 2.3. `reinterpret_cast`
* **Utilizare**: Conversii low level intre tipuri complet neinrudite (ex: un pointer la un intreg).

> Este periculos si depinde de arhitectura hardware. Se foloseste rar, de obicei in drivere sau optimizari extreme.

## 3. RTTI (Run-Time Type Information) si `typeid`

Pentru a identifica tipul real al unui obiect la executie, C++ ofera operatorul `typeid`.

```cpp
#include <iostream>
#include <typeinfo> 

class Animal {
public:
    virtual ~Animal() {} 
};

class Caine : public Animal {};

class Fruct {};

class Mar : public Fruct {};


int main() {
    // test pe clasa poilmorfica
    Animal* animalPtr = new Caine();
    
    // folosim dereferentierea (*animalPtr) pentru a verifica obiectul, nu pointerul
    if (typeid(*animalPtr) == typeid(Caine)) {
        std::cout << "Obiectul este cu adevarat un Caine.\n";
    }
    
    std::cout << "Numele real al tipului: " << typeid(*animalPtr).name() << "\n\n";


    // test pe clasa care nue ste polimorfica
    Fruct* fructPtr = new Mar();

    // clasa nu este polimorfica -> compilatorul se uita doar la tipul pointerului
    if (typeid(*fructPtr) == typeid(Mar)) {
        std::cout << "Acest text NU se va afisa.\n";
    } 
    else if (typeid(*fructPtr) == typeid(Fruct)) {
        std::cout << "Programul crede ca este doar un Fruct (tipul static).\n";
    }

    delete animalPtr;
    delete fructPtr;
    return 0;
}
```

> Pointeri vs. Obiecte: cu `typeid(animalPtr)` se afla tipul pointerului (care va fi mereu `Animal*`). Pentru a verifica ce este inauntru, trebuie dereferentiat: `typeid(*animalPtr)`.

> Comparația cu == este sigură: numele returnat de `.name()`variaza de la un compilator la altul. Nu se fac comparatii de genul `if (typeid(x).name() == "Caine")`. Se va comparatia directa a tipurilor: `if (typeid(x) == typeid(Caine))`.