// Trampa.cpp
#include "../include_clases/Trampa.hpp"
#include "../include_clases/Jugador.hpp"
#include <iostream>

class Jugador;

Trampa::Trampa(sf::Texture& textura, int x, int y, int w, int h) {
    this->textura = textura;
    rect.setPosition(sf::Vector2f(x, y));
    rect.setSize(sf::Vector2f(w, h));
    rect.setTexture(&textura);
}

void Trampa::update(sf::RenderWindow &window, Jugador& jugador) {
    event(jugador);
}

void Trampa::draw(sf::RenderWindow &window) {
    window.draw(rect);
}

sf::FloatRect Trampa::get_bounds() {
    return rect.getGlobalBounds();
}

void Trampa::move(float x, float y){
    rect.move(x, y);
}

void Trampa::event(Jugador& jugador) {
    if (rect.getGlobalBounds().intersects(jugador.get_bounds()) && jugador.estado_vida()) {
        jugador.set_estado_vida(false);
        std::cout << "El jugador ha muerto" << std::endl;
    }
}
