#ifndef CUBE_H
#define CUBE_H

#include "IndexedTriangleList.h"

namespace dx11
{
	class Cube
	{
	public:
		
	// Functions:

		template<class V>
		static IndexedTriangleList<V> Make()
		{
			constexpr float32 side = 1.0f / 2.0f;

			std::vector<DirectX::XMFLOAT3> vertices_one;

			vertices_one.emplace_back( -side, -side, -side ); // 0
			vertices_one.emplace_back(  side, -side, -side ); // 1
			vertices_one.emplace_back( -side,  side, -side ); // 2
			vertices_one.emplace_back(  side,  side, -side ); // 3
			vertices_one.emplace_back( -side, -side,  side ); // 4
			vertices_one.emplace_back(  side, -side,  side ); // 5
			vertices_one.emplace_back( -side,  side,  side ); // 6
			vertices_one.emplace_back(  side,  side,  side ); // 7

			std::vector<V> vertices( vertices_one.size() );

			for ( size_t i = 0u; i < vertices_one.size(); i++ )
			{
				vertices[i].position = vertices_one[i];
			}

			return { std::move( vertices ), 
			 	     {
			 	         0, 2, 1,    2, 3, 1,
			 	         
			 	         1, 3, 5,    3, 7, 5,
			 	         
			 	         2, 6, 3,    3, 6, 7,
			 	         
			 	         4, 5, 7,    4, 7, 6,
			 	         
			 	         0, 4, 2,    2, 4, 6,
			 	         
			 	         0, 1, 4,    1, 5, 4
			         }
			};
		}
	};
}

#endif // CUBE_H