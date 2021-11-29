#ifndef PLANE_H
#define PLANE_H

#include "IndexedTriangleList.h"

namespace dx11
{
	class Plane
	{
	public:

		template<class V>
		static IndexedTriangleList<V> MakeTesselated( int32 divisions_x, int32 divisions_y )
		{
			assert( divisions_x >= 1 );

			assert( divisions_y >= 1 );

			constexpr float32 width  = 2.0f;

			constexpr float32 height = 2.0f;

			const int32 nVertices_x = divisions_x + 1;

			const int32 nVertices_y = divisions_y + 1;

			std::vector<V> vertices( nVertices_x * nVertices_y );

			// Anonymous scope.
			{
				const float32 side_x = width  / 2.0f;

				const float32 side_y = height / 2.0f;

				const float32 divisionSize_x = width  / static_cast<float32>( divisions_x );

				const float32 divisionSize_y = height / static_cast<float32>( divisions_y );

				const auto bottonLeft = DirectX::XMVectorSet( -side_x, -side_y, 0.0f, 0.0f );

				for ( int32 y = 0, i = 0; y < nVertices_y; y++ )
				{
					const float32 position_y = static_cast<float32>( y ) * divisionSize_y;

					for ( int32 x = 0; x < nVertices_x; x++, i++ )
					{
						const auto xm_vector = DirectX::XMVectorSet( static_cast<float32>( x ) * divisionSize_x, position_y, 0.0f, 0.0f );

						DirectX::XMStoreFloat3(&vertices[i].position, xm_vector);
					}
				}
			}

			std::vector<uint16> indices;

			// Potential crash !!!!!!!!!!!!!!!!!!!!!!!
			indices.reserve( dx11::Square( divisions_x * divisions_y ) * 6 );

			// Anonymous scope.
			{
				// WHAT IS THAT??????????????
				const auto vxy2i = [nVertices_x]( size_t x, size_t y )
				{
					return static_cast<uint16>( y * nVertices_x + x );
				};

				for ( size_t y = 0; y < divisions_y; y++ )
				{
					for ( size_t x = 0; x < divisions_x; x++ )
					{
						// std::array ?????????? WTF ????????????????
					//	const std::array<uint16, 4> indexArray = { vxy2i(x, y), vxy2i(x + 1, y), vxy2i(x, y + 1), vxy2i(x + 1, y + 1) };
						const uint16 indexArray[4] = { vxy2i( x, y ), vxy2i( x + 1, y ), vxy2i( x, y + 1 ), vxy2i( x + 1, y + 1 ) };

						indices.push_back( indexArray[0] );
						indices.push_back( indexArray[2] );
						indices.push_back( indexArray[1] );
						indices.push_back( indexArray[1] );
						indices.push_back( indexArray[2] );
						indices.push_back( indexArray[3] );
					}
				}
			}

			return { std::move( vertices ), std::move( indices ) };
		}

		template<class V>
		static IndexedTriangleList<V> Make()
		{
			return this->MakeTesselated<V>( 1, 1 );
		}
	};
}

#endif // PLANE_H