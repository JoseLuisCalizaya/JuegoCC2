// Dinamita.hpp
#ifndef DINAMITA_HPP
#define DINAMITA_HPP

#include "Figura.hpp"
#include <memory>
#include <vector>

class Dinamita : public Figura {
public:
    Dinamita(sf::Texture& textura, int x, int y, int w, int h);
    void update(sf::RenderWindow &window, Jugador &jugador) override;
    void draw(sf::RenderWindow &window) override;
    sf::FloatRect get_bounds() override;
    void event(Jugador &jugador) override;
    void move(float x, float y) override;
    void explode(std::vector<std::unique_ptr <Figura>>& figuras);
};

#endif // DINAMITA_HPP
