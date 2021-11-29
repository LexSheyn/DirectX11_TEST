#ifndef SPHERE_H
#define SPHERE_H

#include "IndexedTriangleList.h"

namespace dx11
{
	class Sphere
	{
	public:

	// Functions:

		template <class V>
		static IndexedTriangleList<V> MakeTesselated( int32 lattitudeDiv, int32 longitudeDiv )
		{
			assert( lattitudeDiv >= 3 );

			assert( longitudeDiv >= 3 );

			constexpr float32 radius = 1.0f;

			const auto base = DirectX::XMVectorSet( 0.0f, 0.0f, radius, 0.0f );

			const float32 lattitudeAngle = PI_f32 / lattitudeDiv;

			const float32 longitudeAngle = 2.0f * PI_f32 / longitudeDiv;

			std::vector<V> vertices;

			for ( int32 iLat = 1; iLat < lattitudeDiv; iLat++ )
			{
				const auto latitudeBase = DirectX::XMVector3Transform( base, DirectX::XMMatrixRotationX( lattitudeAngle * iLat ) );

				for ( int32 iLong = 0; iLong < longitudeDiv; iLong++ )
				{
					vertices.emplace_back();

					auto xm_vector = DirectX::XMVector3Transform( latitudeBase, DirectX::XMMatrixRotationZ( longitudeAngle * iLong ) );

					DirectX::XMStoreFloat3( &vertices.back().position, xm_vector );
				}
			}

		// Add the cap vertices:

			const auto iNorthPole = static_cast<uint16>( vertices.size() );

			vertices.emplace_back();

			DirectX::XMStoreFloat3( &vertices.back().position, base );

			const auto iSouthPole = static_cast<uint16>( vertices.size() );

			vertices.emplace_back();

			DirectX::XMStoreFloat3( &vertices.back().position, DirectX::XMVectorNegate( base ) );

			const auto func_CalculateIndex = [lattitudeDiv, longitudeDiv]( uint16 iLat, uint16 iLong )
			{
				return iLat * longitudeDiv + iLong;
			};

			std::vector<uint16> indices;

			for ( uint16 iLat = 0u; iLat < static_cast<uint16>(lattitudeDiv - 2); iLat++ )
			{
				for ( uint16 iLong = 0u; iLong < static_cast<uint16>(longitudeDiv - 1); iLong++ )
				{
					indices.push_back( func_CalculateIndex( iLat, iLong ) );
					indices.push_back( func_CalculateIndex( iLat + 1u, iLong ) );
					indices.push_back( func_CalculateIndex( iLat, iLong + 1u ) );
					indices.push_back( func_CalculateIndex( iLat, iLong + 1u ) );
					indices.push_back( func_CalculateIndex( iLat + 1u, iLong ) );
					indices.push_back( func_CalculateIndex( iLat + 1u, iLong + 1u ) );
				}

			// Wrap band:

				indices.push_back( func_CalculateIndex( iLat, longitudeDiv - 1 ) );
				indices.push_back( func_CalculateIndex( iLat + 1u, longitudeDiv - 1 ) );
				indices.push_back( func_CalculateIndex( iLat, 0u ) );
				indices.push_back( func_CalculateIndex( iLat, 0u ) );
				indices.push_back( func_CalculateIndex( iLat + 1u, longitudeDiv - 1 ) );
				indices.push_back( func_CalculateIndex( iLat + 1u, 0u ) );
			}

		// Cap fans:

			for ( uint16 iLong = 0u; iLong < longitudeDiv - 1u; iLong++ )
			{
			// North:

				indices.push_back( iNorthPole );
				indices.push_back( func_CalculateIndex( 0u, iLong ) );
				indices.push_back( func_CalculateIndex( 0u, iLong + 1u ) );

			// South:

				indices.push_back( func_CalculateIndex( lattitudeDiv - 2, iLong + 1u ) );
				indices.push_back( func_CalculateIndex( lattitudeDiv - 2, iLong ) );
				indices.push_back( iSouthPole );
			}

		// Wrap triangles:
		// North:

			indices.push_back( iNorthPole );
			indices.push_back( func_CalculateIndex( 0, longitudeDiv - 1	 ) );
			indices.push_back( func_CalculateIndex( 0, 0 ) );

		// South:

			indices.push_back( func_CalculateIndex( lattitudeDiv - 2, 0 ) );
			indices.push_back( func_CalculateIndex( lattitudeDiv - 2, longitudeDiv - 1 ) );
			indices.push_back( iSouthPole );

			return { std::move( vertices ), std::move( indices ) };
		}

		template <class V>
		static IndexedTriangleList<V> Make()
		{
			return MakeTesselated<V>( 12, 24 );
		}
	};
}

#endif // SPHERE_H