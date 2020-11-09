#ifndef VECTOR_HPP_
#define VECTOR_HPP_
#define show false
#include <iostream>
#include <stdexcept> // std::out_of_range
#include <iterator> // std::distance

#include "tam.hpp"

using size_type = size_t; 

namespace sc
{
	
	template <class T>
	class vector
	{
		/**
		 * @brief Private:
		 * T *m_storage;  			Where the array will be stored
		 * size_type m_end = 0;		Default empty array 
		 * size_type m_capacity;	Maximum capacity of the array
		 */
		private:			
			T *m_storage;				// where the array will be stored
			size_type m_end = 0;		// default empty array 
			size_type m_capacity;		// maximum capacity of the array

		/**
		 * @brief Public:
		 * @class iterator
		 * @class const_iterator 
		 */
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
					iterator operator-(int a ); 	// ptr-int
					iterator operator+(int a ); 	// ptr+int

					bool operator==( const iterator & ) const;
					bool operator!=( const iterator & ) const;
		
					int operator-(iterator rhs ); // ptr_diff

				private:
					T *current;
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
					T *current;
			};

			/**
			 * @brief Special members
			 * vector( void );												// Default constructor
			 * explicit vector ( size_type count ); 						// Allocate and set to a default
			 * vector( T *first, T *last );									// Copy a array into vector Obj
			 * vector( const vector &other );								// Makes a deep copy of &other
			 * vector( std::initializer_list<T> ilist ); 					// Create a vector by iList
			 * ~vector();													// Default destructor
			 * vector &operator=( const vector & ); 						// Copy content from another object
			 * vector &operator=( std::initializer_list<T> ilist ); 		// Check syntax	
			 * 
			 */
			
			vector( void );												// Default constructor
			explicit vector( size_type count );							// Allocate and set to a default
			vector( T *first, T *last );								// Copy a array into vector Obj
			vector( const vector &other );								// Makes a deep copy of &other
			vector( std::initializer_list<T> ilist ); 					// Create a vector by iList
			~vector();													// Default destructor
			vector &operator=( const vector & ); 						// Copy content from another object		
			vector &operator=( std::initializer_list<T> ilist ); 		// Check syntax	

			
			
			/**
			 * @brief Iterator methods 
			 * typename vector<T>::iterator begin();
			 * typename vector<T>::iterator end();
			 * typename vector<T>::const_iterator cbegin() const;
			 * typename vector<T>::const_iterator cend() const;
			 * 
			 * @return vector<T>::iterator 
			 */
			typename vector<T>::iterator begin();
			typename vector<T>::iterator end();
			typename vector<T>::const_iterator cbegin() const;
			typename vector<T>::const_iterator cend() const;		

			 
			/**
			 * @brief Capacity functions
			 * bool empty(); // Virify if the vector is empty.
			 * @return true 
			 * @return false 
			 * 
			 * size_type size() const; 		
			 * @returns amount of the vector's initialized m_storage	
			 * 
			 * size_type capacity() const; 
			 * @returns amount of memory allocated for the vector
			 * 
			 */
			bool empty();		
			size_type size() const; 		// Returns amount of the vector's initialized m_storage		
			size_type capacity() const; 	// Returns amount of memory allocated for the vector

			/**
			 * @brief Modifiers functions 
			 * void clear(); 														// Clears array from all m_storage
			 * void push_front( const T & );  										// Insert an element on first position
			 * void push_back( const T & );											// Insert an element on last position
			 * void pop_front(); 													// Deletes element on first position
			 * void pop_back(); 													// Deletes element on last position	
			 * iterator insert(iterator pos, const T & value );						// Insert an element on a "pos" position
			 * iterator insert(iterator pos,iterator first, iterator last );		// Inserts range first last elements from a position "pos"
			 * iterator insert(iterator pos,std::initializer_list<T> ilist);		// Inserts elements of an ilist from the position "pos"
			 * void reserve( size_type );  											// If new_cap > capacity allocates (new_cap - capacity) bytes
			 * void shrink_to_fit();   												// Reduces Capacity according to the vector actual size 
			 * void assign(size_type count,  const T & value); 						// Replace the contents with count copies of value "value";
			 * void assign(iterator first, iterator last);							// Replaces the contents of the list with copies of the elements in the range [first; last)
			 * void assign(std::initializer_list<T> ilist);							// Replaces the contents of the list with elements from the initializer list "ilist";			
			 * iterator erase(iterator pos); 										// Deletes element in position pos
			 * iterator erase(iterator first,iterator last);  						// Deletes m_storage in [first,last)
			 */

			void clear(); 														// Clears array from all m_storage
			void push_front( const T & );  										// Insert an element on first position
			void push_back( const T & );										// Insert an element on last position
			void pop_front(); 													// Deletes element on first position
			void pop_back(); 													// Deletes element on last position			
			iterator insert(iterator pos, const T & value );					// Insert an element on a "pos" position
			iterator insert(iterator pos,iterator first, iterator last );		// Inserts range first last elements from a position
			iterator insert(iterator pos,std::initializer_list<T> ilist);		// Inserts elements of an ilist from the position
			void reserve( size_type );  										// If new_cap > capacity allocates (new_cap - capacity) bytes			
			void shrink_to_fit();   											// Reduces Capacity according to the vector actual size 			
			void assign(size_type count,  const T & value); 					// Replace the contents with count copies of value "value";
			void assign(iterator first, iterator last);							// Replaces the contents of the list with copies of the elements in the range [first; last)
			void assign(std::initializer_list<T> ilist);						// Replaces the contents of the list with elements from the initializer list "ilist";			
			iterator erase(iterator pos); 										// Deletes element in position pos
			iterator erase(iterator first,iterator last);  						// Deletes m_storage in [first,last) 		
			

			/**
			 * @brief Element access functions
			 * const T &front() const;			// Acess front member (first member)
			 * const T &back() const;			// Acess back member (last member)
			 * T &operator[]( size_type );		// Access [pos] element by doing object[pos]
			 * T &at( size_type pos );			// Acess [pos] element at the datatype
			 */

			const T &front() const;			// Acess front member (first member)
			const T &back() const;			// Acess back member (last member)
			T &operator[]( size_type );		// Access [pos] element by doing object[pos]
			T &at( size_type pos );			// Acess [pos] element at the datatype
			

			/**
			 * @brief Operator functions
			 * bool operator==( const vector & ); 							// Checks if Vector1 == Vector2	
			 * bool operator!=( const vector & );   						// Checks if Vector1 != Vector2	
			 * @return true 
			 * @return false 
			 */		
			bool operator==( const vector & ); 							// Checks if Vector1 == Vector2		
			bool operator!=( const vector & );   						// Checks if Vector1 != Vector2		
	};
}

/**
 * @file vector.hpp
 * @author Samir Rodrigues & Italo Lima (git @SamirRodrigues & @italo-ce)
 * @brief Vector Implementation
 * @version 0.1
 * @date 2020-11-09
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "vector.inl"

#endif
