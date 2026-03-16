# Supraincarcarea functiilor în C++ (Function Overloading)

**Supraincarcarea functiilor** este un concept fundamental in C++ care face parte din **polimorfismul la compilare (compile-time polymorphism)**. Acesta ne permite sa definim mai multe functii avand *acelasi nume* în acelasi domeniu de vizibilitate (scope), atata timp cat ele iau argumente diferite.

Avantajul principal este lizibilitatea codului: folosim acelasi nume (ex: `afiseaza`, `calculeaza`, `add`) pentru actiuni conceptual identice, dar care operează pe date diferite.

## Cum se face diferenta (criterii de departajare)

Pentru ca doua sau mai multe functii sa poată purta acelasi nume, compilatorul trebuie sa le poata distinge. Acest lucru se face prin **semnatura functiei**. Semnatura = numele functiei si lista de parametri.

-  **Numarul de parametri**
-  **Tipul parametrilor**
-  **Ordinea tipurilor parametrilor** 

##  Ce NU reprezinta un criteriu de departajare

> **Foarte important:** **Tipul returnat de functie** NU face parte din semnatura functiei, deci nu putem face overload bazat doar pe tipul de retur.

Nu se poate supraincarca două functii care au acelasi nume si aceiasi parametri, dar care returnează tipuri de date diferite. La apelul unei functii, compilatorul nu stie ce tip de retur te astepti sa primesti, prin urmare nu poate ghici ce functie ar trebui apelata.

## Cum se gestioneaza apelurile de functii 

Pasii de potrivire sunt verificati in urmatoarea ordine:
1.  **Potrivire exacta (Exact Match):** argumentele trimise corespund exact tipului parametrilor din definitie.
2.  **Promovarea tipurilor (Integral Promotion):** tipurile mai mici sunt promovate la tipuri mai mari (ex: `char` sau `short` -> `int`; `float` -> `double`).
3.  **Conversii standard:** daca nu s-a gasit o potrivire prin promovare, se aplica conversii standard.
4.  **Conversii definite de utilizator:** cand avem clase cu constructori sau operatori de conversie.


## Exemple practice

### Diferentiere prin tipul parametrilor

```cpp
#include <iostream>
using namespace std;

void afiseaza(int x) {
    cout << "am primit un intreg de valoare: " << x << endl;
}

void afiseaza(double x) {
    cout << "am primit un double de valoare: " << x << endl;
}


int main() {
    afiseaza(10);       //se potriveste exact pentru int       
    afiseaza(3.14);     // se potriveste exact pentru double 
    char litera = 'A';  // nu avem definita o functie care sa primesca ca si parametru un char
    afiseaza(litera);   // prin urmare char este promovat la int
    
    return 0;
}

```

### Output
```
am primit un intreg de valoare: 10
am primit un double de valoare: 3.14
am primit un intreg de valoare: 65
```

### Diferentiere prin numarul de parametri
```cpp
#include <iostream>
using namespace std;


int suma(int a, int b) {
    cout << "am primit doi parametri." << endl;
    return a + b;
}

int suma(int a, int b, int c) {
    cout << "am primit trei parametri." << endl;
    return a + b + c;
}


int main() {
    int rezultat1 = suma(10, 20);
    cout << rezultat1 << endl;

    int rezultat2 = suma(5, 10, 15);
    cout << rezultat2 << endl;

    return 0;
}
```

### Output
```
am primit doi parametri.
30
am primit trei parametri.
30
```

### Apel ambiguu generat de valori implicite (Default arguments)

> **Important:** Parametrii cu valoare implicita trebuiesc amplasati la finalul listei de argumente.

```cpp
#include <iostream>
using namespace std;

void afiseaza(int x) {
    cout << "am apelat functia cu un parametru:" << x << endl;
}

void afiseaza(int x, int y = 100) {
    cout << "am apelat functia cu doi parametri:" << x << " si " << y << endl;
}

int main() {
    afiseaza(5, 20); 
    // afiseaza(5); este un apel ambiguu, nu stie pe care din cele doua versiuni sa o apeleze

    return 0;
}
```

### Eroare de redefinire generata de tipul returnat

```cpp
int suma(int a, int b) {
    return a + b;
}

double suma(int a, int b) { 
    return (double)(a + b);
}

int main() {
    // suma(a, b) va genera eroare de compilare
    // tipul de retur nu este suficient pentru a face diferenta 
    return 0;
}
```

### Ambiguitate generata de Conversii Standard 

**Regula generală:** Cand compilatorul nu gaseste o potrivire exacta și nici o promovare, va incerca sa aplice **conversii standard**. Daca exista mai multe functii care pot accepta parametrul prin conversii standard diferite, apelul devine **ambiguu**. Compilatorul acorda aceeași "prioritate" tuturor conversiilor standard numerice.

```cpp
#include <iostream>
using namespace std;

void afiseazz(float x) {
    cout << "am primit un float." << endl;
}

void afiseaza(double x) {
    cout << "am primit un double" << endl;
}

int main() {
    int numar = 10;
    // calculeaza(numar); // EROARE: Call to 'calculeaza' is ambiguous

    //atat conversia de la int la float, cat si de la int la double se afla in aceeasi clasa de priorotati -> compilatorul nu stie ce conversie sa aplice
    
    // CUM REZOLVAM? 
    // trebuie sa fim expliciti prin casting:
    // afiseaza((float)numar);  // pentru apelul primei variante
    // calculeaza((double)numar); // pentru apelul celei de-a doua variante
    
    return 0;
}
```

## Alte capcane: Pointeri, Tablouri si Referinte

Pe langa ambiguitatile generate de parametrii impliciti, exista doua situatii speciale foarte frecvente care pot genera erori atunci cand incercam sa supraincarcam functii.

### Eroare de redefinire: Pointeri vs. Tablouri

```cpp
void f(int *p) {
    // ...
}

// EROARE: Redefinition of 'f'
// compilatorul vede exact aceeasi semnatura ca mai sus
void f(int p[]) { 
    // ...
}
```

### Trimitere prin Valoare vs. Trimitere prin Referrinta
```cpp
void f(int x) {
    cout << x << endl;
    
}

void f(int& x) {
    cout << x << endl;
}

int main() {
    int a = 10;
    // f(a); // EROARE: Call to 'f' is ambiguous
    //compilatorul nu face diferenta intre transmiterea parametrului prin valoare sau prin referinta
   
    return 0;
}
```





