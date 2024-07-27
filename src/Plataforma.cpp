// Plataforma.cpp
#include "../include_clases/Plataforma.hpp"

Plataforma::Plataforma(sf::Texture& textura, int x, int y, int w, int h) {
    this->textura = textura;
    rect.setPosition(sf::Vector2f(x, y));
    rect.setSize(sf::Vector2f(w, h));
    rect.setTexture(&textura);
}

void Plataforma::update(sf::RenderWindow &window, Jugador &jugador) {
    event(jugador);
}

void Plataforma::draw(sf::RenderWindow &window) {
    window.draw(rect);
}

sf::FloatRect Plataforma::get_bounds() {
    return rect.getGlobalBounds();
}

void Plataforma::move(float x, float y) {
    rect.move(x, y);
}
