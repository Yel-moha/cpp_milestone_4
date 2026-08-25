#include "fixed.hpp"

const int Fixed::fractionalBits = 8;

Fixed::Fixed(void) : fixed(0)
{
}

Fixed::Fixed(const int num)
{
    this->fixed = num << fractionalBits;
}

Fixed::Fixed(const float num)
{
    this->fixed = static_cast<int>(roundf(num * (1 << fractionalBits)));
}

Fixed::Fixed(const Fixed &other)
{
    *this = other;
}

Fixed &Fixed::operator=(const Fixed &other)
{
    if (this != &other)
        this->fixed = other.fixed;
    return (*this);
}

Fixed::~Fixed()
{
}

int Fixed::getRawBits(void) const
{
    return (this->fixed);
}

void Fixed::setRawBits(int const raw)
{
    this->fixed = raw;
}

float Fixed::toFloat(void) const
{
    return (static_cast<float>(this->fixed) / (1 << fractionalBits));
}

int Fixed::toInt(void) const
{
    return (this->fixed >> fractionalBits);
}

bool Fixed::operator>(const Fixed &other) const
{
    return (this->fixed > other.fixed);
}

bool Fixed::operator<(const Fixed &other) const
{
    return (this->fixed < other.fixed);
}

bool Fixed::operator>=(const Fixed &other) const
{
    return (this->fixed >= other.fixed);
}

bool Fixed::operator<=(const Fixed &other) const
{
    return (this->fixed <= other.fixed);
}

bool Fixed::operator==(const Fixed &other) const
{
    return (this->fixed == other.fixed);
}

bool Fixed::operator!=(const Fixed &other) const
{
    return (this->fixed != other.fixed);
}

Fixed Fixed::operator+(const Fixed &other) const
{
    Fixed result;

    result.fixed = this->fixed + other.fixed;
    return (result);
}

Fixed Fixed::operator-(const Fixed &other) const
{
    Fixed result;

    result.fixed = this->fixed - other.fixed;
    return (result);
}

Fixed Fixed::operator*(const Fixed &other) const
{
    Fixed result;
    long temp;

    temp = static_cast<long>(this->fixed) * static_cast<long>(other.fixed);
    result.fixed = static_cast<int>(temp >> fractionalBits);
    return (result);
}

Fixed Fixed::operator/(const Fixed &other) const
{
    Fixed result;
    long temp;

    temp = (static_cast<long>(this->fixed) << fractionalBits) / other.fixed;
    result.fixed = static_cast<int>(temp);
    return (result);
}

Fixed &Fixed::operator++(void)
{
    ++this->fixed;
    return (*this);
}

Fixed Fixed::operator++(int)
{
    Fixed temp(*this);

    ++this->fixed;
    return (temp);
}

Fixed &Fixed::operator--(void)
{
    --this->fixed;
    return (*this);
}

Fixed Fixed::operator--(int)
{
    Fixed temp(*this);

    --this->fixed;
    return (temp);
}

Fixed &Fixed::min(Fixed &a, Fixed &b)
{
    if (a < b)
        return (a);
    return (b);
}

const Fixed &Fixed::min(const Fixed &a, const Fixed &b)
{
    if (a < b)
        return (a);
    return (b);
}

Fixed &Fixed::max(Fixed &a, Fixed &b)
{
    if (a > b)
        return (a);
    return (b);
}

const Fixed &Fixed::max(const Fixed &a, const Fixed &b)
{
    if (a > b)
        return (a);
    return (b);
}

std::ostream &operator<<(std::ostream &out, const Fixed &fixed)
{
    out << fixed.toFloat();
    return (out);
}