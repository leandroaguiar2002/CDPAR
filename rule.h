#ifndef RULE_H
#define RULE_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>


class Rule{

    public:

        int min(std::vector<std::vector<int>> &matrix, int index, std::queue<int> memory);

        int distance(int pixel_1, int pixel_2);

        int single_index(std::vector<std::vector<int>>& mat, int row, int col);

        bool valid_pixel(std::vector<std::vector<int>>& mat, int row, int col);

        int tiebreaker(int curr, int next);

        bool isInQueue(std::queue<int> queue, int index);
};

#endif