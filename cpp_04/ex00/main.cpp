#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main(void)
{
    std::cout << "----- Subject example (correct polymorphism) -----" << std::endl;
    const Animal* meta = new Animal();
    const Animal* j = new Dog();
    const Animal* i = new Cat();

    std::cout << j->getType() << " " << std::endl;
    std::cout << i->getType() << " " << std::endl;
    i->makeSound(); // will output the cat sound!
    j->makeSound();
    meta->makeSound();

    delete meta;
    delete j;
    delete i;

    std::cout << std::endl << "----- Copy constructor / assignment operator -----" << std::endl;
    Dog dog1;
    Dog dog2(dog1);
    Dog dog3;
    dog3 = dog1;
    std::cout << "dog2 type after copy: " << dog2.getType() << std::endl;
    std::cout << "dog3 type after assignment: " << dog3.getType() << std::endl;

    std::cout << std::endl << "----- Array of Animal* (mixed Dog/Cat) -----" << std::endl;
    Animal* animals[4];
    animals[0] = new Dog();
    animals[1] = new Cat();
    animals[2] = new Dog();
    animals[3] = new Cat();
    for (int k = 0; k < 4; k++)
        animals[k]->makeSound();
    for (int k = 0; k < 4; k++)
        delete animals[k];

    std::cout << std::endl << "----- WrongAnimal / WrongCat (broken polymorphism) -----" << std::endl;
    const WrongAnimal* wrongMeta = new WrongAnimal();
    const WrongAnimal* wrongCat = new WrongCat();

    wrongMeta->makeSound();
    wrongCat->makeSound(); // NOT virtual -> outputs the WrongAnimal sound, not the cat one!

    delete wrongMeta;
    delete wrongCat;

    return (0);
}
