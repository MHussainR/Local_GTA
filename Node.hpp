#pragma once

struct Node
{
    int x, y, gridx, gridy;
    float gCost, hCost;
    Node *parent;
    Node(float g, float h, int x, int y, Node *parentN);
    Node(float g, float h, int x, int y);
    ~Node();
};