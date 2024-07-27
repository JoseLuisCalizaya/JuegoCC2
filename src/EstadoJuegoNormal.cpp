// EstadoJuegoNormal.cpp
#include "../include_clases/EstadoJuegoNormal.hpp"
#include "../include_clases/EstadoEdicionMapa.hpp"
#include "../include_clases/Jugador.hpp"
#include <iostream>
#include <memory>

EstadoJuegoNormal::EstadoJuegoNormal(Juego& juego, Jugador* jugador1, Jugador* jugador2, std::vector<std::unique_ptr <Figura>>& figuras)
    : juego(juego), jugador1(jugador1), jugador2(jugador2), figuras(figuras) {}

void EstadoJuegoNormal::manejar_eventos(sf::Event event) {
    if ((jugador1->get_estado_ganar() && jugador2->get_estado_ganar())){
        std::cout << "Ambos jugadores ganaron!" << std::endl;

    } else if ((jugador1->get_estado_ganar() && !jugador2->estado_vida())){
        std::cout << "El jugador 1 ganó!" << std::endl;

    } else if ((jugador2->get_estado_ganar() && !jugador1->estado_vida())){
        std::cout << "El jugador 2 ganó!" << std::endl;

    }
}

void EstadoJuegoNormal::actualizar(float deltaTime) {
    hilos_jugadores.clear();
    hilos_jugadores.emplace_back(&Juego::update_jugador, &juego, deltaTime, jugador1);
    hilos_jugadores.emplace_back(&Juego::update_jugador, &juego, deltaTime, jugador2);
    for (auto& hilo : hilos_jugadores) {
        if (hilo.joinable()) {
            hilo.join();
        }
    }

    if ((jugador1->get_estado_ganar() && jugador2->get_estado_ganar()) || 
        (!jugador1->estado_vida() && !jugador2->estado_vida()) ||
        (!jugador1->estado_vida() && jugador2->get_estado_ganar()) || 
        (jugador1->get_estado_ganar() && !jugador2->estado_vida())) {
        std::cout << "Puntaje Jugador 1:" << jugador1->obt_puntage()<<std::endl;
        std::cout << "Puntaje Jugador 2:" << jugador2->obt_puntage()<<std::endl;
        std::cout << "¡Cambio de modo!" << std::endl;
        juego.cambiar_estado(new EstadoEdicionMapa(juego, jugador1, jugador2, figuras));
    }
}

void EstadoJuegoNormal::renderizar(sf::RenderWindow& window) {
    window.clear();
    window.draw(juego.getBackground());
    for (const auto& figura : figuras) {
        figura->draw(window);
    }
    jugador1->draw(window);
    jugador2->draw(window);
    window.display();
}
