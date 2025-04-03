#ifndef BUTTON_HPP
#define BUTTON_HPP
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <filesystem>
#include <random>
#include <stdexcept>
#include <map>

namespace button {
class Button {
    public:
        Button(float x, float y, const std::string& type, const std::wstring& text, sf::Font& font);

        virtual void draw(sf::RenderWindow& window);
        virtual bool isClicked(const sf::Vector2f& mousePos) const;
        virtual void update(const sf::Vector2f& mousePos);

    protected:
        sf::Sprite sprite;
        sf::Text label;
        sf::FloatRect clickableArea;
        sf::Texture texture;
        bool hovered = false;

        void configureClickableArea(const std::string& type);
};

class SoundEffectButton : public Button {
    public:
        SoundEffectButton(float x, float y, std::string type, const std::wstring& text, sf::Font& font, const std::string& soundName);
        void play();

    private:
        sf::Music music;
};

class MusicThemeButton : public button::Button {
    public:
        MusicThemeButton(float x, float y, const std::wstring& text, sf::Font& font, const std::string& folder);
        void playOrStop();
        void updateLoop();
    
    private:
        std::string musicFolder;
        std::vector<std::string> playlist;
        sf::Music music;
        bool isPlaying;
    
        void playRandom();
    };
}


#endif
