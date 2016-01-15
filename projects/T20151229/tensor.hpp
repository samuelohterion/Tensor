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

		SubTensor< T >
		operator [ ]( std::size_t p_eidx ) const {

			return SubTensor< T >( this, EIdx( p_eidx ), true );
		}
};

template< typename T >
class TreeSubTensor;

template< typename T >
class SubTensor :
public Term< T  > {

	public:

		SubTensor( Tensor< T > *p_tensor, EIdx *p_eidx, bool p_reference = true ) :
		Term< T >( new TreeSubTensor< T >( this ) ),
		__reference( p_reference ),
		__t( __reference ? p_tensor : new Tensor< T >( p_tensor->properties.extents( ) ) ) {

			__subscription.addEIdx( p_eidx );
		}

		SubTensor( Tensor< T > *p_tensor, Subscription const &p_subscription, bool p_reference = false ) :
		Term< T >( new TreeSubTensor< T >( this ) ),
		__reference( p_reference ),
		__t( __reference ? p_tensor : new Tensor< T >( p_tensor->properties.extents( ) ) ),
		__subscription( p_subscription ) {

			std::copy( p_tensor->x.cbegin( ), p_tensor->x.cend( ), __t->x.begin( ) );
		}

		SubTensor( Subscription &p_subscription ) :
		Term< T >( new TreeSubTensor< T >( this ) ),
		__reference( false ),
		__t( 0 ),
		__subscription( p_subscription ) {

			__buildFromSubscription( );
		}

		~SubTensor( ) {

			if( !__reference ) {

				delete __t;
			}
		}

	public:

		bool
		__reference;

		Tensor< T >
		*__t;

		Subscription
		__subscription;

	private:

		std::size_t
		__address( ) const {

			int
			addr = 0;

			for( std::size_t i = 0; i < __t->properties.extents( ).size( ); ++i ) {

				addr += __subscription[ i ]->val( ) * __t->properties.subVolume( i );
			}

			return addr;
		}

		void
		__buildFromSubscription( ) {

			std::vector< std::size_t >
			extents;

			for( auto i : __subscription ) {

				if( !i->isConstant( ) ) {

					extents.push_back( i->getCount( ) );
				}
			}

			__t = new Tensor< T >( extents );
		}


	public:

		SubTensor< T >
		&operator =( Term< T > const &p_term ) {

			Counter
			c;

			c.buildFromSubscription( __subscription );

			while( c.isOK( ) ) {

				set( p_term.val( ) );

				++c;
			}


			return *this;
		}

		SubTensor< T >
		&operator =( SubTensor< T > const &p_subTensor ) {

			if( this->__t == p_subTensor.__t ) {

				SubTensor< T >
				tmp( p_subTensor.__t, p_subTensor.__subscription, false );

				Counter
				c;

				c.buildFromSubscription( __subscription );

				while( c.isOK( ) ) {

					set( tmp.eval( ) );

					++c;
				}

				return *this;
			}

			Counter
			c;

			c.buildFromSubscription( __subscription );

			while( c.isOK( ) ) {

				set( p_subTensor.eval( ) );

				++c;
			}

			return *this;
		}

		SubTensor< T >
		&operator [ ]( std::size_t const &p_eidx ) {

			__subscription.addEIdx( new EIdx( p_eidx ) );

			return *this;
		}

		SubTensor< T >
		&operator [ ]( EIdx &p_eidx ) {

			if( !p_eidx.isConstant( ) ) {

				p_eidx.setFirst( 0 ).setCount( __t->properties.extent( __subscription.size( ) ) ).reset( );
			}

			__subscription.addEIdx( &p_eidx );

			return *this;
		}

		SubTensor< T >
		operator *( SubTensor< T > const &p_subtensor ) const {

			Counter
			cOuter,
			cInner;

			cOuter.buildForMultiplicationOuterLoop( __subscription, p_subtensor.__subscription );
			cInner.buildForMultiplicationInnerLoop( __subscription, p_subtensor.__subscription );

			SubTensor< T >
			ret( cOuter );

			cOuter.reset( );

			while( cOuter.isOK( ) ) {

				T
				sum = T( 0 );

				cInner.reset( );

				while( cInner.isOK( ) ) {

					sum += this->eval( ) * p_subtensor.eval( );

					++cInner;
				}

				ret.set( sum );

				++cOuter;
			}

			return ret;
		}

		SubTensor< T >
		operator *( Term< T > const &p_term ) const {

			Counter
			c;

			c.buildFromSubscription( __subscription );

			SubTensor< T >
			ret( c );

			while( c.isOK( ) ) {

				ret.set( eval( ) * p_term.val( ) );

				++c;
			}

			return ret;
		}

		T
		eval( ) const {

			return __t->x[ __address( ) ];

		}

		SubTensor< T >
		&set( T p_val ) {

			__t->x[ __address( ) ] = p_val;

			return *this;
		}

		std::string
		str( std::size_t const &p_width = 0 ) const {

			std::stringstream
			ss;

			Counter
			c;

			c.buildFromSubscription( __subscription );

			if( p_width < 1 ) {

				std::size_t
				width = 0;

				while( c.isOK( ) ) {

					ss.str( "" );

					ss << eval( );

					std::size_t
					w = ss.str( ).length( );

					if( width < w ) {

						width = w;
					}

					++c;
				}

				width += 2;

				ss.str( "" );
				c.reset( );

				while( c.isOK( ) ) {

					ss << ( 0 < c.size( ) - c.lcd( ) ? std::string( c.size( ) - c.lcd( ) - 1u, '\n' ) : "" ) << std::setw( width ) << eval( );

					++c;
				}

				return ss.str( );
			}

			ss.str( "" );
			c.reset( );

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
		*cpy( ) const {

			return new TreeSubTensor< T >( __subTensor );
		}

		T
		val( ) const {

			return __subTensor->eval( );
		}
};

template< typename T >
std::ostream
&operator <<( std::ostream &p_os, SubTensor< T > const &p_st ) {

	p_os << p_st.str( );

	return p_os;
}


#endif // TENSOR_HPP
