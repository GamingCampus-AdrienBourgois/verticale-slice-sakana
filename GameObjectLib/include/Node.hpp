#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include <unordered_set>

class Node {
public:
    sf::Vector2i position;
    int gCost; // Cost from start to current node
    int hCost; // Heuristic cost from current node to target
    Node* parent;

    Node(sf::Vector2i pos, Node* p = nullptr) : position(pos), gCost(0), hCost(0), parent(p) {}
    ~Node() {

    }
    int fCost() const {
        return gCost + hCost;
    }

    int heuristic(const sf::Vector2i& a, const sf::Vector2i& b) {
        return std::abs(a.x - b.x) + std::abs(a.y - b.y);
    }

    std::vector<sf::Vector2i> getNeighbors() {
        return {
            {position.x + 1, position.y},
            {position.x - 1, position.y},
            {position.x, position.y + 1},
            {position.x, position.y - 1}
        };
    }
    std::vector<sf::Vector2i> findPath(const std::vector<std::vector<bool>>& matrice, const sf::Vector2i& start, const sf::Vector2i& target) {
        auto cmp = [](Node* a, Node* b) { return a->fCost() > b->fCost(); };
        std::priority_queue<Node*, std::vector<Node*>, decltype(cmp)> openSet(cmp);
        std::unordered_set<int> closedSet; // To keep track of visited nodes

        Node* startNode = new Node(start);
        openSet.push(startNode);

        while (!openSet.empty()) {
            Node* currentNode = openSet.top();
            openSet.pop();

            // Reached target
            if (currentNode->position == target) {
                std::vector<sf::Vector2i> path;
                while (currentNode) {
                    path.push_back(currentNode->position);
                    currentNode = currentNode->parent;
                }
                std::reverse(path.begin(), path.end());
                return path;
            }

            int hash = currentNode->position.y * matrice.size() + currentNode->position.x;
            if (closedSet.find(hash) != closedSet.end()) {
                continue;
            }

            closedSet.insert(hash);

            for (const auto& neighborPos : currentNode->getNeighbors()) {
                // Check boundaries and if it's a wall
                if (neighborPos.x < 0 || neighborPos.y < 0 || neighborPos.x >= matrice[0].size() || neighborPos.y >= matrice.size() || matrice[neighborPos.y][neighborPos.x]) {
                    continue;
                }

                Node* neighbor = new Node(neighborPos, currentNode);
                neighbor->gCost = currentNode->gCost + 1;
                neighbor->hCost = neighbor->heuristic(neighborPos, target);

                openSet.push(neighbor);
            }
        }


        std::vector<sf::Vector2i> vec;

        // Ajouter des éléments au vecteur (exemple)
        vec.push_back(sf::Vector2i(0, 0));
        vec.push_back(sf::Vector2i(0, 0));
        // No path found
        return vec;
    }

};