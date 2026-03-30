# Functiile Virtuale si Polimorfismul la executie în C++

## 1. Polimorfism: compilare vs executie
Polimorfismul permite ca o singura interfața sa reprezinte tipuri diferite. In C++, acesta se imparte in doua mari categorii:

* **La compilare (Static / Early Binding):** decizia despre ce functie va fi apelata este luata de compilator inainte ca programul sa ruleze (function overloading & templates)
* **La executie (Dinamic / Late Binding):** decizia este amanata pana cand programul ruleaza. Se bazeaza pe tipul *real* al obiectului din memorie, nu pe tipul variabilei care il stocheaza -> **functii virtuale**.

---

## 2. Upcasting
>**Un pointer sau o referinta de tipul clasei de baza poate stoca/indica spre un obiect al clasei derivate.** Acest proces se numește `Upcasting`.

```cpp
class Animal {
public:
    void sunet() { cout << "animal\n"; }
};

class Caine : public Animal {
public:
    void sunet() { cout << "caine\n"; }
};

int main() {
    Caine Rex;
    Animal* ptrAnimal = &Rex; //upcasting ( pointer de tip baza indica catre un obiect derivat)
    
    ptrAnimal->sunet();
    //se afiseaza "animal"
    return 0;
}
```

Deși pointerul `ptrAnimal` arata spre un obiect de tip `Caine`, compilatorul se uita doar la tipul pointerului (`Animal*`) si face legatura (**Early Binding**) cu functia din clasa de baza. Aici intervine `virtual`.

## 3. Cuvantul cheie `virtual`
Cuvantul cheie `virtual` este pus în fata unei functii din clasa de baza pentru a-i spune compilatorului sa verifice abia le executie ce tip de obiect se afla, in realitate, la acea adresa de memorie.

Daca modificam exemplul anterior:
```cpp
class Animal {
public:
    //acum functia este declarata ca fiidn virtuala 
    virtual void sunet() { cout << "animal\n"; }
};

class Caine : public Animal {
public:
    void sunet() { cout << "caine\n"; }
};

int main() {
    Caine Rex;
    Animal* ptrAnimal = &Rex; 
    
    ptrAnimal->sunet(); 
    //se face late binding -> se afiseaza "caine"
    return 0;
}
```

>Folosim `virtual` ori de cate ori anticipam ca o metoda din clasa de baza va trebui **suprascrisa (overridden)** în clasele derivate, iar interactiunea cu acele obiecte se face prin intermediul pointerilor/referintelor la clasa de baza.

## 4. Early Binding vs Late Binding

| Caracteristică | Early Binding  | Late Binding  |
| :--- | :--- | :--- |
| **Momentul asocierii apelului** | la momentul compilarii (*compile-time*) | in timpul executiei (*run-time*) |
| **Criteriul de decizie** | **tipul static** al variabilei (al pointerului sau referintei) | **tipul dinamic** (real) al obiectului instantiat în memorie |
| **Overhead** | executie foarte rapida (fara costuri de performanta suplimentare la rulare) | mai lenta |
| **Implementare specifică C++** | functii normale (non-virtuale), funcții supraincarcate (*overloading*), sabloane (*templates*) | functii declarate explicit cu modificatorul `virtual` in clasa de baza |

## 5. Reguli, restrictii pentru folosirea cuvantului cheie `virtual`

### 5.1. Destructor virtual
Daca se foloseste polimorfism (clasa respectiva contine cel putin o functie virtuala sau este menita sa fie moștenita) si un obiect derivat este sters folosind un pointer de baza, **destructorul clasei de baza trebuie sa fie obligatoriu** `virtual`. Altfel, se va apela doar destructorul bazei, iar partea specifica derivatei va ramane in memorie -> **Memory Leak**

Declararea destructorului ca `virtual` asigura polimorfismul la distrugere: se va apela intai destructorul derivatei (late binding), urmat automat de destructorul bazei.

```cpp
class Baza {
public:
    virtual ~Baza() { cout << "~Baza\n"; } 
};
```

### 5.2. Constructorii NU pot fi virtuali

De ce?  Apelurile virtuale (late binding) functioneaza pe baza unui pointer ascuns (`vptr`) care indica spre o tabela virtuala (`VTable`). Acest `vptr` este setat si configurat chiar *in timpul* executiei constructorului, deci nu putem folosi mecanism polimorfic inainte de a avea propriu zis infrastructura construita.

### 5.3. Tipuri de Retur Covariante (exceptia de la semnatura)
Regula generala dicteaza ca functia suprascrisa (*overridden*) din clasa derivata trebuie sa aiba **exact aceeasi semnatura** (nume, parametri, tip de retur) ca functia virtuala din clasa de baza. 

>Excpetie!!: tipurile de retur covariante.
Daca functia din clasa de baza returnează un **pointer sau o referinta** catre clasa de bază, functia suprascrisa din clasa derivata poate returna un pointer sau o referinta catre *clasa derivata*.

```cpp
class Baza {
public:
    virtual Baza* clone() const { 
        //copy constructor
        return new Baza(*this); 
    }
};

class Derivata : public Baza {
public:
    Derivata* clone() const override { 
        return new Derivata(*this); 
    }
};
```

### 5.4. Functiile virtuale NU pot fi Statice
O functie declarata `static` apartine clasei, nu unei instante (obiect) anume. In consecinta, functiile statice nu primesc pointerul implicit `this`.