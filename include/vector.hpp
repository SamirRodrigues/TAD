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
	template <class T>
	class vector
	{
		private:
			T *m_first;					// an 'first' pointer
			T *m_last;					// an 'last' pointer
			T *elements;				// where the array will be stored
			size_type m_size = 0;		// default empty array 
			size_type m_capacity;		// maximum capacity of the array

		public:
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

			// Iterator methods 
			typename vector<T>::iterator begin();
			typename vector<T>::iterator end();
			typename vector<T>::const_iterator cbegin() const;
			typename vector<T>::const_iterator cend() const;		

			// Special functions 
			vector( void );							// Default constructor
			explicit vector( size_type count );		// Allocate and set to a default
			vector( T *first, T *last );			// Copy a array into vector Obj
			vector( const vector &other );			// Makes a deep copy of &other
			vector( std::initializer_list<T> ilist ); // Create a vector by iList
			~vector();								// Default destructor

			// Capacity functions 
			bool empty();		
			size_type size() const; 		// Returns amount of the vector's initialized elements		
			size_type capacity() const; 	// Returns amount of memory allocated for the vector		
			void reserve( size_type );  	// If new_cap > capacity allocates (new_cap - capacity) bytes

			// Modifiers functions 
			/*! Deletes all elements from the vector */
			void clear(); 					// Clears array from all elements
			void push_front( const T & );  	// insert an element on first position
			void push_back( const T & );	// insert an element on last position
			void pop_front(); 				// deletes element on first position
			void pop_back(); 				// deletes element on last position
			
			iterator insert(iterator pos, const T & value );
			iterator insert(iterator pos,iterator first, iterator last );
			iterator insert(iterator pos,std::initializer_list<T> ilist);
			
			void shrink_to_fit();   //Reduces Capacity according to the vector actual size 
			
			void assign(size_type count,  const T & value);
			void assign(iterator first, iterator last);
			void assign(std::initializer_list<T> ilist);
			iterator erase(iterator pos); 					// Deletes element in position pos
			iterator erase(iterator first,iterator last);  	// Deletes elements in [first,last) 		
			

			// Element access functions
			const T &front() const;		// Acess front member (first member)
			const T &back() const;		// Acess back member (last member)
			T &at( size_type pos );		// TODO Acess [pos] element at the datatype
			

			// Operator functions		
			vector &operator=( const vector & ); // Copy content from another object		
			vector &operator=( std::initializer_list<T> ilist ); // Check syntax		
			bool operator==( const vector & ); // Checks if Vector1 == Vector2		
			bool operator!=( const vector & );   // Checks if Vector1 != Vector2		
			T &operator[]( size_type );	 		 // Access [pos] element by doing object[pos]
	};
}

// Source code 
#include "vector.inl"

#endif
