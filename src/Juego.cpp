#include "../include_clases/Juego.hpp"
#include "../include_clases/Constantes.hpp"
#include "../include_clases/FiguraFactory.hpp"
#include "../include_clases/EstadoJuegoNormal.hpp"
#include <iostream>

Juego& Juego::getInstance() {
    static Juego instance;
    return instance;
}

Juego::Juego()
    : window(sf::VideoMode(WINDOW_WIGHT, WINDOW_HEIGHT), "Test") {
    if (!backTexture.loadFromFile(DIRECCION "fondo.jpg") ||
        !dinoTexture.loadFromFile(DIRECCION "spriten.png") ||
        !dino2Texture.loadFromFile(DIRECCION "image.png") ||
        !plataforma2Texture.loadFromFile(DIRECCION "plataforma_2.png") ||
        !plataforma3Texture.loadFromFile(DIRECCION "plataforma_3.png") ||
        !plataforma1Texture.loadFromFile(DIRECCION "plataforma_1.png") ||
        !trampaTexture.loadFromFile(DIRECCION "trampa.png") ||
        !dinamitaTexture.loadFromFile(DIRECCION "dinamita.png") ||
        !inicioTexture.loadFromFile(DIRECCION "inicio.png") ||
        !metaTexture.loadFromFile(DIRECCION "meta.png")) {
        std::cout << "Error al cargar las texturas!" << std::endl;
        window.close();
        return;
    }

    sf::Vector2u TextureSize = backTexture.getSize();
    sf::Vector2u WindowSize = window.getSize();
    float ScaleX = static_cast<float>(WindowSize.x) / TextureSize.x;
    float ScaleY = static_cast<float>(WindowSize.y) / TextureSize.y;

    background.setTexture(backTexture);
    background.setScale(ScaleX, ScaleY);

    jugador1 = new Jugador(dinoTexture, "Jugador 1", sf::Vector2f(50, 50),15,140,32,50);
    jugador2 = new Jugador(dino2Texture, "Jugador 2", sf::Vector2f(50, 100),15,140,32,50);
    jugador1->set_posicion(50.0f, 100.0f);
    jugador2->set_posicion(50.0f, 100.0f);
    jugador1->set_keys(sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up);
    jugador2->set_keys(sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::W);
    inicio = FiguraFactory::createFigura(FiguraType::FiguraInicio, inicioTexture, 0, 500, PLATAFORMA_WIGHT, PLATAFORMA_HEIGHT);
    meta = FiguraFactory::createFigura(FiguraType::FiguraMeta, metaTexture, 1500, 300, PLATAFORMA_WIGHT, PLATAFORMA_HEIGHT);
    Figuras.push_back(std::move(inicio));
    Figuras.push_back(std::move(meta));

    estadoActual = new EstadoJuegoNormal(*this, jugador1, jugador2, Figuras);
}

Juego::~Juego() {
    delete estadoActual;
}

void Juego::cambiar_estado(EstadoJuego* nuevoEstado) {
    delete estadoActual;
    estadoActual = nuevoEstado;
}

void Juego::run() {
    while (window.isOpen()) {
        processEvents();
        float deltaTime = clock.restart().asSeconds();
        estadoActual->actualizar(deltaTime);
        estadoActual->renderizar(window);
    }
}

void Juego::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        estadoActual->manejar_eventos(event);
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }
}

sf::RenderWindow& Juego::getWindow() {
    return window;
}

sf::Sprite& Juego::getBackground() {
    return background;
}

std::unique_ptr <Figura> Juego::create_figure_accesibles(int random, float x, float y) {
    switch (random) {
        case 1:
            return FiguraFactory::createFigura(FiguraType::Plataforma, plataforma1Texture, x, y, PLATAFORMA_WIGHT, PLATAFORMA_HEIGHT);
        case 2:
            return FiguraFactory::createFigura(FiguraType::Plataforma, plataforma2Texture, x, y, PLATAFORMA_WIGHT, PLATAFORMA_HEIGHT);
        case 3:
            return FiguraFactory::createFigura(FiguraType::Plataforma, plataforma3Texture, x, y, PLATAFORMA_WIGHT / 2, PLATAFORMA_HEIGHT);
        case 4:
        case 5:
            return FiguraFactory::createFigura(FiguraType::Trampa, trampaTexture, x, y, TRAMPA_WIGHT, TRAMPA_HEIGHT);
        case 6:
            return FiguraFactory::createFigura(FiguraType::Dinamita, dinamitaTexture, x, y, 100, 100);
        default:
            return nullptr;
    }
}

void Juego::update_jugador(float deltaTime, Jugador* jugador) {
    for (auto& figura : Figuras) {
        figura->update(window, *jugador);
    }
    jugador->update(deltaTime, window, Figuras);
}
