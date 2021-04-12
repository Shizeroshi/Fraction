#include <iostream>

using namespace std;

#define DEBUG

class Fraction; // Class declaration - объявление класса
Fraction operator+(Fraction left, Fraction right); // Прототип
Fraction operator-(Fraction left, Fraction right);
Fraction operator*(Fraction left, Fraction right);
Fraction operator/(Fraction left, Fraction right);
bool operator==(Fraction left, Fraction right);


class Fraction
{
	bool minus;
	bool plus;
	int integer; // Целая часть
	int numerator; // Числитель
	int denominator; // Знаменатель

public:
	bool get_minus()const
	{
		return minus;
	}
	int get_integer()const
	{
		return integer;
	}
	int get_numerator()const
	{
		return numerator;
	}
	int get_denomintor()const
	{
		return denominator;
	}
	void set_minus(bool minus)
	{
		this->minus = minus;
	}
	void set_integer(int integer)
	{
		this->integer = integer;
	}
	void set_numenator(int numenator)
	{
		this->numerator = numenator;
	}
	void set_denominator(int denominator)
	{
		if (denominator == 0)denominator = 1;
		this->denominator = denominator;
	}
	Fraction& set_minus_to_number()
	{
		if (minus)
		{
			integer = -integer;
			numerator = -numerator;
			minus = false;
		}
		return *this;
	}
	Fraction& get_minus_from_number()
	{
		if (integer < 0)
		{
			integer = -integer;
			minus = true;
		}
		if (numerator < 0)
		{
			numerator = -numerator;
			minus = true;
		}
		return *this;
	}

	// constructors
	Fraction()
	{
		this->minus = false;
		this->integer = 0;
		this->numerator = 0;
		this->denominator = 1;
		cout << "Default constructor:\t" << this << endl;
	}
	explicit Fraction(int integer)
	{
		this->minus = false;
		this->plus = false;
		this->integer = integer;
		this->numerator = 0;
		this->denominator = 1;
		if (integer < 0)
		{
			minus = true;
			this->integer = -integer;
		}
#ifdef DEBUG
		cout << "Constructor1:\t" << this << endl;
#endif // DEBUG

	}
	Fraction(double decimal)
	{
		decimal += 1e-10;
		minus = decimal < 0 ? true : false;
		if (decimal < 0)
		{
			minus = true;
			decimal = -decimal;
		}
		integer = decimal;
		decimal -= integer;
		denominator = 1e+9;
		numerator = decimal * denominator;
		reduce();

#ifdef DEBUG
		cout << "Constructor double:\t" << this << endl;
#endif // DEBUG


	}


	Fraction(int numerator, int denomenator)
	{
		this->minus = false;
		this->integer = 0;
		this->numerator = numerator;
		this->set_denominator(denomenator);
#ifdef DEBUG
		cout << "Constructor2:\t\t" << this << endl;
#endif // DEBUG

		if (numerator < 0)
		{
			minus = true;
			this->numerator = -numerator;
		}
	}

	Fraction(int integer, int numerator, int denominator)
	{
		this->minus = false;
		this->integer = integer;
		this->numerator = numerator;
		this->set_denominator(denominator);
#ifdef DEBUG
		cout << "Constructor3:\t\t" << this << endl;

#endif // DEBUG
		if (integer < 0)
		{
			minus = true;
			this->integer = -integer;
		}
		if (numerator < 0)
		{
			minus = true;
			this->numerator = -numerator;
		}
	}
	~Fraction()
	{
#ifdef DEBUG
		cout << "Destructor:\t" << this << endl;
#endif // DEBUG

	}

	Fraction& operator=(const Fraction& other)
	{
		this->minus = other.minus;
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
#ifdef DEBUG
		cout << "CopyAssignment:\t" << this << endl;
#endif // DEBUG
		return *this;
	}

	Fraction& operator+=(const Fraction& other)
	{
		return *this = *this + other;
	}

	Fraction& operator-=(const Fraction& other)
	{
		return *this = *this - other;
	}

	Fraction& operator*=(const Fraction& other)
	{
		return *this = *this * other;
	}

	Fraction& operator/=(const Fraction& other)
	{
		return *this = *this / other;
	}

	// increment/decrement

	Fraction& operator++()
	{
		this->integer++;
		return *this;
	}

	Fraction& operator++(int)
	{
		Fraction old = *this;
		this->integer++;
		return old;
	}

	Fraction& operator--()
	{
		this->integer--;
		return *this;
	}
	Fraction& operator--(int)
	{
		Fraction old = *this;
		this->integer--;
		return old;
	}

	// type cast operators

	explicit operator int()const
	{
		return minus ? -integer : integer;
	}
	explicit operator double()const
	{
		double number =	integer + (double)numerator / denominator;
		if (minus)number = -number;
		return number;
	}

	// Methods:

	Fraction& to_proper()
	{
		get_minus_from_number();
		integer += numerator / denominator;
		numerator %= denominator;
		return *this;
	}
	Fraction& to_improper()
	{
		get_minus_from_number();
		numerator += integer * denominator;
		integer = 0;
		return *this;
	}
	Fraction& reduce()
	{
		if (numerator == 0)return *this;
		int more, less, rest;
		// Выясняем кто больше, числитель, или знаменатель
		if (numerator > denominator)more = numerator, less = denominator;
		else less = numerator, more = denominator;
		// Находим наибольший числитель
		do
		{
			rest = more % less;
			more = less;
			less = rest;
		} while (rest);

		int GCD = more; // Greatest Common Divisor
		// Собственно сокращаем дробь
		numerator /= GCD;
		denominator /= GCD;
		return *this;
	}
};


Fraction operator+(Fraction left, Fraction right)
{
	left.to_proper();
	right.to_proper();
	left.set_minus_to_number();
	right.set_minus_to_number();

	Fraction result;
	result.set_integer(left.get_integer() + right.get_integer());
	result.set_numenator(left.get_numerator()*right.get_denomintor() + right.get_numerator()*left.get_denomintor());
	result.set_denominator(left.get_denomintor()*right.get_denomintor());
	result.to_proper().get_minus_from_number();
	return result.reduce();
}

Fraction operator-(Fraction left, Fraction right)
{
	/*left.to_proper().set_minus_to_number();
	right.to_proper().set_minus_to_number();
	return Fraction
	(
		left.get_integer() - right.get_integer(),
		left.get_numerator() * right.get_denomintor() - right.get_numerator() * left.get_denomintor(),
		left.get_denomintor() *	right.get_denomintor()
	).to_proper().get_minus_from_number();*/
	left.to_improper().set_minus_to_number();
	right.to_improper().set_minus_to_number();
	return Fraction
	(
		left.get_numerator() * right.get_denomintor() - right.get_numerator() * left.get_denomintor(),
		left.get_denomintor() *	right.get_denomintor()
	).to_proper().reduce();
}

Fraction operator*(Fraction left, Fraction right)
{
	left.to_improper().set_minus_to_number();
	right.to_improper().set_minus_to_number();
	return Fraction
	(
		left.get_numerator()*right.get_numerator(),
		left.get_denomintor()*right.get_denomintor()
	).to_proper().get_minus_from_number().reduce();
}

Fraction operator/(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	Fraction result
	(
		left.get_numerator()*right.get_denomintor(),
		right.get_numerator()*left.get_denomintor()
	);
	result.to_proper();
	if (left.get_minus() || right.get_minus())result.set_minus(true);
	if (left.get_minus() && right.get_minus())result.set_minus(false);
	return result.reduce();
}

bool operator==(Fraction left, Fraction right)
{
	left.to_improper().reduce();
	right.to_improper().reduce();
	/*if (left.get_numerator()*right.get_denomintor() == right.get_numerator()*left.get_denomintor())
	{
		return true;
	}
	else
	{
		return false;
	}*/
	/*if (left.get_numerator() == right.get_numerator() && left.get_denomintor() == right.get_denomintor())
	{
		return true;
	}
	else
	{
		return false;
	}*/

	return left.get_numerator() == right.get_numerator() && left.get_denomintor() == right.get_denomintor();
}

bool operator!=(const Fraction& left, const Fraction& right)
{
	return !(left == right);
}

bool operator<(const Fraction& left, const Fraction& right)
{
	return (double)left < (double)right;
}

bool operator>(const Fraction& left, const Fraction& right)
{
	return (double)left > (double)right;
}

bool operator>=(const Fraction& left, const Fraction& right)
{
	return left > right || left == right;
}

bool operator<=(const Fraction& left, const Fraction& right)
{
	return !(left > right);
}

ostream& operator<<(ostream& os, const Fraction& obj)
{
	if (obj.get_minus())os << "(-";
	if (obj.get_integer())os << obj.get_integer();
	if (obj.get_integer() && obj.get_numerator())os << "(";
	if (obj.get_numerator())os << obj.get_numerator() << "/" << obj.get_denomintor();
	if (obj.get_integer() && obj.get_numerator())os << ")";
	if (obj.get_integer() == 0 && obj.get_numerator() == 0)os << 0;
	if (obj.get_minus())os << ")";
	return os;
}

//#define Constructors_check
//#define ArithmeticalOperatorsCheck
//#define CompaundAssignmentCheck
//#define IncrementsCheck
//#define TypeConnvertions
#define CompatisonOperators

void main()
{
	setlocale(LC_ALL, "");
	system("color 0A");
#ifdef Constructors_check
	Fraction A; // Default constructor
	cout << A << endl;
	Fraction B = -5; // single argument constructor
	cout << B << endl;
	Fraction C(-1, 2);
	cout << C << endl;
	Fraction D(-2, 3, 4);
	cout << D << endl;
#endif // Constructors_check

	/*Fraction A(7, 2);
	cout << A << " = " << A.to_proper() << endl;
	cout << A << " = " << A.to_improper() << endl;*/

	/*double a = 2.7;
	double b = 3.5;
	cout << a * b << endl;*/

#ifdef ArithmeticalOperatorsCheck
	Fraction A(2, 3, 5);
	Fraction B(-5, 6, 7);
	cout << A << "\t" << B << endl;
	cout << A << " + " << B << " = " << A + B << endl;
	cout << B << " - " << B << " = " << B - B << endl;
	cout << B << " - " << B << " = " << B - A << endl;
	cout << B << " - " << B << " = " << A - B << endl;
	cout << A << " * " << B << " = " << A * B << endl;
	cout << A << " / " << B << " = " << A / B << endl;
	cout << A << "\t" << B << endl;
#endif // ArithmeticalOperatorsCheck
#ifdef CompaundAssignmentCheck
	Fraction A(2, 3, 4);
	Fraction B(5, 6, 7);
	A += B;
	cout << A << endl;
	A -= B;
	cout << A << endl;
	A *= B;
	cout << A << endl;
	A /= B;
	cout << A << endl;

	Fraction reduce(840, 3600);
	cout << reduce.reduce() << endl;
	cout << Fraction(30, 7).reduce() << endl;
#endif // CompaundAssignmentCheck

#ifdef IncrementsCheck
	Fraction reduce(840, 3600);
	cout << reduce.reduce() << endl;
	cout << Fraction(30, 7).reduce() << endl;

	for (double i = .3; i < 10; i++)
	{
		cout << i << "\t";
	}
	cout << endl;
	for (Fraction i(1, 2); i < 10; i++)
	{
		cout << i << "\t";
	}
	cout << endl;
#endif // IncrementsCheck

#ifdef TypeConnvertions
	/*
int a = 2;
double b = 2;
int c = b;
double d = 2.5;
int e = d;
*/
//Fraction A = (Fraction)5; // From other to this / single argument constructor
	Fraction A(5); // Если конструктор эксплист то его можно вызвать только так
	cout << "Fraction A = " << A << endl;
	//a = (int)A;
	//cout << "int a = " << a << endl;

	/*Fraction B(-3, 4, 5);
	cout << B << endl;
	double b = (double)B;
	cout << b << endl;

	int c = (int)B;
	cout << c << endl;
	*/

	Fraction C = 2.3;
	cout << C << endl;
	cout << (double)C << endl;
#endif // TypeConnvertions

#ifdef CompatisonOperators
	Fraction A(1, 2);
	Fraction B(5, 11);
	/*if (A == B)
	{
		cout << "Fractions equal" << endl;
	}
	else
	{
		cout << "Fractions different" << endl;
	}*/
	/*cout << "Fractions " << (A == B ? "Equal" : "Different") << endl;*/
	cout << "Strict:\t";
	cout << (A == B) << endl;
	cout << (A != B) << endl;
	cout << "Not strict:\t";
	cout << (A <= B) << endl;
	cout << (A >= B) << endl;
#endif // CompatisonOperators


}