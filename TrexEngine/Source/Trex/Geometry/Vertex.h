#pragma once

#include "../3rdparty/glm/vec3.hpp"
#include "../3rdparty/glm/vec2.hpp"

namespace TrexEngine
{
	struct Vertex
	{
		glm::vec3 Position;
		glm::vec3 Normals;
		glm::vec2 TextureCoordinates;
	};
};