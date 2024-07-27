// Dinamita.cpp
#include "../include_clases/Dinamita.hpp"
#include <memory>
#include <vector>


Dinamita::Dinamita(sf::Texture& textura, int x, int y, int w, int h) {
    rect.setTexture(&textura);
    rect.setSize(sf::Vector2f(w, h));
    rect.setPosition(x, y);
}

void Dinamita::update(sf::RenderWindow &window, Jugador &jugador) {
    // Implementación específica si es necesaria
}

void Dinamita::draw(sf::RenderWindow &window) {
    window.draw(rect);
}

sf::FloatRect Dinamita::get_bounds() {
    return rect.getGlobalBounds();
}

void Dinamita::event(Jugador &jugador) {
    // Implementación específica si es necesaria
}

void Dinamita::move(float x, float y) {
    rect.move(x, y);
}

void Dinamita::explode(std::vector<std::unique_ptr <Figura>>& figuras) {
    auto bounds = get_bounds();
    figuras.erase(std::remove_if(figuras.begin(), figuras.end(),
                                 [bounds](const std::unique_ptr<Figura>& figura) {
                                     if (figura->get_bounds().intersects(bounds)) {
                                         return true;
                                     }
                                     return false;
                                 }), figuras.end());
}
