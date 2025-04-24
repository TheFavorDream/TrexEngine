
#include "Camera.h"

namespace TrexEngine
{
	Camera::Camera(Vec3 pPosition, float pFieldOfView)
		: m_FOV(pFieldOfView)
	{
		Logger::CoreLogger->SetInfo("Camera Created");
		m_CameraPosition = glm::vec3(pPosition.x, pPosition.y, pPosition.z);
	}

	Camera::~Camera()
	{
		Logger::CoreLogger->SetInfo("Camera Destroyed");
	}

	void Camera::Matrix(float pNearPlane, float pFarPlane, uint32 pWidth, uint32 pHeight, const Shader *pCurrentShader)
	{
		glm::mat4 ViewMat = glm::mat4(1.0f);

		ViewMat = glm::lookAt(m_CameraPosition, m_CameraPosition+m_CameraOriantation, m_Up);
		m_ProjectionMatrix = glm::perspective(glm::radians(m_FOV), float(pWidth / pHeight), pNearPlane, pFarPlane);

		pCurrentShader->SetUniformMat4("View", (ViewMat));
		pCurrentShader->SetUniformMat4("Projection", (m_ProjectionMatrix));

	}
	TX_API void Camera::SetCameraPosition(Vec3 pPosition)
	{
		m_CameraPosition.x = pPosition.x;
		m_CameraPosition.y = pPosition.y;
		m_CameraPosition.z = pPosition.z;

	}
};