#include "vector.hpp"

namespace sc
{	
	#pragma region ////=== [I] SPECIAL MEMBERS

	template <class T>
	vector<T>::vector( size_type count )
	{
		m_capacity = 2;

		if( count >= m_capacity )
		{
			while( count >= m_capacity)
			{
				m_capacity *= 2;
			}
		}

		// alocating [count] m_storage of type T
		m_storage = new T[m_capacity];

		for( int i = 0; i < count; i++ )
		{
			m_storage[i] = 0;
		}
		m_end = count;

	}

	template <class T>
	vector<T>::vector( void )
	{
		m_capacity = 2;	
		m_storage = new T[m_capacity];
		m_end = 0; 
	}

	template <class T>
	vector<T>::vector( const vector &other )
	{
		int temp_capacity;
		if( other.size() > 2 )
		{
			temp_capacity = int(2*other.size());

			if( other.size() > temp_capacity )
			{
				temp_capacity *= 2;
			}
		} 
		else 
		{
			temp_capacity = other.size();
		}

		m_storage = new T[temp_capacity];

		for( int i = 0; i < temp_capacity; i++ )
		{
			m_storage[i] = other.m_storage[i];	
		}

		m_end = other.size();
		m_capacity = temp_capacity;
	}

	template <class T>
	vector<T>::vector( std::initializer_list<T> ilist )
	{
		int temp_capacity;	

		if( ilist.size() > 2 )
		{
			temp_capacity = int (2*ilist.size());	

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
		int buf = 0;

		for( auto *i = ilist.begin(); i < ilist.end(); i++, buf++ )
		{
			m_storage[buf] = *i;
		}

		m_end = ilist.size();
		m_capacity = temp_capacity;
	}
	
	template <class InputIt>
	vector<InputIt>::vector( InputIt *first, InputIt *last )
	{
		int temp_capacity;		
		int size = std::distance(first, last);

		if( size > 2 )
		{
			temp_capacity = int(2*size);

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
		int buf = 0;

		for( auto *i = first; i < last; i++, buf++ )
		{
			m_storage[buf] = *i;
		}

		m_end = size;
		m_capacity = temp_capacity;
	}

	template <class T>
	vector<T>::~vector()
	{
		if(m_storage != NULL)
		{
			delete[] m_storage;
		}
	}
	
	#pragma endregion

	#pragma region  //=== [II] ITERATORS

	template <class T>
	typename vector<T>::iterator vector<T>::begin()
	{
		return vector<T>::iterator(m_storage);
	}

	template <class T>
	typename vector<T>::iterator vector<T>::end()
	{
		return vector<T>::iterator(m_storage+m_end);
	}

	template <class T>
	typename vector<T>::const_iterator vector<T>::cbegin() const
	{
		return vector<T>::const_iterator(m_storage);
	}

	template <class T>
	typename vector<T>::const_iterator vector<T>::cend() const
	{
		return vector<T>::const_iterator(m_storage+m_end);
	}

	#pragma endregion  //=== [II] ITERATORS

	#pragma region // [III] Capacity

	template <class T>
	bool vector<T>::empty()
	{
		return m_end == 0;
	}
	
	template <class T>
	size_type vector<T>::size() const
	{
		return m_end;
	}

	
	template <class T>
	size_type vector<T>::capacity() const
	{
		return m_capacity;
	}

	#pragma endregion  // [III] Capacity

	#pragma region  // [IV] Modifiers 

	template <class T>
	void vector<T>::reserve(size_type new_cap)
	{
		if( new_cap > m_capacity )
		{
			while(new_cap > m_capacity)
			{
				m_capacity *= 2;	
			}
			
			T * temp_storage = new T[m_capacity];

			std::copy( m_storage, m_storage+m_end, temp_storage );

            delete [] m_storage;
			
            m_storage = temp_storage;
		}
	}

	template <class T>
	void vector<T>::push_back( const T& value )
	{		
		if( m_end < m_capacity )
		{
			m_storage[m_end] = value;
			m_end++;
		} 
		else 
		{			
			reserve( m_capacity * 2 );	
			m_storage[m_end] = value;
			m_end++;
		}
	}

	template <typename T>
	void vector<T>::push_front(const T & value)
	{	
		if( m_end < m_capacity )
		{
			std::copy(m_storage, m_storage + m_end, m_storage+1);
			m_storage[0] = value;
			m_end += 1;
		} 
		else 
		{			
			reserve( m_capacity * 2 );	
			std::copy(m_storage, m_storage + m_end, m_storage+1);
			m_storage[0] = value;
			m_end += 1;
		}
	}
	
	template <typename T>
	void vector<T>::pop_front()
	{
		if(!empty()){
			std::copy(m_storage+1,m_storage+m_end,m_storage);
			m_end--;
		}
		else
		{
			throw std::runtime_error("Can't pop an empty vector");
		}
	}
	
	template <typename T>
	void vector<T>::pop_back()
	{
		if(!empty()){
			m_end--;
		}
		else
		{
			throw std::runtime_error("Can't pop an empty vector");
		}
	}

	template <typename T>
	typename vector<T>::iterator vector<T>::insert(iterator pos, const T &value)
	{
		int distance = pos - m_storage;

		if(++m_end >= m_capacity)
		{
			reserve(m_capacity*2);
		}		

		if(distance == m_end)
		{
			m_storage[m_end++] = value;
			return m_storage+m_end;
		}
		else
		{
			std::copy(m_storage+distance,m_storage+m_end,m_storage+distance+1);
			m_storage[distance] = value;
			m_end++;
		}

		return m_storage+distance;
	}

	template <typename T>
	typename vector<T>::iterator vector<T>::insert(iterator pos,iterator first, iterator last )
	{
		int distance = last-first;
		int first_index = pos-m_storage;

		T * temp_storage = new T[distance];	
		int index = 0;
		for (auto i = first; i != last; ++i,++index) 
		{
			temp_storage[index] = *i;
		}	

		reserve(m_end+distance);

		std::copy(m_storage+first_index, m_storage+m_end, m_storage+first_index+distance);
	
		m_end += distance;		

		std::copy(temp_storage,temp_storage+distance,m_storage+first_index);
	
		delete[] temp_storage;

		return m_storage+first_index; 
	}

	template <typename T>
	typename vector<T>::iterator vector<T>::insert(iterator pos,std::initializer_list<T> ilist)
	{
		int first_index = pos-m_storage;
		
		if(m_end+ilist.size() > m_capacity)
		{
			reserve(m_end+ilist.size());
		}
		
		std::copy(m_storage+first_index, m_storage+m_end, m_storage+first_index+ilist.size());
		std::copy(ilist.begin(), ilist.end(), m_storage+first_index);
	
		m_end += ilist.size();

		return m_storage+first_index; 
	}

	template <typename T>
	void vector<T>::clear(void)
	{
		delete[] m_storage;

		m_end = 0;

		m_storage = new T[m_capacity];
	}

	template <typename T>
	void vector<T>::assign(size_type count,  const T & value)
	{
		for (size_t i = 0; i < count; ++i) {
			m_storage[i] = value;	
		}

		m_end = count;

	}

	template <typename T>
	void vector<T>::assign(iterator first, iterator last)
	{			
		int count = 0;
		for (auto i = first;  i != last; i++) 
		{				
			m_storage[count] = *first;
			first++;
			count++;
		}

		m_end = count;
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
		m_end = ilist.size( )+1;
		std::copy(ilist.begin(), ilist.end(), m_storage);	
	}

	template <typename T>
	void vector<T>::shrink_to_fit(void)
	{
		m_capacity = m_end;
		T *temp_storage = new T[m_end];
		std::copy(m_storage, m_storage+m_end, temp_storage);
		delete [] m_storage;
		m_storage = temp_storage;

	}

	template <typename T>
	typename vector<T>::iterator vector<T>::erase(iterator pos)
	{
		int index = pos-m_storage;
		if(pos == end()-1 || pos == end())
		{
			m_end--;
			return end();
		}
		
		std::copy(m_storage+index+1, m_storage+m_end, m_storage+index);
		m_end--;
		return m_storage+index;
		
	} 

	template <typename T>
	typename vector<T>::iterator vector<T>::erase( iterator first, iterator last )
	{
		int index = first-m_storage;
		int index_l = last-m_storage;

		std::copy(m_storage+index_l, m_storage+m_end, m_storage+index);

		m_end -= last-first;

		return m_storage+index;
	} 

	template <class T>
	const T &vector<T>::front() const
	{
		return *m_storage;
	}

	template <class T>
	const T &vector<T>::back() const
	{
		T *valid_l = m_storage+m_end-1;
		return *valid_l;
	}
	
	template <class T>
	T &vector<T>::at( size_type pos )
	{
		if(pos >= m_end || pos < 0 /*0 == pos initial*/)
		{				
			throw std::out_of_range("Out Of Range, returning last element");						
			return m_storage[m_end-1];
		}

		return ( m_storage[pos] );
	}

	template <class T>
	T& vector<T>::operator[]( size_type pos )
	{
		return m_storage[pos];
	}

	template <class T>
	vector<T> &vector<T>::operator=( const vector<T> &rhs )
	{
		if( m_end < rhs.m_end )
		{
			reserve( rhs.m_end );
		}

		m_capacity = rhs.m_capacity;
		m_end = rhs.m_end;

		for( int i = 0; i < rhs.m_end; i++ )
		{
			m_storage[i] = rhs.m_storage[i];
		}

		return *this;
	}

	template <class T>
	vector<T> &vector<T>::operator=( std::initializer_list<T> ilist )
	{
		delete[] m_storage;

		int temp_capacity;
		if( ilist.size() > 2 )
		{
			temp_capacity = int(2*ilist.size());			
		} 
		else 
		{
			temp_capacity = ilist.size();
		}

		m_storage = new T[temp_capacity];

		int idx = 0;
		for( auto i = std::begin(ilist); i != std::end(ilist); i++)
		{
			m_storage[idx] = *i;
			idx++;
		}

		m_end = size_type(m_storage+ilist.size());
		m_end = ilist.size();
		m_capacity = temp_capacity;
	}

	template <class T>
	bool vector<T>::operator==( const vector &rhs )
	{
		if( rhs.m_end != m_end )
		{
			return false;
		} 
		else
		{
			for( int i = 0; i < rhs.m_end ; i++ )
			{
				if( *(m_storage+i) != *(rhs.m_storage + i) )
				{
					return false;
				}
			}
		}

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
	vector<T>::iterator::iterator( T *ptr )
	{
		current = ptr;
	}

	template <class T>
	vector<T>::iterator::iterator( const vector<T>::iterator &itr )
	{
		current = itr.current;
	}

	template <class T>
	vector<T>::iterator::~iterator() = default;

	template <class T>
	typename vector<T>::iterator &vector<T>::iterator::operator=( const vector::iterator &rhs )
	{
		current = rhs.current;
	}

	template <class T>
	bool vector<T>::iterator::operator==( const vector::iterator &rhs ) const
	{
		return current == rhs.current;
	}

	template <class T>
	bool vector<T>::iterator::operator!=( const vector::iterator &rhs ) const
	{
		return current != rhs.current;
	}

	template <class T>
	T &vector<T>::iterator::operator*( void ) const
	{
		return *current;
	}	

	template <class T>
	typename vector<T>::iterator vector<T>::iterator::operator-(int a )
	{
		return current-a;
	}

	template <class T>
	int vector<T>::iterator::operator-(iterator rhs )
	{
		return current-rhs.current;
	}

	template <class T>
	typename vector<T>::iterator vector<T>::iterator::operator+(int a )
	{
		return current+a;
	}

	template <class T>
	typename vector<T>::iterator vector<T>::iterator::operator++( void )
	{
		return ++current;
	}

	template <class T>
	typename vector<T>::iterator vector<T>::iterator::operator++( int )
	{
		return current++;
	}

	template <class T>
	typename vector<T>::iterator vector<T>::iterator::operator--( void )
	{
		return --current;
	}

	template <class T>
	typename vector<T>::iterator vector<T>::iterator::operator--( int )
	{
		return current--;
	}

	template <class T>
	vector<T>::const_iterator::const_iterator( T *ptr )
	{
		current = ptr;
	}

	template <class T>
	vector<T>::const_iterator::const_iterator( const vector<T>::const_iterator &itr )
	{
		current = itr.current;
	}

	template <class T>
	vector<T>::const_iterator::~const_iterator() = default;

	template <class T>
	typename vector<T>::const_iterator &vector<T>::const_iterator::operator=( const vector::const_iterator &rhs )
	{
		current = rhs.current;
	}

	template <class T>
	bool vector<T>::const_iterator::operator==( const vector::const_iterator &rhs ) const
	{
		return current == rhs.current;
	}

	template <class T>
	bool vector<T>::const_iterator::operator!=( const vector::const_iterator &rhs ) const
	{
		return current != rhs.current;
	}

	template <class T>
	const T &vector<T>::const_iterator::operator*( void ) const
	{
		return *current;
	}

	template <class T>
	typename vector<T>::const_iterator vector<T>::const_iterator::operator++( void )
	{
		return ++current;
	}

	template <class T>
	typename vector<T>::const_iterator vector<T>::const_iterator::operator-(int a )
	{
		return current-a;
	}

	template <class T>
	int vector<T>::const_iterator::operator-(const_iterator rhs )
	{
		return current-rhs.current;
	}

	template <class T>
	typename vector<T>::const_iterator vector<T>::const_iterator::operator+(int a )
	{
		return current+a;
	}

	template <class T>
	typename vector<T>::const_iterator vector<T>::const_iterator::operator++( int )
	{
		return current++;
	}

	template <class T>
	typename vector<T>::const_iterator vector<T>::const_iterator::operator--( void )
	{
		return --current;
	}

	template <class T>
	typename vector<T>::const_iterator vector<T>::const_iterator::operator--( int )
	{
		return current--;
	}
}