// EstadoEdicionMapa.cpp
#include "../include_clases/EstadoEdicionMapa.hpp"
#include "../include_clases/Constantes.hpp"
#include "../include_clases/Dinamita.hpp"
#include "../include_clases/EstadoJuegoNormal.hpp"
#include <memory>
#include <iostream>

EstadoEdicionMapa::EstadoEdicionMapa(Juego& juego, Jugador* jugador1, Jugador* jugador2, std::vector<std::unique_ptr <Figura>>& figuras)
    : juego(juego), jugador1(jugador1), jugador2(jugador2), figuras(figuras) {
    int tipo1 = rand() % FIGURAS_DISPONIBLES + 1;
    int tipo2 = rand() % FIGURAS_DISPONIBLES + 1;
    figuraJugador1 = juego.create_figure_accesibles(tipo1, 100,  500);
    figuraJugador2 = juego.create_figure_accesibles(tipo2, 500, 500);
}

void EstadoEdicionMapa::manejar_eventos(sf::Event event) {
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
            case sf::Keyboard::A: figuraJugador1->move(-50, 0); break;
            case sf::Keyboard::D: figuraJugador1->move(50, 0); break;
            case sf::Keyboard::W: figuraJugador1->move(0, -50); break;
            case sf::Keyboard::S: figuraJugador1->move(0, 50); break;
            case sf::Keyboard::Left: figuraJugador2->move(-50, 0); break;
            case sf::Keyboard::Right: figuraJugador2->move(50, 0); break;
            case sf::Keyboard::Up: figuraJugador2->move(0, -50); break;
            case sf::Keyboard::Down: figuraJugador2->move(0, 50); break;
            case sf::Keyboard::Space:
                if (figuraJugador1 && dynamic_cast<Dinamita*>(figuraJugador1.get())) {
                    dynamic_cast<Dinamita*>(figuraJugador1.get())->explode(figuras);
                } else if (figuraJugador1) {
                    figuras.push_back(std::move(figuraJugador1));
                }
                figuraJugador1 = nullptr;
                break;
            case sf::Keyboard::Enter:
                if (figuraJugador2 && dynamic_cast<Dinamita*>(figuraJugador2.get())) {
                    dynamic_cast<Dinamita*>(figuraJugador2.get())->explode(figuras);
                } else if (figuraJugador2) {
                    figuras.push_back(std::move(figuraJugador2));
                }
                figuraJugador2 = nullptr;
                break;
            default: break;
        }
    }
}

void EstadoEdicionMapa::actualizar(float deltaTime) {
    if (figuraJugador1 == nullptr && figuraJugador2 == nullptr) {
        std::cout << "¡Volviendo al mapa!" << std::endl;
        jugador1->set_estado_meta(false);
        jugador2->set_estado_meta(false);
        jugador1->set_estado_vida(true);
        jugador2->set_estado_vida(true);
        jugador1->set_posicion(100.0f, 100.0f);
        jugador2->set_posicion(100.0f, 100.0f);
        juego.cambiar_estado(new EstadoJuegoNormal(juego, jugador1, jugador2, figuras));
    }
}

void EstadoEdicionMapa::renderizar(sf::RenderWindow& window) {
    window.clear();
    window.draw(juego.getBackground());
    for (const auto& figura : figuras) {
        figura->draw(window);
    }
    if (figuraJugador1) figuraJugador1->draw(window);
    if (figuraJugador2) figuraJugador2->draw(window);
    window.display();
}

EstadoEdicionMapa::~EstadoEdicionMapa() {

}
