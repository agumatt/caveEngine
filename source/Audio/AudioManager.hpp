#pragma once
#ifndef AUDIOMANAGER_HPP
#define AUDIOMANAGER_HPP
#include <AL/al.h>
#include <AL/alc.h>
#include <vector>
namespace cave {

	class AudioManager {

	private:
		static std::vector<int> buffers = {};

	public:
		static void StartUp();
		static void setListenerData(float x, float y, float z);
		static int loadSound(std::string fileName);
		void ShutDown();
		AudioManager();
		~AudioManager();

	};


	class Source {

	private:
		ALuint sourceId;

	public:
		void play(int buffer);
		void deleteSource();
		void setVolume(float volume);
		void setPitch(float pitch);
		void setPosition(float x, float y, float z);
		void setVelocity(float x, float y, float z);
		void setLooping(bool setLoop);
		bool isPlaying();
		void pause();
		void continuePlaying();

		Source();
		~Source();


	};

}