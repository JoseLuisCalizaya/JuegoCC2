#ifndef FIGURA_FACTORY_HPP
#define FIGURA_FACTORY_HPP

#include "Figura.hpp"
#include "Trampa.hpp"
#include "FiguraInicio.hpp"
#include "FiguraMeta.hpp"
#include "Dinamita.hpp"
#include "Plataforma.hpp"
#include <memory>
enum class FiguraType {
    Plataforma,
    Trampa,
    FiguraInicio,
    FiguraMeta,
    Dinamita
};

class FiguraFactory {
public:
    static std::unique_ptr <Figura> createFigura(FiguraType type, sf::Texture& textura, int x, int y, int w, int h);
};

#endif
