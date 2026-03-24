#include <iostream>
using namespace std;

class Complex
{
private:
    double real, imag;

public:
    // Constructor
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}

    // Copy constructor (optional, default works)
    Complex(const Complex &c) = default;

    // ----------------- Arithmetic Operators -----------------
    // Complex + Complex
    Complex operator+(const Complex &c) const
    {
        return Complex(real + c.real, imag + c.imag);
    }

    // Complex - Complex
    Complex operator-(const Complex &c) const
    {
        return Complex(real - c.real, imag - c.imag);
    }

    // Complex * Complex
    Complex operator*(const Complex &c) const
    {
        return Complex(real * c.real - imag * c.imag,
                       real * c.imag + imag * c.real);
    }

    // Complex / Complex
    Complex operator/(const Complex &c) const
    {
        double denom = c.real * c.real + c.imag * c.imag;
        return Complex((real * c.real + imag * c.imag) / denom,
                       (imag * c.real - real * c.imag) / denom);
    }

    // ----------------- Arithmetic with int -----------------
    Complex operator+(int val) const { return Complex(real + val, imag); }
    Complex operator-(int val) const { return Complex(real - val, imag); }
    Complex operator*(int val) const { return Complex(real * val, imag * val); }
    Complex operator/(int val) const { return Complex(real / val, imag / val); }

    // Non-member to allow int + Complex
    friend Complex operator+(int val, const Complex &c) { return Complex(c.real + val, c.imag); }
    friend Complex operator-(int val, const Complex &c) { return Complex(val - c.real, -c.imag); }
    friend Complex operator*(int val, const Complex &c) { return Complex(c.real * val, c.imag * val); }
    friend Complex operator/(int val, const Complex &c)
    {
        double denom = c.real * c.real + c.imag * c.imag;
        return Complex((val * c.real) / denom, (-val * c.imag) / denom);
    }

    // ----------------- Unary Operators -----------------
    Complex operator-() const { return Complex(-real, -imag); }

    // ----------------- Increment / Decrement -----------------
    Complex &operator++()
    {
        ++real;
        return *this;
    } // prefix
    Complex operator++(int)
    {
        Complex temp = *this;
        ++real;
        return temp;
    } // postfix
    Complex &operator--()
    {
        --real;
        return *this;
    }
    Complex operator--(int)
    {
        Complex temp = *this;
        --real;
        return temp;
    }

    // ----------------- Comparison -----------------
    bool operator==(const Complex &c) const { return real == c.real && imag == c.imag; }
    bool operator!=(const Complex &c) const { return !(*this == c); }

    // ----------------- Stream Operators -----------------
    friend ostream &operator<<(ostream &out, const Complex &c)
    {
        out << c.real;
        if (c.imag >= 0)
            out << "+";
        out << c.imag << "i";
        return out;
    }

    friend istream &operator>>(istream &in, Complex &c)
    {
        cout << "Enter real: ";
        in >> c.real;
        cout << "Enter imag: ";
        in >> c.imag;
        return in;
    }

    // ----------------- Getter Functions (optional) -----------------
    double getReal() const { return real; }
    double getImag() const { return imag; }
};

int main()
{
    Complex c1(2, 3), c2(1, -4);

    Complex sum = c1 + c2;
    Complex diff = c1 - c2;
    Complex prod = c1 * c2;
    Complex quot = c1 / c2;

    cout << "c1: " << c1 << "\n";
    cout << "c2: " << c2 << "\n";
    cout << "Sum: " << sum << "\n";
    cout << "Difference: " << diff << "\n";
    cout << "Product: " << prod << "\n";
    cout << "Quotient: " << quot << "\n";

    cout << "c1 + 5 = " << c1 + 5 << "\n";
    cout << "10 + c2 = " << 10 + c2 << "\n";

    ++c1;
    cout << "After prefix ++c1: " << c1 << "\n";
    c2--;
    cout << "After postfix c2--: " << c2 << "\n";

    if (c1 != c2)
        cout << "c1 and c2 are not equal\n";
    else
        cout << "c1 and c2 are equal\n";

    Complex inputC;
    cin >> inputC;
    cout << "You entered: " << inputC << "\n";

    return 0;
}