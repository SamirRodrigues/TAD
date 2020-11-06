#ifndef __TADVECTOR_H__
#define __TADVECTOR_H__

#include <iostream>

template <class T>
class vector 
{
    private:
        T * elements;
        int capacity;
        int size;
    
    public:

        TADVector();
        ~TADVector();

        void helloWorld();  
        void setName(T value);
        void add(T valueA, T valueB);
        T getName();
        T getResult();


        //T TADVector operator+(TADVector); 

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