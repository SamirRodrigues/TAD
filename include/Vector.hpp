#include "MyIterator.hpp"
namespace sc
{
    template < typename T >
    class vector 
    {
        public:
            using size_type = unsigned long;                //!< The size type.
            using value_type = T;                           //!< The value type.
            using pointer = value_type*;                    //!< Pointer to a value stored in the container.
            using reference = value_type&;                  //!< Reference to a value stored in the container.
            using const_reference = const value_type&;      //!< Const reference to a value stored in the container.
            using iterator = MyIterator< T >;               // See Code 3
            using const_iterator = MyIterator< const T >;   // See Code 3


            //=== [I] SPECIAL MEMBERS
            explicit vector ( size_type = 0 );
            virtual ~vector ( void );
            vector( const vector & );
            vector( std::initializer_list<T> );
            vector( vector && );

            template < typename InputItr >
            vector( InputItr, InputItr );
            vector& operator=( const vector& );
            vector& operator=( vector && );

            //=== [II] ITERATORS
            iterator begin( void );
            iterator end( void );
            const_iterator cbegin( void ) const;
            const_iterator cend( void ) const;

            // [III] Capacity
            size_type size( void ) const;
            size_type capacity( void ) const;
            bool empty( void ) const;

            // [IV] Modifiers
            void clear( void );
            void push_front( const_reference );
            void push_back( const_reference );
            void pop_back( void );
            void pop_front( void );
            iterator insert( iterator, const_reference );

            template < typename InputItr >
            iterator insert( iterator , InputItr, InputItr );
            iterator insert( iterator , const std::initializer_list< value_type >& );
            void reserve( size_type );
            void shrink_to_fit( void );

            void assign( syze_type, const_reference );
            void assign( const std::initializer_list<T>& );

            template < typename InputItr >
            void assign( InputItr, InputItr );

            iterator erase( iterator, iterator );
            iterator erase( iterator );

            //[V] Element access
            const_reference back( void ) const;
            reference back( void );
            const_reference front( void ) const;
            reference front( void );
            const_reference operator[]( size_type ) const;
            const_reference at( size_type ) const;
            reference at( size_type );
            pointer data( void );
            const_reference data( void ) const;

            // [VI] Friend functions.
            friend std::ostream& operator <<( std::ostream&, const vector<T>& );
            friend void swap( vector<T>&, vector<T>& );

        private:
            size_type m_end;                        //!< Current list size (or index past-last valid element).
            size_type m_capacity;                   //!< List’s storage capacity.
            //std::unique_ptr<T[]> m_storage;       //!< Data storage area for the dynamic array.
            value_type * m_storage;                           //!< Data storage area for the dynamic array.
    };
}

// [III] Capacity
template <typename T>
size_type sc::vector<T>::size(){
    return m_end;
}

template <typename T>
size_type sc::vector<T>::capacity(){
    return m_capacity;
}

template <typename T>
bool sc::vector<T>::empty(){
    return m_end == 0;
}


// [IV] Modifiers
template <typename T>
sc::vector<T>::clear( void ){

    delete[] m_storage;

    m_storage = new T[m_capacity];

}

template <typename T>
sc::vector<T>::push_front( const_reference /*value*/){
    
    if(m_end > m_capacity)
    {
        return 0;                   
    }

    for (size_t i = m_end; i > 0; i--)
    {
        m_storage[i] = m_storage[i-1];
    }

    m_storage[0] = /*value*/;

    return 1;                          

}

template <typename T>
sc::vector<T>::push_back( const_reference /*value*/){

    if(m_end > m_capacity)
    {
        return 0;
    }
    
    m_storage[m_end++] = /*value*/;

    return 1;

}

template <typename T>
sc::vector<T>::pop_back( void ){

    if(empty())
    {
        return 0;
    }

    m_end--;

    return 1;

}

template <typename T>
sc::vector<T>::pop_front( void ){

    if(empty())
    {
        return 0;
    }
    
    for (size_t i = 0; i < m_end; i++)
    {
        m_storage[i] = m_storage[i+1];
    }

    m_end--;

    return 1;

}

template <typename T>
iterator sc::vector<T>::insert( iterator, const_reference ){

}