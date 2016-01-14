#ifndef TERM_HPP
#define TERM_HPP

#include <iomanip>
#include <string>
#include <sstream>
//#include "idx.h"

template< typename T >
class Tree {

	public:

		Tree( ) {

		}

		virtual
		~Tree( ) {

		}

	public:

		virtual Tree< T >
		*cpy( ) = 0;

		std::string
		str( std::size_t const &p_width = 0 ) {

			std::stringstream
			ss;

			if( p_width ) {

				ss << std::setw( p_width ) << val( );

				return ss.str( );
			}

			ss << val( );

			return ss.str( );
		}

		virtual T
		val( ) = 0;
};

template< typename T >
class TreeValue :
public Tree< T > {

	public:

		TreeValue( T const &p_val ) :
		Tree< T >( ),
		__val( p_val ) {

		}

		~TreeValue( ) {

		}

	private:

		T
		__val;

	public:

		Tree< T >
		*cpy( ) {

			return new TreeValue< T >( __val );
		}

		TreeValue< T >
		&set( T const &p_val ) {

			__val = p_val;

			return *this;
		}

		T
		val( ) {

			return __val;
		}
};

template< typename T >
class TreeBranch :
public Tree< T > {

	public:

		TreeBranch( Tree< T > *p_lhs, Tree< T > *p_rhs ) :
		Tree< T >( ),
		_lhs( p_lhs ),
		_rhs( p_rhs ) {

		}

		~TreeBranch( ) {

			delete _lhs;
			delete _rhs;
		}

	protected:

		Tree< T >
		*_lhs,
		*_rhs;

	public:

		Tree< T >
		*lhs( bool p_copy = false ) {

			return p_copy ? _lhs->cpy( ) : _lhs;
		}

		Tree< T >
		*rhs( bool p_copy = false ) {

			return p_copy ? _rhs->cpy( ) : _rhs;
		}
};

template< typename T >
class TreeSum :
public TreeBranch< T > {

	public:

		TreeSum( Tree< T > *p_lhs, Tree< T > *p_rhs ) :
		TreeBranch< T >( p_lhs, p_rhs ) {

		}

		~TreeSum( ) {

		}

	public:


		Tree< T >
		*cpy( ) {

			return new TreeSum( this->lhs( true ), this->rhs( true ) );
		}

		T
		val( ) {

			return this->lhs( )->val( ) + this->rhs( )->val( );
		}
};

template< typename T >
class TreeDif :
public TreeBranch< T > {

	public:

		TreeDif( Tree< T > *p_lhs, Tree< T > *p_rhs ) :
		TreeBranch< T >( p_lhs, p_rhs ) {

		}

		~TreeDif( ) {

		}

	public:


		Tree< T >
		*cpy( ) {

			return new TreeDif( this->lhs( true ), this->rhs( true ) );
		}

		T
		val( ) {

			return this->lhs( )->val( ) - this->rhs( )->val( );
		}
};

template< typename T >
class TreeMul :
public TreeBranch< T > {

	public:

		TreeMul( Tree< T > *p_lhs, Tree< T > *p_rhs ) :
		TreeBranch< T >( p_lhs, p_rhs ) {

		}

		~TreeMul( ) {

		}

	public:


		Tree< T >
		*cpy( ) {

			return new TreeMul( this->lhs( true ), this->rhs( true ) );
		}

		T
		val( ) {

			return this->lhs( )->val( ) * this->rhs( )->val( );
		}
};

template< typename T >
class TreeDiv :
public TreeBranch< T > {

	public:

		TreeDiv( Tree< T > *p_lhs, Tree< T > *p_rhs ) :
		TreeBranch< T >( p_lhs, p_rhs ) {

		}

		~TreeDiv( ) {

		}

	public:


		Tree< T >
		*cpy( ) {

			return new TreeDiv( this->lhs( true ), this->rhs( true ) );
		}

		T
		val( ) {

			return this->lhs( )->val( ) / this->rhs( )->val( );
		}
};

template< typename T, typename T2 >
class TreeCast :
public Tree< T > {

	public:

		TreeCast( Tree< T2 > *p_tree ) :
		Tree< T >( ),
		__from( p_tree ) {

		}

		~TreeCast( ) {

			delete __from;
		}

	private:

		Tree< T2 >
		*__from;

	public:

		Tree< T >
		*cpy( ) {

			return new TreeCast< T, T2 >( __from->cpy( ) );
		}

		T
		val( ) {

			return __from->val( );
		}
};



template< typename T >
class Term {

	public:

		Term(  ) :
		__tree( 0 ) {

		}

		Term( Tree< T > *p_tree ) :
		__tree( p_tree ) {

		}

		template< typename T2 >
		Term( Term< T2 > const &p_term ) :
		__tree( new TreeCast< T, T2 >( p_term.cpy( ) ) ) {

		}

		~Term(  ) {

			delete __tree;
		}

	private:

		Tree< T >
		*__tree;

	public:

		Tree< T >
		*cpy( ) const {

			return __tree->cpy( );
		}

		Tree< T >
		*tree( ) const {

			return __tree;
		}

		T
		val( ) {

			return __tree->val( );
		}

		std::string
		str( ) {

			return __tree->str( );
		}

	public:

		Term< T >
		&operator =( Term< T > &p_term ) {

			delete __tree;

			__tree = p_term.cpy( );
		}

		Term< T >
		operator +( Term< T > const &p_term ) {

			return Term< T >( new TreeSum< T >( this->cpy( ), p_term.cpy( ) ) );
		}

		Term< T >
		operator +( T const &p_val ) {

			return Term< T >( new TreeSum< T >( this->cpy( ), new TreeValue< T >( p_val ) ) );
		}

		Term< T >
		operator -( Term< T > const &p_term ) {

			return Term< T >( new TreeDif< T >( this->cpy( ), p_term.cpy( ) ) );
		}

		Term< T >
		operator -( T const &p_val ) {

			return Term< T >( new TreeDif< T >( this->cpy( ), new TreeValue< T >( p_val ) ) );
		}

		Term< T >
		operator *( Term< T > const &p_term ) {

			return Term< T >( new TreeMul< T >( this->cpy( ), p_term.cpy( ) ) );
		}

		Term< T >
		operator *( T const &p_val ) {

			return Term< T >( new TreeMul< T >( this->cpy( ), new TreeValue< T >( p_val ) ) );
		}

		Term< T >
		operator /( Term< T > const &p_term ) {

			return Term< T >( new TreeDiv< T >( this->cpy( ), p_term.cpy( ) ) );
		}

		Term< T >
		operator /( T const &p_val ) {

			return Term< T >( new TreeDiv< T >( this->cpy( ), new TreeValue< T >( p_val ) ) );
		}
};

template< typename T >
Term< T >
operator +( T const &p_val, Term< T > const &p_term ) {

	return Term< T >( new TreeSum< T >( new TreeValue< T >( p_val ), p_term.cpy( ) ) );
}

template< typename T >
Term< T >
operator -( T const &p_val, Term< T > const &p_term ) {

	return Term< T >( new TreeDif< T >( new TreeValue< T >( p_val ), p_term.cpy( ) ) );
}

template< typename T >
Term< T >
operator *( T const &p_val, Term< T > const &p_term ) {

	return Term< T >( new TreeMul< T >( new TreeValue< T >( p_val ), p_term.cpy( ) ) );
}

template< typename T >
Term< T >
operator /( T const &p_val, Term< T > const &p_term ) {

	return Term< T >( new TreeDiv< T >( new TreeValue< T >( p_val ), p_term.cpy( ) ) );
}

#endif // TERM_HPP
