#pragma once
#ifndef AUDIOSOURCECOMPONENT_HPP
#define AUDIOSOURCECOMPONENT_HPP
#include "AudioManager.hpp"


namespace cave {

	enum class AudioSourceState {
		Stopped,
		Playing,
		Paused
	};

	struct AudioSourceComponent {

		AudioSource m_audioSource;

		AudioSourceComponent(float volume, float pitch, bool setLoop=true, caveVec3f pos=caveVec3f(0,0,0), caveVec3f vel=caveVec3f(0,0,0));
		~AudioSourceComponent();

		void play(std::string fileName);
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

	};




}