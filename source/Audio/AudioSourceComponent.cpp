#include "AudioSourceComponent.hpp"
#include <iostream>

namespace cave {
	
	AudioSourceComponent::AudioSourceComponent(float volume, float pitch, bool setLoop, caveVec3f pos , caveVec3f vel) {
		m_audioSource = AudioSource::AudioSource(volume, pitch, setLoop, pos, vel);
	}

	void AudioSourceComponent::play(std::string uniqueName) {
		std::cout << "ABOUT TO PLAY: " << AudioManager::m_buffers[uniqueName];
		m_audioSource.play(AudioManager::m_buffers[uniqueName]);
	}
	void AudioSourceComponent::setVolume(float volume) {
		m_audioSource.setVolume(volume);
	}
	void AudioSourceComponent::setPitch(float pitch) {
		m_audioSource.setPitch(pitch);
	}
	void AudioSourceComponent::setPosition(caveVec3f pos) {
		m_audioSource.setPosition(pos);
	}
	void AudioSourceComponent::setVelocity(caveVec3f vel) {
		m_audioSource.setVelocity(vel);
	}
	void AudioSourceComponent::setLooping(bool setLoop) {
		m_audioSource.setLooping(setLoop);
	}
	bool AudioSourceComponent::isPlaying() {
		return m_audioSource.isPlaying();
	}
	bool AudioSourceComponent::isPaused() {
		return m_audioSource.isPaused();
	}
	bool AudioSourceComponent::isStopped() {
		return m_audioSource.isStopped();
	}
	void AudioSourceComponent::pause() {
		m_audioSource.pause();
	}
	void AudioSourceComponent::continuePlaying() {
		m_audioSource.continuePlaying();
	}

}