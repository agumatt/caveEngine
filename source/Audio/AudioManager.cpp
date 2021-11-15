#include "AudioManager.hpp"
#include <iostream>


namespace cave {

	//AudioManager
	std::map<std::string, int> AudioManager::m_buffers;

	void AudioManager::StartUp() {
		m_buffers = {};
	}

	void AudioManager::ShutDown() {

	}
	
	int AudioManager::loadSound(std::string audioFilePath, std::string uniqueName) {
		WavData audioData;
		ALuint buffers[1] = { 0 };
		drwav_int16* sampleData = drwav_open_file_and_read_pcm_frames_s16(audioFilePath.c_str(), &audioData.channels,
			&audioData.sampleRate,
			&audioData.totalPCMFrameCount,
			nullptr);
		if (!sampleData) {
			std::cout<<"Audio Clip Error: Failed to load file "<< audioFilePath;
			drwav_free(sampleData, nullptr);
			m_buffers[uniqueName] = buffers[0];
		}
		else if (audioData.GetTotalSamples() > drwav_uint64(std::numeric_limits<size_t>::max())) {
			std::cout << "Audio Clip Error: File is to big to be loaded. "<< audioFilePath;
			drwav_free(sampleData, nullptr);
			m_buffers[uniqueName] = buffers[0];
		}
		else {
			//Primero se copian todos los datos a un vector de uint16_t, para luego liberar los datos recien copiados.
			std::memcpy(audioData.pcmData.data(), sampleData, audioData.pcmData.size() * 2);
			drwav_free(sampleData, nullptr);

			//Se pasa este vector de uint16_t a OpenAL
			ALuint buffers[1];
			alGenBuffers(1, buffers);
			m_buffers[uniqueName] = buffers[0];
			alBufferData(buffers[0], audioData.channels > 1 ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16, audioData.pcmData.data(), audioData.pcmData.size() * 2, audioData.sampleRate);
		}

		return buffers[0];

	}
	void AudioManager::setListenerData(caveVec3f pos, caveVec3f vel) {
		alListener3f(AL_POSITION, pos.x, pos.y, pos.z);
		alListener3f(AL_VELOCITY, vel.x, vel.y, vel.z);
	}



	AudioSource::AudioSource() {
		alGenSources(1, &m_sourceId);
	}
	void AudioSource::play(int buffer) {
		alSourceStop(m_sourceId);
		alSourcei(m_sourceId, AL_BUFFER, buffer);
		alSourcePlay(m_sourceId);
	}
	void AudioSource::deleteSource() {
		alSourceStop(m_sourceId);
		alDeleteSources(1, &m_sourceId);
	}
	void AudioSource::setVolume(float volume) {
		alSourcef(m_sourceId, AL_GAIN, volume);
	}
	void AudioSource::setPitch(float pitch) {
		alSourcef(m_sourceId, AL_PITCH, pitch);
	}
	void AudioSource::setPosition(caveVec3f pos) {
		alSource3f(m_sourceId, AL_POSITION, pos.x, pos.y, pos.z);
	}
	void AudioSource::setVelocity(caveVec3f vel) {
		alSource3f(m_sourceId, AL_VELOCITY, vel.x, vel.y, vel.z);
	}
	void AudioSource::setLooping(bool setLoop) {
		alSourcei(m_sourceId, AL_LOOPING, setLoop ? AL_TRUE : AL_FALSE);
	}
	bool AudioSource::isPlaying() {
		ALint sourceState;
		alGetSourcei(m_sourceId, AL_SOURCE_STATE, &sourceState);
		return  sourceState == AL_PLAYING;
	}

	bool AudioSource::isPaused() {
		ALint sourceState;
		alGetSourcei(m_sourceId, AL_SOURCE_STATE, &sourceState);
		return  sourceState == AL_PAUSED;
	}
	bool AudioSource::isStopped() {
		ALint sourceState;
		alGetSourcei(m_sourceId, AL_SOURCE_STATE, &sourceState);
		return  sourceState == AL_STOPPED;
	}

	void AudioSource::pause() {
		alSourcePause(m_sourceId);
	}
	void AudioSource::continuePlaying() {
		alSourcePlay(m_sourceId);
	}


}
