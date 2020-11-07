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

            //iterator class
            
            class iterator
			{
				public:

					typedef std::ptrdiff_t difference_type;
					typedef std::bidirectional_iterator_tag iterator_category;

					// constructors
					iterator( T* ptr=nullptr );
					iterator( const iterator & );

					// destructors
					~iterator( void );
					
					// operators 
					iterator &operator=( const iterator & );
					T &operator*( void ) const;

					iterator operator++( void );	// ++it
					iterator operator++( int );		// it++
					iterator operator--( void );	// --it
					iterator operator--( int );		// it--
					iterator operator-(int a ); // ptr-int
					iterator operator+(int a ); // ptr+int

					bool operator==( const iterator & ) const;
					bool operator!=( const iterator & ) const;
		
					int operator-(iterator rhs ); // ptr_diff

				private:
					T *m_ptr;
			};
            	
            //const_iterator class
			class const_iterator
			{
				public:
					// Public Code
					typedef std::ptrdiff_t difference_type;
					typedef std::bidirectional_iterator_tag iterator_category;

					// constructors
					const_iterator( T* ptr=nullptr );
					const_iterator( const const_iterator & );

					// destructors
					~const_iterator( void );
					
					// operators 
					const_iterator &operator=( const const_iterator & );
					const T &operator*( void ) const;

					const_iterator operator++( void );		// ++it
					const_iterator operator++( int );		// it++
					const_iterator operator--( void );		// --it
					const_iterator operator--( int );		// it--
					const_iterator operator-( int ); 		// ptr-int
					const_iterator operator+( int ); 		// ptr+int
					
					bool operator==( const const_iterator & ) const;
					bool operator!=( const const_iterator & ) const;
		
					int operator-(const_iterator rhs ); // ptr_diff
					
				private:
					T *m_ptr;
            };

            #pragma region  //=== [I] SPECIAL MEMBERS
            
            
            explicit vector ( size_type = 0 );
            virtual ~vector ( void );
            vector( const vector & );
            vector( std::initializer_list<T> );
            vector( vector && );

            template < typename InputItr >
            vector( InputItr, InputItr );
            vector& operator=( const vector& );
            vector& operator=( vector && );


            #pragma endregion
            
            #pragma region  //=== [II] ITERATORS
            
            
            iterator begin( void );
            iterator end( void );
            const_iterator cbegin( void ) const;
            const_iterator cend( void ) const;


            #pragma endregion
            
            #pragma region  // [III] Capacity
            
            
            size_type size( void ) const;
            size_type capacity( void ) const;
            bool empty( void ) const;


            #pragma endregion
            
            #pragma region  // [IV] Modifiers
            
            
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


            #pragma endregion
            
            #pragma region  //[V] Element access
            
            
            const_reference back( void ) const;
            reference back( void );
            const_reference front( void ) const;
            reference front( void );
            const_reference operator[]( size_type ) const;
            const_reference at( size_type ) const;
            reference at( size_type );
            pointer data( void );
            const_reference data( void ) const;


            #pragma endregion
            
            #pragma region  // [VI] Friend functions.
            
            
            friend std::ostream& operator <<( std::ostream&, const vector<T>& );
            friend void swap( vector<T>&, vector<T>& );
            

            #pragma endregion

        private:
            size_type m_end;                        //!< Current list size (or index past-last valid element).
            size_type m_capacity;                   //!< List’s storage capacity.
            //std::unique_ptr<T[]> m_storage;       //!< Data storage area for the dynamic array.
            value_type * m_storage;                           //!< Data storage area for the dynamic array.
    };
}

#pragma region  //vector



#pragma region  //=== [I] SPECIAL MEMBERS
template <typename T>
sc::vector<T>::Vector( size_type count ){

    m_capacity = 2;

    if( count >= 2 )
    {

        while( count >= m_capacity)
        {

            m_capacity *= 2;
        
        }

    }

    // alocating [count] elements of type T
    m_storage = new T[m_capacity];

    for( int i = 0; i < count; i++ )
    {

        if(debug) m_storage[i] = i;			// debug inicializer
        else m_storage[i] = 0;				// normal inicializer
    
    }

    m_end = count;

}

template <typename T>
sc::vector<T>::~Vector(){

    delete[] m_storage;

}

template <typename T>
sc::vector<T>::Vector( const vector &other ){

    

    /* isso eh necessario? vvv
    int temp_capacity;
    
    if( other.size() > 2 )
    {
        temp_capacity = pow( 2, int(log2(other.size())) );

        if( other.size() > temp_capacity )
        {
            temp_capacity *= 2;
        }
    } 
    else 
    {
        temp_capacity = other.size();
    }*/ 
    
    m_storage = new T[other->capacity()];
    
    for (size_t i = 0; i < other->size(); i++)
    {
    
        m_storage[i] = other[i];
    
    }

    m_end = other->size();
    m_capacity = other->capacity();
    
}

template <typename T>
sc::vector<T>::Vector( std::initializer_list<T> ilist ){

    int temp_capacity;	

    if( ilist.size() > 2 )
    {
    
        temp_capacity = pow( 2, int(log2(ilist.size())) );	

        if( ilist.size() > temp_capacity )
        {
    
            temp_capacity *= 2;		
    
        }
    
    } 
    else 
    {
    
        temp_capacity = ilist.size();	
    
    }

    m_storage = new T[temp_capacity];
    int j = 0;

    for( auto *i = ilist.begin(); i < ilist.end(); i++, j++ )
    {
    
        elements[j] = *i;
    
    }

    m_end = ilist.size();
    m_capacity = temp_capacity;

}

template <typename InputIt>
sc::vector<T>::Vector( InputIt *first, InputIt *last ){

    int temp_capacity;		
    int size = std::distance(first, last);

    if( size > 2 )
    {
    
        temp_capacity = pow( 2, int(log2( size )) );

        if( size > temp_capacity )
        {
    
            temp_capacity *= 2;	
    
        }
    
    } 
    else 
    {
    
        temp_capacity = size;
    
    }

    m_storage = new InputIt[temp_capacity];
    int j = 0;

    for( auto *i = first; i < last; i++, j++ )
    {
    
        elements[j] = *i;
    
    }

    m_end = size;
    m_capacity = temp_capacity;

}

template <class T>
vector<T> &vector<T>::operator=( const vector<T> &other )
{
    if( m_size < other->m_size )
    {
    
        reserve( other.m_size );
    
    }

    m_capacity = other->m_capacity;
    m_end = other->m_size;
    

    /* a funcao reserve ja nao faz isso???
    for( int i = 0; i < rhs.m_size; i++ )
    {
        m_storage[i] = other->m_storage[i];
    }
    */

    return *this;
}

template <class T>
vector<T> &vector<T>::operator=( vector && )
{
    

    return *this;
}

#pragma endregion  //=== [I] SPECIAL MEMBERS


#pragma region  //=== [II] ITERATORS


template <class T>
vector<T>::iterator vector<T>::begin()
{
    return vector<T>::iterator(m_storage[0]);
}

template <class T>
vector<T>::iterator vector<T>::end()
{
    return vector<T>::iterator(m_storage[m_end-1]);
}

template <class T>
vector<T>::const_iterator vector<T>::cbegin() const
{
    return vector<T>::const_iterator(m_storage[0]);
}

template <class T>
vector<T>::const_iterator vector<T>::cend() const
{
    return vector<T>::const_iterator(m_storage[m_end-1]);
}


#pragma endregion  //=== [II] ITERATORS


#pragma region // [III] Capacity


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


#pragma endregion  // [III] Capacity


#pragma region  // [IV] Modifiers 


template <typename T>
sc::vector<T>::clear( void ){

    delete[] m_storage;

    m_end = 0;

    m_storage = new T[m_capacity];

}

template <typename T>
sc::vector<T>::push_front( const_reference value){
    
    if(m_end > m_capacity)
    {
        return 0;                   
    }

    for (size_t i = m_end; i > 0; i--)
    {
        m_storage[i] = m_storage[i-1];
    }

    m_storage[0] = value;

    return 1;                          

}

template <typename T>
sc::vector<T>::push_back( const_reference value){

    if(m_end > m_capacity)
    {
        return 0;
    }
    
    m_storage[m_end++] = value;

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
void sc::vector<T>::assign( size_type size, const_reference value){
    
    
    clear();
    reserve(size);

    for (size_t i = 0; i < size_type; i++)
    {
        m_storage[i] = value;
    }
    
    
}

template <class T>
void vector<T>::reserve( size_type new_cap )
	{
		if( new_cap > m_capacity )
		{
			while(new_cap > m_capacity)
			{
				m_capacity *= 2;	
			}
			
			T * temp_storage = new T[m_capacity];

			if(m_storage != m_storage+m_end-1)
            {

                std::copy( m_storage, m_storage+m_end-1, temp_storage );
			
            }
            delete [] m_storage;
			
            m_storage = temp_storage;

		}
	}



#pragma endregion  // [IV] Modifiers 



#pragma endregion  //vector

#pragma region  //vector::iterator


#pragma region  //iterator

template <class T>
vector<T>::iterator::iterator( T *ptr )
{
    this->m_ptr = ptr;
}

template <class U>
vector<U>::iterator::iterator( const vector<U>::iterator &itr )
{
    this->m_ptr = itr.m_ptr;
}

template <class U>
vector<U>::iterator::~iterator() = default;

template <class T>
typename vector<T>::iterator &vector<T>::iterator::operator=( const vector::iterator &rhs )
{
    this->m_ptr = rhs.m_ptr;
}

template <class T>
bool vector<T>::iterator::operator==( const vector::iterator &rhs ) const
{
    return this->m_ptr == rhs.m_ptr;
}

template <class T>
bool vector<T>::iterator::operator!=( const vector::iterator &rhs ) const
{
    return this->m_ptr != rhs.m_ptr;
}

template <class T>
T &vector<T>::iterator::operator*( void ) const
{
    return *this->m_ptr;
}

template <class T>
typename vector<T>::iterator vector<T>::iterator::operator++( void )
{
    // ++it
    return ++this->m_ptr;
}

template <class T>
typename vector<T>::iterator vector<T>::iterator::operator-(int a )
{
    // --it
    return this->m_ptr-a;
}

template <class T>
int vector<T>::iterator::operator-(iterator rhs )
{
    return this->m_ptr-rhs.m_ptr;
}

template <class T>
typename vector<T>::iterator vector<T>::iterator::operator+(int a )
{
    // ++it
    return this->m_ptr+a;
}

template <class T>
typename vector<T>::iterator vector<T>::iterator::operator++( int )
{
    // it++
    return this->m_ptr++;
}

template <class T>
typename vector<T>::iterator vector<T>::iterator::operator--( void )
{
    // --it
    return --this->m_ptr;
}

template <class T>
typename vector<T>::iterator vector<T>::iterator::operator--( int )
{
    // it--
    return this->m_ptr--;
}
#pragma endregion  //iterator



#pragma region  //const_iterator


template <class T>
vector<T>::const_iterator::const_iterator( T *ptr )
{
    this->m_ptr = ptr;
}

template <class U>
vector<U>::const_iterator::const_iterator( const vector<U>::const_iterator &itr )
{
    this->m_ptr = itr.m_ptr;
    std::cout << "vector<U>::const_iterator::const_iterator( itr ) created.\n";
}

template <class U>
vector<U>::const_iterator::~const_iterator() = default;

template <class T>
typename vector<T>::const_iterator &vector<T>::const_iterator::operator=( const vector::const_iterator &rhs )
{
    this->m_ptr = rhs.m_ptr;
}

template <class T>
bool vector<T>::const_iterator::operator==( const vector::const_iterator &rhs ) const
{
    return this->m_ptr == rhs.m_ptr;
}

template <class T>
bool vector<T>::const_iterator::operator!=( const vector::const_iterator &rhs ) const
{
    return this->m_ptr != rhs.m_ptr;
}

template <class T>
const T &vector<T>::const_iterator::operator*( void ) const
{
    return *this->m_ptr;
}

template <class T>
typename vector<T>::const_iterator vector<T>::const_iterator::operator++( void )
{
    // ++it
    return ++this->m_ptr;
}

template <class T>
typename vector<T>::const_iterator vector<T>::const_iterator::operator-(int a )
{
    // ++it
    return this->m_ptr-a;
}

template <class T>
int vector<T>::const_iterator::operator-(const_iterator rhs )
{
    return this->m_ptr-rhs.m_ptr;
}

template <class T>
typename vector<T>::const_iterator vector<T>::const_iterator::operator+(int a )
{
    // ++it
    return this->m_ptr+a;
}

template <class T>
typename vector<T>::const_iterator vector<T>::const_iterator::operator++( int )
{
    // it++
    return this->m_ptr++;
}

template <class T>
typename vector<T>::const_iterator vector<T>::const_iterator::operator--( void )
{
    // --it
    return --this->m_ptr;
}

template <class T>
typename vector<T>::const_iterator vector<T>::const_iterator::operator--( int )
{
    // it--
    return this->m_ptr--;
}
#pragma endregion  //const_iterator


#pragma endregion  //vector::iterator


