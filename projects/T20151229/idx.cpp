#include "idx.h"


//---------------------------------------------------------------------------


EIdx::EIdx( ) :
TermI( new TreeEinsteinIndex( this ) ),
__isConstant( false ),
__begin( 0 ),
__current( 0 ),
__end( 0 ) {

}

EIdx::EIdx( int const &p_idx ) :
TermI( new TreeEinsteinIndex( this ) ),
__isConstant( true ),
__begin( p_idx ),
__current( __begin ),
__end( __begin + 1 ) {

}

EIdx::~EIdx( ) {

}


TreeI
*EIdx::cpy( ) {

	return new TreeEinsteinIndex( this );
}

EIdx
&EIdx::inc( ) {

	++__current;

	return *this;
}

bool
EIdx::is( EIdx *p_idx ) const {

	if( isConstant( ) || p_idx->isConstant( ) ) {

		return false;
	}

	return p_idx == this;
}

bool
EIdx::isConstant( ) const {

	return __isConstant;
}

bool
EIdx::isOK( ) const {

	return __current < __end && __begin <= __current;
}

EIdx
&EIdx::reset( ) {

	__current = __begin;

	return *this;
}

EIdx
&EIdx::set( int const &p_value ) {

	__current = p_value;

	return *this;
}

EIdx
&EIdx::setCount( int const &p_count ) {

	__end = __begin + p_count;

	return *this;
}

EIdx
&EIdx::setFirst( int const &p_first ) {

	int
	d_ = __end - __begin;

	__begin = p_first;
	__end = __begin + d_;
	__current = __begin;

	return *this;
}

int
EIdx::val( ) {

	return __current;
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
&Subscription::addIdx( EIdx *p_idx ) {

	push_back( p_idx );

	return *this;
}

bool
Subscription::contains( EIdx *p_eidx ) const {

	for( auto i : *this ) {

		if( i->is( p_eidx ) ) {

			return true;
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

			if( !contains( i ) ) {

				push_back( i );
			}
		}
	}

	return *this;
}

bool
Counter::contains( EIdx *p_eidx ) const {

	for( auto i : *this ) {

		if( i->is( p_eidx ) ) {

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
