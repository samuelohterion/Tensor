#include "idx.h"

Idx::Idx( ) {

}

Idx::~Idx( ) {

}

//---------------------------------------------------------------------------


CIdx::CIdx( ) :
Idx( ),
TermI( new TreeConstantIndex( 0 ) ) {

}

CIdx::CIdx( CIdx &p_idx ) :
Idx( ),
TermI( new TreeConstantIndex( p_idx.val( ) ) ) {

}

CIdx::CIdx( int const &p_val ) :
Idx( ),
TermI( new TreeConstantIndex( p_val ) ) {

}

CIdx::~CIdx( ) {

}

TreeI
*CIdx::cpy( ) {

	return new TreeConstantIndex( val( ) );
}

int
CIdx::eval( ) {

	return tree( )->val( );
}

bool
CIdx::is( Idx & ) const {

	return false;
}

bool
CIdx::isConstant( ) const {

	return true;
}

bool
CIdx::isReference( ) const {

	return false;
}

int
CIdx::val( ) {

	return tree( )->val( );
}


//---------------------------------------------------------------------------


TreeConstantIndex::TreeConstantIndex( int const &p_value ) :
TreeI( ),
__value( p_value ) {

}

TreeI
*TreeConstantIndex::cpy( ) {

	return new TreeConstantIndex( __value );
}

int
TreeConstantIndex::val( ) {

	return __value;
}


//---------------------------------------------------------------------------


EIdx::EIdx( ) :
TermI( new TreeEinsteinIndex( this ) ),
__isReference( false ),
__begin( new int( 0 ) ),
__current( new int( 0 ) ),
__end( new int( 0 ) ) {

}

EIdx::EIdx( EIdx const &p_idx ) :
TermI( new TreeEinsteinIndex( this ) ),
__isReference( true ),
__begin( p_idx.__begin ),
__current( p_idx.__current ),
__end( p_idx.__end ) {

}

EIdx::~EIdx( ) {

	if( !__isReference ) {

		delete __begin;
		delete __current;
		delete __end;
	}
}


TreeI
*EIdx::cpy( ) {

	return new TreeEinsteinIndex( this );
}

int
EIdx::eval( ) {

	return *__current;
}

EIdx
&EIdx::inc( ) {

	++*__current;

	return *this;
}

bool
EIdx::is( Idx &p_idx ) const {

	if( isConstant( ) || p_idx.isConstant( ) ) {

		return true;
	}

	return ( static_cast< EIdx & >( p_idx ) ).__begin == __begin;
}

bool
EIdx::isConstant( ) const {

	return false;
}

bool
EIdx::isOK( ) const {

	return *__current < *__end && *__begin <= *__current;
}

bool
EIdx::isReference( ) const {

	return __isReference;
}

EIdx
&EIdx::reset( ) {

	*__current = *__begin;

	return *this;
}

EIdx
&EIdx::set( int const &p_value ) {

	*__current = p_value;

	return *this;
}

EIdx
&EIdx::setCount( int const &p_count ) {

	*__end = *__begin + p_count;

	return *this;
}

EIdx
&EIdx::setFirst( int const &p_first ) {

	int
	d_ = *__end - *__begin;

	*__begin = p_first;
	*__end = *__begin + d_;
	*__current = *__begin;

	return *this;
}

int
EIdx::val( ) {

	return *__current;
}

EIdx
&EIdx::operator ++( ) {

	return inc( );
}


//---------------------------------------------------------------------------


TreeEinsteinIndex::TreeEinsteinIndex( EIdx *p_eIdx ) :
TreeI( ),
__einsteinIndex( p_eIdx ) {

}

TreeI
*TreeEinsteinIndex::cpy( ) {

	return new TreeEinsteinIndex( __einsteinIndex );
}

int
TreeEinsteinIndex::val( ) {

	return __einsteinIndex->val( );
}


//---------------------------------------------------------------------------


Subscription::Subscription( ) {

}

Subscription::~Subscription( ) {

}

Subscription
&Subscription::addIdx( Idx *p_idx ) {

	push_back( p_idx );

	return *this;
}

bool
Subscription::contains( EIdx *p_eidx ) const {

	for( auto i : *this ) {

		if( !i->isConstant( ) ) {

			if( i->is( *p_eidx ) ) {

				return true;
			}
		}
	}

	return false;
}

//---------------------------------------------------------------------------


Counter::Counter( ) :
std::vector< EIdx * >( ) {

}

Counter::~Counter( ) {

}

Counter
&Counter::operator ++( ) {

	return inc( );
}

Counter
&Counter::addEIdx( EIdx *p_eidx ) {

	push_back( p_eidx );

	return *this;
}

Counter
&Counter::buildFromSubscription( Subscription const &p_subscription ) {

	resize( 0 );

	for( auto i : p_subscription ) {

		if( !i->isConstant( ) ) {

			if( !contains( static_cast< EIdx * >( i ) ) ) {

				push_back( static_cast< EIdx * >( i ) );
			}
		}
	}

	return *this;
}

bool
Counter::contains( EIdx *p_eidx ) const {

	for( auto i : *this ) {

		if( i->is( *p_eidx ) ) {

			return true;
		}
	}

	return false;
}

Counter
&Counter::inc( ) {

	__lastChangedDigit = size( );

	while( 0 <= --__lastChangedDigit ) {

		if( ( ++*at( __lastChangedDigit ) ).isOK( ) ) {

			return *this;
		}

		at( __lastChangedDigit )->reset( );
	}

	return *this;
}

bool
Counter::isOK( ) const {

	return 0 <= __lastChangedDigit;
}

int
Counter::lcd( ) const {

	return __lastChangedDigit;
}

Counter
&Counter::reset( ) {

	for( auto i : *this ) {

		i->reset( );
	}

	__lastChangedDigit = size( );

	return *this;
}
