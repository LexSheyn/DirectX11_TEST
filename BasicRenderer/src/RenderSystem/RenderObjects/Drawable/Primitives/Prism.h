#ifndef PRISM_H
#define PRISM_H

#include "IndexedTriangleList.h"

namespace dx11
{
	class Prism
	{
	public:

	// Functions:

		template <class V>
		static IndexedTriangleList<V> MakeTesselated( int32 longDiv )
		{
			assert( longDiv >= 3 );

			const auto base = DirectX::XMVectorSet( 1.0f, 0.0f, -1.0f, 0.0f );
			
			const auto offset = DirectX::XMVectorSet( 0.0f, 0.0f, 2.0f, 0.0f );

			const float32 longitudeAngle = 2.0f * PI_f32 / longDiv;

		// Near center:

			std::vector<V> vertices;

			vertices.emplace_back();
			vertices.back().position = { 0.0f, 0.0f, -1.0f };

			const auto iCenterNear = static_cast<uint16>(vertices.size() - 1u);

		// Far center:

			vertices.emplace_back();
			vertices.back().position = { 0.0f, 0.0f, 1.0f };

			const auto iCenterFar = static_cast<uint16>(vertices.size() - 1u);

		// Base vertices:

			for ( int32 iLong = 0; iLong < longDiv; iLong++ )
			{
				// Near base.
				{
					vertices.emplace_back();

					auto xm_vector = DirectX::XMVector3Transform( base, DirectX::XMMatrixRotationZ( longitudeAngle * iLong ) );

					DirectX::XMStoreFloat3( &vertices.back().position, xm_vector );
				}

				// Far base.
				{
					vertices.emplace_back();

					auto xm_vector = DirectX::XMVector3Transform( base, DirectX::XMMatrixRotationZ( longitudeAngle * iLong ) );

					xm_vector = DirectX::XMVectorAdd( xm_vector, offset );

					DirectX::XMStoreFloat3( &vertices.back().position, xm_vector );
				}
			}

		// Side indices:

			std::vector<uint16> indices;

			for ( uint16 iLong = 0u; iLong < longDiv; iLong++ )
			{
				const auto i = iLong * 2;

				const auto mod = longDiv * 2;

				indices.push_back(  i + 2 );
				indices.push_back( (i + 2) % mod + 2 );
				indices.push_back(  i + 1 + 2 );
				indices.push_back( (i + 2) % mod + 2 );
				indices.push_back( (i + 3) % mod + 2 );
				indices.push_back(  i + 1 + 2 );
			}

		// Base indices:

			for ( uint16 iLong = 0u; iLong < longDiv; iLong++ )
			{
				const auto i = iLong * 2;

				const auto mod = longDiv * 2;

				indices.push_back(  i + 2 );
				indices.push_back( iCenterNear );
				indices.push_back( (i + 2) % mod + 2 );
				indices.push_back( iCenterFar );
				indices.push_back(  i + 1 + 2 );
				indices.push_back( (i + 3) % mod + 2 );
			}

			return { std::move( vertices ), std::move( indices ) };
		}

		template <class V>
		static IndexedTriangleList<V> Make()
		{
			return this->MakeTesselated<V>( 24 );
		}
	};
}

#endif // PRISM_H