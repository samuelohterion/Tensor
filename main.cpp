#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <complex>
#include "include/tensor.hpp"
#include "include/codeprinter.hpp"

//@just some code for convenience
typedef Term< double >    Dbl;
typedef Tensor< double >  TDbl;

template< typename T >
void
print(SubTensor< T > const & p_tensor, std::string const & p_text = "") {

	std::cout << p_text << (p_text.length() ? "\n" : "") << p_tensor.str() << std::endl << std::endl;
}

template< typename T >
void
print(std::string const & p_text, Term< T > const & p_term) {

	std::cout << p_text << std::endl << p_term.str() << std::endl << std::endl;
}
//@

int
main() {
//@Main
	// to use code printer create an instance with the name of the cpp file as argument
	CodePrinter
	cp("../main.cpp");

	// then use @ instead of AT to frame all snippets by:
	//ATsome unique snippet identifying text'
	// c++
	// snippet
	//AT

	// wait for a key:
	// CodePrinter::WFE();

	// and print snippet by:
	// cp.print("some unique snippet identifying text");
//@
	std::cout << "Tensor\n------\n\n";
	CodePrinter::WFE(); cp.print("Main");
	CodePrinter::WFE(); cp.print("just some code for convenience");

	CodePrinter::WFE(); cp.print("create some double vector");
//@create some double vector

	// create a vector (tensor of degree 1 and 2 dimensions)
	Tensor< double >
	tDbl = {2};

	// initit
	tDbl[0] = 3.14;
	tDbl[1] = 2.72;

	// but how to print?
	// this is not possible
	// std::cout << tDbl << std::endl;
//@

	CodePrinter::WFE(); cp.print("Einstein Indices");
//@Einstein Indices
	// to do this we need an
	// EINSTEIN INDEX i
	EIdx
	i;

	// to print a tensor of deg 1 we need 1 Einstein Index
	std::cout << tDbl[i] << std::endl;
//@

	CodePrinter::WFE(); cp.print("now create some more vectors and print them");
//@now create some more vectors and print them
	TDbl
	five_ten = {2},
	three_ones = {3},
	one_two_three = {3};
	print(five_ten[i]);
	print(three_ones[i], "three_ones");
	print(one_two_three[i], "one_two_three");
//@

	CodePrinter::WFE(); cp.print("init them");
//@init them
	// EINSTEIN INDICES can be used to initialize a tensor with values
	// EINSTEIN INDICES can be combined by operations +,-,*,/ with another EI or integer values
	// EINSTEIN INDICES start at 0

	five_ten[i] = 5 * (i + 1); //  5  10
	three_ones[i] = 1;         //  1  1  1
	one_two_three[i] = i + 1;  //  1  2  3
	print(five_ten[i], "five_ten");
	print(three_ones[i], "three_ones");
	print(one_two_three[i], "one_two_three");
//@

	CodePrinter::WFE(); cp.print("now create some matrices");
//@now create some matrices
	// we need an another EINSTEIN INDEX j
	EIdx
	j;

	// create some double matrices (tensors of deg 2)
	TDbl
	m22 = {2, 2}, // 2 x 2
	m23 = {2, 3}, // 2 x 3
	m32 = {3, 2}, // 3 x 2
	m33 = {3, 3}; // 3 x 3

	// initialize them again with i and j
	m22[i][j] = i * 2 + j;
	m23[i][j] = i * 3 + j;
	m32[i][j] = m23[j][i];
	m33[i][j] = i * 3 + j;

	// show the results now using the two indices i and j
	print(m22[i][j], "m22");
	print(m23[i][j], "m23");
	print(m32[j][i], "m32");
	print(m33[i][j], "m33");
//@

	CodePrinter::WFE(); cp.print("and now some more magic");
//@and now some more magic
	// Einstein Summation works like this
	// if one has the same index in a product of two tensors
	// then all elements are multiplied pairwise and summed up afterwards
	// thats the classical scalar product
	// v = (1, 2, 3), u = (-1, 0, +1) u[i]*v[i] = 1 * (-1) + 2 * 0 + 3 * 1 = 2
	// so let's see whtat's possible here!
//@

	CodePrinter::WFE(); cp.print("the scalar product");
//@the scalar product
	print(three_ones[i], "three_ones[i]");
	print(one_two_three[i], "one_two_three[i]");
	print(three_ones[i] * three_ones[i], "three_ones[i] * three_ones[i]");
	print(three_ones[i] * one_two_three[i], "three_ones[i] * one_two_three[i]");
	print(one_two_three[i] * three_ones[i], "one_two_three[i] * three_ones[i]");
	print(one_two_three[i] * one_two_three[i], "one_two_three[i] * one_two_three[i]");
//@

	CodePrinter::WFE(); cp.print("create a 2x2 matrix via outer product of two vectors");
//@create a 2x2 matrix via outer product of two vectors
	print(five_ten[i] * one_two_three[j], "five_ten[i] * one_two_three[j]");
	print(one_two_three[i] * five_ten[j], "one_two_three[i] * five_ten[j]");
//@

	CodePrinter::WFE(); cp.print("matrices times vectors");
//@matrices times vectors
	print(m22[i][j] * five_ten[j], "m22[i][j] * five_ten[j]");
	print(five_ten[i] * m22[i][j], "five_ten[i] * m22[i][j]");
	print(m32[i][j] * five_ten[j], "m32[i][j] * five_ten[j]");
	print(one_two_three[i] * m32[i][j], "one_two_three[i] * m32[i][j]");
//@
	CodePrinter::WFE(); cp.print("matrices times matrices");
//@matrices times matrices
	// for this we need a third EINSTEIN INDEX k
	EIdx
	k;

	print(m32[i][k] * m23[k][j], "m32 x m23 < == > m32[i][k] * m23[k][j]");
	print(m23[i][k] * m32[k][j], "m23 x m32 < == > m23[i][k] * m32[k][j]");
//@

	CodePrinter::WFE(); cp.print("now create a new double 3x3 matrix");
//@now create a new double 3x3 matrix
	TDbl
	m = {3, 3};

	m[i][j] = (1 + i + 3 * j) *(1 + i + 3 * j);

	print(m[i][j], "m[i][j]");
//@

	CodePrinter::WFE(); cp.print("trace of a matrix");
//@trace of a matrix
	// we can use a unit matrix
	TDbl
	mUnit3x3 = {3, 3};

	// mUnit3x3[i][j] = i == j;
	// or simply
	mUnit3x3[i][i] = 1;
	
	print(
		mUnit3x3[i][j],
		"mUnit3x3[i][j]"
	);
	
	print(
		mUnit3x3[i][j] * m[i][j],
		"mUnit3x3[i][j] * m[i][j]"
	);	

	// or we can simply use our vector three_ones: (1,1,1)	
	print(
		m[i][i] * three_ones[i],
		"m[i][i] * three_ones[i]"
	);	
//@

	CodePrinter::WFE(); cp.print("sum of vector elements");
//@sum of vector elements
	print(three_ones[i], "three_ones");
	print(one_two_three[i], "one_two_three");
	print(three_ones[i] * one_two_three[i], "three_ones[i] * one_two_three[i]");
	print(one_two_three[i] * three_ones[i], "one_two_three[i] * three_ones[i]");
//@

	CodePrinter::WFE(); cp.print("sum of matrix row or column elements");
//@sum of matrix row or column elements
	print(three_ones[i] * m[i][j], "three_ones[i] * m[i][j]");
	print(m[i][j] * three_ones[j], "m[i][j] * three_ones[j]");
//@

	CodePrinter::WFE(); cp.print("sum of all matrix elements");
//@sum of all matrix elements
	// need a matrix containing ones only
	m33[i][j] = 1;
	print(m33[i][j] * m[i][j], "m33[i][j] * m[i][j]");
	print(m[i][j] * m33[i][j], "m[i][j] * m33[i][j]");
//@

	CodePrinter::WFE(); cp.print("the levi cevita tensor");
//@the levi cevita tensor
	TDbl
	eps = {3, 3, 3};

	eps[i][j][k] =
		(((i < j) & (j < k)) | ((k < i) & (i < j)) | ((j < k) & (k < i))) -
		(((i > j) & (j > k)) | ((k > i) & (i > j)) | ((j > k) & (k > i)));

	print(eps[i][j][k], "eps");
//@

	CodePrinter::WFE(); cp.print("cross product of three_ones and one_two_three");
//@cross product of three_ones and one_two_three
	print(three_ones[i], "three_ones");
	print(one_two_three[i], "one_two_three");

	// cross product
	print(eps[i][j][k] * three_ones[j] * one_two_three[k], "eps[i][j][k] * three_ones[j] * one_two_three[k]");
	print(eps[i][j][k] * one_two_three[j] * three_ones[k], "eps[i][j][k] * one_two_three[j] * three_ones[k]");
//@

	CodePrinter::WFE(); cp.print("create the adjugate matrix of m");
//@create the adjugate matrix of m
	// adjugate matrix
	TDbl
	mA = {3, 3};

	mA[i][0] = eps[i][j][k] * m[1][j] * m[2][k];
	mA[i][1] = eps[i][j][k] * m[2][j] * m[0][k];
	mA[i][2] = eps[i][j][k] * m[0][j] * m[1][k];

	print(m[i][j], "m");
	print(mA[i][j], "mA");
//@

	CodePrinter::WFE(); cp.print("calculate the determinant of m");
//@calculate the determinant of m

	// determinant of m by rows
	print(
		 eps[i][j][k] * m[0][i] * m[1][j] * m[2][k],
		"eps[i][j][k] * m[0][i] * m[1][j] * m[2][k]");

	// determinant of m by columns
	print(
		 eps[i][j][k] * m[i][0] * m[j][1] * m[k][2],
		"eps[i][j][k] * m[i][0] * m[j][1] * m[k][2]");
//@

	CodePrinter::WFE(); cp.print("use adjugate of m and determinant of m to create the inverse of m");
//@use adjugate of m and determinant of m to create the inverse of m
	TDbl
	mInv = {3, 3};

	mInv[i][j] = mA[i][j] / (eps[i][j][k] * m[i][0] * m[j][1] * m[k][2]);

	// invers of m
	print(mInv[i][j], "mInv");
//@

	CodePrinter::WFE(); cp.print("check result, calculate inverse of m times m");
//@check result, calculate inverse of m times m
	print(mInv[i][j] * m[j][k], "mInv[i][j] * m[j][k]");
//@

	CodePrinter::WFE(); cp.print("moment of inertia");
//@moment of inertia
	TDbl
	axis   = {3},
	xyz    = {3, 3},
	lambda = {3, 3};

	axis[i] = 1 + 2 * i;
	axis[i] = axis[i] / sqrt(axis[j] * axis[j]);
	lambda[i][j] = Dbl(i == j) * (axis[i] * axis[i]) - axis[i] * axis[j];

	xyz[0][i] = (i == 0) * 1 + (i == 1) * 0 + (i == 2) * 0;
//	xyz[0][i] = eps[i][j][k] * axis[j] * xyz[0][k];
	xyz[0][i] = xyz[0][i] / sqrt(xyz[0][i] * xyz[0][i]);

	xyz[1][i] = eps[i][j][k] * axis[j] * xyz[0][k];
	xyz[1][i] = xyz[1][i] / sqrt(xyz[1][i] * xyz[1][i]);
	xyz[2][i] = eps[i][j][k] * axis[j] * xyz[1][k];
	xyz[2][i] = xyz[2][i] / sqrt(xyz[2][i] * xyz[2][i]);

	print(axis[i], "axis");
	print(xyz[0][i], "xyz[0][i]");
	print(xyz[1][i], "xyz[1][i]");
	print(xyz[2][i], "xyz[2][i]");
	print(lambda[i][j], "lambda");

	print(lambda[i][j] * axis[j], "lambda[i][j] * axis[j]");
	print(lambda[i][j] * xyz[0][j], "lambda[i][j] * xyz[0][j]");
	print(lambda[i][j] * xyz[1][j], "lambda[i][j] * xyz[1][j]");
	print(lambda[i][j] * xyz[2][j], "lambda[i][j] * xyz[2][j]");

	print(axis[i] * lambda[i][j], "axis[i] * lambda[i][j]");
	print(axis[i] * axis[i], "axis[i] * axis[i]");
	print(axis[i] * lambda[i][j] * axis[j], "axis[i] * lambda[i][j] * axis[j]");

	print(xyz[0][i] * lambda[i][j], "xyz[0][i] * lambda[i][j]");
	print(xyz[0][i] * xyz[0][i], "xyz[0][i] * xyz[0][i]");
	print(xyz[0][i] * lambda[i][j] * xyz[0][j], "xyz[0][i] * lambda[i][j] * xyz[0][j]");

	print(xyz[1][i] * lambda[i][j], "xyz[1][i] * lambda[i][j]");
	print(xyz[1][i] * xyz[1][i], "xyz[1][i] * xyz[1][i]");
	print(xyz[1][i] * lambda[i][j] * xyz[1][j], "xyz[1][i] * lambda[i][j] * xyz[1][j]");

	print(xyz[2][i] * lambda[i][j], "xyz[2][i] * lambda[i][j]");
	print(xyz[2][i] * xyz[2][i], "xyz[2][i] * xyz[2][i]");
	print(xyz[2][i] * lambda[i][j] * xyz[2][j], "xyz[2][i] * lambda[i][j] * xyz[2][j]");
//@

	CodePrinter::WFE(); cp.print("big one");
//@big one
	Tensor< int >
	big = {2, 3, 4, 5, 6, 7};

	EIdx
	a, b, c, d, e, f;

	big[a][b][c][d][e][f] = 0 + f + 7 * (e + 6 * (d + 5 * (c + 4 * (b + 3 * a))));

	print(big[a][b][c][d][e][f], "big");
//@

	CodePrinter::WFE(); cp.print("cut out some sub tensors");
//@cut out some sub tensors
	print(big[i][0][j][1][k][2], "big[i][0][j][1][k][2]");
	print(big[0][0][0][0][i][j], "big[0][0][0][0][i][j]");
	print(big[i][0][0][0][0][j], "big[i][0][0][0][0][j]");

	Tensor< int >
	small = {7, 2};
	small[i][j] = big[j][0][0][0][0][i];

	print(small[i][j], "small[i][j]");
//@

	CodePrinter::WFE(); cp.print("hadamard product of two vectors");
//@hadamard product of two vectors
	Tensor< int >
	t1 = {3, 2};

    t1[i][j] = 3 * j + i + 1;

	Tensor< int >
	mul = {3, 3};

	mul[i][j] = t1[i][0] * t1[j][1];

    print(t1[i][j], "t1[i][j] = 3 * j + i + 1");
    print(mul[i][j], "mul[i][j] = t1[i][0] * t1[j][1]");
    print(mul[i][i], "mul[i][i]");
//@
    return 0;
}
