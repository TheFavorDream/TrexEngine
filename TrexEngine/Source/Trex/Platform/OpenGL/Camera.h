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

	enum CameraMovement {
		CAM_UP, CAM_DOWN, CAM_RIGHT, CAM_LEFT, CAM_FRONT, CAM_BACK
	};

	class Camera
	{
	public:
		TX_API  Camera(Vec3 pPosition, float pFieldOfView);
		TX_API ~Camera();

		TX_API glm::mat4&  GetProjection(float pNearPlane, float pFarPlane, uint32 pWidth, uint32 pHeight);
		TX_API glm::mat4&  GetView();

		TX_API void Move(CameraMovement Movement);
		TX_API void MouseMove(float MouseX, float MouseY);
		TX_API void CalculateCamera();
		
		TX_API inline float& GetYaw() { return m_Yaw; }
		TX_API inline float& GetPitch() { return m_Pitch; }

		TX_API inline glm::vec3& GetFront() { return m_CameraFront; }
		TX_API void SetCameraPosition(Vec3 pPosition);

		TX_API inline glm::vec3 GetCameraPosition() { return m_CameraPosition; }

	private:
		glm::vec3 m_CameraPosition = glm::vec3(0.0f);
		glm::vec3 m_CameraUp = glm::vec3(0.0f);
		glm::vec3 m_CameraFront = glm::vec3(0.0f);
		glm::vec3 m_CameraRight = glm::vec3(0.0f);

		glm::mat4 m_View = glm::mat4(1.0f);
		glm::mat4 m_Projection = glm::mat4(1.0f);

		float m_Yaw = -90.0f;
		float m_Pitch = 0.0f;
		float m_Sensetivity = 0.1f;
		float m_Speed = 0.02f;
		float m_FOV;

	};
};