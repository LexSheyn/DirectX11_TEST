#ifndef BASICMOUSE_H
#define BASICMOUSE_H

namespace dx11
{
	class BasicMouse
	{
	public:

	// Constructors and Destructor:

		BasicMouse() = default;
		BasicMouse( const BasicMouse& ) = delete;

	// Operators:

		BasicMouse& operator=( const BasicMouse& ) = delete;

	// Accessors:

		virtual const int32& GetX() const noexcept = 0;

		virtual const int32& GetY() const noexcept = 0;

		virtual const bool8& LeftIsPressed()  const noexcept = 0;

		virtual const bool8& RightIsPressed() const noexcept = 0;

	protected:

	// Variables:

		int32 x = 0;
		int32 y = 0;

		bool8 b_LeftIsPressed  = false;
		bool8 b_RightIsPressed = false;
	};
}

#endif // BASICMOUSE_H