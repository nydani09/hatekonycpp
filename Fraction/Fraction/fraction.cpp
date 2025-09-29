#include "fraction.h"
#include <stdexcept>
#include <numeric>
#include <iostream>
#include <string>

Fraction::Fraction(int wholeNumber) :
	numerator{wholeNumber},
	denominator{1}
{
}

Fraction::Fraction(int numerator, int denominator) :
	numerator{ numerator },
	denominator{ denominator }
{
	normalize();
}

Fraction::Fraction(double decFrac) 
{
	const int Precision = 1000000;
	numerator = static_cast<int>(decFrac * Precision+0.5);
	denominator = Precision;
	normalize();
}

Fraction::Fraction(const Fraction& other) : // A copy constructort írja itt felül, de az eleve kb. így működik. Nem értem, hogy mi indokolja a felülírást.
	numerator{ other.getNumerator() },
	denominator{ other.getDenominator() }
{
}


Fraction::Fraction():
	numerator{0},
	denominator{1}
{
}

void Fraction::normalize() {

	if (denominator == 0) {
		throw std::invalid_argument("A nevezõ nem lehet 0!");
	}

	if (denominator < 0) {
		numerator = -numerator;
		denominator = -denominator;
	}

	int g = std::gcd(numerator, denominator);

	numerator /= g;
	denominator /= g;
}

int Fraction::getNumerator() const{
	return numerator;
}

int Fraction::getDenominator() const {
	return denominator;
}

void Fraction::setNumerator(int num) { // Ha módosítható a számláló, akkor utána normalizálni kéne a törtet.
	numerator = num;
}

void Fraction::setDenominator(int den) { // Ha módosítható a nevező, akkor utána normalizálni kéne a törtet.
	denominator = den;
}

Fraction& Fraction::operator+=(const Fraction& other) {
	numerator = this->numerator * other.denominator + this->denominator * other.numerator;
	denominator = this->denominator * other.denominator;
	normalize();
	return *this;
}

Fraction& Fraction::operator-=(const Fraction& other) {
	numerator = this->numerator * other.denominator - this->denominator * other.numerator;
	denominator = this->denominator * other.denominator;
	normalize();
	return *this;
}

Fraction& Fraction::operator*=(const Fraction& other) {
	numerator *= other.numerator;
	denominator *= other.denominator;
	normalize();
	return *this;
}

Fraction& Fraction::operator/=(const Fraction& other) {
	if (other.numerator == 0)
		throw std::invalid_argument("0-val nem lehet osztani!");
	numerator *= other.denominator;
	denominator *= other.numerator;
	normalize();
	return *this;
}

Fraction operator+(Fraction lhs, const Fraction& rhs) { // Szép megoldás.
	lhs += rhs;
	return lhs;
}

Fraction operator-(Fraction lhs, const Fraction& rhs) {
	lhs -= rhs;
	return lhs;
}
Fraction operator*(Fraction lhs, const Fraction& rhs) {
	lhs *= rhs;
	return lhs;
}

Fraction operator/(Fraction lhs, const Fraction& rhs) {
	lhs /= rhs;
	return lhs;
}

void Fraction::print() const{ // Ez miért kell?
	if (denominator == 1)
		std::cout << numerator << std::endl;
	else
		std::cout << numerator << "/" << denominator << std::endl;
}

std::ostream& operator<<(std::ostream& outputStream, const Fraction& frac) {
	return outputStream << frac.getNumerator() << "/" << frac.getDenominator();
}

std::istream& operator>>(std::istream& inputStream, Fraction& frac) {
	char per;
	int n, d;

	if (inputStream >> n >> per >> d) {
		if (per != '/') {
			inputStream.setstate(std::ios::failbit);
		}
		else if (d == 0) {
			throw std::invalid_argument("A nevezõ nem lehet 0!");
		}
		else { // Én inkább létrehoznék egy új Fraction objektumot és azzal felülírnám a paraméterként átvett objektumot.
			frac.setNumerator(n);
			frac.setDenominator(d);
		}
	}
	return inputStream;
}

bool Fraction::operator==(const Fraction& other)  {
	return (numerator * other.denominator == denominator * other.numerator);
}
// Hiányolom a !=, <, <=, > és >= operátorokat.

Fraction::operator int() const {
	return numerator / denominator;
}

Fraction::operator double() const {
	return static_cast<double>(numerator) / denominator;
}

Fraction::operator bool() const {
	return numerator != 0;
}

Fraction::operator std::string() const { // Ha van ilyen operátor, akkor az std::ostream-re írást is lehetne erre építeni.
	if (denominator == 1)
		return std::to_string(numerator);
	else
		return std::to_string(numerator) + "/" + std::to_string(denominator);
}

Fraction Fraction::FractionParse(const std::string& s) {

	size_t perIndex = s.find("/");
	int num, den;
	if (perIndex != std::string::npos) {
		num = std::stoi(s.substr(0, perIndex));
		den = std::stoi(s.substr(perIndex + 1));
	}
	else
		throw std::invalid_argument("Nem alakítható át, mert nem tört!");
	
	if (den == 0)
		throw std::invalid_argument("A nevezõ nem lehet 0");

	Fraction f{num, den};
	return f; // Lehetne simán return Fraction{ num, den }, nincs szükség a lokális temporálisra.
}
