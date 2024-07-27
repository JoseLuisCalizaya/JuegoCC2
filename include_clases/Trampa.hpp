// Trampa.hpp
#ifndef TRAMPA_HPP
#define TRAMPA_HPP

#include "Figura.hpp"

class Trampa : public Figura {
public:
    Trampa(sf::Texture& textura, int x, int y, int w, int h);
    void update(sf::RenderWindow &window, Jugador& jugador) override;
    void draw(sf::RenderWindow &window) override;
    sf::FloatRect get_bounds() override;
    void event(Jugador& jugador) override;
    void move(float x, float y) override;
};

#endif // TRAMPA_HPP
