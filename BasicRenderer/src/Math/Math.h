#ifndef MATH_H
#define MATH_H

namespace dx11
{
	constexpr float32 PI_f32 = 3.14159265f;

	constexpr float64 PI_f64 = 3.1415926535897932;

// Template Functions:

	template <typename T>
	constexpr auto Square(const T& x)
	{
		return x * x;
	}

	template <typename T>
	T WrapAngle( T theta )
	{
		const T modded = std::fmod( theta, static_cast<T>( 2.0 ) * static_cast<T>(PI_f64) );

		return ( modded > static_cast<T>(PI_f64) ) ? ( modded - static_cast<T>(2.0) * static_cast<T>(PI_f64) ) : modded ;
	}

	template <typename T>
	constexpr T Interpolate( const T& source, const T& dst, float32 alpha )
	{
		return source + ( dst - source ) * alpha;
	}

	template <typename T>
	constexpr T ToRadians( T degree )
	{
		return degree * PI_f32 / static_cast<T>(180.0);
	}
}

#endif // MATH_H