#pragma once
#ifndef AUDIOMANAGER_HPP
#define AUDIOMANAGER_HPP
#include <AL/al.h>
#include <AL/alc.h>
#include <map>
#include <string>
#include <vector>
#include "../Utils/Utils.hpp"
namespace cave {

	class AudioManager {
	public:
		static std::map<std::string, int> m_buffers;
		static void StartUp();
		static void setListenerData(caveVec3f pos, caveVec3f vel = caveVec3f(0,0,0));
		static int loadSound(std::string fileName, std::string uniqueName);
		static void ShutDown();
		AudioManager();
	};


	class AudioSource {

	private:
		ALuint m_sourceId;

	public:
		void play(int buffer);
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

		AudioSource();
		~AudioSource();


	};

	struct WavData {
		//unsigned int channels = 0;
		//unsigned int sampleRate = 0;
		//drwav_uint64 totalPCMFrameCount = 0;
		//std::vector<uint16_t> pcmData;
		//drwav_uint64 GetTotalSamples() const { return totalPCMFrameCount * channels; }
	};

}

#endif