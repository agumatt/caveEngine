#pragma once
#ifndef CAMERACOMPONENT_HPP
#define CAMERACOMPONENT_HPP
#include "RenderingManager.hpp"

namespace cave {

	struct CameraComponent {
		caveVec3f m_position;
		caveVec3f m_lookAt;
		float m_nearClipDistance;
		float m_farClipDistance;

		CameraComponent(caveVec3f position, caveVec3f lookAt, float nearClipDistance = 1.0f, float farClipDistance = 10000.0f);

		void configureCamera(caveVec3f position, caveVec3f lookAt, float nearClipDistance = 1.0f, float farClipDistance = 10000.0f);


	};


}

#endif