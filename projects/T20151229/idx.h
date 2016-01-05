#ifndef IDX_H
#define IDX_H

#include "term.hpp"
#include <vector>

//---------------------------------------------------------------------------

typedef Term< int >
TermI;

typedef Tree< int >
TreeI;


//---------------------------------------------------------------------------


class EIdx :
public TermI {

	public:

		EIdx( );

		EIdx( int const &p_idx );

		~EIdx( );

	private:

		bool
		__isConstant;

		int
		__begin,
		__current,
		__end;

	public:

		TreeI
		*cpy( );

		EIdx
		&inc( );

		bool
		is( EIdx &p_idx ) const;

		bool
		isConstant( ) const;

		bool
		isOK( ) const;

		bool
		isReference( ) const;

		EIdx
		&reset( );

		EIdx
		&set( int const &p_value );

		EIdx
		&setCount( int const &p_count );

		EIdx
		&setFirst( int const &p_first );

		int
		val( );

	public:

		EIdx
		&operator ++( );
};


//---------------------------------------------------------------------------


class TreeEinsteinIndex :
public TreeI {

	public:

		TreeEinsteinIndex( EIdx *p_eIdx );

	private:

		EIdx
		*__einsteinIndex;

	public:

		TreeI
		*cpy( );

		int
		val( );
};


//---------------------------------------------------------------------------


class Subscription :
public std::vector< EIdx * > {

	public:

		Subscription( );

		~Subscription( );

	public:

		Subscription
		&addIdx( EIdx *p_idx );

		bool
		contains( EIdx * p_eidx ) const;
};

class Counter :
public std::vector< EIdx * > {

	public:

		Counter( );

		~Counter( );

	private:

		int
		__lastChangedDigit;

	public:

		Counter
		&operator ++( );

	public:

		Counter
		&addEIdx( EIdx *p_eidx );

		Counter
		&buildFromSubscription( Subscription const &p_subscription );

		bool
		contains( EIdx *p_edix ) const;

		Counter
		&inc( );

		bool
		isOK( ) const;

		int
		lcd( ) const;

		Counter
		&reset( );
};

#endif // IDX_H
