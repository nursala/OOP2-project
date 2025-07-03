#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Candle/LightingArea.hpp"


class RenderLayers {
public:
    RenderLayers();

    void setView(const sf::View& view);

    void clear();
    void display();

    void drawBackground(const sf::Drawable& drawable , const sf::BlendMode = sf::BlendAdd);
    void drawForeground(const sf::Drawable& drawable, const sf::BlendMode = sf::BlendAdd );
    void drawLight(candle::LightSource& light);

    void renderFinal(sf::RenderTarget& target) const;

private:
    sf::RenderTexture m_background;
    sf::RenderTexture m_foreground;
    candle::LightingArea m_lightingArea;

    sf::Vector2u m_currentSize;
    sf::View m_view;
    sf::Texture m_mapTexture;
};
