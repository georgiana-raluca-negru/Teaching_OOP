# Gestiunea Exceptiilor in Limbajul C++: Principii si Mecanisme Fundamentale

## 1. Arhitectura Mecanismului de Exceptii

In limbajul C++, gestiunea exceptiilor se realizeaza prin intermediul a trei componente structurale:
- **Blocul `try`**: Delimiteaza sectiunea de cod in care pot aparea erori.
- **Instructiunea `throw`**: Semnaleaza aparitia unei conditii anormale prin aruncarea unui obiect de exceptie.
- **Blocul `catch`**: Prinde si proceseaza exceptiile de un anumit tip.

## 2. Ordinea de Interceptare (The Catch Order)

Un aspect critic in C++ este ordinea in care sunt evaluate blocurile `catch`. Compilatorul analizeaza clauzele de interceptare in ordine secventiala, de sus in jos.

### 2.1. Principiul Specificitatii
In cazul ierarhiilor de clase, este imperativ ca blocurile `catch` care vizeaza clasele derivate sa fie pozitionate inaintea celor care vizeaza clasele de baza.

```cpp
try {
    throw std::runtime_error("Eroare specifica");
} 
catch (const std::runtime_error& e) {
    // prinde tipul specific sau derivate din acesta
} 
catch (const std::exception& e) {
    // prinde tipul de baza (mai general)
}
catch (...) {
    // interceptor universal (catch-all) pentru orice tip de date
}
```
Daca ordinea ar fi inversata, blocul `catch (const std::exception&)` ar prinde orice obiect derivat (datorita polimorfismului), facand blocurile ulterioare inaccesibile (unreachable code).

## 3. Propagarea si Terminarea Executiei

### 3.1. Aruncarea unei exceptii in afara unui context `try`
Daca o exceptie este aruncata (prin `throw`) si nu exista niciun bloc `try-catch` activ in functia curenta sau in functiile apelante (pe stiva de apeluri), runtime-ul C++ va apela functia `std::terminate()`. Aceasta duce la oprirea imediata si anormala a programului.

### 3.2 Mecanismul de Stack Unwinding
In momentul aruncarii unei exceptii, sistemul de executie parcurge stiva de apeluri in sens invers pentru a gasi un bloc `catch` corespunzator. In acest proces, toate obiectele locale create intre punctul de `throw` si cel de `catch` sunt distruse prin apelarea destructorilor acestora. Acest proces garanteaza eliberarea resurselor, cu conditia ca destructorii sa nu genereze la randul lor exceptii.

## 4. Reguli Esentiale de Siguranta (Exception Safety)

### 4.1. Prinderea prin Referinta
Se recomanda prinderea exceptiilor prin referinta constanta (`const Type& e`) pentru a evita

- **Slicing**: Pierderea informatiei specifice clasei derivate daca obiectul este copiat intr-o instanta a clasei de baza.

- **Overhead**: Evitarea copierii inutile a obiectului de exceptie.

### 4.2 Exceptii in destructori

> Este interzisa propagarea unei exceptii in afara unui destructor. Daca o exceptie este aruncata in timpul procesului de 'stack unwinding' (cand o alta exceptie este deja activa), programul va apela instantaneu `std::terminate()`.

### 4.3. Specificatorul `noexcept`
Functiile care sunt garantate sa nu genereze exceptiipot fi marcate cu `noexcept`. Aceasta permite compilatorului sa optimizeze codul, eliminand structurile necesare pentru 'stack unwinding'.

## 5. Ierarhia Standard `std::exception`

Toate exceptiile definitite in biblioteca standard C++ deriva din clasa `std::exception`. Aceasta ofera metoda virtuala `what()`, care returneaza o descriere a erorii.

| Exceptie           | Context utilizare
| :---               | :---
| `std::bad_alloc`     | Esec la alocarea memoriei dinamice.
| `std::out_of_range`  | Accesarea unui index in afara limitelor unui container.
| `std::logic_error`   | Erori ce tin de logica programului, detectabile teoretic inainte de executie.
| `std::runtime_erorr` | Erori ce pot fi detectate doar in timpul executiei.