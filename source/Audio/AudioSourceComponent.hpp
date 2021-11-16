#pragma once
#ifndef AUDIOSOURCECOMPONENT_HPP
#define AUDIOSOURCECOMPONENT_HPP
#include "AudioManager.hpp"


namespace cave {

	/**Componente que representa una fuente de audio. Permite reproducir pistas de sonido asociadas a un buffer.
	*
	*/
	struct AudioSourceComponent {

		AudioSource m_audioSource; /**< Fuente de sonido asociada al componente*/

		AudioSourceComponent(float volume, float pitch, bool setLoop=true, caveVec3f pos=caveVec3f(0,0,0), caveVec3f vel=caveVec3f(0,0,0));

		void play(std::string uniqueName); /**< Reproduce la fuente de audio asociada a un nombre desde el comienzo*/
		void setVolume(float volume); /**< Setea el volumen*/
		void setPitch(float pitch);/**< Setea el tono */
		void setPosition(caveVec3f pos);/**< Setea la posicion */
		void setVelocity(caveVec3f vel);/**< Setea la velocidad */
		void setLooping(bool setLoop); /**< Setea si la fuente de audio reproduce la pista en loop o no */
		bool isPlaying(); /**< Retorna verdadero si se esta reproduciendo */
		bool isPaused(); /**< Retorna verdadero si esta en pausa */
		bool isStopped();/**< Retorna verdadero si esta detenido */
		void pause();/**< Pausa la fuente de audio */
		void continuePlaying();/**< Reproduce la fuente de audio desde donde se dejo*/
	};




}

#endif