#pragma once
#include <iostream>
#include <string>
class Fraction
{
public:
	Fraction(int wholeNumber);
	Fraction(int numerator, int denominator);
	Fraction(double decFrac);
	Fraction(const Fraction& other);
	Fraction();

	operator int() const;
	operator double() const;
	operator bool() const;
	operator std::string() const;

	int getNumerator() const;
	int getDenominator() const;
	void setNumerator(int num);
	void setDenominator(int den);

	Fraction& operator+=(const Fraction& other);
	Fraction& operator-=(const Fraction& other);
	Fraction& operator*=(const Fraction& other);
	Fraction& operator/=(const Fraction& other);
	bool operator==(const Fraction& other) ;

	friend Fraction operator+(Fraction lhs, const Fraction& rhs);
	friend Fraction operator-(Fraction lhs, const Fraction& rhs);
	friend Fraction operator*(Fraction lhs, const Fraction& rhs);
	friend Fraction operator/(Fraction lhs, const Fraction& rhs);
	void print() const;

	Fraction FractionParse(const std::string& f);


private:
	int numerator;
	int denominator;
	void normalize();

};

std::ostream& operator<<(std::ostream& outputStream, const Fraction& frac);
std::istream& operator>>(std::istream& inputStream, Fraction& frac);


