#ifndef MOUSE_H
#define MOUSE_H

#include "Base/BasicMouse.h"

#include "MouseEvent.h"

namespace dx11
{
	class Mouse : public BasicMouse
	{
		friend class MouseEvent;
		friend class Window;

	public:

	// Constructors and Destructor:

		Mouse() = default;
		Mouse( const Mouse& ) = delete;

	// Operators:

		Mouse& operator=( const Mouse& ) = delete;

	// Functions:

		MouseEvent Read()  noexcept;

		void       Flush() noexcept;

	// Accessors:

		std::pair<int32, int32> GetPosition() const noexcept { return { x, y }; }

		const int32& GetX() const noexcept override { return x; }

		const int32& GetY() const noexcept override { return y; }

		const bool8& LeftIsPressed()  const noexcept override { return b_LeftIsPressed; }

		const bool8& RightIsPressed() const noexcept override { return b_RightIsPressed; }

		bool8 IsEmpty() const noexcept { return m_Buffer.empty(); }

	private:

	// Private Functions:

		void OnMouseMove( int32 _x, int32 _y )    noexcept;

		void OnLeftPress( int32 _x, int32 _y )    noexcept;

		void OnLeftRelease( int32 _x, int32 _y )  noexcept;

		void OnRightPress( int32 _x, int32 _y )   noexcept;

		void OnRightRelease( int32 _x, int32 _y ) noexcept;

		void OnWheelUp( int32 _x, int32 _y )      noexcept;

		void OnWheelDown( int32 _x, int32 _y )    noexcept;

		void TrimBuffer()                         noexcept;

	// Variables:

		static constexpr uint32 m_BufferSize = 16u;

	// Inherited from BasicMouse:

	//	int32 x = 0;
	//	int32 y = 0;
	//
	//	bool8 b_LeftIsPressed  = false;
	//	bool8 b_RightIsPressed = false;

		std::queue<MouseEvent> m_Buffer;
	};
}

#endif // MOUSE_H