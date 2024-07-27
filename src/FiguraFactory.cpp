// FiguraFactory.cpp
#include "../include_clases/FiguraFactory.hpp"
#include <memory>

std::unique_ptr <Figura>  FiguraFactory::createFigura(FiguraType type, sf::Texture& textura, int x, int y, int w, int h) {
    switch (type) {
        case FiguraType::Plataforma:
            return std::make_unique <Plataforma> (Plataforma(textura, x, y, w, h));
        case FiguraType::Trampa:
            return std::make_unique <Trampa> (Trampa(textura, x, y, w, h));
        case FiguraType::FiguraInicio:
            return std::make_unique <FiguraInicio> (FiguraInicio(textura, x, y, w, h));
        case FiguraType::FiguraMeta:
            return std::make_unique <FiguraMeta> (FiguraMeta(textura, x, y, w, h));
        case FiguraType::Dinamita:
            return std::make_unique <Dinamita> (Dinamita(textura, x, y, w, h));
        default:
            return nullptr;
    }
}
