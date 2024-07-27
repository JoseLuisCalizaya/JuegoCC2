// Jugador.hpp
#ifndef JUGADOR_HPP
#define JUGADOR_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Figura.hpp"

class Jugador {
private:
    sf::Sprite cuerpo;
    sf::Texture textura;
    sf::Vector2f movimiento;
    bool en_el_suelo;
    bool vivo;
    bool gano;
    int puntage;
    float salto;
    float velocidad;
    float gravedad;
    sf::Keyboard::Key tecla_izquierda;
    sf::Keyboard::Key tecla_derecha;
    sf::Keyboard::Key tecla_saltar;

    std::string nombre;
    sf::Font fuente;
    sf::Text textoNombre;
    sf::Text textoPuntaje;
    sf::Vector2f posicionPuntaje;


    sf::Clock reloj_animacion;
    float intervalo_animacion;
    float tiempo_transcurrido;
    int x_textura;
    const int y_textura;
    const int ancho_frame;
    const int alto_frame;
    const int numero_frames;

public:
    Jugador(sf::Texture& textura, const std::string& nombre, sf::Vector2f posicionPuntaje, int width, int height, int maxWidth, int maxHeight);
    void update(float deltaTime, sf::RenderWindow &window, const std::vector<std::unique_ptr <Figura>>& figuras);
    sf::Vector2f get_posicion();
    void set_posicion(float x, float y);
    void draw(sf::RenderWindow &window);
    void move(float deltaTime);
    void manejar_colisiones(const std::vector<std::unique_ptr <Figura>>& figuras);
    void saltar();
    void set_estado_vida(bool estado);
    void set_estado_meta(bool estado);
    void add_puntage(int x);
    int obt_puntage();
    bool estado_vida();
    bool get_estado_ganar();
    int get_puntage();
    sf::Texture& get_textura();
    std::string get_nombre();
    bool colisiona(sf::FloatRect rect);
    sf::FloatRect get_bounds();
    void set_keys(sf::Keyboard::Key izquierda, sf::Keyboard::Key derecha, sf::Keyboard::Key saltar);
    void actualizarPuntaje();
};

#endif // JUGADOR_HPP
