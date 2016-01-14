#ifndef TENSOR_HPP
#define TENSOR_HPP


#include <iomanip>
#include <iostream>
#include <ostream>
#include <string>
#include <sstream>

#include "idx.h"
#include "term.hpp"

class Properties {

	public:

		Properties( std::vector< std::size_t > const &p_extents ) :
		__extents( p_extents.cbegin( ), p_extents.cend( ) ) {

			__computeSubVolumes( );
		}

		Properties( std::initializer_list< std::size_t > const &p_extents ) :
		__extents( p_extents.begin( ), p_extents.end( ) ) {

			__computeSubVolumes( );
		}

		~Properties( ) {

		}

	private:

		std::vector< std::size_t >
		__extents,
		__subvolumes;

	private:

		void
		__computeSubVolumes( ) {

			__subvolumes.resize( __extents.size( ) );

			std::size_t
			vol = 1;

			auto
			s = __subvolumes.rbegin( );

			auto
			e = __extents.crbegin( );

			while( e != __extents.crend( ) ) {

				*s++ = vol;
				vol *= *e++;
			}
		}

	public:

		std::size_t
		extent( std::size_t const p_id ) const {

			return __extents[ p_id ];
		}

		std::vector< std::size_t > const
		&extents( ) const {

			return __extents;
		}

		std::size_t
		subVolume( std::size_t const &p_id ) const {

			return __subvolumes[ p_id ];
		}

		std::size_t
		volume( ) const {

			return __extents[ 0 ] * __subvolumes[ 0 ];
		}
};

template< typename T >
class SubTensor;

template< typename T >
class Tensor {

	public:

		Tensor( std::vector< std::size_t > const &p_extents ) :
		properties( p_extents ),
		x( properties.volume( ) ) {

		}

		Tensor( std::initializer_list< std::size_t > const &p_extents ) :
		properties( p_extents ),
		x( properties.volume( ) ) {

		}

		~Tensor( ) {

		}

	public:

		Properties
		properties;

		std::vector< T >
		x;

	public:

		SubTensor< T >
		operator [ ]( EIdx &p_eidx ) {

			if( !p_eidx.isConstant( ) ) {

				p_eidx.setFirst( 0 ).setCount( properties.extent( 0 ) ).reset( );
			}

			return SubTensor< T >( this, &p_eidx, true );
		}
};

template< typename T >
class TreeSubTensor;

template< typename T >
class SubTensor :
Term< T  > {

	public:

		SubTensor( Tensor< T > *const p_tensor, EIdx *p_eidx, bool p_reference = true ) :
		Term< T >( new TreeSubTensor< T >( this ) ),
		__reference( p_reference ),
		__t( __reference ? p_tensor : new Tensor< T >( p_tensor->properties.extents( ) ) ) {

			__subscription.addIdx( p_eidx );
		}

		~SubTensor( ) {

			if( !__reference ) {

				delete __t;
			}
		}

	private:

		bool
		__reference;

		Tensor< T >
		*__t;

		Subscription
		__subscription;

	private:

		std::size_t
		__address( ) {

			std::size_t
			addr = 0;

			for( std::size_t i = 0; i < __t->properties.extents( ).size( ); ++i ) {

				addr += __subscription[ i ]->val( ) * __t->properties.subVolume( i );
			}

			return addr;
		}

	public:

		SubTensor< T >
		&operator =( Term< T > p_term ) {

			Counter
			c;

			c.buildFromSubscription( __subscription );

			c.reset( );

			while( c.isOK( ) ) {

				set( p_term.val( ) );

				++c;
			}


			return *this;
		}

		SubTensor< T >
		&operator [ ]( EIdx &p_eidx ) {

			if( !p_eidx.isConstant( ) ) {

				p_eidx.setFirst( 0 ).setCount( __t->properties.extent( __subscription.size( ) ) ).reset( );
			}

			__subscription.addIdx( &p_eidx );

			return *this;
		}

		T
		eval( ) {

			return __t->x[ __address( ) ];

		}

		SubTensor< T >
		&set( T p_val ) {

			__t->x[ __address( ) ] = p_val;

			return *this;
		}

		std::string
		str( std::size_t const &p_width = 0 ) {

			std::stringstream
			ss;

			Counter
			c;

			c.buildFromSubscription( __subscription );

			while( c.isOK( ) ) {

				if( p_width ) {

					ss << ( 0 < c.size( ) - c.lcd( ) ? std::string( c.size( ) - c.lcd( ) - 1u, '\n' ) : "" ) << std::setw( p_width ) << eval( );
				}
				else {

					ss << ( 0 < c.size( ) - c.lcd( ) ? std::string( c.size( ) - c.lcd( ) - 1u, '\n' ) : "" ) << eval( );
				}

				++c;
			}

			return ss.str( );
		}
};

template< typename T >
class TreeSubTensor :
public Tree< T > {

	public:

		TreeSubTensor( SubTensor< T > *const p_subTensor ) :
		Tree< T >( ),
		__subTensor( p_subTensor ) {

		}

	private:

		SubTensor< T >
		*__subTensor;

	public:

		Tree< T >
		*cpy( ) {

			return new TreeSubTensor< T >( __subTensor );
		}

		T
		val( ) {

			return __subTensor->eval( );
		}
};

//template< typename T, typename T2 >
//Term< T >
//operator +( T const &p_val, Term< T2 > &p_term ) {

//	return Term< T >( new TreeSum< T >( new TreeValue< T >( p_val ), new TreeCast< T, T2 >( p_term.cpy( ) ) ) );
//}


#endif // TENSOR_HPP
