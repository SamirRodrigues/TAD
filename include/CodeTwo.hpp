    void assign( syze_type, const_reference );
    void assign( const std::initializer_list<T>& );
    template < typename, InputItr >
    void assign( InputItr, InputItr );

    iterator erase( iterator, iterator );
    iterator erase( iterator );

    //[V] Element access
    const_reference back( void ) const;
    reference back( void );
    const_reference front( void ) const;
    reference front( void );
    const_reference operator[]( size_type ) const;
    const_reference at( size_type ) const;
    reference at( size_type );
    pointer data( void );
    const_reference data( void ) const;

    // [VII] Friend functions.
    friend std::ostream& operator <<( std::ostream&, const vector<T>& );
    friend void swap( vector<T>&, vector<T>& );

private:
    size_type m_end; //!< Current list size (or index past-last valid element).
    size_type m_capacity; //!< List’s storage capacity.
    //std::unique_ptr<T[]> m_storage; //!< Data storage area for the dynamic array.
    T *m_storage; //!< Data storage area for the dynamic array.
);