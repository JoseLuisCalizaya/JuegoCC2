// EstadoJuegoNormal.hpp
#ifndef ESTADO_JUEGO_NORMAL_HPP
#define ESTADO_JUEGO_NORMAL_HPP

#include "EstadoJuego.hpp"
#include "Juego.hpp"
#include "Jugador.hpp"
#include "Figura.hpp"
#include <memory>
class EstadoJuegoNormal : public EstadoJuego {
private:
    Juego& juego;
    Jugador* jugador1;
    Jugador* jugador2;
    std::vector<std::thread> hilos_jugadores;
    std::vector<std::unique_ptr <Figura>>& figuras;

public:
    EstadoJuegoNormal(Juego& juego, Jugador* jugador1, Jugador* jugador2, std::vector<std::unique_ptr <Figura>>& figuras);
    void manejar_eventos(sf::Event event) override;
    void actualizar(float deltaTime) override;
    void renderizar(sf::RenderWindow& window) override;
};

#endif // ESTADO_JUEGO_NORMAL_HPP
