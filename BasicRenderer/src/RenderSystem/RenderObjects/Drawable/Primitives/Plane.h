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
			// ...
		}
	};
}

#endif // PLANE_H