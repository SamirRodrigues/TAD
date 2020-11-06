#include "Vector.hpp"

namespace sc
{    
    template <typename T>
    class MyIterator 
    {
        public:
            // Below we have the iterator_traits common interface
            /// Difference type used to calculated distance between iterators.
            typedef std::ptrdiff_t difference_type;
            typedef T value_type; //!< Value type the iterator points to.
            typedef T* pointer; //!< Pointer to the value type.
            typedef T& reference; //!< Reference to the value type.
            typedef std::bidirectional_iterator_tag iterator_category; //!< Iterator category.
            MyIterator( );
            MyIterator& operator=( const MyIterator& ) = default;
            MyIterator( const MyIterator& ) = default;
            pointer operator ->( void ) const { assert( m_ptr != nullptr ); return m_ptr; }
            MyIterator& operator++ ( ); // ++it;
            MyIterator operator++ ( int ); // it++;
            MyIterator& operator-- ( ); // --it;
            MyIterator operator-- ( int ); // it--;
            friend MyIterator operator+( difference_type, MyIterator );
            friend MyIterator operator+( MyIterator, difference_type );
            friend MyIterator operator-( difference_type, MyIterator );
            friend MyIterator operator-( MyIterator, difference_type );
            bool operator== ( const MyIterator& ) const;
            bool operator!= ( const MyIterator& ) const;
        private:
            T *current;
    };
}
