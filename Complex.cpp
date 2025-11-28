#include <string>
#include <cmath>
#include <numbers>
#include <sstream>
#include "Complex.hpp"

double Complex::getRe() const {
    return _re;
}

double Complex::getIm() const {
    return _im;
}

void Complex::setRe(double re) {
    _re = re;
}

void Complex::setIm(double im) {
    _im = im;
}

double Complex::abs() const {
    return sqrt(_re*_re + _im*_im);
}

double Complex::absSquared() const {
    return _re*_re + _im*_im;
}

double Complex::phase() const {
    return atan2(_im, _re);
}

Complex Complex::add(const Complex& num) const {
    return Complex(_re + num._re, _im + num._im);
}

Complex Complex::sub(const Complex& num) const {
    return Complex(_re - num._re, _im - num._im);
}

Complex Complex::mul(const Complex& num) const {
    return Complex(_re*num._re - _im*num._im, _im*num._re + _re*num._im);
}

Complex Complex::div(const Complex& num) const {
    double den = num._re*num._re + num._im*num._im;
    return Complex( (_re*num._re + _im*num._im) / den , (_im*num._re - _re*num._im) / den );
}

Complex Complex::operator+(const Complex& num) const {
    return this->add(num);
}

Complex Complex::operator-(const Complex& num) const {
    return this->sub(num);
}

Complex Complex::operator*(const Complex& num) const {
    return this->mul(num);
}

Complex Complex::operator/(const Complex& num) const {
    return this->div(num);
}

bool Complex::equals(const Complex& num) const {
    return (_re == num._re && _im == num._im);
}

std::string Complex::format() const {
    std::stringstream s;
    s << _re << (_im >= 0 ? " + i" : " - i") << std::abs(_im);
    return s.str();
}
