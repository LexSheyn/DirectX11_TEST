#ifndef SPHERE_H
#define SPHERE_H

#include "IndexedTriangleList.h"

namespace dx11
{
	class Shpere
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

			// 39
		}
	};
}

#endif // SPHERE_H