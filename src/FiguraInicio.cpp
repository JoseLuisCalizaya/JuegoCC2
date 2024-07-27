// FiguraInicio.cpp
#include "../include_clases/FiguraInicio.hpp"

FiguraInicio::FiguraInicio(sf::Texture& textura, int x, int y, int w, int h) {
    this->textura = textura;
    rect.setPosition(sf::Vector2f(x, y));
    rect.setSize(sf::Vector2f(w, h));
    rect.setTexture(&textura);
}

void FiguraInicio::update(sf::RenderWindow &window, Jugador &jugador) {
    event(jugador);
}

void FiguraInicio::draw(sf::RenderWindow &window) {
    window.draw(rect);
}

sf::FloatRect FiguraInicio::get_bounds() {
    return rect.getGlobalBounds();
}

void FiguraInicio::event(Jugador &jugador) {
    // Implementación de event si es necesario
}

void FiguraInicio::move(float x, float y){
    rect.move(x, y);
}
