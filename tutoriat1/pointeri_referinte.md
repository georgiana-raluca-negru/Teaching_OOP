# Pointeri si Referinte in C++

Pointerii si referintele sunt mecanisme prin care putem accesa și manipula direct memoria calculatorului. Desi ambele permit modificarea datelor la care se "uita", ele functionează diferit in spate si au reguli de utilizare distincte.

---

## 1. Ce este un Pointer?

Un **pointer** este o variabila care stocheaza **adresa de memorie** a altei variabile, nu valoarea in sine. 
* Pentru a afla adresa unei variabile folosim operatorul `&` (address-of).
* Pentru a accesa sau modifica valoarea de la acea adresa folosim operatorul `*` (dereferențiere).

### Exemplu
```cpp
#include <iostream>
using namespace std;

int main() {
    int x = 10;
    int* ptr = &x; // ptr va stoca adresa la care se afla x in memorie

    cout << "Valoarea lui x: " << x << endl;             
    cout << "Adresa lui x: " << &x << endl;              
    cout << "Valoarea stocata in ptr: " << ptr << endl; 
    
    // dereferentiere (modificam valoarea de la adresa pe care o retine ptr)
    *ptr = 20; 
    cout << "Noua valoare a lui x: " << x << endl;       
    
    return 0;
}
```

### Output
```
Valoarea lui x: 10
Adresa lui x: 0x7ffeeb42 (de ex)
Valoarea stocata in ptr: 0x7ffeeb42
Noua valoare a lui x: 20
```

## 2. Ce este o Referinta?
O **referinta** este un **alias** (un alt nume) pentru o variabila deja existenta. Odată ce o referinta este legata de o variabila, orice operatiune facuta asupra referintei se aplica direct variabilei originale. Nu are o adresa de memorie proprie, ci imparte aceeasi zona de memorie cu variabila originala.

### Exemplu

```cpp
#include <iostream>
using namespace std;

int main() {
    int y = 50;
    int& ref = y; // ref este un alias pentru y

    ref = 100;    // modificam ref, ceea ce modifica automat si y
    
    cout << "Valoarea lui y: " << y << endl;     
    cout << "Valoarea lui ref: " << ref << endl; 
    
    return 0;
}
```

### Output
```
Valoarea lui y: 100
Valoarea lui ref: 100
```

## 3. Pointeri vs. Referinte

| Caracteristica | Pointer (`*`) | Referinta (`&`) |
| :--- | :--- | :--- |
| **Inițializare** | Poate fi lasat neinitializat la declarare. | **Trebuie neaparat** initializata la declarare. |
| **Reatribuire** | Poate fi reatribuit pentru a indica spre alta variabilă. | **Nu poate fi reatribuita.** Ramane legata de variabila initiala pana la terminarea programului. |
| **Valoare Nula** | Poate fi `nullptr` (nu indica spre nimic). | Nu poate fi nula (trebuie să refere ceva existent). |
| **Aritmetica** | Suporta operatii matematice (`p++`, `p + 2`). | Nu suporta aritmetica. |
| **Memorie**| Are propria sa adresa de memorie pe stack. | Imparte adresa cu variabila originala. |
| **Sintaxă** | Necesită dereferențiere (`*p`) pentru a accesa valoarea. | Se folosește direct, la fel ca o variabilă normală. |


## 4. Aritmetica Pointerilor

Deoarece pointerii stochează adrese (numere care reprezintă locații în memorie), putem face matematică cu ei. 

> **Important: adunare/scadere cu un numar:** Cand se aduna sau scade `1` dintr-un pointer, adresa nu se modifică cu 1 byte, ci cu `sizeof(tipul_de_data)`. De exemplu, pentru un pointer la `int` (care ocupa 4 bytes), `ptr + 1` va muta adresa cu 4 bytes mai departe.

> **Important: scăderea a doi pointeri:** Daca se  scad doi pointeri de acelasi tip (`ptr2 - ptr1`), rezultatul **NU** este o adresa de memorie, ci un **numar intreg**. Acesta reprezinta distanta dintre cei doi pointeri, masurata in numarul de elemente de acel tip.

### Exemplu
```cpp
#include <iostream>
using namespace std;

int main() {
    int numere[5] = {10, 20, 30, 40, 50};
    
    int* p_start = numere;      // p_start si numele vor pointa catre inceputul tabloului 
    int* p_urmator = p_start + 1; // ne mutam 4 bytes fata de adresa primului element -> ajungem la cel de-al doilea
    
    cout << "Primul element: " << *p_start << endl;      
    cout << "Urmatorul element: " << *p_urmator << endl;  
    
    int* p_final = &numere[4];  // retinem adresa celui de-al patrulea element
    // numere[4] = *(numere + 4)
    
    int distanta = p_final - p_start; 
    
    cout << "Distanta in elemente: " << distanta << endl; 
    
    return 0;
}
```

### Output
```
Primul element: 10
Urmatorul element: 20
Distanta in elemente: 4
```

## 5. Pointeri Constanti (The `const` Keyword)

### 5.1. Pointer catre o valoare Constanta
Nu se poate modifica valoarea **strict** prin pointer, dar se poate muta pointerul.

```cpp
int a = 10;
int b = 20;
const int* p1 = &a; 
// echivalent 
//int const* p1 = &a;

// *p1 = 15;     //EROARE: nu se poate modifica valoarea prin pointer
a = 15;          // CORECT: nu pot modifica valoarea prin pointer, dar prin variabila pot
p1 = &b;         // CORECT: pot muta pointerul
```

### 5.2. Pointer Constant
Se poate modifica valoarea prin pointer, **DAR** nu se poate muta pointerul astfel incat sa arate spre alta zona de memorie.

```cpp
int c = 30;
int d = 40;
int* const p2 = &c; 

*p2 = 35;       // CORECT: pot modifica valoarea spre care arata
// p2 = &d;     // EROARE: nu pot muta pointerul la o alta adresa
```

### 5.3. Pointer Constant catre o Constanta
Nu se poate modifica nici adresa pointerului, nici valoarea de la adresa respectiva.

```cpp
int e = 50;
const int* const p3 = &e;
e = 6;         // CORECT: nu modific prin p3
// *p3 = 6;    //EROARE
```

> **Important:** Un pointer non-constant **NU** poate stoca adresa unei variabile constante. Cand se declara o variabila ca fiind `const`,compilatorului garanteze ca valoarea ei nu va fi modificata niciodata. Dacă C++ ar permite legarea un pointer normal (non-const) la acea variabila, s-ar crea un ,,backdoor" prin care s-ar putea modifica valoarea folosind dereferențierea (`*ptr = noua_valoare`).

```cpp

#include <iostream>
using namespace std;

int main() {
    const int x= 1234; 
    // int* ptr = x ;              //  EROARE: invalid conversion from 'const int*' to 'int*'.

    const int* ptr_const = &x;     // CORECT
    
    // *ptr_const = 9999;          // EROARE: assignment of read-only location
    return 0;
}
```