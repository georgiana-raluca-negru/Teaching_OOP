# Template-uri in C++

Pentru reutilizarea codului. In loc sa scrii aceeasi functie sau clasa de mai multe ori pentru tipuri de date diferite (int, float, double), scrii o singura data un "sablon" (template).

Compilatorul va lua acest sablon si va genera automat codul specific pentru tipul de date de care ai nevoie in programul tau.

## 1. Functii Template

Sa presupunem ca vrei o functie care sa iti returneze cel mai mare numar dintre doua valori. Fara template-uri, ar trebui sa scrii o functie pentru numere intregi, una pentru numere cu virgula, etc. Cu template-uri, rezolvi totul dintr-o lovitura.

```cpp
C++
#include <iostream>

// T este un inlocuitor (placeholder) pentru orice tip de date.
template <typename T>
T maxim(T a, T b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

int main() {
    // Aici compilatorul vede ca folosesti int si creeaza o functie maxim() speciala pentru int.
    std::cout << "Maximul dintre 10 si 20 este: " << maxim(10, 20) << "\n";

    // la fel
    std::cout << "Maximul dintre 3.14 si 2.71 este: " << maxim(3.14, 2.71) << "\n";
    return 0;
}
```

## 2. Clase Template


```bash
# include <iostream>
# include <string>

// Definim sablonul clasei
template <typename T>
class Cutie {
private:
    T continut; // Continutul va avea tipul de date 'T'

public:
    // Constructorul primeste o valoare de tipul 'T'
    Cutie(T valoare) {
        continut = valoare;
    }

    // O metoda care returneaza valoarea, tot de tipul 'T'
    T getContinut() {
        return continut;
    }
};

int main() {
    // Cand cream obiectul, trebuie sa spunem in unghiulare < > ce tip de date va tine

    // O cutie care pastreaza un numar intreg
    Cutie<int> cutieCuNumar(100);
    std::cout << "Cutia contine numarul: " << cutieCuNumar.getContinut() << "\n";

    // Aceeasi clasa, dar acum cutia pastreaza un text
    Cutie<std::string> cutieCuText("Salutari din cutie!");
    std::cout << "Cutia contine textul: " << cutieCuText.getContinut() << "\n";

    return 0;
}
```
Scrii mult mai putin cod: Nu te repeti. (Principiul de baza in programare numit DRY - Don't Repeat Yourself).


## Specializare
```cpp
// 1. Sablonul general (pentru 99% din cazuri)
template <typename T>
void afiseaza(T valoare) {
    std::cout << "Valoare normala: " << valoare << "\n";
}

// 2. Specializarea (exceptia doar pentru tipul 'bool')
template <>
void afiseaza(bool valoare) {
    // In loc de 0 si 1, vrem sa scrie "Adevarat" sau "Fals"
    if (valoare) {
        std::cout << "Valoare booleana: Adevarat\n";
    } else {
        std::cout << "Valoare booleana: Fals\n";
    }
}
```

## Alti parametrii in templates

```cpp
template <typename T, int NumarElemente>
class ArrayStatic {
private:
    // Cream un vector de tip T, de marime fixa
    T elemente[NumarElemente]; 

public:
    int getMarime() {
        return NumarElemente;
    }
};
```

# Cum functioneaza `std::vector`

- Alocat dinamic, gestioneaza o zona de memorie pe heap
- Are $O(1)$ acces, ca un vector din C
- Tine 3 pointeri (iteratori) in spate:
    - begin: catre primul element
    - end: catre ultimul element
    - end_of_storage: catre finalul blocului alocat
    
Un `std::vector` poate sa creasca in dimensiune prin realocare. Un `push_back` decurge astfel:
- Verifica capacitatea `size < capacity`
- Daca nu mai e loc, facem realocare. Aloca un bloc de memorie de 1.5x - 2x mai mare decat capacitatea curenta
- Muta elementele la zona noua alocata
- Dezaloca blocul de memorie

> Pentru ca realocarea se face destul de rar, avem $O(1)$ amortizat