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

        void draw(sf::RenderWindow& window);
        bool isClicked(const sf::Vector2f& mousePos) const;
        void update(const sf::Vector2f& mousePos);

    private:
        sf::Sprite sprite;
        sf::Text label;
        sf::FloatRect clickableArea;
        sf::Texture texture;
        bool hovered = false;

        void configureClickableArea(const std::string& type);
};

}


#endif
