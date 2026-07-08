#include "fixed.hpp"

const int Fixed::fractionalBits = 8;

Fixed::Fixed(void) // Costruttore di default
{
    this->fixed = 0;
    std::cout << "Default constructor called" << std::endl;
}

// Costruttore di copia: Fixed::Fixed(const Fixed &other)
// Fixed: È il nome della funzione.
// Fixed::Fixed: Poiché si chiama come la classe, il compilatore sa che è un costruttore.
// const Fixed &: ricevo una reference costante ad un altro oggetto Fixed.
// const in questo caso perche' si limita a copiare il contenuto della classe senza modificarlo
Fixed::Fixed(const Fixed &other)
{
    std::cout << "Copy constructor called" << std::endl;
    *this = other;
    //this->fixed = other.fixed;
}

// Operatore di assegnazione 
// Fixed &: La funzione restituisce una reference ad un Fixed.
// operator= E' semplicemente il nome della funzione.
//Il compilatore dice questa funzione rappresenta l'operatore =
//Per questo possiamo scrivere a = b; e viene tradotto in a.operator=(b);Sono la stessa cosa.
Fixed &Fixed::operator=(const Fixed &other)
{
    std::cout << "Copy assignment operator called" << std::endl;
    if (this != &other)
        this->fixed = other.fixed;
    return (*this);
}

//Questo equivale a `num * 256`, ma usando lo shift bitwise perche' fractionalBits = 8;
Fixed::Fixed(const int num)
{
    std::cout << "Int constructor called" << std::endl;
    this->fixed = num << fractionalBits;
}

Fixed::Fixed(const float num)
{
    std::cout << "Float constructor called" << std::endl;
    this->fixed = roundf(num * (1 << fractionalBits));
}

float Fixed::toFloat(void) const
{
    return ((float)this->fixed / (1 << fractionalBits));
}

int Fixed::toInt(void) const
{
    return (this->fixed >> fractionalBits);
}

std::ostream &operator<<(std::ostream &out, const Fixed &fixed)
{
    out << fixed.toFloat();
    return (out);
}

Fixed::~Fixed()
{
    std::cout << "Destructor called" << std::endl;
}

int Fixed::getRawBits(void) const
{
    std::cout << "getRawBits member function called" << std::endl;
    return (this->fixed);
}

void Fixed::setRawBits(int const raw)
{
    std::cout << "setRawBits member function called" << std::endl;
    this->fixed = raw;
}
