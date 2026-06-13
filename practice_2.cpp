#include <iostream>
#include <memory>
using namespace std;

int main() {

    // Declared a pointer to store
    // the address of the allocated memory
    int *nptr;
    
    // Allocate and initialize memory
    nptr = new int[2];
    nptr[0] = 52;
    // Print the value
    cout << *nptr << endl;

    // Print the address of memory
    // block
    cout << nptr << endl;


    nptr[1] = 55;

    // Print the value 2
    cout << *nptr << endl;

    // Print the address of memory
    // block
    cout << nptr[1] << endl;
    cout << &nptr[1] << endl;

    //delete nptr;


    return 0;
}