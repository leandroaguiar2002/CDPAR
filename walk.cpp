#include "walk.h"

std::vector<std::vector<int>> Walk::compute(std::vector<std::vector<int>> &matrix,
                                        Rule rule, int size_memory, int rows,
                                        int cols) {
    this->P = std::vector<std::list<int>>(rows * cols);
    int next, p, size_att;
    std::list<int> attractor;
    std::list<int> mem = create_memory(size_memory);
    create_historic(rows);

    std::vector<std::vector<int>> distribution(MAX, std::vector<int>(MAX, 0));

    for (auto i = 0; i < rows; i++) {
      for (auto j = 0; j < cols; j++) {
        next = rule.single_index(matrix, i, j);
        attractor.clear();
        for (const int &elem : mem) {
          memory.push(elem);
        }
        p = -1;
        L.clear();
        clear_historic(rows);

        do {
          p++;
          memory.push(next);
          memory.pop();
          L.push_back(next);
          P[next].push_back(p);
          attractor = verifyAttractor(next);
          next = rule.min(matrix, next, memory);                                             //só faz a caminhada para o pixel presente em [i][j]
        } while (attractor.empty() && p < MAX && next > -1);

        size_att = 0;
        if (!(attractor.empty())) {
            size_att = (int) attractor.size();
          if (size_att < MAX && p - (size_att * 2) < MAX) {
            distribution[size_att - (size_memory + 1)][p - (size_att * 2)]++;
          }
        }
        res.push_back(L);
      }
    }
    return res;
  }


std::list<int> Walk::verifyAttractor(int id) {
    if (P[id].size() >= 3) {
        auto it = P[id].end();
        std::advance(it, -3);
        std::list<int> pos(it, P[id].end());

        std::list<int> s1;
        std::list<int> s2;
        if (pos.size() >= 2) {
            auto it1 = pos.begin();
            auto it2 = it1;
            std::advance(it2, 1);
            s1.assign(it1, it2);
        }
        if (pos.size() >= 3) {
            auto it1 = pos.begin();
            auto it2 = it1;
            std::advance(it1, 1);
            std::advance(it2, 2);
            s2.assign(it1, it2);
        }

        bool ok = (s1 == s2);
        if (ok) {
            return s1;
        }
    }
    return std::list<int>();
}

int Walk::get(std::list<int> &l, int index) {
    std::list<int>::iterator it = l.begin();
    for (int i = 0; i < index; i++)
      ++it;
    return *it;
}

std::list<int> Walk::subList(std::list<int> &source, int from, int to) {
    std::list<int> sub;
    if (from > source.size() || to == 0) {
      std::cout << "erro!" << std::endl;
      return sub;
    }

    auto fromIter = std::next(source.begin(), from);
    auto toIter = std::next(fromIter, to);

    for (auto it = fromIter; it != toIter; ++it)
      sub.push_back(*it);

    return sub;
}

std::list<int> Walk::create_memory(int size) {
    int i = 0;
    std::list<int> mem;
    while (i < size) {
      mem.push_back(NULL);
      i++;
    }
    return mem;
}

void Walk::create_historic(int size) {
    for (int i = 0; i < size; i++) {
      P[i] = std::list<int>();
    }
}

void Walk::clear_historic(int size) {
    for (int i = 0; i < size; i++) {
      P[i].clear();
    }
}