#include "AudioManager.hpp"

namespace cave {

	//AudioManager
	std::map<std::string, ALuint> AudioManager::m_buffers;
	ALCdevice* AudioManager::m_ALdevice;
	ALCcontext* AudioManager::m_ALcontext;
	float AudioManager::m_masterVolume;

	std::string AudioSource::getALSourceState() {
		ALenum sourceState = 999;
		alGetSourcei(m_sourceId, AL_SOURCE_STATE, &sourceState);
		if (sourceState == AL_INITIAL) {
			return "AL_INITIAL";
		}
		else if (sourceState == AL_STOPPED) {
			return "AL_STOPPED";
		}
		else if (sourceState == AL_PAUSED) {
			return "AL_PAUSED";
		}
		else if (sourceState == AL_PLAYING) {
			return "AL_PLAYING";
		}
		return "UNDEFINED_STATE";
	}

	std::string AudioManager::getALError() {
		ALenum error = alGetError();
		if (error == AL_INVALID_OPERATION) {
			return "AL_INVALID_OPERATION";
		}
		else if (error == AL_NO_ERROR) {
			return "AL_NO_ERROR";
		}
		else if (error == AL_INVALID_NAME) {
			return "AL_INVALID_NAME";
		}
		else if (error == AL_INVALID_ENUM) {
			return "AL_INVALID_ENUM";
		}
		else if (error == AL_INVALID_VALUE) {
			return "AL_INVALID_VALUE";
		}
		else if (error == AL_OUT_OF_MEMORY) {
			return "AL_OUT_OF_MEMORY";
		}
		return "UNDEFINED_ERROR";
	}

	void AudioManager::StartUp() {
		//Opening default device
		m_ALdevice = alcOpenDevice(nullptr);
		if (!m_ALdevice) {
			std::cout << "OPENAL COULDN'T OPEN DEVICE";
		}
		m_ALcontext = alcCreateContext(m_ALdevice, nullptr);
		if (!alcMakeContextCurrent(m_ALcontext)) {
			std::cout << "OPENAL FAILED TO MAKE CONTEXT CURRENT.";
		}
		//alDistanceModel(AL_LINEAR_DISTANCE_CLAMPED);
		m_masterVolume = 1.0f;
		ALCALL(alListenerf(AL_GAIN, m_masterVolume));
		caveVec3f lisPos = RenderingManager::getPlayerPosition();
		ALCALL(alListener3f(AL_POSITION, lisPos.x, lisPos.y, lisPos.z));
		ALCALL(alListener3f(AL_VELOCITY, 0, 0, 0));
		m_buffers = {};
	}

	void AudioManager::ShutDown() {

	}

	

	ALuint AudioManager::loadSound(std::string audioFilePath, std::string uniqueName) {
		WavData audioData;
		ALuint buffer = 0;
		drwav_int16* sampleData = drwav_open_file_and_read_pcm_frames_s16(audioFilePath.c_str(), &audioData.channels,
			&audioData.sampleRate,
			&audioData.totalPCMFrameCount,
			nullptr);
		if (!sampleData) {
			std::cout<<"Audio Clip Error: Failed to load file "<< audioFilePath;
			drwav_free(sampleData, nullptr);
			m_buffers[uniqueName] = buffer;
		}
		else if (audioData.GetTotalSamples() > drwav_uint64(std::numeric_limits<size_t>::max())) {
			std::cout << "Audio Clip Error: File is to big to be loaded. "<< audioFilePath;
			drwav_free(sampleData, nullptr);
			m_buffers[uniqueName] = buffer;
		}
		else {
			//Si la carga usando dr_wav fue exitosa se comienza el transpaso de estos datos a OpenAL.
			audioData.pcmData.resize(size_t(audioData.GetTotalSamples()));

			//Primero se copian todos los datos a un vector de uint16_t, para luego liberar los datos recien copiados.
			std::memcpy(audioData.pcmData.data(), sampleData, audioData.pcmData.size() * 2);
			drwav_free(sampleData, nullptr);

			//Se pasa este vector de uint16_t a OpenAL
			ALCALL(alGenBuffers(1, &buffer));
			m_buffers[uniqueName] = buffer;
			ALCALL(alBufferData(buffer, audioData.channels > 1 ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16, audioData.pcmData.data(), audioData.pcmData.size() * 2, audioData.sampleRate));
			std::cout << "LOADED FILE:  " << audioFilePath << " WITH CHANNELS: "<< audioData.channels <<"TO BUFFER: " << buffer<<std::endl;
		}

		return buffer;

	}
	void AudioManager::updateListenerData() {
		caveVec3f pos = RenderingManager::getPlayerPosition();
		ALCALL(alListener3f(AL_POSITION, pos.x, pos.y, pos.z));
		//alListener3f(AL_VELOCITY, vel.x, vel.y, vel.z);
	}


	//AudioSource
	AudioSource::AudioSource(float volume, float pitch, float radius, bool setLoop, caveVec3f pos, caveVec3f vel) {
		ALCALL(alGenSources(1, &m_sourceId));
		ALCALL(alSourcef(m_sourceId, AL_GAIN, volume));
		ALCALL(alSourcef(m_sourceId, AL_PITCH, pitch));
		ALCALL(alSourcef(m_sourceId, AL_MAX_DISTANCE, radius));
		ALCALL(alSourcei(m_sourceId, AL_LOOPING, setLoop ? AL_TRUE : AL_FALSE));
		ALCALL(alSource3f(m_sourceId, AL_POSITION, pos.x, pos.y, pos.z));
		ALCALL(alSource3f(m_sourceId, AL_VELOCITY, vel.x, vel.y, vel.z));
	}
	AudioSource::AudioSource() {

	}
	void AudioSource::play(ALuint buffer) {
		ALCALL(alSourceStop(m_sourceId));
		ALCALL(alSourcei(m_sourceId, AL_BUFFER, buffer));
		ALCALL(alSourcePlay(m_sourceId));
	}
	void AudioSource::deleteSource() {
		ALCALL(alSourceStop(m_sourceId));
		ALCALL(alDeleteSources(1, &m_sourceId));
	}
	void AudioSource::setVolume(float volume) {
		ALCALL(alSourcef(m_sourceId, AL_GAIN, volume));
	}
	void AudioSource::setPitch(float pitch) {
		ALCALL(alSourcef(m_sourceId, AL_PITCH, pitch));
	}
	void AudioSource::setRadius(float radius) {
		ALCALL(alSourcef(m_sourceId, AL_MAX_DISTANCE, radius));
	}
	void AudioSource::setPosition(caveVec3f pos) {
		ALCALL(alSource3f(m_sourceId, AL_POSITION, pos.x, pos.y, pos.z));
	}
	void AudioSource::setVelocity(caveVec3f vel) {
		ALCALL(alSource3f(m_sourceId, AL_VELOCITY, vel.x, vel.y, vel.z));
	}
	void AudioSource::setLooping(bool setLoop) {
		ALCALL(alSourcei(m_sourceId, AL_LOOPING, setLoop ? AL_TRUE : AL_FALSE));
	}
	bool AudioSource::isPlaying() {
		ALint sourceState = 0;
		ALCALL(alGetSourcei(m_sourceId, AL_SOURCE_STATE, &sourceState));
		return  sourceState == AL_PLAYING;
	}

	bool AudioSource::isPaused() {
		ALint sourceState;
		ALCALL(alGetSourcei(m_sourceId, AL_SOURCE_STATE, &sourceState));
		return  sourceState == AL_PAUSED;
	}
	bool AudioSource::isStopped() {
		ALint sourceState;
		ALCALL(alGetSourcei(m_sourceId, AL_SOURCE_STATE, &sourceState));
		return  sourceState == AL_STOPPED;
	}

	void AudioSource::pause() {
		ALCALL(alSourcePause(m_sourceId));
	}
	void AudioSource::continuePlaying() {
		ALCALL(alSourcePlay(m_sourceId));
	}


}
