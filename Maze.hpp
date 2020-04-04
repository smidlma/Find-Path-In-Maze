#include <iostream>
#include <memory>

using namespace std;

class Maze {
 private:
  unique_ptr<char[]> maze;
  int rows;
  int cols;

 public:
  Maze(const char* file_path);
  ~Maze();
  void Show();
};

Maze::Maze(const char* file_path) {
  FILE* file = fopen(file_path, "rt");

  fscanf(file, "%d\n", &this->rows);
  fscanf(file, "%d\n", &this->cols);
  // Allocate memory for maze matrix
  this->maze = make_unique<char[]>(this->rows * this->cols);
  // Read each element and add it to the maze
  for (int y = 0; y < this->rows; y++) {
    for (int x = 0; x < this->cols; x++) {
      fscanf(file, "%c", &this->maze[x + y * this->cols]);
    }
    fscanf(file, "\n");
  }

  fclose(file);
  file = NULL;
}

void Maze::Show() {
  for (int y = 0; y < this->rows; y++) {
    for (int x = 0; x < this->cols; x++) {
      cout << this->maze[x + y * this->cols];
    }
    cout << endl;
  }
}

Maze::~Maze() {}
