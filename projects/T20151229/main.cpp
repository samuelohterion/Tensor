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

	cout << endl;

	typedef Tensor< int > TInt;

	TInt
	ti0 = { 3, 2, 4 };

	ti0[ i ][ 1 ][ k ] = 8 * i + 4 + k;

	cout << "ti0[ i ][ j ][ k ]" << endl << ti0[ i ][ j ][ k ] << endl << endl;

	typedef Term< double > Dbl;
	typedef Tensor< double > TDbl;

	TDbl
	td0 = { 3, 2, 4 };

	td0[ i ][ j ][ k ] = Dbl( 2 * i + j + 10 * ti0[ i ][ j ][ k ] ) + .1 * Dbl( k * k );

	cout << endl << "td0[ i ][ j ][ k ]" << endl << td0[ i ][ j ][ k ] << endl << endl;

	TInt
	a = { 3 },
	b = { 2 },
	ab = { 3, 2 };

	a[ i ] = i + 1;
	ab[ i ][ j ] = ( i + 1 ) * ( j - 2 );

	b[ i ] = ab[ j ][ i ] * a[ j ];

	cout << "a[ i ]\n" << a[ i ] << endl << endl;
	cout << "ab[ i ][ j ]\n" << ab[ i ][ j ] << endl << endl;
	cout << "b[ i ]\n" << b[ i ] << endl << endl;

	size_t const
	ROWS = 3,
	COLS = 4;

	TInt
	u = { ROWS },
	v = { COLS },
	w = { COLS },
	M = { ROWS, COLS },
	N = { COLS, ROWS };

	u[ i ] = 1 + i;

	M[ i ][ j ] = 1 + 5 * i + j;

	N[ i ][ j ] = M[ j ][ i ];

	v[ i ] = ( -u[ j ] * M[ j ][ i ] ) * ( i + 1 );

	w[ i ] = N[ i ][ j ] * u[ j ] / ( i + 1 );

	cout << "u[ i ]\n" << u[ i ] << endl << endl;
	cout << "M[ i ][ j ]\n" << M[ i ][ j ] << endl << endl;
	cout << "N[ i ][ j ]\n" << N[ i ][ j ] << endl << endl;
	cout << "v[ i ]\n" << v[ i ] << endl << endl;
	cout << "w[ i ]\n" << w[ i ] << endl << endl;


	TInt
	O = { ROWS, ROWS };

	O[ i ][ j ] = i - j;
	cout << "O[ i ][ j ]\n" << O[ i ][ j ] << endl << endl;

	O[ i ][ j ] = O[ j ][ i ];
	cout << "O[ i ][ j ]\n" << O[ i ][ j ] << endl << endl;

	cout << "O[ i ][ j ] + O[ i ][ j ]\n" << ( O[ i ][ j ] + O[ j ][ i ] ) << endl << endl;

	TInt
	P = { ROWS, ROWS };

	P[ i ][ j ] = O[ i ][ j ] + O[ j ][ i ];
	cout << "P[ i ][ j ]\n" << P[ i ][ j ] << endl << endl;

	int
	scalar = u[ i ] * u[ i ];

	cout << "scalar\n" << scalar << endl << endl;

	scalar = M[ i ][ j ] * N[ j ][ i ];

	cout << "scalar\n" << scalar << endl << endl;

	v[ k ] = k * ( M[ i ][ j ] * N[ j ][ i ] ) / ( k + 1 );

	cout << "v[ k ]\n" << v[ k ] << endl << endl;

	// BUT!!!   NOTE!!!
	// v[ k ] = k * M[ i ][ j ] * N[ j ][ i ];  means
	// v[ k ] = ( k * M[ i ][ j ] ) * N[ j ][ i ];
	// this is not correct!!!! one cannot know, what's the range of k in k * M[ i ][ j ]


	// this works fine!!!
	TInt
	Q = { ROWS, ROWS, COLS };

	Q[ k ][ i ][ j ] = k * M[ i ][ j ] - N[ j ][ i ] + -u[ k ] + ~v[ j ];
	cout << "Q[ i ][ j ][ k ]\n" << Q[ i ][ j ][ k ] << endl << endl;

	return 0;
}

