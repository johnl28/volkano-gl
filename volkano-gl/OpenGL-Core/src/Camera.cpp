#include "Camera.h"
#include "GLFW/glfw3.h"
#include "glm/gtc/matrix_transform.hpp"

namespace glcore {

	Camera::Camera(glm::vec3 position, Projection projection):
		m_Position(position), m_Projection(projection)
	{
		m_CameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
		m_CameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	}

	void Camera::Update(float deltaTime)
	{

	}

	void Camera::SetPosition(const glm::vec3& position)
	{
		m_Position = position;
		m_isViewMatrixDirty = true;
	}

	void Camera::MoveX(float direction)
	{
		m_Position += glm::normalize(glm::cross(m_CameraUp, m_CameraFront)) * direction * m_CameraSpeed;
		m_isViewMatrixDirty = true;
	}

	void Camera::MoveY(float direction)
	{
		m_Position += glm::normalize(glm::cross(m_CameraUp, m_CameraFront)) * direction * m_CameraSpeed;
		m_isViewMatrixDirty = true;
	}

	void Camera::MoveZ(float direction)
	{
		m_Position += m_CameraFront * direction * m_CameraSpeed;
		m_isViewMatrixDirty = true;
	}

	void Camera::Yaw(float offset)
	{
		m_Yaw += offset * m_Sensitivity;
		m_isViewMatrixDirty = true;
	}

	void Camera::Pitch(float offset)
	{
		m_Pitch += offset * m_Sensitivity;

		if (m_Pitch > 89.0f)
		{
			m_Pitch = 89.0f;
		}
		else if (m_Pitch < -89.0f)
		{
			m_Pitch = -89.0f;
		}

		m_isViewMatrixDirty = true;
	}

	void Camera::SetFOV(float fov)
	{
		m_Projection.fov = fov;
		m_isProjectionMatrixDirty = true;
	}

	const glm::mat4 &Camera::GetViewMatrix()
	{
		if (m_isViewMatrixDirty)
		{
			UpdateViewMatrix();
		}

		return m_ViewMatrix;
	}

	void Camera::UpdateViewMatrix()
	{
		glm::vec3 direction;
		direction.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		direction.y = sin(glm::radians(m_Pitch));
		direction.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		m_CameraFront = glm::normalize(direction);

		m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_CameraFront, m_CameraUp);
		m_isViewMatrixDirty = false;
	}

	const glm::mat4 &Camera::GetProjectionMatrix()
	{
		if (m_isProjectionMatrixDirty)
		{
			UpdateProjectionMatrix();
		}

		return m_ProjectionMatrix;
	}

	const glm::vec3& Camera::GetPosition()
	{
		return m_Position;
	}

	void Camera::UpdateProjectionMatrix()
	{
		m_ProjectionMatrix = glm::perspective(glm::radians(m_Projection.fov), m_Projection.aspect, m_Projection.near, m_Projection.far);

		m_isProjectionMatrixDirty = false;
	}

}