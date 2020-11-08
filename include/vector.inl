#include "vector.hpp"

namespace sc
{	
	template <class T>
	vector<T>::vector( size_type count )
	{
		m_capacity = 2;

		if( count >= 2 )
		{
			while( count >= m_capacity)
			{
				m_capacity *= 2;
			}
		}

		// alocating [count] elements of type T
		this->elements = new T[m_capacity];

		for( int i = 0; i < count; i++ )
		{
			if(debug) elements[i] = i;			// debug inicializer
			else elements[i] = 0;				// normal inicializer
		}

		this->m_first = elements;
		this->m_last = elements + count;
		this->m_size = count;

		if(debug) std::cout << "> vector allocated with sucess!" << std::endl;
	}

	template <class T>
	vector<T>::vector( void )
	{
		int temp_capacity = 2;		

		this->elements = new T[temp_capacity];
		this->m_first = elements;
		this->m_last = elements;
		this->m_size = 0; 
		this->m_capacity = temp_capacity;

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

		this->m_first = elements;
		this->m_last = elements + other.size();
		this->m_size = other.size();
		this->m_capacity = temp_capacity;
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

		this->m_first = elements;
		this->m_last = elements + ilist.size();
		this->m_size = ilist.size();
		this->m_capacity = temp_capacity;
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

		this->m_first = elements;
		this->m_last = elements + size;
		this->m_size = size;
		this->m_capacity = temp_capacity;
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
		return (m_size == 0 ? true : false);
	}
	
	template <class T>
	size_type vector<T>::size() const
	{
		return this->m_size;
	}

	
	template <class T>
	size_type vector<T>::capacity() const
	{
		return this->m_capacity;
	}

	template <class T>
	void vector<T>::reserve(size_type new_cap)
	{
		if( new_cap > m_capacity )
		{
			while(new_cap > m_capacity)
			{
				m_capacity *= 2;	
			}
			
			T *temp_elements = new T[m_capacity];
			if(m_first != m_last) std::copy( elements, m_last, temp_elements );
			delete [] elements;
			elements = temp_elements;
			m_first = elements;
			m_last = elements+m_size;
		}
	}

	template <class T>
	void vector<T>::push_back( const T& value )
	{		
		if( m_size < m_capacity )
		{
			*(m_last++) = value;
			m_size += 1;
		} 
		else 
		{			
			this->reserve( m_capacity * 2 );	
			m_size += 1;
			*(m_last++) = value;
		}
	}

	template <typename T>
	void vector<T>::push_front(const T & value)
	{	
		if(m_size <= 2)
		{
			this->reserve(2);
			m_size += 1;

			if(m_size >= 1)
			{
				 std::copy(m_first,m_last,m_first+1);
			}

			m_last++;
			*m_first = value;
		}
		
		else if( m_size < m_capacity )
		{
			std::copy(m_first,m_last,m_first+1);
			*m_first = value;
			m_size += 1;
			m_last++;
		} 
		else 
		{			
			this->reserve( m_capacity * 2 );	
			m_size += 1;
			std::copy(m_first,m_last,m_first+1);
			*m_first = value;
			m_last++;
		}
	}
	
	template <typename T>
	void vector<T>::pop_front()
	{
		if(m_size != 0){
			std::copy(m_first+1,m_last,m_first);
			m_size--;
			m_last--;
		}
		else
		{
			throw std::runtime_error("Don't pop an empty vector");
		}
	}
	
	template <typename T>
	void vector<T>::pop_back()
	{
		if(m_size != 0){
			m_size--;
			m_last--;
		}
		else
		{
			throw std::runtime_error("Don't pop an empty vector");
		}
	}

	template <typename T>
	typename vector<T>::iterator vector<T>::insert(iterator pos, const T &value)
	{
		int distance = pos - m_first;

		bool reserved = false;	
		if(++m_size >= m_capacity)
		{
			this->reserve(m_capacity*2);
			reserved = true;
		}
		
		if(debug) std::cout << "Distance: " << distance << std::endl;

		if(distance == m_size)
		{
			*m_last = value;
			if(!reserved) m_last++;
			return elements+m_size;
		}
		else
		{
			T temp;
			std::copy(elements+distance,elements+m_size,elements+distance+1);
			*(elements+distance) = value;
			if(!reserved) m_last++;
		}

		return elements+distance;
	}

	template <typename T>
	typename vector<T>::iterator vector<T>::insert(iterator pos,iterator first, iterator last )
	{
		int distance = last-first;
		int first_index = pos-m_first;

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

		reserve(m_size+distance);

		std::copy(elements+first_index, elements+m_size, elements+first_index+distance);
	
		m_size += distance;
		
		if(debug) 
		{
			std::cout << "After : ";
			std::copy(elements,elements+m_size,	std::ostream_iterator<int>( std::cout ," " ));
			std::cout << std::endl;
		}

		std::copy(temp,temp+distance,elements+first_index);
		
		m_last += distance;
		return elements+first_index; 
	}

	template <typename T>
	typename vector<T>::iterator vector<T>::insert(iterator pos,std::initializer_list<T> ilist)
	{
		int first_index = pos-m_first;
		if(1)
		{
			std::cout << "Before : ";
			std::cout << "Cap : " << capacity() << std::endl;
			std::cout << "size : " << size() << std::endl;
			std::copy(m_first,m_last, std::ostream_iterator<int>(std::cout ," "));
			std::cout << std::endl;
		}
		
		if(m_size+ilist.size() > m_capacity)
		{
			reserve(m_size+ilist.size());
		}
		
		std::copy(elements+first_index, elements+m_size, elements+first_index+ilist.size());
		std::copy(ilist.begin(), ilist.end(), elements+first_index);
	
		m_size += ilist.size();
		m_last += ilist.size();

		if(1) 
		{
			std::cout << "After : ";
			std::cout << "Cap : " << capacity() << std::endl;
			std::cout << "size : " << size() << std::endl;
			std::copy(elements, elements+m_size, std::ostream_iterator<int>(std::cout ," "));
			std::cout << std::endl;
		}

		return elements+first_index; 
	}

	template <typename T>
	void vector<T>::clear(void)
	{
		m_size = 0;
		m_first = elements;
		m_last = elements;
	}

	template <typename T>
	void vector<T>::assign(size_type count,  const T & value)
	{
		clear();
		reserve(count);

		for (int i = 0; i < count; ++i) {
			elements[i] = value;	
		}

		m_last += count;
		m_size += count;
	}

	template <typename T>
	void vector<T>::assign(iterator first, iterator last)
	{	
		int distance = last-first;
		clear();
		reserve(distance);

		for (auto i(first);  i != last;++i ) 
		{
			*m_last++ = *i;	
			m_size++;
		}
	}

	template <typename T>
	void vector<T>::assign(std::initializer_list<T> ilist)
	{
		if(m_capacity < ilist.size())
		{
			while(m_capacity < ilist.size( ))
			{
				m_capacity *= 2;	
			}
			
			reserve(m_capacity);
		}

		clear();	
		m_last+= ilist.size();
		m_size+= ilist.size();
		std::copy(ilist.begin(), ilist.end(), elements);	
	}

	template <typename T>
	void vector<T>::shrink_to_fit(void)
	{
		m_capacity = pow( 2, int(log2(m_size))+1 );
		T *temp_elements = new T[m_capacity];
		std::copy(elements, elements+m_size, temp_elements);
		delete [] elements;
		elements = temp_elements;
		m_first = elements;
		m_last = elements+m_size;
	}

	template <typename T>
	typename vector<T>::iterator vector<T>::erase(iterator pos)
	{
		int index = pos-m_first;
		if(pos == end()-1 or pos == end())
		{
			m_last--;
			m_size--;
			return end();
		}

		if(pos != begin())
		{
			std::copy(elements+index+1, elements+m_size, elements+index);
			m_size--;
			m_last--;
			std::cout << "debug " << index-1 << std::endl;
			return elements+index;
		}		
		else
		{
			std::copy(elements+index+1, elements+m_size, elements+index);
			m_size--;
			m_last--;
			return elements;
		}
	} 

	template <typename T>
	typename vector<T>::iterator vector<T>::erase( iterator first, iterator last )
	{
		int index = first-m_first;
		int index_l = last-m_first;

		std::copy(elements+index_l, elements+m_size, elements+index);

		m_size -= last-first;
		m_last -= last-first;

		return elements+index;
	} 

	template <class T>
	const T &vector<T>::front() const
	{
		return *(this->m_first);
	}

	template <class T>
	const T &vector<T>::back() const
	{
		T *valid_l = this->m_last - 1;
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
		if( this->m_size < rhs.m_size )
		{
			this->reserve( rhs.m_size );
		}

		this->m_capacity = rhs.m_capacity;
		this->m_size = rhs.m_size;
		this->m_first = this->elements; 
		this->m_last = this->elements + m_size;

		for( int i = 0; i < rhs.m_size; i++ )
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

		this->m_first = elements;
		this->m_last = elements + ilist.size();
		this->m_size = ilist.size();
		this->m_capacity = temp_capacity;

		if(debug) std::cout << ">> Saiu da função!" << std::endl;
	}

	template <class T>
	bool vector<T>::operator==( const vector &rhs )
	{
		if( rhs.m_size != this->m_size )
		{
			return false;
		} 
		else
		{
			for( int i = 0; i < rhs.m_size ; i++ )
			{
				if( *(this->m_first+i) != *(rhs.m_first + i) )
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
		return vector<T>::iterator(this->m_first);
	}

	template <class T>
	typename vector<T>::iterator vector<T>::end()
	{
		return vector<T>::iterator(this->m_last);
	}

	template <class T>
	typename vector<T>::const_iterator vector<T>::cbegin() const
	{
		return vector<T>::const_iterator(this->m_first);
	}

	template <class T>
	typename vector<T>::const_iterator vector<T>::cend() const
	{
		return vector<T>::const_iterator(this->m_last);
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