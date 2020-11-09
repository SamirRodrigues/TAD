#include <iostream>
#include <random>
#include <chrono>
#include "vector.hpp"


namespace client
{
	template <class T>
	void print_it( sc::vector<T> &V, char sep )
	{
		std::cout << "{ ";
		for( auto it = V.begin(); it != V.end(); it++ ){
			std::cout << *it << sep;
		}
		std::cout << "}";
		std::cout << std::endl;
	}

	// Populate a given array with random values between [0, 300).
	template <class T>
	void populate( sc::vector<T> &V ){
		for( auto it = V.begin(); it != V.end(); ++it ){
			auto seed = 
				std::chrono::system_clock::now().time_since_epoch().count();
			std::mt19937 rd (seed);
			*it = rd() % 300;
		}
	}
}


int main( void ){

	// Special members tests 
	{
		tam::title("Special members tests"); std::cout << std::endl;

		{
			tam::bold("Empty constructor"); std::cout << std::endl;
			
			// Declaration
			sc::vector<int> EmptyVector; 
			std::cout << "EmptyVector object created!\n";

			// Populating
			std::cout << "Populating EmptyVector with push_back()...\n";
			for( int i = 0; i < 10; i++ )
			{
				EmptyVector.push_back(i);
			}

			// Simple print the object
			std::cout << "EmptyVector elements: ";
			client::print_it(EmptyVector, ' ');
		}

		{
			tam::bold("Constructor with pre-defined size"); std::cout << std::endl;

			// Declaration
			std::cout << "sc::vector<int> SizeVector(10);\n";
			sc::vector<int> SizeVector(10);
			
			// Populating
			std::cout << "Populating SizeVector with positive values...\n";
			for( int i = 0; i < 10; i++ )
				SizeVector[i] = i;

			// Simple print the object
			std::cout << "SizeVector elements: ";
			client::print_it( SizeVector, ' ' );
		}

		{
			tam::bold("Copy constructor from a simple array"); std::cout << std::endl;

			// Declaration
			int Vet[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
			std::cout << "Copy vector elements: ";
			sc::vector<int> cVector( Vet, Vet+10 );
			client::print_it( cVector, ' ' );
		}
		
		{
			tam::bold("Copy constructor from another sc::vector"); std::cout << std::endl;

			// Declaration
			sc::vector<int> origVec(10);
			client::populate( origVec );
			sc::vector<int> copyVec( origVec );

			// Simple print
			std::cout << "Copied vector elements: ";
			client::print_it( copyVec, ' ' );
		}

		{
			tam::bold("Object construtor by std::initializer"); std::cout << std::endl;
			
			// Declaration
			sc::vector<int> initVec = { 1, 4, 3, 2, 5, 9, 10 };

			// Simple print
			std::cout << "Initializer vector elements: ";
			client::print_it(initVec, ' ');
		}

		{
			tam::bold("vector destructor"); std::cout << std::endl;
			// Declaration
			sc::vector<int> *V = new sc::vector<int>;
			std::cout << "vector allocated on " << V << std::endl;
			
			std::cout << "Trying to delete " << V << "..." << std::endl;
			delete V;
			std::cout << "vector deleted with sucess!\n";
		}

		// Assignment Operator tests
		{
			tam::bold("Assignment Operator"); std::cout << std::endl;

			sc::vector<int> V = { 11, 13, 12, 15, 14 };
			sc::vector<int> V2 = { 1, 2, 3, 4, 5 };
			sc::vector<int> V3 = { 3, 4, 2 };

			std::cout << "Expected >> V = { 11, 13, 12, 15, 14 } " << std::endl;
			std::cout << "Result >> V = ";			
			client::print_it(V, ' ');
			std::cout << "Expected >> V2 = { 1, 2, 3, 4, 5 } " << std::endl;
			std::cout << "Result >> V2 = ";
			client::print_it(V2, ' ');
			std::cout << "Expected >> V3 = { 3, 4, 2 } " << std::endl;
			std::cout << "Result >> V3 = ";
			client::print_it(V3, ' ');	
			
			std::cout << std::endl << "V = V2" << std::endl;
			V = V2;
			std::cout << "V = ";
			client::print_it(V, ' ');
			std::cout << "V2 = ";
			client::print_it(V2, ' ');

			V = { 11, 13, 12, 15, 14 };
			std::cout << "V = ";
			client::print_it(V, ' ');
			std::cout << "V3 = ";
			client::print_it(V3, ' ');
		}

		tam::sep();
	}
	
	// Iterators methods tests
	{
		tam::title("Iterators methods tests");		 std::cout << std::endl;
		{		
		tam::bold("Begin & End methods"); std::cout << std::endl;
		sc::vector<int> V(10);
		client::populate(V);
		std::cout << "for loop to print elements in the vector\n";

		std::cout << std::endl;
		std::cout << "for( auto &it : V ){ std::cout << it << ' '; }" << std::endl;		
		for( auto &it : V ){ std::cout << it << ' '; }

		std::cout << std::endl << std::endl;
		std::cout << "Const begin/end:" << std::endl;
		std::cout << "for( auto it = V.begin(); it != V.end(); it++ ){ std::cout << *it << ' '; }" << std::endl;
		for( auto it = V.begin(); it != V.end(); it++ ){ std::cout << *it << ' '; }

		std::cout << std::endl << std::endl;
		std::cout << "Const begin/end: \n(if we try to change a value, it get's a compilation error)\n";
		std::cout << "for( auto it = V.cbegin(); it != V.cend(); ++it ){ std::cout << *it << ' '; }" << std::endl;
		for( auto it = V.cbegin(); it != V.cend(); ++it ){ std::cout << *it << ' '; }
		
		std::cout << std::endl;

		tam::sep();
	}
	}
	
	// Capacity methods tests
	{
		tam::title("Capacity methods tests"); std::cout << std::endl;
		{
			tam::bold("Empty method test"); std::cout << std::endl;
			// Declaration
			sc::vector<int> V(10);
			client::populate(V);
			std::cout << "created vector V with 10 elements\n";
			sc::vector<int> V_emp;	
			std::cout << "created vector V_emp with 0 elements\n";

			// tests
			std::cout << "Is V empty? ";
			std::cout << ( V.empty() ? "Yes\n" : "No\n" );
			std::cout << "Is V_emp empty? ";
			std::cout << ( V_emp.empty() ? "Yes\n" : "No\n" );
		}

		{
			tam::bold("Size method test"); std::cout << std::endl;
			sc::vector<int> V(10);
			client::populate(V);
			std::cout << "vector V has " << V.size() << " elements\n";

			sc::vector<int> V2(40);
			std::cout << "vector V2 created\n";
			client::populate(V2);
			std::cout << "vector V2 has " << V2.size() << " elements\n";
		}
		
		{
			tam::bold("Capacity method test"); std::cout << std::endl;
			// declaration
			sc::vector<int> V(20);	// this should give a capacity of 2^5
			std::cout << "vector V created with 20 elements\n";
			std::cout << "It should have a capacity of 2^(ceil(log2(20)))\n";
			std::cout << "Capacity: " << V.capacity() << std::endl;
		}
		
		tam::sep();
	}
	
	// Modifiers methods tests
	{
		tam::title("Modifiers methods tests"); std::cout << std::endl;

		{
			tam::bold("Clear method test"); std::cout << std::endl;
			// Declaration
			sc::vector<int> cVec(10);
			client::populate(cVec);
			std::cout << "vector cVec created and populated ~" << &cVec;	
			std::cout << std::endl << "cVec elements: ";
			client::print_it(cVec, ' ');

			std::cout << "Running clear() on cVec\n";
			cVec.clear();
			std::cout << "cVec.size() = " << cVec.size() << std::endl;
		}

		{
			tam::bold("Push_front & push_back method test"); std::cout << std::endl;
			sc::vector<int> pVec = {2, 3, 4};
			std::cout << "vector pVec elements: ";
			client::print_it(pVec, ' ');

			pVec.push_front(-20);
			pVec.push_back(99);

			std::cout << "After push_back & push_front: ";
			client::print_it(pVec, ' ');

		}

		{
			tam::bold("Pop_front & pop_backmethod test"); std::cout << std::endl;
			// Declaration
			sc::vector<int> pVec = { 2, 2, 2 };
			std::cout << "vector pVec elements: ";
			client::print_it(pVec, ' ');

			pVec.pop_back();
			pVec.pop_front();

			std::cout << "after pop_front & pop_back: ";
			client::print_it(pVec, ' ');
		}

		{
			tam::bold("Insert methods test"); std::cout << std::endl;

			// Declaration
			std::cout << "Creating iVec(10)\n";
			sc::vector<int> iVec(10);
			std::cout << "Populating iVec with random elements...\n";
			client::populate(iVec);
			std::cout<< "iVec =";
			client::print_it( iVec, ' ' );

			std::cout << "iVec.insert( iVec.begin(), 10 );\n";
			iVec.insert( iVec.begin(), 10 );
			client::print_it( iVec, ' ' );

			std::cout << "\nCreating Vet[] = { 10, 3, 4, 2, 10, 11 };\n";
			int Vet[] = { 10, 3, 4, 2, 10, 11 };
			
			std::cout << "iVec.insert( iVec.begin(), std::begin(Vet), std::end(Vet) );\n";
			iVec.insert( iVec.begin(), std::begin(Vet), std::end(Vet) );
			client::print_it( iVec, ' ' );

			std::cout << "iVec.insert( iVec.begin(), { 10, 20, 30, 40, 50, 60 } );\n";
			iVec.insert( iVec.begin(), { 10, 20, 30, 40, 50, 60 } );
			client::print_it( iVec, ' ' ); 
		}

		{
			tam::bold("Reserve method test & Shrink_to_fit method test"); std::cout << std::endl;
			// declaration
			sc::vector<int> V(20);
			std::cout << "Vector V created with 20 elements" << std::endl;
			std::cout << "It has the initial capacity of 2^20 => V.capacity() = ";
			std::cout << V.capacity() << std::endl;
			std::cout << "calling reserve(40)...\n";
			V.reserve(40);	
			std::cout << "2^40 => V.capacity() = " << V.capacity() << std::endl << std::endl;
			
			std::cout << "Using Shrink_to_fit method:" << std::endl;
			std::cout << "Before = " << V.capacity() << std::endl;
			V.shrink_to_fit();
			std::cout << "After = " << V.capacity() << std::endl;
		}

		{
			tam::bold("Assign method test"); std::cout << std::endl;

			sc::vector<int> iVec(10);
			client::populate(iVec);
			std::cout << "iVec elements: ";
			client::print_it(iVec, ' ');

			sc::vector<int> aVec(20);
			client::populate(aVec);
			std::cout << "aVec elements: ";
			client::print_it(aVec, ' ');
						

			std::cout << "\niVec.assign(8, 10) = ";
			iVec.assign(8, 10);
			client::print_it(iVec, ' ');			

			std::cout << "iVec.assign({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 }) = ";
			iVec.assign({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 });
			client::print_it(iVec, ' ');

			std::cout << "iVec.assign(aVec.begin(), aVec.end()) = ";
			iVec.assign(aVec.begin(), aVec.end());
			client::print_it(iVec, ' ');
		}

		{
			tam::bold("Erase method with iterator"); std::cout << std::endl;
			sc::vector<int> iVec(10);
			client::populate(iVec);
			
			std::cout << "Before elements: ";
			client::print_it(iVec, ' ');
			
			std::cout << "\niVec.erase(iVec.end())\n" << std::endl;
			iVec.erase(iVec.end());
			client::print_it(iVec, ' ');
			std::cout << "iVec.erase( iVec.begin(), iVec.end() - 3)" << std::endl;
			iVec.erase( iVec.begin(), iVec.end() - 3);
			client::print_it(iVec, ' ');
			
			std::cout << "\nAfter elements: ";
			client::print_it(iVec, ' ');
		}
		tam::sep();
	}

	// Element access methods tests
	{	
		tam::title("Element access methods tests"); std::cout << std::endl;
		{
			tam::bold("Front, back, [] and at method test"); std::cout << std::endl;
			sc::vector<int> Vec(10);
			client::populate(Vec);
			std::cout << "Vec elements: ";
			client::print_it(Vec, ' ');
			std::cout << "Vec.front() = " << Vec.front() << std::endl;
			std::cout << "Vec.back() = " << Vec.back() << std::endl;
			std::cout << "Vec[4] = " << Vec[4] << std::endl;
			std::cout << "Vec.at(2) = " << Vec.at(2) << std::endl;
		}
		tam::sep();
	}

	// Operators tests 
	{
		tam::title("Operators tests"); std::cout << std::endl;
		{
			tam::bold("\"==\" and \"!=\" test"); std::cout << std::endl;

			sc::vector<int> V = { 11, 13, 12, 15, 14 };
			sc::vector<int> V2 = { 1, 2, 3, 4, 5 };
			sc::vector<int> V3 = { 3, 4, 2 };

			std::cout << "V = "; client::print_it(V, ' ');
			std::cout << "V2 = "; client::print_it(V2, ' ');
			std::cout << "V3 = "; client::print_it(V3, ' ');

			std::cout << "\nV == V3 ? ";
			(V == V3) ? std::cout << "True\n" : std::cout << "False\n";

			std::cout << "V != V2 ? ";			
			( V != V2 ) ? std::cout << "True\n" : std::cout << "False\n";
		}
		tam::sep();
	}

	return 0;
}

