#ifndef DRAWABLETEMPLATE_H
#define DRAWABLETEMPLATE_H

#include "Drawable.h"

namespace dx11
{
	template<class T>
	class DrawableTemplate : public Drawable
	{
	public:

		// Functions:

		bool8 IsStaticInitialized() const noexcept
		{
			return !m_StaticBinds.empty();
		}

		void AddStaticBind(std::unique_ptr<Bindable> bind) noexcept
		{
			assert("*Must* use AddIndexBudder to bind index buffer" && typeid(*bind));

			m_StaticBinds.push_back(std::move(bind));
		}

		void AddStaticIndexBuffer(std::unique_ptr<IndexBuffer> indexBuffer) noexcept
		{
			assert( "Attempint to add index buffer a second time" && m_pIndexBuffer == nullptr );

			m_pIndexBuffer = indexBuffer.get();

			m_StaticBinds.push_back(std::move(indexBuffer));
		}

		void SetIndexFromStatic() noexcept
		{
			assert( "Attempint to add index buffer a second time" && m_pIndexBuffer == nullptr );

			for ( const auto& bind : m_StaticBinds )
			{
				if ( const auto pointer = dynamic_cast<IndexBuffer*>(bind.get()) )
				{
					m_pIndexBuffer = pointer;

					return;
				}
			}

			assert( "Failed to find index buffer in static binds" && m_pIndexBuffer != nullptr );
		}

	private:

		// Private Accessors:

		const std::vector<std::unique_ptr<Bindable>>& GetStaticBinds() const noexcept override;
		{
			return m_StaticBinds;
		}

		// Variables:

		static std::vector<std::unique_ptr<Bindable>> m_StaticBinds;
	};

	template<class T>
	std::vector<std::unique_ptr<Bindable>> DrawableTemplate<T>::m_StaticBinds;
}

#endif // DRAWABLETEMPLATE_H