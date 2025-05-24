
#include "Camera.h"

namespace TrexEngine
{
	Camera::Camera(Vec3 pPosition, float pFieldOfView)
		: m_FOV(pFieldOfView)
	{
		Logger::CoreLogger->SetInfo("Camera Created");

		m_CameraPosition = glm::vec3(pPosition.x, pPosition.y, pPosition.z);
		CalculateCamera();
	}

	Camera::~Camera()
	{
		Logger::CoreLogger->SetInfo("Camera Destroyed");
	}

	glm::mat4& Camera::GetProjection(float pNearPlane, float pFarPlane, uint32 pWidth, uint32 pHeight)
	{
		if (pHeight == 0)
			return glm::mat4(1.0f);
		m_Projection = glm::perspective(glm::radians(m_FOV), (float(pWidth) / float(pHeight)), pNearPlane, pFarPlane);
		return m_Projection;
	}

	glm::mat4 & Camera::GetView()
	{
		m_View = glm::lookAt(m_CameraPosition, m_CameraPosition + m_CameraFront, m_CameraUp);
		return m_View;
	}



	void Camera::Move(CameraMovement Movement)
	{
		float Volecity = m_Speed * Timer::GetDeltaTime();

		switch (Movement)
		{
		case CAM_FRONT:
			m_CameraPosition += m_CameraFront * Volecity;
			break;
		case CAM_BACK:
			m_CameraPosition -= m_CameraFront * Volecity;
			break;
		case CAM_LEFT:
			m_CameraPosition -= m_CameraRight * Volecity;
			break;
		case CAM_RIGHT:
			m_CameraPosition += m_CameraRight * Volecity;
			break;
		case CAM_UP:
			m_CameraPosition += m_CameraUp * Volecity;
			break;
		case CAM_DOWN:
			m_CameraPosition -= m_CameraUp * Volecity;
		}

	}

	TX_API void Camera::MouseMove(float MouseX, float MouseY)
	{
		MouseX *= m_Sensetivity;
		MouseY *= m_Sensetivity;

		m_Yaw += MouseX;
		m_Pitch += MouseY;

		// make sure that when pitch is out of bounds, screen doesn't get flipped
		
		if (m_Pitch > 89.0f)
			m_Pitch = 89.0f;
		if (m_Pitch < -89.0f)
			m_Pitch = -89.0f;
		

		// update Front, Right and Up Vectors using the updated Euler angles
		CalculateCamera();
	}

	TX_API void Camera::SetCameraPosition(Vec3 pPosition)
	{
		m_CameraPosition.x = pPosition.x;
		m_CameraPosition.y = pPosition.y;
		m_CameraPosition.z = pPosition.z;

	}
	void Camera::CalculateCamera()
	{
		glm::vec3 front;
		front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		front.y = sin(glm::radians(m_Pitch));
		front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));

		m_CameraFront = glm::normalize(front);
		m_CameraRight = glm::normalize(glm::cross(m_CameraFront, glm::vec3(0.0f, 1.0f, 0.0)));
		m_CameraUp = glm::normalize(glm::cross(m_CameraRight, m_CameraFront));
	}
};