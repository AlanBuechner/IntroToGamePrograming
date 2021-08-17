#include "Entity.h"
#include "Renderer\Renderer.h"

namespace Engine
{
	void Drawable::Draw()
	{
		Renderer::Draw(m_Texture, m_Transform);
	}
}
