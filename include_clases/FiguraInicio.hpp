// FiguraInicio.hpp
#ifndef FIGURA_INICIO_HPP
#define FIGURA_INICIO_HPP

#include "Figura.hpp"

class FiguraInicio : public Figura {
public:
    FiguraInicio(sf::Texture& textura, int x, int y, int w, int h);
    void update(sf::RenderWindow &window, Jugador &jugador) override;
    void draw(sf::RenderWindow &window) override;
    void event(Jugador &jugador) override;
    sf::FloatRect get_bounds() override;
    void move(float x, float y) override;
};

#endif // FIGURA_INICIO_HPP
