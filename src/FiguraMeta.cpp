// FiguraMeta.cpp
#include "../include_clases/FiguraMeta.hpp"
#include <iostream>

FiguraMeta::FiguraMeta(sf::Texture& textura, int x, int y, int w, int h) {
    this->textura = textura;
    rect.setPosition(sf::Vector2f(x, y));
    rect.setSize(sf::Vector2f(w, h));
    rect.setTexture(&textura);
}

void FiguraMeta::update(sf::RenderWindow &window, Jugador& jugador) {
    event(jugador);
}

void FiguraMeta::draw(sf::RenderWindow &window) {
    window.draw(rect);
}

sf::FloatRect FiguraMeta::get_bounds() {
    return rect.getGlobalBounds();
}

void FiguraMeta::event(Jugador &jugador){
    if (get_bounds().intersects(jugador.get_bounds()) && !jugador.get_estado_ganar()){
        jugador.set_estado_meta(true);
        jugador.add_puntage(10);
        std::cout << "El jugador ganó" << std::endl;
    }
}

void FiguraMeta::move(float x, float y){
    rect.move(x, y);
}

bool FiguraMeta::checkIfOnTop(Jugador* jugador) {
    return get_bounds().intersects(jugador->get_bounds());
}

bool FiguraMeta::checkVictory(Jugador* jugador1, Jugador* jugador2) {
    return checkIfOnTop(jugador1) && checkIfOnTop(jugador2);
}
