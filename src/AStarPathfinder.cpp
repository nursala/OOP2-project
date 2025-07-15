#include "AStarPathfinder.h"
#include <queue>
#include <unordered_map>
#include <cmath>
#include <limits>
#include <algorithm>
#include <iostream>

struct Node {
    sf::Vector2i position;
    float gCost; 
    float hCost; 
    float fCost() const { return gCost + hCost; }

    bool operator>(const Node& other) const 
    {
        return fCost() > other.fCost();
    }
};

//-------------------------------------
// A* Pathfinding algorithm implementation
std::vector<sf::Vector2i> AStarPathfinder::findPath(
    const LoadMap& map,
    const sf::Vector2i& start,
    const sf::Vector2i& goal)
{
    int width = map.getWidth();
    int height = map.getHeight();

    auto inBounds = [&](const sf::Vector2i& pos) {
        return pos.x >= 0 && pos.y >= 0 && pos.x < width && pos.y < height;
		}; //check if position is within bounds of the map

    auto heuristic = [&](const sf::Vector2i& a, const sf::Vector2i& b) {
        return static_cast<float>(std::abs(a.x - b.x) + std::abs(a.y - b.y));
		}; // Manhattan distance heuristic for grid-based pathfinding

    auto toIndex = [&](const sf::Vector2i& pos) {
        return pos.y * width + pos.x;
		}; // Convert 2D position to 1D index for easier storage in maps

	std::priority_queue<Node, std::vector<Node>, std::greater<>> openSet; // Priority queue to store nodes to explore, ordered by fCost
	std::unordered_map<int, sf::Vector2i> cameFrom;// To reconstruct the path later
	std::unordered_map<int, float> costSoFar; // To store the cost to reach each node

    openSet.push({ start, 0.f, heuristic(start, goal) });
    costSoFar[toIndex(start)] = 0.f;
    cameFrom[toIndex(start)] = { -1, -1 };

    const std::vector<sf::Vector2i> directions = {
        {1, 0}, {-1, 0}, {0, 1}, {0, -1}
    };

    while (!openSet.empty()) {
        Node current = openSet.top();
        openSet.pop();

        if (current.position == goal) {
            break;
        }

        for (const auto& dir : directions) {
            sf::Vector2i next = current.position + dir;

            if (!inBounds(next)) continue;

			if (!map.isWalkable(next.x, next.y) && next != goal) // check if the next position is walkable
                continue;

            float newCost = costSoFar[toIndex(current.position)] + 1.f;

            if (costSoFar.find(toIndex(next)) == costSoFar.end() || newCost < costSoFar[toIndex(next)]) {
                costSoFar[toIndex(next)] = newCost;
                cameFrom[toIndex(next)] = current.position;
                openSet.push({ next, newCost, heuristic(next, goal) });
            }
        }
    }

    std::vector<sf::Vector2i> path;
    sf::Vector2i current = goal;

    if (cameFrom.find(toIndex(current)) == cameFrom.end())
		return path; 

    while (current != start) {
        path.push_back(current);
        current = cameFrom[toIndex(current)];
    }

    std::reverse(path.begin(), path.end());
    return path;
}
