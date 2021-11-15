#include "AudioManager.hpp"
#include <dr_wav.h>


namespace cave {

	//AudioManager
	std::map<std::string, int> AudioManager::m_buffers;

	void AudioManager::StartUp() {
		m_buffers = {};
	}

	void AudioManager::ShutDown() {

	}
	
	int AudioManager::loadSound(std::string fileName, std::string uniqueName) {
		ALuint buffers[1];
		alGenBuffers(1, buffers);
		m_buffers[uniqueName] = buffers[0];
		//drwav audioFile;
		//if (!drwav_init_file(&audioFile, fileName.c_str(), NULL)) {
		//	return -1;
		//}
		//int32_t* pSampleData = (int32_t*)malloc((size_t)audioFile.totalPCMFrameCount * audioFile.channels * sizeof(int32_t));
		//drwav_read_pcm_frames_s32(&audioFile, audioFile.totalPCMFrameCount, pSampleData);
		// At this point pSampleData contains every decoded sample as signed 32-bit PCM.

		//drwav_uninit(&audioFile);
		//alBufferData(buffers[0], audioFile.channels > 1 ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16, audioFile.pcmData.data(), audioFile.pcmData.size() * 2, audioFile.sampleRate);
		return buffers[1];

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
