#pragma once
#include "glm/glm.hpp"


namespace glcore {

	enum ProjectionType
	{
		PERSPECTIVE_PROJECTION,
		ORTHOGRAPHIC_PROJECTION
	};

	struct Projection
	{
		ProjectionType type;
		float fov;
		float aspect;
		float near;
		float far;
	};

	class Camera
	{
	public:
		Camera(glm::vec3 position, Projection projection);

		void Move(glm::vec3 velocity);
		void Yaw(float offset);
		void Pitch(float offset);

		const glm::mat4 &GetViewMatrix();
		const glm::mat4 &GetProjectionMatrix();

		bool IsViewMatrixDirty() const { return m_isViewMatrixDirty; }
		bool IsProjectionMatrixDirty() const { return m_isProjectionMatrixDirty; }


	private:
		void UpdateViewMatrix();
		void UpdateProjectionMatrix();

	private:
		glm::vec3 m_position;
		float m_yaw = 0.0f;
		float m_pitch = -90.0f;

		Projection m_projection;

		bool m_isViewMatrixDirty = true;
		bool m_isProjectionMatrixDirty = true;

		glm::mat4 m_viewMatrix = glm::mat4(1.0f);
		glm::mat4 m_projectionMatrix = glm::mat4(1.0f);
	};

}