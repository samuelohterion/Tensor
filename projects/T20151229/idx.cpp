#include "idx.h"

Idx::Idx( ) :
Term< int >( ) {

}

Idx::~Idx( ) {

}

std::string
Idx::str( ) const {

	std::stringstream
	ss;

	ss << val( );

	return ss.str( );
}


TreeCIdx::TreeCIdx( int const &p_constantIndex ) :
TreeValue< int >( p_constantIndex ) {

}



CIdx::CIdx( ) :
Idx( ),
__value( 0 ) {

}

CIdx::CIdx( CIdx const &p_idx ) :
Idx( ),
__value( p_idx.__value ) {

}

CIdx::CIdx( int const &p_idx ) :
Idx( ),
__value( p_idx ) {

}

//Tree< int >
//*CIdx::cpy( ) const {

//	return new TreeCIdx( )
//}

//inline bool
//CIdx::is( Idx const &p_idx ) {

//	return false;
//}

//inline bool
//CIdx::isConstant( ) const {

//	return true;
//}

//inline bool
//CIdx::isReference( ) {

//	return false;
//}

//TreeValue
//&Idx::set( int const &p_val ) {

//	*__current = p_val;

//	return *this;
//}

//TreeValue
//&Idx::setCount( int const &p_count ) {

//	*__end = *__begin + p_count;

//	return *this;
//}

//TreeValue
//&Idx::setFirst( int const &p_first ) {

//	*__begin = p_first;

//	return *this;
//}



//int
//Idx::val( ) const {

//	return __val;
//}
