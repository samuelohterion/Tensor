#ifndef IDX_H
#define IDX_H

#include "term.hpp"
#include <vector>

class Idx {

	public:

		Idx( );

		virtual
		~Idx( );

	public:

		virtual bool
		is( Idx &p_idx ) const = 0;

		virtual bool
		isConstant( ) const = 0;

		virtual bool
		isReference( ) const = 0;

		virtual int
		eval( ) = 0;
};


//---------------------------------------------------------------------------

typedef Term< int >
TermI;

typedef Tree< int >
TreeI;

class CIdx :
public Idx,
public TermI {

	public:

		CIdx( );

		CIdx( CIdx &p_idx );

		CIdx( int const &p_val );

		~CIdx( );

	public:

		TreeI
		*cpy( );

		int
		eval( );

		bool
		is( Idx & ) const;

		bool
		isConstant( ) const;

		bool
		isReference( ) const;

		int
		val( );
};


//---------------------------------------------------------------------------


class TreeConstantIndex :
public TreeI {

	public:

		TreeConstantIndex( int const &p_value );

	private:

		int const
		__value;

	public:

		TreeI
		*cpy( );

		int
		val( );
};


//---------------------------------------------------------------------------


class EIdx :
public Idx,
public TermI {

	public:

		EIdx( );

		EIdx( EIdx const &p_idx );

		~EIdx( );

	private:

		bool
		__isReference;

		int
		*__begin,
		*__current,
		*__end;

	public:

		TreeI
		*cpy( );

		int
		eval( );

		EIdx
		&inc( );

		bool
		is( Idx &p_idx ) const;

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
public std::vector< Idx * > {

	public:

		Subscription( );

		~Subscription( );

	public:

		Subscription
		&addIdx( Idx *p_idx );

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
