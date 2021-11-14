#include "AudioManager.hpp"
#include <dr_wav.h>


namespace cave {

	AudioManager::AudioManager() {

	}

	AudioManager::StartUp() {

	}

	AudioManager::ShutDown() {

	}

	AudioManager::loadSound(std::string fileName, std::string uniqueName) {
		int buffer = alGenBuffers();
		m_buffers[uniqueName] = buffer;
		drwav audioFile;
		if (!drwav_init_file(&audioFile, fileName, NULL)) {
			return -1;
		}
		int32_t* pSampleData = (int32_t*)malloc((size_t)audioFile.totalPCMFrameCount * audioFile.channels * sizeof(int32_t));
		drwav_read_pcm_frames_s32(&audioFile, audioFile.totalPCMFrameCount, pSampleData);
		// At this point pSampleData contains every decoded sample as signed 32-bit PCM.

		drwav_uninit(&audioFile);
		alBufferData(buffer, audioFile.channels > 1 ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16, audioFile.pcmData.data(), audioFile.pcmData.size() * 2, audioFile.sampleRate);
		delete audioFile;
		return buffer;

	}
	AudioManager::setListenerData(caveVec3f pos, caveVec3f vel) {
		alListener3f(AL_POSITION, pos.x, pos.y, pos.z);
		alListener3f(AL_VELOCITY, vel.x, vel.y, vel.z);
	}



	AudioSource::AudioSource() {
		m_sourceId = alGenSources();
	}
	AudioSource::play(int buffer) {
		alSourceStop(m_sourceId);
		alSourcei(m_sourceId, AL_BUFFER, buffer);
		alSourcePlay(m_sourceId);
	}
	AudioSource::deleteSource() {
		alSourceStop(m_sourceId);
		alDeleteSources(1, &m_sourceId);
	}
	AudioSource::setVolume(float volume) {
		alSourcef(m_sourceId, AL_GAIN, volume);
	}
	AudioSource::setPitch(float pitch) {
		alSourcef(m_sourceId, AL_PITCH, pitch);
	}
	AudioSource::setPosition(caveVec3f pos) {
		alSource3f(m_sourceId, AL_POSITION, pos.x, pos.y, pos.z);
	}
	AudioSource::setVelocity(caveVec3f vel) {
		alSource3f(m_sourceId, AL_VELOCITY, vel.x, vel.y, vel.z);
	}
	AudioSource::setLooping(bool setLoop) {
		alSourcei(m_sourceId, AL_LOOPING, setLoop ? AL_TRUE : AL_FALSE);
	}
	AudioSource::isPlaying() {
		return alGetSourcei(m_sourceId, AL_SOURCE_STATE) == AL_PLAYING;
	}

	AudioSource::isPaused() {
		return alGetSourcei(m_sourceId, AL_SOURCE_STATE) == AL_PAUSED;
	}
	AudioSource::isStopped() {
		return alGetSourcei(m_sourceId, AL_SOURCE_STATE) == AL_STOPPED;
	}

	AudioSource::pause() {
		alSourcePause(m_sourceId);
	}
	AudioSource::continuePlaying() {
		alSourcePlay(m_sourceId);
	}


}