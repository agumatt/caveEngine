#pragma once
#ifndef CAMERACOMPONENT_HPP
#define CAMERACOMPONENT_HPP
#include "RenderingManager.hpp"

namespace cave {

	struct CameraComponent {
		caveVec3f m_position; /**< Posicion de la camara */
		caveVec3f m_lookAt; /**< Direccion a la que apunta la camara */
		float m_nearClipDistance; /**< Distancia de visibilidad minima */
		float m_farClipDistance; /**< Distancia de visibilidad maxima */

		CameraComponent(caveVec3f position, caveVec3f lookAt, float nearClipDistance = 1.0f, float farClipDistance = 10000.0f);

		void configureCamera(caveVec3f position, caveVec3f lookAt, float nearClipDistance = 1.0f, float farClipDistance = 10000.0f);


	};


}

#endif