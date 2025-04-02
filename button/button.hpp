#ifndef BUTTON_HPP
#define BUTTON_HPP
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
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
}


#endif
