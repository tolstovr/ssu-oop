#include <iostream>
#include <cmath>
#include <iomanip>
#include <stdexcept>

#include "custstl.cpp"

using namespace std;

typedef long double ld;

class Complex {
private:
    ld real;
    ld imag;

public:
    Complex() : real(0), imag(0) {}
    Complex(ld r, ld i) : real(r), imag(i) {}

    ld getReal() const {
        return real;
    }

    ld getImag() const {
        return imag;
    }

    Complex operator+(const Complex& other) const {
        return Complex(getReal() + other.getReal(), getImag() + other.getImag());
    }

    Complex operator-(const Complex& other) const {
        return Complex(getReal() - other.getReal(), getImag() - other.getImag());
    }

    Complex operator*(const Complex& other) const {
        return Complex(getReal() * other.getReal() - getImag() * other.getImag(),
                       getReal() * other.getImag() + getImag() * other.getReal());
    }

    Complex operator/(const Complex& other) const {
        ld denominator = other.getReal() * other.getReal() + other.getImag() * other.getImag();
        if (denominator == 0) {
            throw invalid_argument("Division by zero");
        }
        return Complex((getReal() * other.getReal() + getImag() * other.getImag()) / denominator,
                       (getImag() * other.getReal() - getReal() * other.getImag()) / denominator);
    }

    ld modulus() const {
        return sqrt(getReal() * getReal() + getImag() * getImag());
    }

    bool operator<(const Complex& other) const {
        return modulus() < other.modulus();
    }

    bool operator>(const Complex& other) const {
        return modulus() > other.modulus();
    }

    bool operator==(const Complex& other) const {
        return getReal() == other.getReal() && getImag() == other.getImag();
    }

    void print() const {
        cout << fixed << setprecision(2);
        if (getImag() >= 0)
            cout << getReal() << " + " << getImag() << "i";
        else
            cout << getReal() << " - " << -getImag() << "i";
        cout << endl;
    }

    friend ostream& operator<<(ostream& os, const Complex& complex);
};

ostream& operator<<(ostream& os, const Complex& complex) {
    os << fixed << setprecision(2);
    if (complex.getImag() >= 0)
        os << complex.getReal() << " + " << complex.getImag() << "i";
    else
        os << complex.getReal() << " - " << -complex.getImag() << "i";
    
    return os;
}

int main() {
    ld real, imag;

    cout << "Input real and imaginary part of complex: ";
    cin >> real >> imag;
    Complex complex1(real, imag);

    cout << "Input real and imaginary part of another complex: ";
    cin >> real >> imag;
    Complex complex2(real, imag);

    cout << "Complex1: " << complex1 << endl;
    cout << "Complex2: " << complex2 << endl;

    cout << "Sum: " << (complex1 + complex2) << endl;
    cout << "Diff: " << (complex1 - complex2) << endl;
    cout << "Mult: " << (complex1 * complex2) << endl;
    cout << "Div: " << (complex1 / complex2) << endl;
    cout << "Greater: " << (complex1 > complex2) << endl;
    cout << "Equals: " << (complex1 == complex2) << endl;
    cout << "Less: " << (complex1 < complex2) << endl;

    // ld real, imag;
    // cout << "Input number of complex: ";
    // size_t n;
    // cin >> n;

    // List<Complex> complexList;
    // for (size_t i = 0; i < n; ++i) {
    //     cout << "Input real and imaginary part of complex #" << i + 1 << ": ";
    //     cin >> real >> imag;
    //     complexList.add(Complex(real, imag));
    // }

    // complexList.print();

    return 0;
}