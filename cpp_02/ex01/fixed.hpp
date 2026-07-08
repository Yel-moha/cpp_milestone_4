#ifndef FIXED_HPP
# define FIXED_HPP

#include <iostream>
#include <cmath> //per poder usare la funzione roundf la quale arrotonda ad intero il numero frazionario


class Fixed
{
private:
    int fixed; //Variabile per salvare l'intero in questione che per' ha un significato particolare
    static const int fractionalBits; //Una costante condivisa da tutti gli ogetti

public:
    Fixed(void);
    Fixed(const int num);
    Fixed(const Fixed &other);
    Fixed &operator=(const Fixed &other);
    ~Fixed();

    int getRawBits(void) const;
    void setRawBits(int const raw);
    Fixed(const float num);

    float toFloat(void) const;
    int toInt(void) const;
};

std::ostream &operator<<(std::ostream &out, const Fixed &fixed);

#endif