#ifndef __TADVECTOR_H__
#define __TADVECTOR_H__

#include <iostream>
#include <string>

template <typename T>
class TADVector 
{
    public:

        TADVector();
        ~TADVector();

        T helloWorld();  
        T setName(T value);
        T getName();
        
        void add(T valueA, T valueB);
        T getResult();


        T TADVector operator+(TADVector); 

    private:
        T name;
        T result;

};

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
void TADVector<T>::add(T valueA, T valueB)
{
    result = valueA + valueB;
}

template <typename T>
T TADVector<T>::getResult()
{
    return result; 
}

template <typename T>
T TADVector<T>::operator+(T value);
    T newvalue;

     

#endif // __TADVECTOR_H__