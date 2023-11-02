#pragma once
#include <SFML/Graphics.hpp>
#include <queue>
#include <cmath>
#include <algorithm>
#include <vector>

class Node {
    sf::Vector2i position;
    float Dalt; // distance alternative
    float Dgoal; // distance to goal
    bool obstacle; // is the node an obstacle?
    bool visited; // was it already visited?
    Node* parent;   // next node
    std::vector<Node*> vecNeighbours; // connections to neighboors

public:
    int fCost() const { return Dalt + Dgoal; } // total cost


    Node(sf::Vector2i pos, Node* p = nullptr) : position(pos), Dalt(0), Dgoal(0), parent(p) {}

    int heuristic(const sf::Vector2i& a, const sf::Vector2i& b) {
        return std::abs(a.x - b.x) + std::abs(a.y - b.y);
    }
    std::vector<sf::Vector2i> findPath(const std::vector<std::vector<bool>>& matrice, const sf::Vector2i& start, const sf::Vector2i& target) {
        


                




        return std::vector<sf::Vector2i>{sf::Vector2i(2, 2)};
    }


};
