# Gestiunea Obiectelor: Parametri & Tipuri de Retur

In programarea orientata pe obiecte, modul in care transmitem obiectele catre functii si modul in care le returnam are un impact masiv atat asupra **performanței** ( copierilor inutile de memorie), cat si asupra **corectitudinii** programului (polimorfism, gestiunea memoriei).

Sunt trei moduri principale de a transmite sau returna un obiect: **prin valoare**, **prin referinta** si **prin pointer** (mai rar folosit direct pentru retur, similar cu referinta).

## 1. Transmiterea Parametrilor catre Functii

### 1.1 **Prin Valoare** (`Pass by Value`)

-  Se creeaza o copie **independenta** a obiectului original. Functia lucreaza exclusiv cu aceasta clona locala

- Compilatorul apeleaza **Constructorul de Copiere** (`Copy Constructor`) pentru a crea clona. La finalul functiei, se apeleaza **Destructorul** pentru aceasta copie temporara

> **Atentie la Object Slicing!!**    
Daca transmitem, _prin valoare_, un obiect derivat unei functii care asteapta un obiect de baza, partea specifica clasei derivate este "taiata" (`sliced`) si pierduta.

```cpp
#include <iostream>

class Animal {
public:
    virtual void sunet() const { std::cout << "Sunet generic de animal\n"; }
    virtual ~Animal() {}
};

class Caine : public Animal {
public:
    void sunet() const override { std::cout << "Ham!\n"; }
};

void f(Animal a) {
    a.sunet();
}

int main() {
    Caine rex;
    f(rex); 
    
    return 0;
}
```

### Output
```
Sunet generic de animal
```

### De ce?

- Transmiterea prin valoare implica crearea unei noi instante -> **Costructorului de Copiere**

- Semnatura functiei solicita un parametru de tip `Animal`, deci compilatorul va apela constructorul de copiere al clasei de baza: `Animal(const Animal& other)`

- Constructorul este programat sa identifice si sa transcrie **doar** atributele specifice clasei de baza. In consecinta, procesul de transcriere preia doar segmentul superior al memoriei `(partea de baza)` si ignora complet datele aditionale, rezultand astfel „taierea” acestora


### 1.2. **Prin Referinta** (`Pass by Reference`)

- Functia preia un alias (o adresa directa) catre instanta originala din memorie

- Procesul exclude apelarea constructorului de copiere, deci orice alterare a starii obiectului in interiorul metodei **se va reflecta permanent in instanta originala**

- Se utilizeaza cand scopul arhitectural al functiei este de a actiona direct asupra starii obiectului primit

### 1.3 **Prin Referinta Constanta**(`Pass by Const Reference`)

- Se transmite referinta obiectului, alaturi de constrangerea imuabilitatii lui in cadrul functiei apelate

- Abordarea imbina optimizarea performantei referintei (eliminarea copierii de memorie) cu siguranța transmiterii prin const (obiectul original deivine _read-only_)

```cpp
#include <iostream>
#include <string>

class Student {
private:
    std::string nume;
public:
    Student(const std::string& nume) : nume(nume) {}
    std::string getNume() const { return nume; }
    void setNume(std::string nume) { this.nume = nume; }
};

void afisare(const Student& s) {
    std::cout << "Nume student: " << s.getNume() << "\n";
}

void actualizeaza(Student& s, const std::string& numeNou) {
    s.setNume(numeNou);
}
```

## 2. Tipuri de retur

### 2.2 **Returnarea prin Valoare**(`Return by Value`)

- Functia returneaza o instanta complet noua in spatiul de memorie apelant

- Rezultatul generat este clasificat de atre compilator drept un **obiect temporar** (`rvalue`). Un astfel de obiect nu poseda o adresa de memorie permanenta si identificabila, deci ciclul sau de viata se rezuma la **evaluarea expresiei in care a fost creat**

### Utilizarea obiectelor temporare ca parametri pentru alte functii

#### 1. **Interziza** asocierea cu o `Referinta Non-const`

> Un obiect temporar **nu poate** fi transmis ca parametru unei functii care solicita o referinta non-constanta (`lvalue reference`).

### De ce?

- O referinta non-const indica intentia functiei de a modifica obiectul

- Totusi, obiectul este temporar, deci el **va fi distrus imediat dupa terminarea instructiunii curente**

- Compilatorul va genera o eroare de compilare din start

#### 2. **Permisa** asocierea cu o `Referinta Constanta`

> Un obiect temporar **poate** fi transmis in siguranta unei functii care solicită o referinta constanta (`const lvalue reference`).

### De ce?

- Cand un obiect temporar este legat de o referinta constanta, compilatorul prelungeste automat ciclul de viata al acelui obiect **pana cand referinta insasi iese din domeniul de vizibilitate** (_scope_)

## 2.3. **Returnarea prin Referinta** (`Return by Reference`)

- Se returneaza o adresa catre un obiect _deja existent_. Procesul exclude generarea de obiecte temporare sau executarea operațiunilor de copiere

- Utilizare in contextul supraincarcarii operatorilor (`operator=` sau `operator<<`), cu scopul de a facilita **înlănțuirea operațiunilor** (chaining)

```cpp
class Numar {
private:
    int val;
public:
    Numar(int val) : valoare(val) {}

    Numar& operator=(const Numar& other) {
        if (this != &other) {
            this->val = other.val;
        }
        return *this; 
    }
};

int main() {
    Numar a(1), b(2), c(3);
    a = b = c; 
    return 0;
}
```

## 3. Problema `Dangling Reference`

> Este **interzisa** returnarea unei referinte (sau a unui pointer) care indica spre o variabilă locala, instantiata in cadrul stivei functiei curente.

### De ce?

- Variabilele locale sunt distruse automat si memoria lor este eliberata la finalizarea executiei functiei

- Daca se returneaza o referinta catre o astfel de entitate, contextul apelant intra in posesia unei referinte catre o zona de memorie nealocata si invalida -> _Segmentation Fault_


















