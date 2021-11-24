/*
#ifndef DXGIINFOMANAGER_H
#define DXGIINFOMANAGER_H

namespace dx11
{
	class DxgiInfoManager
	{
	public:

	// Constructors and Destructor:

		DxgiInfoManager();
		DxgiInfoManager( const DxgiInfoManager& ) = delete;

		~DxgiInfoManager();

	// Operators:

		DxgiInfoManager& operator=( const DxgiInfoManager& ) = delete;

	// Functions:

		void Set() noexcept;

	// Accessors:

		std::vector<std::string> GetMessages() const;

	private:

	// Variables:

		uint64 next = 0u;
		struct IDXGIInfoQueue* m_pDxgiInfoQueue = nullptr;
	};
}

#endif // DXGIINFOMANAGER_H
*/