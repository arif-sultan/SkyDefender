#ifndef AUDIOMANAGER_HPP
#define AUDIOMANAGER_HPP

#include <SFML/Audio.hpp>

// Handles optional background music and a firing sound.
class AudioManager
{
private:
    sf::Music backgroundMusic;
    sf::SoundBuffer shootBuffer;
    sf::Sound shootSound;
    bool shootSoundLoaded;

public:
    AudioManager();

    void playMusic(const std::string& fileName);
    void playShootSound(const std::string& fileName);
    void playShoot();
};

#endif
