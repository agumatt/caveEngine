#include "AudioManager.hpp"
#include <dr_wav.h>


namespace cave {
	AudioManager::loadSound(std::string fileName) {
		int buffer = alGenBuffers();
		buffers.push_back(buffer);
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
	AudioManager::setListenerData(float x, float y, float z) {

	}



	Source::Source() {
		sourceId = alGenSources();
	}
	Source::play(int buffer) {
		stop();
		alSourcei(sourceId, AL_BUFFER, buffer);
		alSourcePlay(sourceId);
	}
	Source::deleteSource() {
		stop();
		alDeleteSources(1, &sourceId);
	}
	Source::setVolume(float volume) {
		alSourcef(sourceId, AL_GAIN, volume);
	}
	Source::setPitch(float pitch) {
		alSourcef(sourceId, AL_PITCH, pitch);
	}
	Source::setPosition(float x, float y, float z) {
		alSource3f(sourceId, AL_POSITION, x, y, z);
	}
	Source::setVelocity(float x, float y, float z) {
		alSource3f(sourceId, AL_VELOCITY, x, y, z);
	}
	Source::setLooping(bool setLoop) {
		alSourcei(sourceId, AL_LOOPING, setLoop ? AL_TRUE : AL_FALSE);
	}
	Source::isPlaying() {
		return alGetSourcei(sourceId, AL_SOURCE_STATE) == AL_PLAYING;
	}
	Source::pause() {
		alSourcePause(sourceId);
	}
	Source::continuePlaying() {
		alSourcePlay(sourceId);
	}


}
