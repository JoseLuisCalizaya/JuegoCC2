// Juego.hpp
#ifndef JUEGO_HPP
#define JUEGO_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <thread>
#include <memory>
#include "EstadoJuego.hpp"
#include "Figura.hpp"
#include "Jugador.hpp"

class Juego {
public:
    static Juego& getInstance();
    Juego(const Juego&) = delete;
    Juego& operator=(const Juego&) = delete;

    void run();
    void cambiar_estado(EstadoJuego* nuevoEstado);
    void update_jugador(float deltaTime, Jugador* jugador);
    std::unique_ptr <Figura> create_figure_accesibles(int random, float x, float y);
    sf::RenderWindow& getWindow();
    sf::Sprite& getBackground();

private:
    Juego();
    ~Juego();

    void processEvents();
    void update(float deltaTime);
    void render();

    EstadoJuego* estadoActual;
    sf::RenderWindow window;
    sf::Texture backTexture, dinoTexture, dino2Texture, plataforma1Texture, 
                plataforma2Texture, plataforma3Texture, trampaTexture, 
                dinamitaTexture, inicioTexture, metaTexture;
    sf::Sprite background;
    Jugador* jugador1;
    Jugador* jugador2;
    std::vector<std::thread> hilos_jugadores;
    std::vector<std::unique_ptr<Figura>> Figuras;
    std::unique_ptr<Figura> inicio;
    std::unique_ptr<Figura> meta;
    sf::Clock clock;
};

#endif // JUEGO_HPP
