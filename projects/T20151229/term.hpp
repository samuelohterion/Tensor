#ifndef TERM_HPP
#define TERM_HPP

#include <string>
#include <sstream>

template< typename T >
class Tree {

	public:

		Tree( ) {

		}

	public:

		virtual Tree< T >
		*cpy( ) const = 0;

		virtual std::string
		str( ) const {

			std::stringstream
			ss;

			ss << val( );

			return ss.str( );
		}

		virtual T
		val( ) const = 0;
};

template< typename T >
class TreeValue :
public Tree< T > {

	public:

		TreeValue( T const &p_val ) :
		Tree< T >( ),
		__val( p_val ) {

		}

	private:

		T
		__val;

	public:

		virtual Tree< T >
		*cpy( ) const {

			return new TreeValue< T >( __val );
		}

		virtual TreeValue
		&set( T const &p_val ) {

			__val = p_val;

			return *this;
		}

		virtual T
		val( ) const {

			return __val;
		}
};

template< typename T >
class TreeConstantValue :
public TreeValue< T > {

	public:

		TreeValue( T const &p_val ) :
		Tree< T >( ),
		__val( p_val ) {

		}

	private:

		T
		__val;

	public:

		virtual Tree< T >
		*cpy( ) const {

			return new TreeValue< T >( __val );
		}

		virtual TreeValue
		&set( T const &p_val ) {

			__val = p_val;

			return *this;
		}

		virtual T
		val( ) const {

			return __val;
		}
};

class TreeConstantIndex :
public TreeValue< int > {

	public:

		TreeConstantIndex( int const &p_val ) :
		TreeValue< int >( ),
		__val( p_val ) {

		}

	private:

		T
		__val;

	public:

		virtual Tree< T >
		*cpy( ) const {

			return new TreeValue< T >( __val );
		}

		virtual TreeValue
		&set( T const &p_val ) {

			__val = p_val;

			return *this;
		}

		virtual T
		val( ) const {

			return __val;
		}
};

template< typename T >
class Term {

	public:

		Term( ) {

		}
};

#endif // TERM_HPP
