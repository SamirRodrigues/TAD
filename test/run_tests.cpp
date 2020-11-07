#include<iostream>
#include<vector>

#include "../lib/test_manager.h"
#include "../include/vector.hpp"
#include "../include/vector.inl"

#define which_lib sc
// ============================================================================
// TESTING VECTOR AS A CONTAINER OF INTEGERS
// ============================================================================

int main( void )
{
    TestManager tm{ "IntVector"};
    {
        BEGIN_TEST(tm,"ConstructorSize", "checking the initialize with default constructor.");

        which_lib::vector<int> vec;
        
        EXPECT_EQ( vec.size(), 0);
        EXPECT_EQ( vec.capacity(), 0);
        EXPECT_TRUE( vec.empty() );
    }

    {
        BEGIN_TEST(tm,"ListContructor", "checking the initialize with a list of integers");
       
        which_lib::vector<int> vec{ 1, 2, 3, 4, 5 };

        EXPECT_EQ( vec.size(), 5 );
        EXPECT_FALSE( vec.empty() );

        for( auto i{0u} ; i < vec.size() ; ++i )
            EXPECT_EQ( i+1, vec[i] );
    }   
     
    {
     BEGIN_TEST(tm,"RangeConstructor", "checking constructors with a range of values");
        // Range = the entire vector.
        which_lib::vector<int> vec{ 1, 2, 3, 4, 5 };
        which_lib::vector<int> vec2( vec.begin(), vec.end() );
        
        EXPECT_EQ( vec2.size(), 5 );
        EXPECT_FALSE( vec.empty() );

        for( auto i{0u} ; i < vec.size() ; ++i )
            EXPECT_EQ( i+1, vec[i] );

        // Range is part of the vector.
        which_lib::vector<int> vec3( std::next( vec.begin(), 1 ), std::next( vec.begin(), 3 ) );
        EXPECT_EQ( vec3.size(), 2 );
        EXPECT_FALSE( vec3.empty() );

        for( auto i{0u} ; i < vec3.size() ; ++i )
            EXPECT_EQ( vec[i+1], vec3[i] );
    }
    
    {
        BEGIN_TEST(tm, "CopyConstructor","constructor copy values of another vector.");
        // Range = the entire vector.
        which_lib::vector<int> vec{ 1, 2, 3, 4, 5 };
        which_lib::vector<int> vec2( vec );

        EXPECT_EQ( vec2.size(), 5 );
        EXPECT_FALSE( vec2.empty() );

        // CHeck whether the copy worked.
        for( auto i{0u} ; i < vec2.size() ; ++i )
            EXPECT_EQ( i+1, vec2[i] );

        // Change the original vector and check
        // whether that also changes the second vec.
        vec[2] = 10;
        for( auto i{0u} ; i < vec.size() ; ++i )
            EXPECT_EQ( i+1, vec2[i] );
    }

    {
        BEGIN_TEST(tm, "MoveConstructor", "move the elements from another");
        // Range = the entire vector.
        which_lib::vector<int> vec{ 1, 2, 3, 4, 5 };
        which_lib::vector<int> vec2( std::move( vec ) );
        
        EXPECT_EQ( vec2.size(), 5 );
        // EXPECT_FALSE( vec2.empty() );

        // CHeck whether the copy worked.
        for( auto i{0u} ; i < vec2.size() ; ++i )
            EXPECT_EQ( i+1, vec2[i] );
    }


    {
        BEGIN_TEST(tm, "AssignOperator", "ASSIGN OPERATOR");
        // Range = the entire vector.
        which_lib::vector<int> vec{ 1, 2, 3, 4, 5 };
        which_lib::vector<int> vec2;

        vec2 = vec;
        EXPECT_EQ( vec2.size(), 5 );
        EXPECT_FALSE( vec2.empty() );

        // CHeck whether the copy worked.
        for( auto i{0u} ; i < vec2.size() ; ++i )
            EXPECT_EQ( i+1, vec2[i] );
    }

    
    {
        BEGIN_TEST(tm, "MoveAssignOperator", "MoveAssignOperator");
        // Range = the entire vector.
        which_lib::vector<int> vec{ 1, 2, 3, 4, 5 };
        which_lib::vector<int> vec2;

        vec2 = std::move( vec );
        EXPECT_EQ( vec2.size(), 5 );
        EXPECT_FALSE( vec2.empty() );
        EXPECT_EQ( vec.size(), 0 );
        EXPECT_EQ( vec.capacity(), 0 );
        EXPECT_TRUE( vec.empty() );

        // CHeck whether the copy worked.
        for( auto i{0u} ; i < vec2.size() ; ++i )
            EXPECT_EQ( i+1, vec2[i] );
    }


    {
        BEGIN_TEST(tm, "ListInitializerAssign","ListInitializerAssign");
        // Range = the entire vector.
        sc::vector<int> vec = { 1, 2, 3, 4, 5 };

        EXPECT_EQ( vec.size(), 5 );
        EXPECT_EQ( vec.capacity(), 5 );
        EXPECT_FALSE( vec.empty() );

        // CHeck whether the copy worked.
        for( auto i{0u} ; i < vec.size() ; ++i )
            EXPECT_EQ( i+1, vec[i] );
    }


    {
        BEGIN_TEST(tm, "Clear", "clear");
        // Range = the entire vector.
        which_lib::vector<int> vec = { 1, 2, 3, 4, 5 };

        EXPECT_EQ( vec.size(), 5 );
        EXPECT_EQ( vec.capacity(), 5 );
        EXPECT_FALSE( vec.empty() );

        vec.clear();

        EXPECT_EQ( vec.size(), 0 );
        EXPECT_EQ( vec.capacity(), 5 );
        EXPECT_TRUE( vec.empty() );
    }

    {
        BEGIN_TEST(tm, "PushFront","PushFront");
        // #1 From an empty vector.
        sc::vector<int> vec;

        EXPECT_TRUE( vec.empty() );
        for ( auto i{0} ; i < 5 ; ++i )
        {
            vec.push_front( i+1 );
            EXPECT_EQ( vec.size(),  i+1 );
        }
        EXPECT_FALSE( vec.empty() );

        for( auto i{4u} ; i >= vec.size() ; --i )
            EXPECT_EQ( i+1, vec[i] );

        // REmove all elements.
        vec.clear();
        EXPECT_TRUE(vec.empty()  );
        for ( auto i{0} ; i < 5 ; ++i )
        {
            vec.push_front( i+1 );
            EXPECT_EQ( vec.size(),  i+1 );
        }
        EXPECT_FALSE( vec.empty() );

        for( auto i{4u} ; i >= vec.size() ; --i )
            EXPECT_EQ( i+1, vec[i] );
    }


    {
        BEGIN_TEST(tm, "PushBack", "PushBack");
        // #1 From an empty vector.
        which_lib::vector<int> vec;

        EXPECT_TRUE( vec.empty() );
        for ( auto i{0} ; i < 5 ; ++i )
        {
            vec.push_back( i+1 );
            EXPECT_EQ( vec.size(),  i+1 );
        }
        EXPECT_FALSE( vec.empty() );

        for( auto i{4u} ; i >= vec.size() ; --i )
            EXPECT_EQ( i+1, vec[i] );

        // REmove all elements.
        vec.clear();
        EXPECT_TRUE( vec.empty()  );
        for ( auto i{0} ; i < 5 ; ++i )
        {
            vec.push_back( i+1 );
            EXPECT_EQ( vec.size(),  i+1 );
        }
        EXPECT_FALSE( vec.empty() );

        for( auto i{4u} ; i >= vec.size() ; --i )
            EXPECT_EQ( i+1, vec[i] );
    }

    {
        BEGIN_TEST(tm, "PopBack", "PopBack");
        // #1 From an empty vector.
        which_lib::vector<int> vec{ 1, 2, 3, 4, 5 };

        while( not vec.empty() )
        {
            vec.pop_back();
            // Checke whether we have the same list except for the last.
            for( auto i{0u} ; i < vec.size() ; ++i )
                EXPECT_EQ( i+1, vec[i] );
        }
    }


    {
        BEGIN_TEST(tm, "PopFront", "PopFront");
        // #1 From an empty vector.
        which_lib::vector<int> vec{ 1, 2, 3, 4, 5 };

        auto start{2};
        while( not vec.empty() )
        {
            vec.pop_front();
            // Checke whether we have the same list except for the last.
            for( auto i{0u} ; i < vec.size() ; ++i )
                EXPECT_EQ( start+i, vec[i] );

            start++;
        }
    }


    {
        BEGIN_TEST(tm, "Front", "front");
        // #1 From an empty vector.
        which_lib::vector<int> vec{ 1, 2, 3, 4, 5 };

        auto i{0};
        while( not vec.empty() )
        {
            auto current_size = vec.size();
            EXPECT_EQ( vec.front(), ++i );
            vec.front() = 100;
            EXPECT_EQ( current_size, vec.size() );
            EXPECT_EQ( vec[0], 100 );

            vec.pop_front();
        }
    }

    {
        BEGIN_TEST(tm, "FrontConst","FrontConst");
        // #1 From an empty vector.
        const sc::vector<int> vec{ 1, 2, 3, 4, 5 };
        EXPECT_EQ( vec.front(), 1 );

        const sc::vector<char> vec2{ 'a', 'e', 'i', 'o', 'u' };
        EXPECT_EQ( vec2.front(), 'a' );
    }


{
    BEGIN_TEST(tm, "Back","Back");
    // #1 From an empty vector.
    sc::vector<int> vec{ 1, 2, 3, 4, 5 };

    auto i{5};
    while( not vec.empty() )
    {
        auto current_size = vec.size();
        EXPECT_EQ( vec.back(), i-- );
        vec.back() = 100;
        EXPECT_EQ( current_size, vec.size() );
        EXPECT_EQ( vec[vec.size()-1], 100 );
        vec.pop_back();
    }
}


{
    BEGIN_TEST(tm, "BackConst","BackConst");
    // #1 From an empty vector.
    const sc::vector<int> vec{ 1, 2, 3, 4, 5 };
    EXPECT_EQ( vec.back(), 5 );

    const sc::vector<char> vec2{ 'a', 'e', 'i', 'o', 'u' };
    EXPECT_EQ( vec2.back(), 'u' );
}


{
    BEGIN_TEST(tm, "AssignCountValue","AssignCountValue");
    // #1 From an empty vector.
    sc::vector<long> vec{ 1, 2, 3, 4, 5 };

    EXPECT_EQ( vec.size(), 5 );
    auto original_cap = vec.capacity();

    // Test assign with a count smaller than the original vec size.
    long value{-4};
    vec.assign( 3, value );
    EXPECT_EQ( vec.size(), 3 );
    // Capacity should be the same.
    EXPECT_EQ( vec.capacity(), original_cap );
    // Verify the elements.
    for ( auto i{0u} ; i < vec.size() ; ++i )
        EXPECT_EQ( value, vec[i] );

    // Test assign with a count GREATER than the original vec size.
    long new_value{42};
    vec.assign( 10, new_value );
    EXPECT_EQ( vec.size(), 10 );
    EXPECT_GE( vec.capacity(), original_cap );
    // Verify the elements.
    for ( auto i{0u} ; i < vec.size() ; ++i )
        EXPECT_EQ( new_value, vec[i] );
}




{
    BEGIN_TEST(tm, "OperatorBracketsRHS","OperatorBracketsRHS");
    const sc::vector<int> vec { 1, 2, 3, 4, 5 };
    const sc::vector<int> vec2 { 1, 2, 3, 4, 5 };

    for ( auto i{0u} ; i < vec.size() ; ++i )
        EXPECT_EQ( vec[i], vec2[i]);
}


{
    BEGIN_TEST(tm, "OperatorBracketsLHS","OperatorBracketsLHS");
    sc::vector<int> vec { 1, 2, 3, 4, 5 };
    sc::vector<int> vec2 { 10, 20, 30, 40, 50 };

    for ( auto i{0u} ; i < vec.size() ; ++i )
        vec[i] = vec2[i];
    for ( auto i{0u} ; i < vec.size() ; ++i )
        EXPECT_EQ( vec[i], vec2[i]);
}


{
    BEGIN_TEST(tm, "AtRHS","AtRHS");
    const sc::vector<int> vec { 1, 2, 3, 4, 5 };
    const sc::vector<int> vec2 { 1, 2, 3, 4, 5 };

    for ( auto i{0u} ; i < vec.size() ; ++i )
        EXPECT_EQ( vec.at(i), vec2.at(i));

    bool worked{false};
    try { vec.at( 40 ); }
    catch( std::out_of_range & e )
    { worked = true; }

    EXPECT_TRUE( worked );
}


{
    BEGIN_TEST(tm, "AtLHS","AtLHS");
    sc::vector<int> vec { 1, 2, 3, 4, 5 };
    sc::vector<int> vec2 { 10, 20, 30, 40, 50 };

    for ( auto i{0u} ; i < vec.size() ; ++i )
        vec.at(i) = vec2.at(i);
    for ( auto i{0u} ; i < vec.size() ; ++i )
        EXPECT_EQ( vec.at(i), vec2.at(i) );

    bool worked{false};
    try { vec.at( vec.size() ) = 100; }
    catch( std::out_of_range & e )
    { worked = true; }

    EXPECT_TRUE( worked );
}


{
    BEGIN_TEST(tm, "Capacity","Capacity");
    sc::vector<int> vec { 1, 2, 3, 4, 5 };

    EXPECT_EQ( vec.capacity(), 5u );
    vec.reserve(10);
    EXPECT_EQ( vec.capacity(), 10u );
    vec.reserve(3); // Nothing happens here.
    EXPECT_EQ( vec.capacity(), 10u );

    auto i{0};
    for( const auto & e : vec )
    {
        EXPECT_EQ( e, ++i );
    }
        
}


{
    BEGIN_TEST(tm, "ShrinkToFit","ShrinkToFit");
    // #1 From an empty vector.
    sc::vector<int> vec { 1, 2, 3, 4, 5 };

    EXPECT_EQ( vec.capacity(), 5u );
    vec.pop_back();
    vec.pop_back();
    EXPECT_EQ( vec.capacity(), 5u );
    vec.shrink_to_fit();
    EXPECT_EQ( vec.capacity(), 3 );
    auto i{0};
    for( const auto & e : vec )
        EXPECT_EQ( e , ++i );
}


{
    BEGIN_TEST(tm, "OperatorEqual","OperatorEqual");
    // #1 From an empty vector.
    sc::vector<int> vec { 1, 2, 3, 4, 5 };
    sc::vector<int> vec2 { 1, 2, 3, 4, 5 };
    sc::vector<int> vec3 { 1, 2, 8, 4, 5 };
    sc::vector<int> vec4 { 8, 4, 5 };

    EXPECT_EQ( vec , vec2 );
    EXPECT_TRUE( not ( vec == vec3 ) );
    EXPECT_TRUE( not ( vec == vec4 ) );
}


{
    BEGIN_TEST(tm, "OperatorDifferent","OperatorDifferent");
    // #1 From an empty vector.
    sc::vector<int> vec { 1, 2, 3, 4, 5 };
    sc::vector<int> vec2 { 1, 2, 3, 4, 5 };
    sc::vector<int> vec3 { 1, 2, 8, 4, 5 };
    sc::vector<int> vec4 { 8, 4, 5 };

    EXPECT_TRUE( not( vec != vec2 ) );
    EXPECT_NE( vec, vec3 );
    EXPECT_NE( vec,vec4 );
}


{
    BEGIN_TEST(tm, "InsertSingleValueAtPosition","InsertSingleValueAtPosition");
    // #1 From an empty vector.
    sc::vector<int> vec { 1, 2, 4, 5, 6 };

    // Insert at front
    vec.insert( vec.begin(), 0 );
    EXPECT_EQ( vec , ( sc::vector<int>{ 0, 1, 2, 4, 5, 6 } ) );
    // Insert in the middle
    // vec.insert( vec.begin()+3, 3 );
    // EXPECT_EQ( vec , ( sc::vector<int>{ 0, 1, 2, 3, 4, 5, 6 } ) );
    // Insert at the end
    vec.insert( vec.end(), 7 );
    EXPECT_EQ( vec , ( sc::vector<int>{ 0, 1, 2, 3, 4, 5, 6, 7 } ) );
}


{
    BEGIN_TEST(tm, "InsertRange","InsertRange");
    // Aux arrays.
    sc::vector<int> vec1 { 1, 2, 3, 4, 5 };
    sc::vector<int> vec2 { 1, 2, 3, 4, 5 };
    sc::vector<int> source { 6, 7, 8, 9, 10 };

    // Inset at the begining.
    vec1.insert( vec1.begin(), source.begin(), source.end() );
    EXPECT_EQ( vec1 , ( sc::vector<int>{ 6, 7, 8, 9, 10, 1, 2, 3, 4, 5 } ) );

    // In the middle
    vec1 = vec2;
    vec1.insert( std::next( vec1.begin(), 2 ), source.begin(), source.end() );
    EXPECT_EQ( vec1 , ( sc::vector<int>{ 1, 2, 6, 7, 8, 9, 10, 3, 4, 5 } ) );

    // At the end
    vec1 = vec2;
    vec1.insert( vec1.end(), source.begin(), source.end() );
    EXPECT_EQ( vec1 , ( sc::vector<int>{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 } ) );

    // Outside
    vec1 = vec2;
    vec1.insert( std::next( vec1.end(), 2 ) , source.begin(), source.end() );
    EXPECT_EQ( vec1 , ( sc::vector<int>{ 1, 2, 3, 4, 5 } ) );

}


{
    BEGIN_TEST(tm, "InsertInitializarList","InsertInitializarList");
    // Aux arrays.
    sc::vector<int> vec1 { 1, 2, 3, 4, 5 };
    sc::vector<int> vec2 { 1, 2, 3, 4, 5 };
    sc::vector<int> source { 6, 7, 8, 9, 10 };

    // Inset at the begining.
    vec1.insert( vec1.begin(), { 6, 7, 8, 9, 10 } );
    EXPECT_EQ( vec1 , ( sc::vector<int>{ 6, 7, 8, 9, 10, 1, 2, 3, 4, 5 } ) );

    // In the middle
    vec1 = vec2;
    vec1.insert( std::next( vec1.begin(), 2 ), { 6, 7, 8, 9, 10 } );
    EXPECT_EQ( vec1 , ( sc::vector<int>{ 1, 2, 6, 7, 8, 9, 10, 3, 4, 5 } ) );

    // At the end
    vec1 = vec2;
    vec1.insert( vec1.end(), { 6, 7, 8, 9, 10 } );
    EXPECT_EQ( vec1 , ( sc::vector<int>{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 } ) );

    // Outside
    vec1 = vec2;
    vec1.insert( std::next( vec1.end(), 2 ) , { 6, 7, 8, 9, 10 } );
    EXPECT_EQ( vec1 , ( sc::vector<int>{ 1, 2, 3, 4, 5 } ) );
}


{
    BEGIN_TEST(tm, "AssignCountValue2","AssignCountValue2");
    // Initial vector.
    sc::vector<char> vec { 'a', 'b', 'c', 'd', 'e' };

    // assigning count values to sc::vector, with count < size().
    vec.assign( 3, 'x' );
    sc::vector<char> vec2 { 'x', 'x', 'x' };
    //ASSERT_EQ( vec , ( sc::vector<char>{ 'x', 'x', 'x' } ) );
    EXPECT_EQ( vec , vec2 );
    EXPECT_EQ( vec.size() , 3 );
    EXPECT_EQ( vec.capacity() , 5 );

    // assigning count values to sc::vector, with count , size().
    vec = { 'a', 'b', 'c', 'd', 'e' };
    vec.assign( 5, 'y' );
    EXPECT_EQ( vec , ( sc::vector<char>{ 'y','y','y','y','y' } ) );
    EXPECT_EQ( vec.size() , 5 );
    EXPECT_EQ( vec.capacity() , 5 );

    // assigning count values to sc::vector, with count > size().
    vec = { 'a', 'b', 'c', 'd', 'e' };
    vec.assign( 8, 'z' );
    EXPECT_EQ( vec , ( sc::vector<char>{ 'z','z','z','z','z','z','z','z' } ) );
    EXPECT_EQ( vec.size() , 8 );
    EXPECT_EQ( vec.capacity() , 8 );
}


{
    BEGIN_TEST(tm, "EraseRange","EraseRange");
    // Initial vector.
    sc::vector<int> vec { 1, 2, 3, 4, 5 };

    // removing a segment from the beginning.
    auto past_last = vec.erase( vec.begin(), std::next(vec.begin(),3) );
    EXPECT_EQ( vec.begin() , past_last );
    EXPECT_EQ( vec , ( sc::vector<int>{ 4, 5 } ) );
    std::cout << *past_last <<" "<< *vec.begin()<< endl;
    EXPECT_EQ( vec.size() , 2 );

    // removing at the middle.
    vec = { 1, 2, 3, 4, 5 };
    past_last = vec.erase( std::next(vec.begin(),1), std::next(vec.begin(),4) );
    std::cout  << *past_last << " "<< *std::next(vec.begin(),1)  << std::endl; 
    EXPECT_EQ( std::next(vec.begin(),1) , past_last );
    EXPECT_EQ( vec , ( sc::vector<int>{ 1, 5 } ) );
    EXPECT_EQ( vec.size() , 2 );

    // removing a segment that reached the end.
    vec = { 1, 2, 3, 4, 5 };
    past_last = vec.erase( std::next(vec.begin(),2), vec.end() );
    EXPECT_EQ( vec.end() , past_last );
    std::cout  << *past_last << " "<< *std::next(vec.begin(),2)  << std::endl; 

    EXPECT_EQ( vec , ( sc::vector<int>{ 1, 2 } ) );
    EXPECT_EQ( vec.size() , 2 );

    // removing the entire vector.
    vec = { 1, 2, 3, 4, 5 };
    past_last = vec.erase( vec.begin(), vec.end() );
    EXPECT_EQ( vec.end() , past_last );
    EXPECT_TRUE( vec.empty() );
}


{
    BEGIN_TEST(tm, "ErasePos","ErasePos");
    // Initial vector.
    sc::vector<int> vec { 1, 2, 3, 4, 5 };

    // removing a single element.
    vec = { 1, 2, 3, 4, 5 };
    auto past_last = vec.erase( vec.begin() );
    EXPECT_EQ( vec , ( sc::vector<int>{ 2, 3, 4, 5 } ) );
    EXPECT_EQ( vec.begin() , past_last );
    EXPECT_EQ( vec.size() , 4 );

    // removing a single element in the middle.
    vec = { 1, 2, 3, 4, 5 };
    past_last = vec.erase( std::next(vec.begin(),2) );
    EXPECT_EQ( vec , ( sc::vector<int>{ 1, 2, 4, 5 } ) );
    EXPECT_EQ( std::next(vec.begin(),2) , past_last );
    EXPECT_EQ( vec.size() , 4 );

    // removing a single element at the end.
    vec = { 1, 2, 3, 4, 5 };
    past_last = vec.erase( std::next(vec.begin(),vec.size()-1 ) );
    EXPECT_EQ( vec , ( sc::vector<int>{ 1, 2, 3, 4 } ) );
    EXPECT_EQ( vec.end() , past_last );
    EXPECT_EQ( vec.size() , 4 );
}

    tm.summary();
    return 0;
}
