#pragma once
#ifndef AUDIOMANAGER_HPP
#define AUDIOMANAGER_HPP
#define STRING(s) #s
#include <AL/al.h>
#include <AL/alc.h>
#include <map>
#include <string>
#include <iostream>
#include <vector>
#include "../Utils/Utils.hpp"
#include <dr_wav.h>
namespace cave {

	class AudioManager {
	public:
		static std::map<std::string, ALuint> m_buffers;
		static ALCdevice* m_ALdevice;
		static ALCcontext* m_ALcontext;
		static float m_masterVolume;
		static std::string getALError();
		static void StartUp();
		static void setListenerData(caveVec3f pos, caveVec3f vel = caveVec3f(0,0,0));
		static ALuint loadSound(std::string audioFilePath, std::string uniqueName);
		static void ShutDown();
		AudioManager();
	};


	class AudioSource {

	private:
		ALuint m_sourceId = 1234;

	public:
		void play(ALuint buffer);
		void deleteSource();
		void setVolume(float volume);
		void setPitch(float pitch);
		void setPosition(caveVec3f pos);
		void setVelocity(caveVec3f vel);
		void setLooping(bool setLoop);
		bool isPlaying();
		bool isPaused();
		bool isStopped();
		void pause();
		void continuePlaying();
		std::string getALSourceState();

		AudioSource(float volume, float pitch, bool setLoop, caveVec3f pos, caveVec3f vel);
		AudioSource();


	};

	struct WavData {
		unsigned int channels = 0;
		unsigned int sampleRate = 0;
		drwav_uint64 totalPCMFrameCount = 0;
		std::vector<uint16_t> pcmData;
		drwav_uint64 GetTotalSamples() const { return totalPCMFrameCount * channels; }
	};

}

#endif