#include "Camera.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace glcore {

	Camera::Camera(glm::vec3 position, Projection projection):
		m_position(position), m_projection(projection)
	{
	}

	void Camera::Move(glm::vec3 velocity)
	{
		m_position += velocity;
		m_isViewMatrixDirty = true;
	}

	void Camera::Yaw(float offset)
	{
		m_yaw += offset;
		m_isViewMatrixDirty = true;
	}

	void Camera::Pitch(float offset)
	{
		m_pitch += offset;
		m_isViewMatrixDirty = true;
	}

	const glm::mat4 &Camera::GetViewMatrix()
	{
		if (m_isViewMatrixDirty)
		{
			UpdateViewMatrix();
		}

		return m_viewMatrix;
	}

	void Camera::UpdateViewMatrix()
	{
		static glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

		glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		cameraFront.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
		cameraFront.y = sin(glm::radians(m_pitch));
		cameraFront.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
		cameraFront = glm::normalize(cameraFront);

		m_viewMatrix = glm::mat4(1.0f);
		m_viewMatrix = glm::translate(m_viewMatrix, m_position);
		//m_viewMatrix = glm::lookAt(m_position,  cameraFront, cameraUp);
		m_isViewMatrixDirty = false;
	}

	const glm::mat4 &Camera::GetProjectionMatrix()
	{
		if (m_isProjectionMatrixDirty)
		{
			UpdateProjectionMatrix();
		}

		return m_projectionMatrix;
	}

	void Camera::UpdateProjectionMatrix()
	{
		m_projectionMatrix = glm::perspective(glm::radians(m_projection.fov), m_projection.aspect, m_projection.near, m_projection.far);

		m_isProjectionMatrixDirty = false;
	}

}