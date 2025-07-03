#include <SFML/System.hpp>
#include <vector>
#include "LoadMap.h"

class AStarPathfinder {
public:
	static std::vector<sf::Vector2i> findPath( // A* algorithm for pathfinding
        const LoadMap& map,
        const sf::Vector2i& start,
        const sf::Vector2i& goal);
};