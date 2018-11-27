#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <tuple>

#define COORD_NUM 2

typedef struct field {
  int value;
  int size;
  bool visited;
} field_t;

typedef std::tuple<int, int> tuple_t;
typedef std::queue<tuple_t> queue_tuple_t;

void count_sectors_size(field_t ***matrix, int rows, int columns);
void count_that_sector_size(field_t ***matrix, int r, int c, int rows,
                            int columns);
bool check_right(field_t ***matrix, int r, int c, int rows, int columns);
bool check_upper(field_t ***matrix, int r, int c, int rows, int columns);
bool check_left(field_t ***matrix, int r, int c, int rows, int columns);
bool check_bottom(field_t ***matrix, int r, int c, int rows, int columns);

int main(int argc, char **argv) {
  int rows, columns;
  field_t ***matrix;
  int start_sector[COORD_NUM];
  int end_sector[COORD_NUM];

  scanf("%d %d", &rows, &columns);
  // printf("%d  %d\n", rows, columns);
  matrix = (field_t ***)malloc(sizeof(field_t **) * rows);
  for (int i = 0; i < rows; i++) {
    matrix[i] = (field_t **)malloc(sizeof(field_t *) * columns);
    for (int j = 0; j < columns; j++) {
      matrix[i][j] = (field_t *)malloc(sizeof(field_t));
    }
  }

  for (int i = 0; i < COORD_NUM; i++) {
    scanf("%d", &start_sector[i]);
  }
  for (int i = 0; i < COORD_NUM; i++) {
    scanf("%d", &end_sector[i]);
  }
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      scanf("%d", &(matrix[i][j]->value));
      matrix[i][j]->size = -1;
      matrix[i][j]->visited = false;
    }
  }

  count_sectors_size(matrix, rows, columns);


  return 0;
}

void count_sectors_size(field_t ***matrix, int rows, int columns) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      if (matrix[i][j]->visited)
        continue;
      else
        count_that_sector_size(matrix, i, j, rows, columns);
    }
  }
}

void count_that_sector_size(field_t ***matrix, int r, int c, int rows,
                            int columns) {
  queue_tuple_t queue_to_process;
  queue_tuple_t queue_processed;

  int r_tmp, c_tmp;

  queue_to_process.push(std::make_tuple(r, c));
  matrix[r][c]->visited = true;

  while (!queue_to_process.empty()) {
    tuple_t coord = queue_to_process.front();
    r_tmp = std::get<0>(coord);
    c_tmp = std::get<1>(coord);

    if (check_right(matrix, r_tmp, c_tmp, rows, columns)) {
      queue_to_process.push(std::make_tuple(r_tmp, c_tmp + 1));
      matrix[r_tmp][c_tmp + 1]->visited = true;
    }

    if (check_upper(matrix, r_tmp, c_tmp, rows, columns)) {
      queue_to_process.push(std::make_tuple(r_tmp - 1, c_tmp));
      matrix[r_tmp - 1][c_tmp]->visited = true;
    }

    if (check_left(matrix, r_tmp, c_tmp, rows, columns)) {
      queue_to_process.push(std::make_tuple(r_tmp, c_tmp - 1));
      matrix[r_tmp][c_tmp - 1]->visited = true;
    }

    if (check_bottom(matrix, r_tmp, c_tmp, rows, columns)) {
      queue_to_process.push(std::make_tuple(r_tmp + 1, c_tmp));
      matrix[r_tmp + 1][c_tmp]->visited = true;
    }

    queue_processed.push(coord);
    queue_to_process.pop();
  }

  int sector_size = queue_processed.size();
  while (!queue_processed.empty()) {
    r_tmp = std::get<0>(queue_processed.front());
    c_tmp = std::get<1>(queue_processed.front());
    matrix[r_tmp][c_tmp]->size = sector_size;
    queue_processed.pop();
  }
}

bool check_right(field_t ***matrix, int r, int c, int rows, int columns) {
  if ((c + 1) >= columns) return false;
  if (matrix[r][c + 1]->visited) return false;

  int val = matrix[r][c++]->value;  // c++ cause of 'right'

  if (matrix[r][c]->value == val) {
    return true;
  } else {
    return false;
  }
}

bool check_upper(field_t ***matrix, int r, int c, int rows, int columns) {
  if ((r - 1) < 0) return false;
  if (matrix[r - 1][c]->visited) return false;

  int val = matrix[r--][c]->value;  // r-- cause of 'up'

  if (matrix[r][c]->value == val) {
    return true;
  } else {
    return false;
  }
}

bool check_left(field_t ***matrix, int r, int c, int rows, int columns) {
  if ((c - 1) < 0) return false;
  if (matrix[r][c - 1]->visited) return false;

  int val = matrix[r][c--]->value;  // c-- cause of 'left'

  if (matrix[r][c]->value == val) {
    return true;
  } else {
    return false;
  }
}

bool check_bottom(field_t ***matrix, int r, int c, int rows, int columns) {
  if ((r + 1) >= rows) return false;
  if (matrix[r + 1][c]->visited) return false;

  int val = matrix[r++][c]->value;  // r++ cause of 'down'

  if (matrix[r][c]->value == val) {
    return true;
  } else {
    return false;
  }
}
