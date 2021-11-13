#include "AudioSourceComponent.hpp"

namespace cave {
	
	AudioSourceComponent::AudioSourceComponent(float volume, float pitch, bool setLoop = true, caveVec3f pos = caveVec3f(0, 0, 0), caveVec3f vel = caveVec3f(0, 0, 0)) {
		audioSource = AudioSource::AudioSource();
	}

	AudioSourceComponent::play(std::string uniqueName) {
		Source::play(AudioManager::buffers[uniqueName]);
	}
	AudioSourceComponent::setVolume(float volume) {
		audioSource.setVolume(volume);
	}
	AudioSourceComponent::setPitch(float pitch) {
		audioSource.setPitch(pitch);
	}
	AudioSourceComponent::setPosition(caveVec3f pos) {
		audioSource.setPosition(pos);
	}
	AudioSourceComponent::setVelocity(caveVec3f vel) {
		audioSource.setVelocity(vel);
	}
	AudioSourceComponent::setLooping(bool setLoop) {
		audioSource.setLooping(setLoop);
	}
	AudioSourceComponent::isPlaying() {
		return audioSource.isPlaying();
	}
	AudioSourceComponent::isPaused() {
		return audioSource.isPaused();
	}
	AudioSourceComponent::isStopped() {
		return audioSource.isStopped();
	}
	AudioSourceComponent::pause() {
		audioSource.pause();
	}
	AudioSourceComponent::continuePlaying() {
		audioSource.continuePlaying();
	}

}