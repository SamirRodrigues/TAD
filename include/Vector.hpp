#ifndef VECTOR_HPP_
#define VECTOR_HPP_
#define debug false
#include <iostream>
#include <cmath> //std::pow
#include <algorithm>
#include <iterator> // std::distance
#include <stdexcept>


using size_type = size_t; 

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
					T *current;
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
					T *current;
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
            
            void clear( void );  //done
            void push_front( const_reference );  //done
            void push_back( const_reference );   //done
            void pop_back( void );   //done
            void pop_front( void );   //done
            iterator insert( iterator, const_reference );

            template < typename InputItr >
            iterator insert( iterator , InputItr, InputItr );
            iterator insert( iterator , const std::initializer_list< value_type >& );
            void reserve( size_type );   //done
            void shrink_to_fit( void );

            void assign( syze_type, const_reference );   //done
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
            size_type end;                        //!< Current list size (or index past-last valid element).
            size_type capacity;                   //!< List’s storage capacity.
            //std::unique_ptr<T[]> storage;       //!< Data storage area for the dynamic array.
            value_type *storage;                 //!< Data storage area for the dynamic array.
    };
}

#include "vector.inl"

#endif