#include "CameraComponent.hpp"

namespace cave {

	caveVec3f m_position;
	caveVec3f m_lookAt;
	float m_nearClipDistance;
	float m_farClipDistance;

	CameraComponent::CameraComponent(caveVec3f position, caveVec3f lookAt, float nearClipDistance, float farClipDistance) {
		m_position = position;
		m_lookAt = lookAt;
		m_nearClipDistance = nearClipDistance;
		m_farClipDistance = farClipDistance;
		RenderingManager::configureCamera(position, lookAt, nearClipDistance, farClipDistance);

	}


	void CameraComponent::configureCamera(caveVec3f position, caveVec3f lookAt, float nearClipDistance, float farClipDistance) {
		m_position = position;
		m_lookAt = lookAt;
		m_nearClipDistance = nearClipDistance;
		m_farClipDistance = farClipDistance;
		RenderingManager::configureCamera(position, lookAt, nearClipDistance, farClipDistance);
	}

}


