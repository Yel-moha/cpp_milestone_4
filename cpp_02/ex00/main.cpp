#include "fixed.hpp"

int main( void )
{
    Fixed a;
    Fixed b( a );
    Fixed c;
    c = b;
    return (0);
}