// Plataforma.hpp
#ifndef PLATAFORMA_HPP
#define PLATAFORMA_HPP

#include "Figura.hpp"

class Plataforma : public Figura {
public:
    Plataforma(sf::Texture& textura, int x, int y, int w, int h);
    void update(sf::RenderWindow &window, Jugador &jugador) override;
    void draw(sf::RenderWindow &window) override;
    void event(Jugador &jugador) override {};
    void move(float x, float y) override;
    sf::FloatRect get_bounds() override;
};

#endif // PLATAFORMA_HPP
