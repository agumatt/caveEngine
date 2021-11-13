#include "AudioSourceComponent.hpp"

namespace cave {
	
	AudioSourceComponent::AudioSourceComponent(float volume, float pitch, bool setLoop = true, caveVec3f pos = caveVec3f(0, 0, 0), caveVec3f vel = caveVec3f(0, 0, 0)) {
		m_audioSource = AudioSource::AudioSource();
	}

	AudioSourceComponent::play(std::string uniqueName) {
		m_audioSource::play(AudioManager::m_buffers[uniqueName]);
	}
	AudioSourceComponent::setVolume(float volume) {
		m_audioSource.setVolume(volume);
	}
	AudioSourceComponent::setPitch(float pitch) {
		m_audioSource.setPitch(pitch);
	}
	AudioSourceComponent::setPosition(caveVec3f pos) {
		m_audioSource.setPosition(pos);
	}
	AudioSourceComponent::setVelocity(caveVec3f vel) {
		m_audioSource.setVelocity(vel);
	}
	AudioSourceComponent::setLooping(bool setLoop) {
		m_audioSource.setLooping(setLoop);
	}
	AudioSourceComponent::isPlaying() {
		return m_audioSource.isPlaying();
	}
	AudioSourceComponent::isPaused() {
		return m_audioSource.isPaused();
	}
	AudioSourceComponent::isStopped() {
		return m_audioSource.isStopped();
	}
	AudioSourceComponent::pause() {
		m_audioSource.pause();
	}
	AudioSourceComponent::continuePlaying() {
		m_audioSource.continuePlaying();
	}

}