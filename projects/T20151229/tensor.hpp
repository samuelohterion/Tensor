#ifndef TENSOR_HPP
#define TENSOR_HPP

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

		std::vector< std::size_t > const
		&extents( ) const {

			return __extents;
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
		operator [ ]( EIdx const &p_eidx ) const {

			return SubTensor< T >( this, p_eidx, true );
		}
};

template< typename T >
class TreeSubTensor :
public Tree< T > {

	public:

		TreeSubTensor( SubTensor< T > const &p_subTensor ) :
		Tree< T >( ) {

		}
	public:

		Tree< T >
		*cpy( ) {

			return new TreeSubTensor( this );
		}

		T
		val( ) {

			return 0;
		}
};

template< typename T >
class SubTensor :
Term< T  > {

	public:

		SubTensor( Tensor< T > *const p_tensor, EIdx const &p_eidx, bool p_reference = true ) :
		Term< T >( new TreeSubTensor< T >( this ) ),
		__reference( p_reference ),
		__t( __reference ? p_tensor : new Tensor< T >( p_tensor->properties.extents( ) ) ),
		__eidx( 1, p_eidx ) {

		}

	private:

		bool
		__reference;

		Tensor< T >
		*__t;

		std::vector< EIdx >
		__eidx;

	public:

		SubTensor< T >
		&operator [ ]( EIdx const &p_eidx ) {

			__eidx.push_back( p_eidx );

			return *this;
		}
};

#endif // TENSOR_HPP
