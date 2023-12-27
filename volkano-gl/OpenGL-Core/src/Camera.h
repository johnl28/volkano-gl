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

		void Update(float deltaTime);

		// Movement
		void MoveX(float direction);
		void MoveY(float direction);
		void MoveZ(float direction);

		// Rotation 
		void Yaw(float offset);
		void Pitch(float offset);


		// Matrix
		const glm::mat4& GetViewMatrix();
		const glm::mat4& GetProjectionMatrix();
		const glm::vec3& GetPosition();

		bool IsViewMatrixDirty() const { return m_isViewMatrixDirty; }
		bool IsProjectionMatrixDirty() const { return m_isProjectionMatrixDirty; }


	private:
		void UpdateViewMatrix();
		void UpdateProjectionMatrix();

	private:
		float m_Yaw = -90.0f;
		float m_Pitch = 0.0f;
		float m_CameraSpeed = 0.3f;

		glm::vec3 m_CameraUp;
		glm::vec3 m_CameraFront;
		glm::vec3 m_Position;

		Projection m_Projection;

		bool m_isViewMatrixDirty = true;
		bool m_isProjectionMatrixDirty = true;

		glm::mat4 m_ViewMatrix = glm::mat4(1.0f);
		glm::mat4 m_ProjectionMatrix = glm::mat4(1.0f);
	};

}