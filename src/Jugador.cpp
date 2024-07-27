#include <iostream>
#include <memory>
#include "../include_clases/Jugador.hpp"
#include "../include_clases/Constantes.hpp"

Jugador::Jugador(sf::Texture& textura, const std::string& nombre,sf::Vector2f posicionPuntaje,int m, int h, int maxW, int maxH)
    : textura(textura), nombre(nombre), velocidad(VELOCIDAD), salto(SALTO), gravedad(GRAVEDAD), en_el_suelo(true), vivo(true), gano(false), posicionPuntaje(posicionPuntaje), intervalo_animacion(0.1f),tiempo_transcurrido(0.0f),x_textura(m),y_textura(h),ancho_frame(maxW),alto_frame(maxH), numero_frames(4) {
    puntage = 0;
    cuerpo.setTexture(textura);
    cuerpo.setTextureRect(sf::IntRect(x_textura, y_textura, ancho_frame, alto_frame));
    cuerpo.setScale(2,2);
    if (!fuente.loadFromFile("C:/Users/LENOVO/source/repos/JUEGO/font/Minecraft.ttf")) {
        // Manejo de errores aquí
    }
    textoNombre.setFont(fuente);
    textoNombre.setString(nombre);
    textoNombre.setCharacterSize(24);
    textoNombre.setFillColor(sf::Color::White);

    textoPuntaje.setFont(fuente);
    textoNombre.setCharacterSize(24);
    textoNombre.setFillColor(sf::Color::White);
}

void Jugador::actualizarPuntaje() {
    textoPuntaje.setString("Puntaje de "+nombre + ": " + std::to_string(puntage));
}

void Jugador::set_keys(sf::Keyboard::Key izquierda, sf::Keyboard::Key derecha, sf::Keyboard::Key saltar) {
    tecla_izquierda = izquierda;
    tecla_derecha = derecha;
    tecla_saltar = saltar;
}

void Jugador::set_posicion(float x, float y) {
    cuerpo.setPosition(x, y);
}

sf::Vector2f Jugador::get_posicion() {
    return cuerpo.getPosition();
}

void Jugador::draw(sf::RenderWindow &window) {
    window.draw(cuerpo);
    sf::Vector2f posicionTexto = cuerpo.getPosition();
    posicionTexto.y -= 30; 
    textoNombre.setPosition(posicionTexto);

    textoPuntaje.setPosition(posicionPuntaje);
    window.draw(textoNombre);
    window.draw(textoPuntaje);
}

void Jugador::set_estado_vida(bool estado) {
    vivo = estado;
}

void Jugador::set_estado_meta(bool estado) {
    gano = estado;
}

void Jugador::add_puntage(int x) {
    puntage += x;
}

int Jugador::get_puntage() {
    return puntage;
}

sf::Texture& Jugador::get_textura() {
    return textura;
}

std::string Jugador::get_nombre() {
    return nombre;
}

bool Jugador::estado_vida() {
    return vivo;
}

bool Jugador::get_estado_ganar() {
    return gano;
}

void Jugador::move(float deltaTime) {
    movimiento.x = 0.0f;
    if (sf::Keyboard::isKeyPressed(tecla_izquierda)) {
        tiempo_transcurrido += reloj_animacion.restart().asSeconds();
        if (tiempo_transcurrido >= intervalo_animacion) {
            tiempo_transcurrido = 0.0f;
            x_textura += 60;
            if (x_textura >= ancho_frame * numero_frames) {
                x_textura = 15;
            }
            cuerpo.setTextureRect(sf::IntRect(x_textura, 75, ancho_frame, alto_frame));
        }
        movimiento.x -= velocidad;
    }
    if (sf::Keyboard::isKeyPressed(tecla_derecha)) {
        tiempo_transcurrido += reloj_animacion.restart().asSeconds();
        if (tiempo_transcurrido >= intervalo_animacion) {
            tiempo_transcurrido = 0.0f;
            x_textura += 60;
            if (x_textura >= ancho_frame * numero_frames) {
                x_textura = 15;
            }
            cuerpo.setTextureRect(sf::IntRect(x_textura, 140, ancho_frame, alto_frame));
        }
        movimiento.x += velocidad;
    }
    if (!en_el_suelo) {
        movimiento.y += gravedad;
    }
    
    if (en_el_suelo && sf::Keyboard::isKeyPressed(tecla_saltar)) {
        saltar();
    }

    if (en_el_suelo) {
        movimiento.y = 0.0f;
    }

    cuerpo.move(movimiento * deltaTime);
}

void Jugador::manejar_colisiones(const std::vector<std::unique_ptr <Figura>>& figuras) {
    sf::FloatRect cuerpo_colision = cuerpo.getGlobalBounds();
    bool estaba_en_el_suelo = en_el_suelo;

    en_el_suelo = false;

    for (const auto& figura : figuras) {
        if (cuerpo_colision.intersects(figura->get_bounds())) {
            sf::FloatRect figura_colision = figura->get_bounds();
            float distancia_left = cuerpo_colision.left + cuerpo_colision.width - figura_colision.left;
            float distancia_right = figura_colision.left + figura_colision.width - cuerpo_colision.left;
            float distancia_top = cuerpo_colision.top + cuerpo_colision.height - figura_colision.top;
            float distancia_bottom = figura_colision.top + figura_colision.height - cuerpo_colision.top;

            bool colisiona_left = distancia_left < distancia_right;
            bool colisiona_top = distancia_top < distancia_bottom;

            float minOverlapX = colisiona_left ? distancia_left : distancia_right;
            float minOverlapY = colisiona_top ? distancia_top : distancia_bottom;

            if (minOverlapX < minOverlapY) {
                movimiento.x = 0.0f;
                cuerpo.move(colisiona_left ? -distancia_left : distancia_right, 0.0f);
            } else {
                movimiento.y = 0.0f;
                if (colisiona_top) {
                    en_el_suelo = true;
                    cuerpo.move(0.0f, -distancia_top);
                } else {
                    cuerpo.move(0.0f, distancia_bottom);
                }
            }
        }
    }
    if (!en_el_suelo && estaba_en_el_suelo) {
        cuerpo.move(0.0f, 0.1f);
    }
}

void Jugador::saltar() {
    if (en_el_suelo) {
        movimiento.y = salto;
        en_el_suelo = false;
    }
}

void Jugador::update(float deltaTime, sf::RenderWindow &window, const std::vector<std::unique_ptr <Figura>>& figuras) {
    if (vivo) {
        move(deltaTime);
        manejar_colisiones(figuras);
    }
    if (cuerpo.getPosition().y >= 700.0f) {
        en_el_suelo = true;
        cuerpo.setPosition(cuerpo.getPosition().x, 700.0f);
        if (vivo) {
            vivo = false;
            std::cout << "El jugador ha muerto" << std::endl;
        }
    }
    actualizarPuntaje();
}

sf::FloatRect Jugador::get_bounds() {
    return cuerpo.getGlobalBounds();
}

bool Jugador::colisiona(sf::FloatRect rect) {
    return cuerpo.getGlobalBounds().intersects(rect);
}

int Jugador::obt_puntage() { return puntage; }