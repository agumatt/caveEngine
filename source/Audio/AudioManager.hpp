#pragma once
#ifndef AUDIOMANAGER_HPP
#define AUDIOMANAGER_HPP
#include <AL/al.h>
#include <AL/alc.h>
#include <map>
#include <string>
#include "../Utils/Utils.hpp"
namespace cave {

	class AudioManager {

	private:
		static std::map<std::string, int> buffers = {};

	public:
		static void StartUp();
		static void setListenerData(caveVec3f pos, caveVec3f vel = caveVec3f(0,0,0));
		static int loadSound(std::string fileName, std::string uniqueName);
		static void ShutDown();
		AudioManager();
		~AudioManager();

	};


	class AudioSource {

	private:
		ALuint sourceId;

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

}