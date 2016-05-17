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

		EIdx( EIdx const &p_idx );

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
		*cpy( ) const;

		int
		getCount( ) const {

			return __end - __begin;
		}

		EIdx
		&inc( );

		bool
		is( EIdx *p_idx ) const;

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
		val( ) const;

	public:

		EIdx
		&operator ++( );
};


//---------------------------------------------------------------------------


class TreeEinsteinIndex :
public TreeI {

	public:

		TreeEinsteinIndex( EIdx const *p_eIdx );

	private:

		EIdx const
		*__einsteinIndex;

	public:

		TreeI
		*cpy( ) const;

		int
		val( ) const;
};


//---------------------------------------------------------------------------


class Subscription :
public std::vector< EIdx * > {

	public:

		Subscription( );

		~Subscription( );

	public:

		Subscription
		&addEIdx( EIdx *p_idx );

		bool
		contains( EIdx * p_eidx ) const;
};

class Counter :
public Subscription {

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
		&buildForMultiplicationInnerLoop( Subscription const &p_lhs, Subscription const &p_rhs );

		Counter
		&buildForMultiplicationOuterLoop( Subscription const &p_lhs, Subscription const &p_rhs );

		Counter
		&buildFromSubscription( Subscription const &p_subscription );

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
