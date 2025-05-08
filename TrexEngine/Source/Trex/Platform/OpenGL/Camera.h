#pragma once


/*
	Created by: The Voltage 
	On: 2025/4/24

	Purpose:
	
	A Camera system for TrexEngine that supports both perspective and Orthographic Cameras.

*/

#define GLM_ENABLE_EXPERIMENTAL

#include "../../Core/Core.h"
#include "Shader.h" 

#include "../../3rdparty/glm/gtc/type_ptr.hpp"
#include "../../3rdparty/glm/gtx/rotate_vector.hpp"
#include "../../3rdparty/glm/gtx/vector_angle.hpp"

namespace TrexEngine
{

	struct Vec3
	{
		float x, y, z;
	};

	class Camera
	{
	public:
		TX_API  Camera(Vec3 pPosition, float pFieldOfView);
		TX_API ~Camera();

		TX_API void Matrix(float pNearPlane, float pFarPlane, uint32 pWidth, uint32 pHeight, const Shader* pCurrentShader, glm::vec3 Translation);


		TX_API void MoveUp();
		TX_API void MoveDown();
		TX_API void MoveLeft();
		TX_API void MoveRight();
		TX_API void MoveFront();
		TX_API void MoveBack();



		TX_API void SetCameraPosition(Vec3 pPosition);
		TX_API inline glm::vec3& GetCameraPosition() { return m_CameraPosition; }
		TX_API inline glm::vec3& GetOriantation() { return m_CameraOriantation; }
		TX_API inline glm::vec3& GetUP() { return m_Up; }
		TX_API inline glm::mat4& GetProjection() { return m_ProjectionMatrix; }
		TX_API inline glm::mat4& GetView() { return ViewMat; }


	private:
		glm::vec3 m_CameraPosition;
		glm::vec3 m_CameraOriantation = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 m_Up = glm::vec3(0.0f, 1.0f, 0.0f);

		glm::mat4 ViewMat = glm::mat4(1.0f);
		glm::mat4 m_ProjectionMatrix = glm::mat4(1.0f);

		float m_Sensetivity = 200.0f;
		float m_Speed = 0.02f;
		float m_FOV;
		
	};
};