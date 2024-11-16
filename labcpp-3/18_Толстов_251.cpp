#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <limits.h>

#include "custstl.cpp"

using namespace std;

typedef long double ld;

class Error {
public:
	virtual void print() {
        cerr << "Undefined error. This is default error message\n";
    }
};

class StringError : public Error {
    string str;
public:
	StringError(string s) : str(s) {
        print();
    }

	void print() {
        cerr << "Invalid string argument: " << str << '\n';
    }
};

class IntError : public Error {
    int num;
public:
    IntError() {
        print();
    }

    void print() {
        cerr << "Invalid integer argument: " << num << '\n';
    }
};

class LongDoubleError : public Error {
    long double num;
public:
    LongDoubleError() {
        print();
    }

    void print() {
        cerr << "Invalid long double argument: " << num << '\n';
    }
};

class SizeTError : public Error {
    size_t size;
public:
    SizeTError() {
        print();
    }

    void print() {
        cerr << "Invalid size_t argument: " << size << '\n';
    }
};

class MemoryError: public Error {
public:
    MemoryError() {
        print();
    }

    void print() {
        cerr << "Memory overflow error" << '\n';
    }
};

class FileError: public Error {
public:
    FileError() {
        print();
    }

    void print() {
        cerr << "File i/o error" << '\n';
    }
};

class Complex {
private:
    ld real;
    ld imag;

public:
    Complex() : real(0), imag(0) {}
    Complex(ld r, ld i) {
        if (r > numeric_limits<ld>::max()
            || r < numeric_limits<ld>::lowest()
            || i > numeric_limits<ld>::max()
            || i < numeric_limits<ld>::lowest()) {
            throw MemoryError();
        }
        
        real = r;
        imag = i;
    }

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

    cout << "Input number of complex: ";
    long long n; // since size_t is basically unsigned int, there's no way to apply to that negative value. That why I'm using a simple long long
    cin >> n;

    if (n <= 0) {
        throw SizeTError();
    }

    if (n > numeric_limits<long long>::max() || n < numeric_limits<long long>::lowest()) {
        throw MemoryError();
    }

    List<Complex> complexList;
    try {
        for (size_t i = 0; i < n; ++i) {
            cout << "Input real and imaginary part of complex #" << i + 1 << ": ";

            while (true) {
                cin >> real >> imag;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    throw LongDoubleError();
                } else {
                    break;
                }
            }

            complexList.add(Complex(real, imag));
        }
    } catch (const LongDoubleError&) {
        throw;
    }

    complexList.print(cout);

    ofstream outputFile;
    string filename;
    cout << "Output file: ";
    cin >> filename;

    try {
        outputFile.open(filename);
        complexList.print(outputFile);
    } catch (FileError) {
        throw FileError();
    }

    return 0;
}