#pragma once
#include <string>

class Complex
{
public:
    Complex() : Complex(0,0) {}
    Complex(double re, double im) : _re(re), _im(im) {}

    double getRe() const;
    double getIm() const;

    void setRe(double val);
    void setIm(double val);

    double abs() const;
    double absSquared() const;
    double phase() const;

    Complex add(const Complex& num) const;
    Complex sub(const Complex& num) const;
    Complex mul(const Complex& num) const;
    Complex div(const Complex& num) const;

    Complex operator+ (const Complex& num) const;
    Complex operator- (const Complex& num) const;
    Complex operator* (const Complex& num) const;
    Complex operator/ (const Complex& num) const;

    bool equals(const Complex& num) const;
    std::string format() const;

private:
    double _re;
    double _im;
};
