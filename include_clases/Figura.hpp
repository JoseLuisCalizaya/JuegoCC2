// Figura.hpp
#ifndef FIGURA_HPP
#define FIGURA_HPP

#include <SFML/Graphics.hpp>

class Jugador;

class Figura {
public:
    virtual ~Figura() = default;
    virtual void update(sf::RenderWindow &window, Jugador &jugador) = 0;
    virtual void draw(sf::RenderWindow &window) = 0;
    virtual sf::FloatRect get_bounds() = 0;
    virtual void event(Jugador &jugador) = 0;
    virtual void move(float x, float y) = 0;

protected:
    sf::RectangleShape rect;
    sf::Texture textura;
};

#endif // FIGURA_HPP
