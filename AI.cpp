// #include "AI.hpp"


// float AI::heuristics(int x_pos_police, int y_pos_police, int x_pos_player, int y_pos_player)
// {
//     return abs((x_pos_police / 100) - (x_pos_player / 100)) + abs((y_pos_police / 100) - (y_pos_player / 100));
// }

// bool AI::compareNodes(const A_sNode *a, const A_sNode *b) const
// {
//     return a->fCost < b->fCost || (a->fCost == b->fCost && a->hCost < b->hCost);
// }

// std::vector<A_sNode> AI::A_StarPath(int x_pos_police, int y_pos_police, int x_pos_player, int y_pos_player)
// {
//     // A_sNode *startNode = new A_sNode(0, heuristics(x_pos_police, y_pos_police, x_pos_player, y_pos_player), 0, x_pos_police, y_pos_player);
//     // openList.push_back(startNode);

//     // while (!openList.empty())
//     // {
//     //     A_sNode* curr = *std::min_element(cu)
//     // }
// }