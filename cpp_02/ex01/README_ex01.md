# Ex01 - Fixed-point

In `ex01` devi estendere `Fixed` per poter costruire numeri fixed-point da `int` e da `float`, e poi riconvertirli.

L'idea base e' questa:

```cpp
valore_interno = numero * 256
```

perche' `fractionalBits = 8`, quindi:

```cpp
1 << fractionalBits == 256
```

Quindi devi procedere cosi'.

Nel tuo `fixed.hpp` aggiungi:

```cpp
Fixed(const float num);

float toFloat(void) const;
int toInt(void) const;
```

e fuori dalla classe dichiari anche:

```cpp
std::ostream &operator<<(std::ostream &out, const Fixed &fixed);
```

Nel `fixed.cpp`, il costruttore da `int` diventa:

```cpp
Fixed::Fixed(const int num)
{
    std::cout << "Int constructor called" << std::endl;
    this->fixed = num << fractionalBits;
}
```

Questo equivale a `num * 256`, ma usando lo shift bitwise.

Poi aggiungi il costruttore da `float`:

```cpp
Fixed::Fixed(const float num)
{
    std::cout << "Float constructor called" << std::endl;
    this->fixed = roundf(num * (1 << fractionalBits));
}
```

Per usare `roundf`, nel `.hpp` o nel `.cpp` devi includere:

```cpp
#include <cmath>
```

Poi le conversioni:

```cpp
float Fixed::toFloat(void) const
{
    return ((float)this->fixed / (1 << fractionalBits));
}

int Fixed::toInt(void) const
{
    return (this->fixed >> fractionalBits);
}
```

Infine l'operatore `<<`, cosi' puoi fare:

```cpp
std::cout << a << std::endl;
```

implementazione:

```cpp
std::ostream &operator<<(std::ostream &out, const Fixed &fixed)
{
    out << fixed.toFloat();
    return (out);
}
```

Esempio mentale:

```cpp
Fixed a(10);
```

Internamente salva:

```cpp
10 << 8 == 2560
```

Quando fai:

```cpp
a.toFloat()
```

ritorna:

```cpp
2560 / 256 == 10.0
```

Per `float`:

```cpp
Fixed b(42.42f);
```

internamente salva circa:

```cpp
roundf(42.42 * 256) == 10860
```

e poi `toFloat()` ritorna circa `42.4219`, perche' il fixed-point ha precisione limitata.

Il tuo `ex01` quindi non e' difficile: e' `ex00` + conversioni `int/float` + stampa con `operator<<`.
