#include <iostream>
#include <string>

#include "../include/TADVector.hpp"

template <typename T>
TADVector<T>::TADVector()
{

}

template <typename T>
TADVector<T>::~TADVector()
{

}

template <typename T>
T TADVector<T>::helloWorld()
{
    std::cout << "Hello World" << std::endl;
}

template <typename T>
T TADVector<T>::setName(T value)
{
    name = value;
}

template <typename T>
T TADVector<T>::getName()
{
    return name;
}

template <typename T>
T TADVector<T>::add(T valueA, T valueB)
{
    return valueA+valueB;
}