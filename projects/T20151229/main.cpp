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

	typedef Tensor< int > TInt;

	TInt
	ti0 = { 3, 2, 4 };

	ti0[ i ][ 1 ][ k ] = 8 * i + 4 + k;

	cout << endl;

	cout << ti0[ i ][ j ][ k ] << endl;

	cout << endl;

	typedef Tensor< double > TDbl;

	TDbl
	td0 = { 3, 2, 4 };

	td0[ i ][ j ][ k ] = Term< double >( 2 * i + j + 10 * ti0[ i ][ j ][ k ] ) + .1 * Term< double >( k * k );

	cout << endl;

	cout << td0[ i ][ j ][ k ] << endl;

	TInt
	a = { 3 },
	b = { 2 },
	ab = { 3, 2 };

	a[ i ] = i;
	ab[ i ][ j ] = i + j;

	b[ i ] = ab[ j ][ i ] * a[ j ];

	cout << "a[ i ]\n" << a[ i ] << endl;
	cout << "ab[ i ][ j ]\n" << ab[ i ][ j ] << endl;
	cout << "b[ i ]\n" << b[ i ] << endl;


	TInt
	u = { 4 },
	v = { 3 },
	w = { 3 },
	M = { 4, 3 },
	N = { 3, 4 };

	u[ i ] = 1 + i;

	M[ i ][ j ] = 1 + 3 * i + j;

	N[ i ][ j ] = M[ j ][ i ];

	v[ i ] = u[ j ] * M[ j ][ i ];

	w[ i ] = N[ i ][ j ] * u[ j ];

	cout << "u[ i ]\n" << u[ i ] << endl;
	cout << "M[ i ][ j ]\n" << M[ i ][ j ] << endl;
	cout << "N[ i ][ j ]\n" << N[ i ][ j ] << endl;
	cout << "v[ i ]\n" << v[ i ] << endl;
	cout << "w[ i ]\n" << w[ i ] << endl;



	return 0;
}

