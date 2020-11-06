template < typename T >
class vector {
    public:
        using size_type = unsigned long;                //!< The size type.
        using value_type = T;                           //!< The value type.
        using pointer = value_type*;                    //!< Pointer to a value stored in the container.
        using reference = value_type&;                  //!< Reference to a value stored in the container.
        using const_reference = const value_type&;      //!< Const reference to a value stored in the co
        using iterator = MyIterator< T >                // See Code 3
        using const_iterator = MyIterator< const T > >  // See Code 3

        //=== [I] SPECIAL MEMBERS
        explicit vector ( size_type );
        virtual ~vector ( void );
        vector( const vector & );
        vector( std::initializer_list<T> );
        vector( vector && );
        template < typename InputItr >
        vector( InputItr, InputItr );
        vector& op e r a to r=( const vector& );
        vector& op e r a to r=( vector && );

        //=== [II] ITERATORS
        iterator begin( void );
        iterator end( void );
        const_iterator cbegin( void ) const;
        const_iterator cend( void ) const;

        // [III] Capacity
        size_type size( void ) const;
        size_type capacity( void ) const;
        bool empty( void ) const;

        // [IV] Modifiers
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

}