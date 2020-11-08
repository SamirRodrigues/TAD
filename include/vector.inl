#include "vector.hpp"

namespace sc
{	
	template <class T>
	vector<T>::vector( size_type count )
	{
		capacity = 2;

		if( count >= 2 )
		{
			while( count >= capacity)
			{
				capacity *= 2;
			}
		}

		// alocating [count] elements of type T
		this->elements = new T[capacity];

		for( int i = 0; i < count; i++ )
		{
			if(debug) elements[i] = i;			// debug inicializer
			else elements[i] = 0;				// normal inicializer
		}

		this->first = elements;
		this->last = elements + count;
		this->size = count;

		if(debug) std::cout << "> vector allocated with sucess!" << std::endl;
	}

	template <class T>
	vector<T>::vector( void )
	{
		int temp_capacity = 2;		

		this->elements = new T[temp_capacity];
		this->first = elements;
		this->last = elements;
		this->size = 0; 
		this->capacity = temp_capacity;

		if(debug) std::cout << "> vector allocated with sucess!" << std::endl;
	}

	template <class T>
	vector<T>::vector( const vector &other )
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

		this->elements = new T[temp_capacity];

		for( int i = 0; i < temp_capacity; i++ )
		{
			elements[i] = other.elements[i];	
		}

		this->first = elements;
		this->last = elements + other.size();
		this->size = other.size();
		this->capacity = temp_capacity;
	}

	template <class T>
	vector<T>::vector( std::initializer_list<T> ilist )
	{
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

		this->elements = new T[temp_capacity];
		int buf = 0;

		for( auto *i = ilist.begin(); i < ilist.end(); i++, buf++ )
		{
			elements[buf] = *i;
		}

		this->first = elements;
		this->last = elements + ilist.size();
		this->size = ilist.size();
		this->capacity = temp_capacity;
	}
	
	template <class InputIt>
	vector<InputIt>::vector( InputIt *first, InputIt *last )
	{
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

		this->elements = new InputIt[temp_capacity];
		int buf = 0;

		for( auto *i = first; i < last; i++, buf++ )
		{
			elements[buf] = *i;
		}

		this->first = elements;
		this->last = elements + size;
		this->size = size;
		this->capacity = temp_capacity;
	}

	template <class T>
	vector<T>::~vector()
	{
		if(elements != NULL)
		{
			delete[] elements;
			if(debug) std::cout << "> vector deleted with sucess!" << std::endl;
		}
	}
	
	template <class T>
	bool vector<T>::empty()
	{
		return (size == 0 ? true : false);
	}
	
	template <class T>
	size_type vector<T>::size() const
	{
		return this->size;
	}

	
	template <class T>
	size_type vector<T>::capacity() const
	{
		return this->capacity;
	}

	template <class T>
	void vector<T>::reserve(size_type new_cap)
	{
		if( new_cap > capacity )
		{
			while(new_cap > capacity)
			{
				capacity *= 2;	
			}
			
			T *temp_elements = new T[capacity];
			if(first != last) std::copy( elements, last, temp_elements );
			delete [] elements;
			elements = temp_elements;
			first = elements;
			last = elements+size;
		}
	}

	template <class T>
	void vector<T>::push_back( const T& value )
	{		
		if( size < capacity )
		{
			*(last++) = value;
			size += 1;
		} 
		else 
		{			
			this->reserve( capacity * 2 );	
			size += 1;
			*(last++) = value;
		}
	}

	template <typename T>
	void vector<T>::push_front(const T & value)
	{	
		if(size <= 2)
		{
			this->reserve(2);
			size += 1;

			if(size >= 1)
			{
				 std::copy(first,last,first+1);
			}

			last++;
			*first = value;
		}
		
		else if( size < capacity )
		{
			std::copy(first,last,first+1);
			*first = value;
			size += 1;
			last++;
		} 
		else 
		{			
			this->reserve( capacity * 2 );	
			size += 1;
			std::copy(first,last,first+1);
			*first = value;
			last++;
		}
	}
	
	template <typename T>
	void vector<T>::pop_front()
	{
		if(size != 0){
			std::copy(first+1,last,first);
			size--;
			last--;
		}
		else
		{
			throw std::runtime_error("Don't pop an empty vector");
		}
	}
	
	template <typename T>
	void vector<T>::pop_back()
	{
		if(size != 0){
			size--;
			last--;
		}
		else
		{
			throw std::runtime_error("Don't pop an empty vector");
		}
	}

	template <typename T>
	typename vector<T>::iterator vector<T>::insert(iterator pos, const T &value)
	{
		int distance = pos - first;

		bool reserved = false;	
		if(++size >= capacity)
		{
			this->reserve(capacity*2);
			reserved = true;
		}
		
		if(debug) std::cout << "Distance: " << distance << std::endl;

		if(distance == size)
		{
			*last = value;
			if(!reserved) last++;
			return elements+size;
		}
		else
		{
			T temp;
			std::copy(elements+distance,elements+size,elements+distance+1);
			*(elements+distance) = value;
			if(!reserved) last++;
		}

		return elements+distance;
	}

	template <typename T>
	typename vector<T>::iterator vector<T>::insert(iterator pos,iterator first, iterator last )
	{
		int distance = last-first;
		int first_index = pos-first;

		T temp[distance];	
		int index = 0;
		for (auto i(first); i != last; ++i,++index) 
		{
			temp[index] = *i;
		}
	
		if(debug)
		{
			std::cout << "Before : ";
			std::copy(temp,temp+distance, std::ostream_iterator<int>(std::cout ," "));
			std::cout << "first_index : " << first_index << std::endl;
		}

		reserve(size+distance);

		std::copy(elements+first_index, elements+size, elements+first_index+distance);
	
		size += distance;
		
		if(debug) 
		{
			std::cout << "After : ";
			std::copy(elements,elements+size,	std::ostream_iterator<int>( std::cout ," " ));
			std::cout << std::endl;
		}

		std::copy(temp,temp+distance,elements+first_index);
		
		last += distance;
		return elements+first_index; 
	}

	template <typename T>
	typename vector<T>::iterator vector<T>::insert(iterator pos,std::initializer_list<T> ilist)
	{
		int first_index = pos-first;
		if(1)
		{
			std::cout << "Before : ";
			std::cout << "Cap : " << capacity() << std::endl;
			std::cout << "size : " << size() << std::endl;
			std::copy(first,last, std::ostream_iterator<int>(std::cout ," "));
			std::cout << std::endl;
		}
		
		if(size+ilist.size() > capacity)
		{
			reserve(size+ilist.size());
		}
		
		std::copy(elements+first_index, elements+size, elements+first_index+ilist.size());
		std::copy(ilist.begin(), ilist.end(), elements+first_index);
	
		size += ilist.size();
		last += ilist.size();

		if(1) 
		{
			std::cout << "After : ";
			std::cout << "Cap : " << capacity() << std::endl;
			std::cout << "size : " << size() << std::endl;
			std::copy(elements, elements+size, std::ostream_iterator<int>(std::cout ," "));
			std::cout << std::endl;
		}

		return elements+first_index; 
	}

	template <typename T>
	void vector<T>::clear(void)
	{
		size = 0;
		first = elements;
		last = elements;
	}

	template <typename T>
	void vector<T>::assign(size_type count,  const T & value)
	{
		clear();
		reserve(count);

		for (int i = 0; i < count; ++i) {
			elements[i] = value;	
		}

		last += count;
		size += count;
	}

	template <typename T>
	void vector<T>::assign(iterator first, iterator last)
	{	
		int distance = last-first;
		clear();
		reserve(distance);

		for (auto i(first);  i != last;++i ) 
		{
			*last++ = *i;	
			size++;
		}
	}

	template <typename T>
	void vector<T>::assign(std::initializer_list<T> ilist)
	{
		if(capacity < ilist.size())
		{
			while(capacity < ilist.size( ))
			{
				capacity *= 2;	
			}
			
			reserve(capacity);
		}

		clear();	
		last+= ilist.size();
		size+= ilist.size();
		std::copy(ilist.begin(), ilist.end(), elements);	
	}

	template <typename T>
	void vector<T>::shrink_to_fit(void)
	{
		capacity = pow( 2, int(log2(size))+1 );
		T *temp_elements = new T[capacity];
		std::copy(elements, elements+size, temp_elements);
		delete [] elements;
		elements = temp_elements;
		first = elements;
		last = elements+size;
	}

	template <typename T>
	typename vector<T>::iterator vector<T>::erase(iterator pos)
	{
		int index = pos-first;
		if(pos == end()-1 or pos == end())
		{
			last--;
			size--;
			return end();
		}

		if(pos != begin())
		{
			std::copy(elements+index+1, elements+size, elements+index);
			size--;
			last--;
			std::cout << "debug " << index-1 << std::endl;
			return elements+index;
		}		
		else
		{
			std::copy(elements+index+1, elements+size, elements+index);
			size--;
			last--;
			return elements;
		}
	} 

	template <typename T>
	typename vector<T>::iterator vector<T>::erase( iterator first, iterator last )
	{
		int index = first-first;
		int index_l = last-first;

		std::copy(elements+index_l, elements+size, elements+index);

		size -= last-first;
		last -= last-first;

		return elements+index;
	} 

	template <class T>
	const T &vector<T>::front() const
	{
		return *(this->first);
	}

	template <class T>
	const T &vector<T>::back() const
	{
		T *valid_l = this->last - 1;
		return *valid_l;
	}
	
	template <class T>
	T &vector<T>::at( size_type pos )
	{
		return ( this->elements[pos] );
	}

	template <class T>
	T& vector<T>::operator[]( size_type pos )
	{
		return this->elements[pos]; 
	}

	template <class T>
	vector<T> &vector<T>::operator=( const vector<T> &rhs )
	{
		if( this->size < rhs.size )
		{
			this->reserve( rhs.size );
		}

		this->capacity = rhs.capacity;
		this->size = rhs.size;
		this->first = this->elements; 
		this->last = this->elements + size;

		for( int i = 0; i < rhs.size; i++ )
		{
			this->elements[i] = rhs.elements[i];
		}

		return *this;
	}

	template <class T>
	vector<T> &vector<T>::operator=( std::initializer_list<T> ilist )
	{
		int temp_capacity;
		if( ilist.size() > 2 )
		{
			temp_capacity = pow( 2, int( log2( ilist.size() ) ) );
			if( ilist.size() > temp_capacity )
			{
				temp_capacity *= 2;
			}
		} 
		else 
		{
			temp_capacity = ilist.size();
		}

		this->elements = new T[temp_capacity];

		int buf = 0;
		for( auto i = std::begin(ilist); i != std::end(ilist); i++, buf++ )
		{
			elements[buf] = *i;
		}

		this->first = elements;
		this->last = elements + ilist.size();
		this->size = ilist.size();
		this->capacity = temp_capacity;

		if(debug) std::cout << ">> Saiu da função!" << std::endl;
	}

	template <class T>
	bool vector<T>::operator==( const vector &rhs )
	{
		if( rhs.size != this->size )
		{
			return false;
		} 
		else
		{
			for( int i = 0; i < rhs.size ; i++ )
			{
				if( *(this->first+i) != *(rhs.first + i) )
				{
					return false;
				}
			}
		}
		// if he ever gets to this point, they're equal
		return true;
	}

	template <class T>
	bool vector<T>::operator!=( const vector &rhs )
	{
		if( *this == rhs )
		{
			return false;
		} 
		else 
		{
			return true;
		}
	}

	template <class T>
	typename vector<T>::iterator vector<T>::begin()
	{
		return vector<T>::iterator(this->first);
	}

	template <class T>
	typename vector<T>::iterator vector<T>::end()
	{
		return vector<T>::iterator(this->last);
	}

	template <class T>
	typename vector<T>::const_iterator vector<T>::cbegin() const
	{
		return vector<T>::const_iterator(this->first);
	}

	template <class T>
	typename vector<T>::const_iterator vector<T>::cend() const
	{
		return vector<T>::const_iterator(this->last);
	}

	template <class T>
	vector<T>::iterator::iterator( T *ptr )
	{
		this->current = ptr;
	}

	template <class U>
	vector<U>::iterator::iterator( const vector<U>::iterator &itr )
	{
		this->current = itr.current;
	}

	template <class U>
	vector<U>::iterator::~iterator() = default;

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

	template <class T>
	vector<T>::const_iterator::const_iterator( T *ptr )
	{
		this->current = ptr;
	}

	template <class U>
	vector<U>::const_iterator::const_iterator( const vector<U>::const_iterator &itr )
	{
		this->current = itr.current;
		std::cout << "vector<U>::const_iterator::const_iterator( itr ) created.\n";
	}

	template <class U>
	vector<U>::const_iterator::~const_iterator() = default;

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
}