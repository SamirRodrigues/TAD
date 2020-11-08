#include "vector.hpp"

namespace tam
{	
	void bug(std::string phrase){
		std::cout << "\e[31;4;1m";
		std::cout << "~ " << phrase;
		std::cout << "\e[0m" << std::endl;
	}
	
}

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

		// alocating [count] m_storage of type T
		this->m_storage = new T[m_capacity];

		for( int i = 0; i < count; i++ )
		{
			if(debug) m_storage[i] = i;			// debug inicializer
			else m_storage[i] = 0;				// normal inicializer
		}

		this->m_first = m_storage;
		this->m_last = m_storage + count;
		this->m_end = count;

		if(debug) tam::bug( "> vector allocated with sucess!" );
	}

	template <class T>
	vector<T>::vector( void )
	{
		int temp_capacity = 2;		

		this->m_storage = new T[temp_capacity];
		this->m_first = m_storage;
		this->m_last = m_storage;
		this->m_end = 0; 
		this->m_capacity = temp_capacity;

		if(debug) tam::bug( "> vector allocated with sucess!" );
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

		this->m_storage = new T[temp_capacity];

		for( int i = 0; i < temp_capacity; i++ )
		{
			m_storage[i] = other.m_storage[i];	
		}

		this->m_first = m_storage;
		this->m_last = m_storage + other.size();
		this->m_end = other.size();
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

		this->m_storage = new T[temp_capacity];
		int buf = 0;

		for( auto *i = ilist.begin(); i < ilist.end(); i++, buf++ )
		{
			m_storage[buf] = *i;
		}

		this->m_first = m_storage;
		this->m_last = m_storage + ilist.size();
		this->m_end = ilist.size();
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

		this->m_storage = new InputIt[temp_capacity];
		int buf = 0;

		for( auto *i = first; i < last; i++, buf++ )
		{
			m_storage[buf] = *i;
		}

		this->m_first = m_storage;
		this->m_last = m_storage + size;
		this->m_end = size;
		this->m_capacity = temp_capacity;
	}

	template <class T>
	vector<T>::~vector()
	{
		if(m_storage != NULL)
		{
			delete[] m_storage;
			if(debug) tam::bug ( "> vector deleted with sucess!" );
		}
	}
	
	template <class T>
	bool vector<T>::empty()
	{
		return (m_end == 0 ? true : false);
	}
	
	template <class T>
	size_type vector<T>::size() const
	{
		return this->m_end;
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
			if(m_first != m_last) std::copy( m_storage, m_last, temp_elements );
			delete [] m_storage;
			m_storage = temp_elements;
			m_first = m_storage;
			m_last = m_storage+m_end;
		}
	}

	template <class T>
	void vector<T>::push_back( const T& value )
	{		
		if( m_end < m_capacity )
		{
			*(m_last++) = value;
			m_end += 1;
		} 
		else 
		{			
			this->reserve( m_capacity * 2 );	
			m_end += 1;
			*(m_last++) = value;
		}
	}

	template <typename T>
	void vector<T>::push_front(const T & value)
	{	
		if(m_end <= 2)
		{
			this->reserve(2);
			m_end += 1;

			if(m_end >= 1)
			{
				 std::copy(m_first,m_last,m_first+1);
			}

			m_last++;
			*m_first = value;
		}
		
		else if( m_end < m_capacity )
		{
			std::copy(m_first,m_last,m_first+1);
			*m_first = value;
			m_end += 1;
			m_last++;
		} 
		else 
		{			
			this->reserve( m_capacity * 2 );	
			m_end += 1;
			std::copy(m_first,m_last,m_first+1);
			*m_first = value;
			m_last++;
		}
	}
	
	template <typename T>
	void vector<T>::pop_front()
	{
		if(m_end != 0){
			std::copy(m_first+1,m_last,m_first);
			m_end--;
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
		if(m_end != 0){
			m_end--;
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
		if(++m_end >= m_capacity)
		{
			this->reserve(m_capacity*2);
			reserved = true;
		}
		
		if(debug) tam::bug ( "Distance: "  ); std::cout << distance << std::endl;

		if(distance == m_end)
		{
			*m_last = value;
			if(!reserved) m_last++;
			return m_storage+m_end;
		}
		else
		{
			T temp;
			std::copy(m_storage+distance,m_storage+m_end,m_storage+distance+1);
			*(m_storage+distance) = value;
			if(!reserved) m_last++;
		}

		return m_storage+distance;
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
			tam::bug ( "Before : ");
			std::copy(temp,temp+distance, std::ostream_iterator<int>(std::cout ," "));
			tam::bug ( "first_index : " ); std::cout << first_index << std::endl;
		}

		reserve(m_end+distance);

		std::copy(m_storage+first_index, m_storage+m_end, m_storage+first_index+distance);
	
		m_end += distance;
		
		if(debug) 
		{
			tam::bug ( "After : ");
			std::copy(m_storage,m_storage+m_end,	std::ostream_iterator<int>( std::cout ," " ));
			std::cout << std::endl;
		}

		std::copy(temp,temp+distance,m_storage+first_index);
		
		m_last += distance;
		return m_storage+first_index; 
	}

	template <typename T>
	typename vector<T>::iterator vector<T>::insert(iterator pos,std::initializer_list<T> ilist)
	{
		int first_index = pos-m_first;
		if(debug)
		{
			tam::bug ( "Before : ");
			tam::bug ( "Cap : "); std::cout << capacity() << std::endl;
			tam::bug ( "size : " ); std::cout << size() << std::endl;
			std::copy(m_first,m_last, std::ostream_iterator<int>(std::cout ," "));
			std::cout << std::endl;
		}
		
		if(m_end+ilist.size() > m_capacity)
		{
			reserve(m_end+ilist.size());
		}
		
		std::copy(m_storage+first_index, m_storage+m_end, m_storage+first_index+ilist.size());
		std::copy(ilist.begin(), ilist.end(), m_storage+first_index);
	
		m_end += ilist.size();
		m_last += ilist.size();

		if(debug) 
		{
			tam::bug ( "After : ");
			tam::bug ( "Cap : "); std::cout << capacity() << std::endl;
			tam::bug ( "size : "); std::cout << size() << std::endl;
			std::copy(m_storage, m_storage+m_end, std::ostream_iterator<int>(std::cout ," "));
			std::cout<< std::endl;
		}

		return m_storage+first_index; 
	}

	template <typename T>
	void vector<T>::clear(void)
	{
		m_end = 0;
		m_first = m_storage;
		m_last = m_storage;
	}

	template <typename T>
	void vector<T>::assign(size_type count,  const T & value)
	{
		clear();
		reserve(count);

		for (int i = 0; i < count; ++i) {
			m_storage[i] = value;	
		}

		m_last += count;
		m_end += count;
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
			m_end++;
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
		m_end+= ilist.size();
		std::copy(ilist.begin(), ilist.end(), m_storage);	
	}

	template <typename T>
	void vector<T>::shrink_to_fit(void)
	{
		m_capacity = pow( 2, int(log2(m_end))+1 );
		T *temp_elements = new T[m_capacity];
		std::copy(m_storage, m_storage+m_end, temp_elements);
		delete [] m_storage;
		m_storage = temp_elements;
		m_first = m_storage;
		m_last = m_storage+m_end;
	}

	template <typename T>
	typename vector<T>::iterator vector<T>::erase(iterator pos)
	{
		int index = pos-m_first;
		if(pos == end()-1 or pos == end())
		{
			m_last--;
			m_end--;
			return end();
		}

		if(pos != begin())
		{
			std::copy(m_storage+index+1, m_storage+m_end, m_storage+index);
			m_end--;
			m_last--;
			tam::bug ( "debug "); std::cout << index-1 << std::endl;
			return m_storage+index;
		}		
		else
		{
			std::copy(m_storage+index+1, m_storage+m_end, m_storage+index);
			m_end--;
			m_last--;
			return m_storage;
		}
	} 

	template <typename T>
	typename vector<T>::iterator vector<T>::erase( iterator first, iterator last )
	{
		int index = first-m_first;
		int index_l = last-m_first;

		std::copy(m_storage+index_l, m_storage+m_end, m_storage+index);

		m_end -= last-first;
		m_last -= last-first;

		return m_storage+index;
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
		return ( this->m_storage[pos] );
	}

	template <class T>
	T& vector<T>::operator[]( size_type pos )
	{
		return this->m_storage[pos]; 
	}

	template <class T>
	vector<T> &vector<T>::operator=( const vector<T> &rhs )
	{
		if( this->m_end < rhs.m_end )
		{
			this->reserve( rhs.m_end );
		}

		this->m_capacity = rhs.m_capacity;
		this->m_end = rhs.m_end;
		this->m_first = this->m_storage; 
		this->m_last = this->m_storage + m_end;

		for( int i = 0; i < rhs.m_end; i++ )
		{
			this->m_storage[i] = rhs.m_storage[i];
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

		this->m_storage = new T[temp_capacity];

		int buf = 0;
		for( auto i = std::begin(ilist); i != std::end(ilist); i++, buf++ )
		{
			m_storage[buf] = *i;
		}

		this->m_first = m_storage;
		this->m_last = m_storage + ilist.size();
		this->m_end = ilist.size();
		this->m_capacity = temp_capacity;

		if(debug) tam::bug (">> Saiu da função!"); std::cout << std::endl;
	}

	template <class T>
	bool vector<T>::operator==( const vector &rhs )
	{
		if( rhs.m_end != this->m_end )
		{
			return false;
		} 
		else
		{
			for( int i = 0; i < rhs.m_end ; i++ )
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