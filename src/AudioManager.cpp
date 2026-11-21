#include "../include/AudioManager.hpp"

// sf::Sound requires a SoundBuffer at construction
AudioManager::AudioManager() : shootSound(shootBuffer), shootSoundLoaded(false)
{
}

void AudioManager::playMusic(const std::string& fileName)
{
    // Missing audio files are allowed; the game continues without music.
    if (backgroundMusic.openFromFile(fileName))
    {
        
        backgroundMusic.setLooping(true);
        backgroundMusic.setVolume(25.0f);
        backgroundMusic.play();
    }
}

void AudioManager::playShootSound(const std::string& fileName)
{
    shootSoundLoaded = shootBuffer.loadFromFile(fileName);

    if (shootSoundLoaded)
    {
        shootSound.setBuffer(shootBuffer);
        shootSound.setVolume(35.0f);
    }
}

void AudioManager::playShoot()
{
    if (shootSoundLoaded)
        shootSound.play();
}