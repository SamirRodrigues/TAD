#include "vector.hpp"

namespace sc
{	
	
	#pragma region  //vector



	#pragma region  //=== [I] SPECIAL MEMBERS

	template <typename T>
	vector<T>::Vector( size_type count ){

		capacity = 2;

		if( count >= 2 )
		{

			while( count >= capacity)
			{

				capacity *= 2;
			
			}

		}

		// alocating [count] elements of type T
		storage = new T[capacity];

		for( int i = 0; i < count; i++ )
		{

			if(debug) storage[i] = i;			// debug inicializer
			else storage[i] = 0;				// normal inicializer
		
		}

		end = count;

	}

	template <typename T>
	vector<T>::~Vector(){

		delete[] storage;

	}

	template <typename T>
	vector<T>::Vector( const vector &other )
	{
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
		} 
		
		storage = new T[other->capacity()];
		
		for (size_t i = 0; i < other->size(); i++)
		{
		
			storage[i] = other[i];
		
		}

		end = other->size();
		capacity = other->capacity();
		
	}

	template <typename T>
	vector<T>::Vector( std::initializer_list<T> ilist ){

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

		storage = new T[temp_capacity];
		int j = 0;

		for( auto *i = ilist.begin(); i < ilist.end(); i++, j++ )
		{
		
			elements[j] = *i;
		
		}

		end = ilist.size();
		capacity = temp_capacity;

	}

	template <typename InputIt>
	vector<T>::Vector( InputIt *first, InputIt *last ){

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

		storage = new InputIt[temp_capacity];
		int j = 0;

		for( auto *i = first; i < last; i++, j++ )
		{
		
			elements[j] = *i;
		
		}

		end = size;
		capacity = temp_capacity;

	}

	template <class T>
	vector<T> &vector<T>::operator=( const vector<T> &other )
	{
		if( size < other->size )
		{
		
			reserve( other.size );
		
		}

		capacity = other->capacity;
		end = other->size;
		

		/* a funcao reserve ja nao faz isso???
		for( int i = 0; i < rhs.size; i++ )
		{
			storage[i] = other->storage[i];
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
		return vector<T>::iterator(storage[0]);
	}

	template <class T>
	vector<T>::iterator vector<T>::end()
	{
		return vector<T>::iterator(storage[end-1]);
	}

	template <class T>
	vector<T>::const_iterator vector<T>::cbegin() const
	{
		return vector<T>::const_iterator(storage[0]);
	}

	template <class T>
	vector<T>::const_iterator vector<T>::cend() const
	{
		return vector<T>::const_iterator(storage[end-1]);
	}


	#pragma endregion  //=== [II] ITERATORS


	#pragma region // [III] Capacity


	template <typename T>
	size_type vector<T>::size(){
		
		return end;

	}

	template <typename T>
	size_type vector<T>::capacity(){
		return capacity;
	}

	template <typename T>
	bool vector<T>::empty(){
		return end == 0;
	}


	#pragma endregion  // [III] Capacity


	#pragma region  // [IV] Modifiers 


	template <typename T>
	vector<T>::clear( void ){

		delete[] storage;

		end = 0;

		storage = new T[capacity];

	}

	template <typename T>
	vector<T>::push_front( const_reference value){
		
		if(end > capacity)
		{
			return 0;                   
		}

		for (size_t i = end; i > 0; i--)
		{
			storage[i] = storage[i-1];
		}

		storage[0] = value;

		return 1;                          

	}

	template <typename T>
	vector<T>::push_back( const_reference value){

		if(end > capacity)
		{
			return 0;
		}
		
		storage[end++] = value;

		return 1;

	}

	template <typename T>
	vector<T>::pop_back( void ){

		if(empty())
		{
			return 0;
		}

		end--;

		return 1;

	}

	template <typename T>
	vector<T>::pop_front( void ){

		if(empty())
		{
			return 0;
		}
		
		for (size_t i = 0; i < end; i++)
		{
			storage[i] = storage[i+1];
		}

		end--;

		return 1;

	}

	template <typename T>
	void vector<T>::assign( size_type size, const_reference value){
		

		clear();
		reserve(size);

		for (size_t i = 0; i < size_type; i++)
		{
			storage[i] = value;
		}
		
		
	}

	template <class T>
	void vector<T>::reserve( size_type new_cap )
		{
			if( new_cap > capacity )
			{
				while(new_cap > capacity)
				{
					capacity *= 2;	
				}
				
				T * temp_storage = new T[capacity];

				if(storage != storage+end-1)
				{

					std::copy( storage, storage+end-1, temp_storage );
				
				}
				delete [] storage;
				
				storage = temp_storage;

			}
		}



	#pragma endregion  // [IV] Modifiers 



	#pragma endregion  //vector

	#pragma region  //vector::iterator


	#pragma region  //iterator


	template <class T>
	vector<T>::iterator::iterator( T *ptr )
	{
		this->current = ptr;
	}

	template <class T>
	vector<T>::iterator::iterator( const vector<T>::iterator &itr )
	{
		this->current = itr.current;
	}

	template <class T>
	vector<T>::iterator::~iterator() = default;

	template <class T>
	typename vector<T>::iterator &vector<T>::iterator::operator=( const vector::iterator &rhs )
	{
		this->current = rhs.current;
	}

	template <class T>
	bool vector<T>::iterator::operator==( const vector::iterator &rhs ) const
	{
		return this->current == rhs.current;
	}

	template <class T>
	bool vector<T>::iterator::operator!=( const vector::iterator &rhs ) const
	{
		return this->current != rhs.current;
	}

	template <class T>
	T &vector<T>::iterator::operator*( void ) const
	{
		return *this->current;
	}

	template <class T>
	typename vector<T>::iterator vector<T>::iterator::operator++( void )
	{
		// ++it
		return ++this->current;
	}

	template <class T>
	typename vector<T>::iterator vector<T>::iterator::operator-(int a )
	{
		// --it
		return this->current-a;
	}

	template <class T>
	int vector<T>::iterator::operator-(iterator rhs )
	{
		return this->current-rhs.current;
	}

	template <class T>
	typename vector<T>::iterator vector<T>::iterator::operator+(int a )
	{
		// ++it
		return this->current+a;
	}

	template <class T>
	typename vector<T>::iterator vector<T>::iterator::operator++( int )
	{
		// it++
		return this->current++;
	}

	template <class T>
	typename vector<T>::iterator vector<T>::iterator::operator--( void )
	{
		// --it
		return --this->current;
	}

	template <class T>
	typename vector<T>::iterator vector<T>::iterator::operator--( int )
	{
		// it--
		return this->current--;
	}


	#pragma endregion  //iterator


	#pragma region  //const_iterator


	template <class T>
	vector<T>::const_iterator::const_iterator( T *ptr )
	{
		this->current = ptr;
	}

	template <class T>
	vector<T>::const_iterator::const_iterator( const vector<T>::const_iterator &itr )
	{
		this->current = itr.current;
		std::cout << "vector<T>::const_iterator::const_iterator( itr ) created.\n";
	}

	template <class T>
	vector<T>::const_iterator::~const_iterator() = default;

	template <class T>
	typename vector<T>::const_iterator &vector<T>::const_iterator::operator=( const vector::const_iterator &rhs )
	{
		this->current = rhs.current;
	}

	template <class T>
	bool vector<T>::const_iterator::operator==( const vector::const_iterator &rhs ) const
	{
		return this->current == rhs.current;
	}

	template <class T>
	bool vector<T>::const_iterator::operator!=( const vector::const_iterator &rhs ) const
	{
		return this->current != rhs.current;
	}

	template <class T>
	const T &vector<T>::const_iterator::operator*( void ) const
	{
		return *this->current;
	}

	template <class T>
	typename vector<T>::const_iterator vector<T>::const_iterator::operator++( void )
	{
		// ++it
		return ++this->current;
	}

	template <class T>
	typename vector<T>::const_iterator vector<T>::const_iterator::operator-(int a )
	{
		// ++it
		return this->current-a;
	}

	template <class T>
	int vector<T>::const_iterator::operator-(const_iterator rhs )
	{
		return this->current-rhs.current;
	}

	template <class T>
	typename vector<T>::const_iterator vector<T>::const_iterator::operator+(int a )
	{
		// ++it
		return this->current+a;
	}

	template <class T>
	typename vector<T>::const_iterator vector<T>::const_iterator::operator++( int )
	{
		// it++
		return this->current++;
	}

	template <class T>
	typename vector<T>::const_iterator vector<T>::const_iterator::operator--( void )
	{
		// --it
		return --this->current;
	}

	template <class T>
	typename vector<T>::const_iterator vector<T>::const_iterator::operator--( int )
	{
		// it--
		return this->current--;
	}
	#pragma endregion  //const_iterator


#pragma endregion  //vector::iterator

}