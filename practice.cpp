#include <iostream>
#include <memory>
using namespace std;

int main() {

    int *ptr;

    int *ptr_2;
    ptr_2 = new int(5);
    cout << *ptr_2 << endl;

    ptr = (int *)(0x3db7eb4 + 1);
    /*
    #include "tests_ft_strlen.h"

    int	segv_test(void)
    {
    	char	*s;

    	s = (char *)0x12345678;
    	ft_strlen(s);
    	return (0);
    }

    */
    cout << *ptr  << endl;


    return 0;
}