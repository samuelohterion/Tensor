#ifndef IDX_H
#define IDX_H

#include "term.hpp"

class Idx :
public Term< int > {

	public:

		Idx( );

		~Idx( );

	public:

		virtual bool
		is( Idx const &p_idx ) const  = 0;

		virtual bool
		isConstant( ) const = 0;

		virtual bool
		isReference( ) const = 0;

		virtual Idx
		&set( int const &p_val );

		virtual int
		val( ) const = 0;

	public:

		std::string
		str( ) const;
};

class TreeCIdx :
public TreeValue< int > {

	public:

		TreeCIdx( int const &p_constantIndex );
};

class CIdx :
public Idx {

	public:

		CIdx( );

		CIdx( CIdx const &p_idx );

		CIdx( int const &p_idx );

		~CIdx( );

	private:

		int const
		__value;

	public:

		Tree< int >
		*cpy( ) const;

		bool
		is( Idx const &p_idx );

		Idx
		&reset( );

		TreeValue
		&set( int const &p_val );

		TreeValue
		&setCount( int const &p_count);

		TreeValue
		&setFirst( int const &p_first);

		std::string
		str( ) const;

		int
		val( ) const;
};

//class Idx :
//public Term< int > {

//	public:

//		Idx( );

//		Idx( Idx const &p_idx );

//		Idx( int const &p_idx );

//		~Idx( );

//	private:

//		bool
//		__constant,
//		__reference;

//		int
//		*__begin,
//		*__current,
//		*__end;

//	public:

//		Tree< int >
//		*cpy( ) const;

//		bool
//		is( Idx const &p_idx );

//		Idx
//		&reset( );

//		TreeValue
//		&set( int const &p_val );

//		TreeValue
//		&setCount( int const &p_count);

//		TreeValue
//		&setFirst( int const &p_first);

//		std::string
//		str( ) const;

//		int
//		val( ) const;
//};

#endif // IDX_H
