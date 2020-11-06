#ifndef __TADVECTOR_H__
#define __TADVECTOR_H__

#include <iostream>

template <class T>
class TADVector 
{
    public:

        TADVector();
        ~TADVector();

        void helloWorld();  
        void setName(T value);
        T getName();
        
        void add(T valueA, T valueB);
        T getResult();


        //T TADVector operator+(TADVector); 

    private:
        T name;
        T result;

};

template <class T>
TADVector<T>::TADVector()
{

}

template <class T>
TADVector<T>::~TADVector()
{

}

template <class T>
void TADVector<T>::helloWorld()
{
    std::cout << "Hello World" << std::endl;
}

template <class T>
void TADVector<T>::setName(T value)
{
    name = value;
}

template <class T>
T TADVector<T>::getName()
{
    return name;
}

template <class T>
void TADVector<T>::add(T valueA, T valueB)
{
    result = valueA + valueB;
}

template <class T>
T TADVector<T>::getResult()
{
    return result; 
}



     

#endif // __TADVECTOR_H__