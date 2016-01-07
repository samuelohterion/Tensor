#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include "tensor.hpp"

using namespace std;

int
main( ) {

	cout << "T20151229\n---------\n\n";

	EIdx
	i,
	j,
	k,
	l;


	EIdx
	ci( 8 ),
	cj( 1111 );

	cout << endl;

	Subscription
	s;

	s.addIdx( &i );
	s.addIdx( &cj );
	s.addIdx( &j );
	s.addIdx( &ci );
	s.addIdx( &k );
	s.addIdx( &ci );
	s.addIdx( &k );
	s.addIdx( &l );

	Counter
	c;

	c.buildFromSubscription( s );
	c.reset( );

	cout << setw( 8 ) << "i" << ", " << setw( 8 ) << "j" << ", " << setw( 8 ) << "k" << endl;

	while( c.isOK( ) ) {

		cout << setw( 8 ) << i.str( ) << ", " << setw( 8 ) << j.str( ) << ", " << setw( 8 ) << k.str( ) << endl;

		++c;
	}

	cout << endl;

	i.setFirst( 0 ).setCount( 2 );
	j.setFirst( 10 ).setCount( 2 );
	k.setFirst( 100 ).setCount( 2 );

	c.reset( );

	cout << setw( 8 ) << "i" << ", " << setw( 8 ) << "j" << ", " << setw( 8 ) << "k" << endl;

	while( c.isOK( ) ) {

		cout << setw( 8 ) << i.str( ) << ", " << setw( 8 ) << j.str( ) << ", " << setw( 8 ) << k.str( ) << endl;

		++c;
	}

	cout << endl;

	i.setFirst( 1 ).setCount( 2 );
	j.setFirst( 1 ).setCount( 2 );
	k.setFirst( 1 ).setCount( 2 );

	c.reset( );

	cout << endl << setw( 8 ) << "100 · i + 10 · j + k" << endl;

	while( c.isOK( ) ) {

		cout << setw( 8 ) << ( 100 * i + 10 * j + k ).str( ) << endl;

		++c;
	}

	cout << endl << setw( 8 ) << "1000 · i + 100 · j + 10 · k + l" << endl;

	int
	cnt = 2;

	for( i.setFirst( 1 ).setCount( ++cnt ), j.setFirst( 1 ).setCount( ++cnt ), k.setFirst( 1 ).setCount( ++cnt ), l.setFirst( 1 ).setCount( ++cnt ), c.reset( ); c.isOK( ); ++c ) {

		cout << ( c.size( ) - c.lcd( ) > 0 ? string( c.size( ) - c.lcd( ) - 1u, '\n' ) : "" ) << setw( 6 ) << ( 1000 * i + 100 * j + 10 * k + l ).str( );
	}

	cout << endl;

	return 0;
}

