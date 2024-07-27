// EstadoJuego.hpp
#ifndef ESTADO_JUEGO_HPP
#define ESTADO_JUEGO_HPP

#include <SFML/Graphics.hpp>

class EstadoJuego {
public:
    virtual ~EstadoJuego() = default;
    virtual void manejar_eventos(sf::Event event) = 0;
    virtual void actualizar(float deltaTime) = 0;
    virtual void renderizar(sf::RenderWindow& window) = 0;
};

#endif // ESTADO_JUEGO_HPP
