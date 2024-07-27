// EstadoEdicionMapa.hpp
#ifndef ESTADO_EDICION_MAPA_HPP
#define ESTADO_EDICION_MAPA_HPP

#include "EstadoJuego.hpp"
#include "Juego.hpp"
#include "Jugador.hpp"
#include "Figura.hpp"
#include <memory>
class EstadoEdicionMapa : public EstadoJuego {
private:
    Juego& juego;
    Jugador* jugador1;
    Jugador* jugador2;
    std::vector<std::unique_ptr <Figura>>& figuras;
    std::unique_ptr <Figura> figuraJugador1;
    std::unique_ptr <Figura> figuraJugador2;

public:
    EstadoEdicionMapa(Juego& juego, Jugador* jugador1, Jugador* jugador2, std::vector<std::unique_ptr <Figura>>& figuras);
    void manejar_eventos(sf::Event event) override;
    void actualizar(float deltaTime) override;
    void renderizar(sf::RenderWindow& window) override;
    ~EstadoEdicionMapa();
};

#endif // ESTADO_EDICION_MAPA_HPP
