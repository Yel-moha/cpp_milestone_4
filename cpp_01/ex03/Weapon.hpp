#include <iostream>

class Weapon
{
private:
    /* data */
    std::string  type;
public:
    Weapon(/* args */);
    Weapon(std::string name);
    ~Weapon();

    std::string const getType();
    void setType ( std::string const weapon_type);
};

