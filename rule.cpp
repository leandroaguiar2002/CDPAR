#include "rule.h"

int Rule::distance(int pixel_1, int pixel_2) { return abs(pixel_1 - pixel_2); }

int Rule::single_index(std::vector<std::vector<int>> &mat, int row, int col) {
    return row * mat[0].size() + col;
}

bool Rule::valid_pixel(std::vector<std::vector<int>> &mat, int row, int col) {
    return (row >= 0 && row < mat.size() && col >= 0 && col < mat[0].size());
}

int Rule::tiebreaker(int curr, int next) {
    if (curr < next)
      return 1;
    else if (curr > next)
      return 0;
    return -1;
}

bool Rule::isInQueue(std::queue<int> queue, int index){
    while(!queue.empty()){
      if(queue.front() == index){
        return true;
      }
        queue.pop();
    }
    return false;  
}

int Rule::min(std::vector<std::vector<int>> &matrix, int index, std::queue<int> memory) {
    int min_dist = std::numeric_limits<int>::max();
    int next_row = -1;
    int next_col = -1;
    int nr = 0;
    int nc = 0;
    int curr_row = index / matrix[0].size();
    int curr_col = index % matrix[0].size();

    int row[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int col[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    for (auto dir = 0; dir < 8; dir++) {
        nr = curr_row + row[dir];
        nc = curr_col + col[dir];

        if (valid_pixel(matrix, nr, nc) && !isInQueue(memory, single_index(matrix, nr, nc))) {
            int dist = distance(matrix[nr][nc], matrix[curr_row][curr_col]);
            if (dist < min_dist) {
                min_dist = dist;
                next_row = nr;
                next_col = nc;
            } else if (dist == min_dist) {
                if (tiebreaker(single_index(matrix, next_row, next_col),
                                   single_index(matrix, nr, nc))) {
                    min_dist = dist;
                    next_row = nr;
                    next_col = nc;
                    }
                }
            }
        }
    return single_index(matrix, next_row, next_col);
}