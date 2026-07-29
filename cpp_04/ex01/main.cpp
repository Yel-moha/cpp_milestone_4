#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main(void)
{
    std::cout << "----- Subject example -----" << std::endl;
    const Animal* j = new Dog();
    const Animal* i = new Cat();

    delete j; // should not create a leak
    delete i;

    std::cout << std::endl << "----- Array of Animal* (half Dog, half Cat) -----" << std::endl;
    unsigned int size = 6;
    Animal* animals[6];

    for (unsigned int k = 0; k < size; k++)
    {
        if (k % 2 == 0)
            animals[k] = new Dog();
        else
            animals[k] = new Cat();
    }
    for (unsigned int k = 0; k < size; k++)
        animals[k]->makeSound();
    for (unsigned int k = 0; k < size; k++)
        delete animals[k]; // deleted through the base pointer, virtual dtor required

    std::cout << std::endl << "----- Deep copy check -----" << std::endl;
    Dog dog1;
    dog1.getBrain()->setIdea(0, "chase the mailman");

    Dog dog2(dog1);
    dog2.getBrain()->setIdea(0, "take a nap");

    std::cout << "dog1 brain address: " << dog1.getBrain() << " idea[0]: " << dog1.getBrain()->getIdea(0) << std::endl;
    std::cout << "dog2 brain address: " << dog2.getBrain() << " idea[0]: " << dog2.getBrain()->getIdea(0) << std::endl;

    Cat cat1;
    cat1.getBrain()->setIdea(0, "knock a glass off the table");

    Cat cat2;
    cat2 = cat1;
    cat2.getBrain()->setIdea(0, "sleep 20 hours");

    std::cout << "cat1 brain address: " << cat1.getBrain() << " idea[0]: " << cat1.getBrain()->getIdea(0) << std::endl;
    std::cout << "cat2 brain address: " << cat2.getBrain() << " idea[0]: " << cat2.getBrain()->getIdea(0) << std::endl;

    std::cout << std::endl << "----- WrongAnimal / WrongCat (broken polymorphism) -----" << std::endl;
    const WrongAnimal* wrongMeta = new WrongAnimal();
    const WrongAnimal* wrongCat = new WrongCat();

    wrongMeta->makeSound();
    wrongCat->makeSound(); // NOT virtual -> outputs the WrongAnimal sound, not the cat one!

    delete wrongMeta;
    delete wrongCat;

    return (0);
}
