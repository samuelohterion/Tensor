#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <complex>
#include "include/tensor.hpp"
#include "include/codeprinter.hpp"

//@typedef for convenience
	typedef Term< double >    Dbl;
	typedef Tensor< double >  TDbl;
//@

//@print for convenience
template< typename T >
void
print( std::string const & p_text, SubTensor< T > const & p_tensor ) {

	std::cout << p_text << std::endl << p_tensor << std::endl << std::endl;
}

template< typename T >
void
print( std::string const & p_text, Term< T > const & p_term ) {

	std::cout << p_text << std::endl << p_term.str( ) << std::endl << std::endl;
}
//@

//@Main
int
main( ) { CodePrinter cp( "../Tensor/main.cpp" );

	std::cout << "Tensor\n------\n\n";

	CodePrinter::WFE( ); cp.print( "typedef for convenience" );
	CodePrinter::WFE( ); cp.print( "print for convenience" );
	CodePrinter::WFE( ); cp.print( "Main" );
	CodePrinter::WFE( ); cp.print( "Einstein Indices" );
//@

//@Einstein Indices
	// we need 3 EINSTEIN INDICES i j k
	EIdx i, j, k;
//@

	CodePrinter::WFE( ); cp.print( "first create two real vectors" );
//@first create two real vectors
	TDbl
	v2 = { 2 },
	v3 = { 3 },
	u3 = { 3 };
	print( "v2[ i ]", v2[ i ] );
	print( "v3[ i ]", v3[ i ] );
	print( "u3[ i ]", u3[ i ] );
//@

	CodePrinter::WFE( ); cp.print( "init them" );
//@init them
	v2[ i ] = 1 - 2 * i;
	v3[ i ] = i + 1;
	u3[ i ] = 1;
	print( "v2[ i ]", v2[ i ] );
	print( "v3[ i ]", v3[ i ] );
	print( "u3[ i ]", u3[ i ] );
//@

	CodePrinter::WFE( ); cp.print( "create some matrices" );
//@create some matrices
	TDbl
	m22 = { 2, 2 },
	m23 = { 2, 3 },
	m32 = { 3, 2 },
	m33 = { 3, 3 };

	m22[ i ][ j ] = i * 2 + j;
	m23[ i ][ j ] = i * 2 + j;
	m32[ i ][ j ] = m23[ j ][ i ];
	m33[ i ][ j ] = i * 3 + j;

	print( "m22[ i ][ j ]", m22[ i ][ j ] );
	print( "m23[ i ][ j ]", m23[ i ][ j ] );
	print( "m32[ i ][ j ]", m32[ j ][ i ] );
	print( "m33[ i ][ j ]", m33[ i ][ j ] );
//@

	CodePrinter::WFE( ); cp.print( "scalar products" );
//@scalar products
	print( "v2[ i ] * v2[ i ]", v2[ i ] * v2[ i ] );
	print( "v3[ i ] * v3[ i ]", v3[ i ] * v3[ i ] );
//@

	CodePrinter::WFE( ); cp.print( "outer product matrices" );
//@outer product matrices
	print( "v2[ i ] * v3[ j ]", v2[ i ] * v3[ j ] );
	print( "v3[ i ] * v2[ j ]", v3[ i ] * v2[ j ] );
//@

	CodePrinter::WFE( ); cp.print( "matrices times vectors" );
//@matrices times vectors
	print( "m22 x v2 < == > m22[ i ][ j ] * v2[ j ]", m22[ i ][ j ] * v2[ j ] );
	print( "v2 x m22 < == > v2[ i ] * m22[ i ][ j ]", v2[ i ] * m22[ i ][ j ] );
	print( "m32 x v2 < == > m32[ i ][ j ] * v2[ j ]", m32[ i ][ j ] * v2[ j ] );
	print( "v3 x m32 < == > v3[ i ] * m32[ i ][ j ]", v3[ i ] * m32[ i ][ j ] );
//@

	CodePrinter::WFE( ); cp.print( "matrices times matrices" );
//@matrices times vectors
	print( "m32 x m23 < == > m32[ i ][ k ] * m23[ k ][ j ]", m32[ i ][ k ] * m23[ k ][ j ] );
	print( "m23 x m32 < == > m23[ i ][ k ] * m32[ k ][ j ]", m23[ i ][ k ] * m32[ k ][ j ] );
//@

	CodePrinter::WFE( ); cp.print( "now create a new double 3x3 matrix" );
//@now create a new double 3x3 matrix
	TDbl
	m = { 3, 3 };

	m[ i ][ j ] = ( i == j ) * ( 1 + i ) + ( i != j ) * ( i * 3 + j );

	print( "m[ i ][ j ]", m[ i ][ j ] );
//@

	CodePrinter::WFE( ); cp.print( "sum of vector elements" );
//@sum of vector elements
	print( "u3[ i ]", u3[ i ] );
	print( "v3[ i ]", v3[ i ] );
	print( "u3[ i ] * v3[ i ]", u3[ i ] * v3[ i ] );
	print( "v3[ i ] * u3[ i ]", v3[ i ] * u3[ i ] );
//@

	CodePrinter::WFE( ); cp.print( "sum of matrix row or column elements" );
//@sum of matrix row or column elements
	print( "u3[ i ] * m[ i ][ j ]", u3[ i ] * m[ i ][ j ] );
	print( "m[ i ][ j ] * u3[ j ]", m[ i ][ j ] * u3[ j ] );
//@

	CodePrinter::WFE( ); cp.print( "sum of all matrix elements" );
//@sum of all matrix elements
	// need a matrix containing ones only
	m33[ i ][ j ] = 1;
	print( "m33[ i ][ j ] * m[ i ][ j ]", m33[ i ][ j ] * m[ i ][ j ] );
	print( "m[ i ][ j ] * m33[ i ][ j ]", m[ i ][ j ] * m33[ i ][ j ] );
//@

	CodePrinter::WFE( ); cp.print( "the levi cevita tensor" );
//@the levi cevita tensor
	TDbl
	epsilon = { 3, 3, 3 };

	epsilon[ i ][ j ][ k ] =
		( ( ( i < j ) & ( j < k ) ) | ( ( k < i ) & ( i < j ) ) | ( ( j < k ) & ( k < i ) ) ) -
		( ( ( i > j ) & ( j > k ) ) | ( ( k > i ) & ( i > j ) ) | ( ( j > k ) & ( k > i ) ) );

	print( "epsilon[ i ][ j ][ k ]", epsilon[ i ][ j ][ k ] );
//@

	CodePrinter::WFE( ); cp.print( "cross product of u3 and v3" );
//@cross product of u3 and v3
	print( "u3[ i ]", u3[ i ] );
	print( "v3[ i ]", v3[ i ] );

	// cross product
	print( "epsilon[ i ][ j ][ k ] * u3[ j ] * v3[ k ]\n", epsilon[ i ][ j ][ k ] * u3[ j ] * v3[ k ] );
	print( "epsilon[ i ][ j ][ k ] * v3[ j ] * u3[ k ]\n", epsilon[ i ][ j ][ k ] * v3[ j ] * u3[ k ] );
//@

	CodePrinter::WFE( ); cp.print( "remember m 1st" );
//@remember m 1st
	// remember matrix m
	print( "m[ i ][ j ]", m[ i ][ j ] );
//@

	CodePrinter::WFE( ); cp.print( "create the adjugate matrix of m" );
//@create the adjugate matrix of m
	// adjugate matrix
	TDbl
	mA = { 3, 3 };

	mA[ 0 ][ i ] = epsilon[ i ][ j ][ k ] * m[ 1 ][ j ] * m[ 2 ][ k ];
	mA[ 1 ][ i ] = epsilon[ i ][ j ][ k ] * m[ 2 ][ j ] * m[ 0 ][ k ];
	mA[ 2 ][ i ] = epsilon[ i ][ j ][ k ] * m[ 0 ][ j ] * m[ 1 ][ k ];

	print( "mA[ i ][ j ]", mA[ i ][ j ] );
//@

	CodePrinter::WFE( ); cp.print( "calculate the determinant of m" );
//@calculate the determinant of m

	// determinant of m
	print(
		"epsilon[ i ][ j ][ k ] * m[ 0 ][ i ] * m[ 1 ][ j ] * m[ 2 ][ k ]",
		 epsilon[ i ][ j ][ k ] * m[ 0 ][ i ] * m[ 1 ][ j ] * m[ 2 ][ k ] );

	// determinant of m
	print(
		"epsilon[ i ][ j ][ k ] * m[ i ][ 0 ] * m[ j ][ 1 ] * m[ k ][ 2 ]",
		 epsilon[ i ][ j ][ k ] * m[ i ][ 0 ] * m[ j ][ 1 ] * m[ k ][ 2 ] );
//@

	CodePrinter::WFE( ); cp.print( "use adjugate of m and determinant of m to create the inverse of m" );
//@use adjugate of m and determinant of m to create the inverse of m
	TDbl
	mInv = { 3, 3 };

	mInv[ i ][ j ] = mA[ j ][ i ] / ( epsilon[ i ][ j ][ k ] * m[ i ][ 0 ] * m[ j ][ 1 ] * m[ k ][ 2 ] );

	// invers of m
	print( "mInv[ i ][ j ]", mInv[ i ][ j ] );
//@

	CodePrinter::WFE( ); cp.print( "check result, calculate invers of m times m" );
//@check result, calculate invers of m times m
	print( "mInv[ i ][ j ] * m[ j ][ k ]", mInv[ i ][ j ] * m[ j ][ k ] );
//@

	CodePrinter::WFE( ); cp.print( "moment of inertia" );
//@moment of inertia
	v3[ i ] = 1 + i;
	m[ i ][ j ] = Dbl( i == j ) * ( v3[ i ] * v3[ i ] ) - v3[ i ] * v3[ j ];
	print( "v3[ i ]", v3[ i ] );
	print( "m[ i ][ j ]", m[ i ][ j ] );
	print( "v3[ i ] * m[ i ][ j ]", v3[ i ] * m[ i ][ j ] );
	print( "m[ i ][ j ] * v3[ j ]", m[ i ][ j ] * v3[ j ] );

	TDbl
	v3a = { 3 },
	v3b = { 3 };

	v3a[ i ] = epsilon[ i ][ j ][ k ] * v3[ j ] * u3[ k ];
	v3b[ i ] = epsilon[ i ][ j ][ k ] * v3a[ j ] * v3[ k ] / 2.;

	print( "v3[ i ]", v3[ i ] );
	print( "v3a[ i ]", v3a[ i ] );
	print( "v3b[ i ]", v3b[ i ] );
	print( "v3[ i ] * m[ i ][ j ]", v3[ i ] * m[ i ][ j ] );
	print( "m[ i ][ j ] * v3[ j ]", m[ i ][ j ] * v3[ j ] );
	print( "m[ i ][ j ] * v3a[ j ]", m[ i ][ j ] * v3a[ j ] );
	print( "m[ i ][ j ] * v3b[ j ]", m[ i ][ j ] * v3b[ j ] );
//@

	return 0;
}

