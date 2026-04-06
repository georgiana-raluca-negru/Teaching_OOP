# Exception handling

În C++ avem mecanismului de excepții prin: `try`, `catch`, `throw`.

## Definirea propriilor exceptii

```cpp
class MyException {
protected:
    string msg;
public:
    MyException(const string& m) : msg(m) {}
    virtual void what() const { cout << msg << endl; }
};

class FileException : public MyException {
public:
    FileException(const string& m) : MyException(m) {}
};

class InvalidValueException : public MyException {
public:
    InvalidValueException(const string& m) : MyException(m) {}
};
```

Aruncarea unei exceptii:

```cpp
void openFile(const string& filename) {
    bool fileExists = false; // Simulare
    if (!fileExists) {
        throw FileException("Fisierul nu a fost gasit: " + filename);
    }
}
```

Prinderea unei exceptii:

```cpp
try {
    openFile("date.txt");
}
catch (FileException& fe) {
    cout << "Eroare fisier: ";
    fe.what();
}
catch (InvalidValueException& ive) {
    cout << "Valoare invalida: ";
    ive.what();
}
catch (MyException& e) {
    cout << "Eroare generala: ";
    e.what();
}
```

## std::exception

Documentatie `std:exception` [aici](https://en.cppreference.com/w/cpp/error/exception.html).

```cpp
class MyException : public std::exception {
protected:
    string msg;
public:
    MyException(const string& m) : msg(m) {}

    // Suprascriem metoda what() din std::exception
    virtual const char* what() const noexcept override {
        return msg.c_str();
    }
};
```

