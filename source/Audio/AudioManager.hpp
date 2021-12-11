#pragma once
#ifndef AUDIOMANAGER_HPP
#define AUDIOMANAGER_HPP
#include <AL/al.h>
#include <AL/alc.h>
#include "../Rendering/RenderingManager.hpp"
#include "../Utils/LibUtils.hpp"
#include "../Utils/Utils.hpp"
#include <dr_wav.h>
#include "../Core/Log.hpp"
#include "AudioMacros.hpp"
namespace cave {

	/**Esta clase maneja el sistema de sonido del engine.
	* 
	*/
	class AudioManager {
	public:
		static std::map<std::string, ALuint> m_buffers; /**< Mapa que asocia un buffer con su nombre unico */
		static ALCdevice* m_ALdevice;/**< Dispositivo de sonido */
		static ALCcontext* m_ALcontext;/**< Contexto de OpenAL */
		static float m_masterVolume; /**< volumen general */
		static std::string getALError(); /**< Retorna estado de error de OpenAL como string */
		static void StartUp(); /**< Inizializacion de elementos de la clase */
		static void updateListenerData(); /**< Configuracion del listener de OpenAL */
		static ALuint loadSound(std::string audioFilePath, std::string uniqueName); /**< Carga un archivo de audio */
		static void ShutDown(); /**< Cierre de la clase */
		AudioManager();
	};

	/**Esta clase representa una fuente de audio.
	*
	*/
	class AudioSource {

	public:
		ALuint m_sourceId = 1234;/**< Identificador de la fuente de audio */
		void play(ALuint buffer); /**< Reproduce la fuente de audio desde el comienzo*/
		void deleteSource(); /**< Elimina la fuente de audio */
		void setVolume(float volume); /**< Setea el volumen */
		void setPitch(float pitch); /**< Setea el tono */
		void setRadius(float radius); /**< Setea la distancia maxima a la que se escucha */
		void setPosition(caveVec3f pos); /**< Setea la posicion */
		void setVelocity(caveVec3f vel); /**< Setea la velocidad */
		void setLooping(bool setLoop); /**< Setea si la fuente de audio reproduce la pista en loop o no */
		bool isPlaying(); /**< Retorna verdadero si se esta reproduciendo */
		bool isPaused(); /**< Retorna verdadero si esta en pausa */
		bool isStopped();/**< Retorna verdadero si esta detenido */
		void pause(); /**< Pausa la fuente de audio */
		void continuePlaying();/**< Reproduce la fuente de audio desde donde se dejo*/
		std::string getALSourceState(); /**< Retorna estado de reproduccion de la fuente como string */

		AudioSource(float volume, float pitch, float radius, bool setLoop, caveVec3f pos, caveVec3f vel);
		AudioSource();


	};

	/**Contiene la informacion de una pista de audio.
	*
	*/
	struct WavData {
		unsigned int channels = 0;
		unsigned int sampleRate = 0;
		drwav_uint64 totalPCMFrameCount = 0;
		std::vector<uint16_t> pcmData;
		drwav_uint64 GetTotalSamples() const { return totalPCMFrameCount * channels; }
	};

}

#endif