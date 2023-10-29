#ifndef WALK_H
#define WALK_H

#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <algorithm>
#include <limits>
#include "rule.h"

#define MAX 20

class Walk{
    
        std::vector<int> L;
        std::vector<std::list<int>> P;
        std::queue<int> memory;
        std::vector<std::vector<int>> res;

    public:
        
        std::vector<std::vector<int>> compute (std::vector<std::vector<int>>& matrix, Rule rule, int size_memory, int rows, int cols);

        std::list<int> verifyAttractor(int id); 

        int get(std::list<int>& l, int index);

        std::list<int> subList(std::list<int>& source, int from, int to);

        std::list<int> create_memory(int size);

        void create_historic(int size);

        void clear_historic(int size);
};


#endif