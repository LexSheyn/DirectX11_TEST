#ifndef CONE_H
#define CONE_H

#include "IndexedTriangleList.h"

namespace dx11
{
	class Cone
	{
	public:

	// Functions:

		template<class V>
		static IndexedTriangleList<V> MakeTesselated(int32 longDiv)
		{			
			assert(longDiv >= 3);

			const auto base = DirectX::XMVectorSet(1.0f,  0.0f,  -1.0f,  0.0f);

			const float32 longitudeAngle = 2.0f * PI_f32 / longDiv;

			// base vertices
			std::vector<V> vertices;

			for (int32 iLong = 0; iLong < longDiv; iLong++)
			{
				vertices.emplace_back();

				auto xm_vector = DirectX::XMVector3Transform( base, DirectX::XMMatrixRotationZ(longitudeAngle * iLong));

				DirectX::XMStoreFloat3(&vertices.back().position,  xm_vector);
			}

		// The center:

			vertices.emplace_back();

			vertices.back().position = { 0.0f, 0.0f, -1.0f };

			const auto iCenter = (uint16)(vertices.size() - 1);

		// The tip :darkness:

			vertices.emplace_back();

			vertices.back().position = { 0.0f, 0.0f, 1.0f };

			const auto iTip = (uint16)(vertices.size() - 1);


		// Base indices:

			std::vector<uint16> indices;

			for (uint16 iLong = 0; iLong < longDiv; iLong++)
			{
				indices.push_back(iCenter);
				indices.push_back((iLong + 1) % longDiv);
				indices.push_back(iLong);
			}

		// Cone indices:

			for (uint16 iLong = 0; iLong < longDiv; iLong++)
			{
				indices.push_back(iLong);
				indices.push_back((iLong + 1) % longDiv);
				indices.push_back(iTip);
			}

			return { std::move(vertices), std::move(indices) };
		}

		template<class V>
		static IndexedTriangleList<V> Make()
		{
			return MakeTesselated<V>( 24 );
		}
	};
}

#endif // CONE_H