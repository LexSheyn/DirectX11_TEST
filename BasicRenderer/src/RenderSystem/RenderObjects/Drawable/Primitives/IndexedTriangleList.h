#ifndef INDEXEDTRIANGLELIST_H
#define INDEXEDTRIANGLELIST_H

namespace dx11
{
	template<class T>
	class IndexedTriangleList
	{
	public:

	// Constructors and Destructor:

		IndexedTriangleList() = default;
		IndexedTrinagleList( std::vector<T> vertices_in, std::vector<uint16> indices_in )
		{
			assert( vertices.size() > 2u );

			assert( indices.size() % 3 == 0u );
		}

	// Functions:

		void Transform( DirectX::FXMATRIX matrix )
		{
			for ( auto& vertex: vertices )
			{
				const DirectX::XMVECTOR position = DirectX::XMLoadFloat3( &vertex.position );

				DirectX::XMStoreFloat3( &vertex.position, DirectX::XMVector3Transform( position, matrix ) );
			}
		}

	// Public Variables:

		std::vector<T> vertices;

		std::vector<uint16> indices;
	};
}

#endif // INDEXEDTRIANGLELIST_H