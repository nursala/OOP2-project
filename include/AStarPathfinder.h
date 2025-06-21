#include <SFML/System.hpp>
#include <vector>
#include "LoadMap.h"

class AStarPathfinder {
public:
    static std::vector<sf::Vector2i> findPath(
        const LoadMap& map,
        const sf::Vector2i& start,
        const sf::Vector2i& goal);
};