#ifndef BOX_H
#define BOX_H

#include "../DrawableBase.h"

#include "../../Bindable/ConstantBuffer.h"
#include "../../Bindable/IndexBuffer.h"
#include "../../Bindable/InputLayout.h"
#include "../../Bindable/PixelShader.h"
#include "../../Bindable/Topology.h"
#include "../../Bindable/MatrixTransformer.h"
#include "../../Bindable/VertexBuffer.h"
#include "../../Bindable/VertexShader.h"

#include "../Primitives/Sphere.h"
#include "../Primitives/Prism.h"
#include "../Primitives/Cube.h"

namespace dx11
{
	class Box : public DrawableBase<Box>
	{
	public:

	// Constructors and Destructor:

		Box( RenderSystem& renderSystem,
			 std::mt19937& rng,
			 std::uniform_real_distribution<float32>& adist,
			 std::uniform_real_distribution<float32>& ddist,
			 std::uniform_real_distribution<float32>& odist,
			 std::uniform_real_distribution<float32>& rdist);

	// Functions:

		void Update( const float32& dt ) noexcept override;

	// Accessors:

		DirectX::XMMATRIX GetTransformXM() const noexcept override;

	private:

	// Positional:

		float32 radius;

		float32 roll  = 0.0f;
		float32 pitch = 0.0f;
		float32 yaw   = 0.0f;

		float32 theta;
		float32 phi;
		float32 chi;

	// Speed ( delta/s ):

		float32 droll;
		float32 dpitch;
		float32 dyaw;

		float32 dtheta;
		float32 dphi;
		float32 dchi;

	// Model transform:

	//	DirectX::XMFLOAT3X3 m_TransformationMatrix;
	};
}

#endif // BOX_H