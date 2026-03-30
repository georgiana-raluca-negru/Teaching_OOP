# Membri si functii `static` in C++

## 1. Ce face `static` intr-o clasa
In mod normal, la crearea obiectelor/instantelor dintr-o clasa, ele primesc propria lor copie a tuturor variabilelor membre. 

Cuvantul cheie `static` schimba aceasta regula: **un membru `static` apartine clasei in sine, nu instantelor clasei.** Indiferent de cate obiecte sunt create din acea clasă (chiar si niciunul), va exista **o singura copie** a membrului static in memorie, partajata de toate obiectele.

---

## 2. Variabile membre statice
O variabila statica este folosita pentru a stoca informatii la nivel de clasa (ex: un contor care tine evidenta numarului de obiecte create).

> Trebuie **declarate** in interiorul clasei si **definite** obligatoriu in afara clasei pentru a aloca memoria o singura data.

```cpp
class Jucator {
public:
    //declarare
    static int numarJuc; 

    Jucator() {
        numarJuc++; //incrementam la fiecare obiect nou creat
    }
};

//initializare in afara clasei
int Jucator::numarJuc = 0;
```

>Exceptie: incepand cu C++17, a fost introdus conceptul de `inline static`. Cu ajutorul cuvantului cheie inline **se poate initializa variabila statica direct in interiorul clasei**.

```cpp
class Jucator {
public:
    inline static int numarJuc = 0; 
};
```

## 3. Functii membre statice (metode statice)
O functie marcata cu `static` actioneaza la nivel de clasa. Pentru apel, nu este nevoie de existenta niciunei instante create; se poate apela direct folosind numele clasei si operatorul de rezolutie de scop (`::`).

```cpp
class Operatie {
public:
    static int adunare(int a, int b) {
        return a + b;
    }
};

int main(){

    int rezultat = Operatie::adunare(5, 10);

    return 0;
}

```

## 4. Ce NU poate face o functie statica

| Restrictie | De ce? |
| :--- | :--- |
| **Fara pointer `this`** | Functia apartine clasei (nu unui obiect specific), deci nu exista "acest obiect" (`this`). |
| **Nu poate accesa membri nestatici** | O funcție statica **nu poate citi sau modifica variabile normale** (nestatice) si **nu poate apela functii normale** din aceeasi clasa in mod direct. Are acces doar la alte variabile statice sau functii statice. |
| **Nu poate fi `virtual`** | Functiile `virtual` reprezinta mecanismul de baza al polimorfismului la executie, care depinde de tipul *obiectului* la runtime. Cum funcția statica nu este legata de nicio instanta, ea nu poate fi virtuala. |
| **Nu poate fi `const`** | Modificatorul `const` la finalul declaratiei unei functii garanteaza ca acea metoda nu va modifica starea obiectului pe care este apelata, dar functia statica nu actioneaza asupra unui obiect |

## 5. Mostenire + static

### 5.1. Membrii statici la mostenire
Daca clasa de baza are o variabila statica (vizibila, ie `protected` sau `public`), clasa derivata o mosteneste.

>Exista in continuare o singura copie in memorie! Clasa de baza si cea derivata impart exact aceeasi variabila.

```cpp
class Baza {
public:
    static int x;
};

int Baza::x = 0;

class Derivata : public Baza {
};

//Baza::x si Derivata::x reprezinta aceeasi adresa de memorie.
//Derivata::x = 5 ->  Baza::x va fi egal cu 5.
```

### 5.2 Functii statice la mostenire
Cum functiile statice nu pot fi `virtual`, **nu se poate face override** la o functie statica. Daca se defineste o functie statica in clasa derivata cu acelasi nume si semnatura ca una din clasa de baza, vom obtine **name hiding**.

```cpp
class Baza {
public:
    static void f() { cout << "Baza"; }
};

class Derivata : public Baza {
public:
    static void f() { cout << "Derivata"; } //name hiding in baza
};

int main(){

    Baza::f();     //Baza
    Derivata::f(); //Derivata

    return 0;
}
```

## 6. Best practices pentru static

- **Gestionarea starii globale a clasei**: contorizarea numarului de instante create
- **Clase de Utilitatii (Utility Classes)**: gruparea unor functii care nu au nevoie de stare
- **Design Pattern Singleton**: asigura ca o clasa are o singura instanta globala