#include <iostream>
#include <string>

#include "../include/TADVector.hpp"

int main ( void )
{
    TADVector<std::string> acesso;
    TADVector<int> value;

    acesso.helloWorld();

    acesso.setName("Jamal");

    std::cout << acesso.getName() << std::endl;

    int a =25;
    float b=50.5;

    value.add(a,a);

    std::cout << value.getResult() << std::endl;

    return 0;
}