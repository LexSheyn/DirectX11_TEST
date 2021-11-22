#ifndef MESSAGEMAP_H
#define MESSAGEMAP_H

namespace dx11
{
	class MessageMap
	{
	public:

	// Constructors and Destructor:

		MessageMap();

		~MessageMap();

	// Operators:

		std::string operator()( DWORD message, LPARAM lParam, WPARAM wParam ) const;

	private:

	// Variables:

		std::unordered_map<DWORD, std::string> m_MessageMap;
	};
}

#endif // MESSAGEMAP_H