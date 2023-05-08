#include "Node.hpp"

Node::Node(float g, float h, int x, int y, Node *parentN) : gCost(g), hCost(h), x(x), y(y) , parent(parentN)
{
    this->gridx = x / 100;
    this->gridy = y / 100;
}

Node::Node(float g, float h, int x, int y) : gCost(g), hCost(h), x(x), y(y), parent(nullptr)
{
    this->gridx = x / 100;
    this->gridy = y / 100;
}

Node::~Node()
{
    delete parent;
    parent = nullptr;
}
