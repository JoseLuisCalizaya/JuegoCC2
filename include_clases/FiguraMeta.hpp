// FiguraMeta.hpp
#ifndef FIGURA_META_HPP
#define FIGURA_META_HPP

#include "Figura.hpp"
#include "Jugador.hpp"

class FiguraMeta : public Figura {
public:
    FiguraMeta(sf::Texture& textura, int x, int y, int w, int h);
    void update(sf::RenderWindow &window, Jugador &jugador) override;
    void draw(sf::RenderWindow &window) override;
    sf::FloatRect get_bounds() override;
    void event(Jugador &jugador) override;
    void move(float x, float y) override;
    bool checkVictory(Jugador* jugador1, Jugador* jugador2);

private:
    bool checkIfOnTop(Jugador* jugador);
};

#endif // FIGURA_META_HPP
