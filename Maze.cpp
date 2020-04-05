#include "Maze.h"

Maze::Maze(const char* file_path) {
  FILE* file = fopen(file_path, "rt");

  // Get firs and second row of file with rows cols info
  fscanf(file, "%d\n", &this->rows);
  fscanf(file, "%d\n", &this->cols);
  // Allocate memory for maze matrix
  this->maze = make_unique<char[]>(this->rows * this->cols);
  // Read each element and add it to the maze
  for (int y = 0; y < this->rows; y++) {
    for (int x = 0; x < this->cols; x++) {
      fscanf(file, "%c", &this->maze[x + y * this->cols]);
      // Remember start possition
      if (this->maze[x + y * this->cols] == '2') {
        this->start.x = x;
        this->start.y = y;
      }
      // Remember finnish possition
      if (this->maze[x + y * this->cols] == '3') {
        this->finish.x = x;
        this->finish.y = y;
      }
    }
    fscanf(file, "\n");
  }

  fclose(file);
  file = NULL;
}

Maze::~Maze() {}

void Maze::Show() {
  for (int y = 0; y < this->rows; y++) {
    for (int x = 0; x < this->cols; x++) {
      cout << this->maze[x + y * this->cols];
    }
    cout << endl;
  }
}

void Maze::FindPath() {
  cout << endl << endl;
  // Start recursion
  this->Solve(this->start.x, this->start.y);
}

void Maze::Solve(int x, int y) {
  this->path.push({x, y});
  this->seen.push_front({x, y});
  // Our Goal
  if (x == this->finish.x && y == this->finish.y) {
    AddPath();
    return;
  }

  // Our Choise
  if (this->isValidMove(x + 1, y)) {  // right
    this->Solve(x + 1, y);
  }
  if (this->isValidMove(x, y - 1)) {  // up
    this->Solve(x, y - 1);
  }
  if (this->isValidMove(x - 1, y)) {  // left
    this->Solve(x - 1, y);
  }
  if (this->isValidMove(x, y + 1)) {  // down
    this->Solve(x, y + 1);
  }

  this->path.pop();  // No option so get out of my path
}

bool Maze::SeenContain(Point2D p) {
  bool found =
      (find(this->seen.begin(), this->seen.end(), p) != this->seen.end());
  return found;
}

bool Maze::isValidMove(int x, int y) {
  char elem = this->maze[x + y * this->cols];
  return ((elem == '0' || elem == '3') && !this->SeenContain({x, y}));
}

void Maze::AddPath() {
  stack<Point2D> path_copy;
  
  path_copy = this->path;
  while (!path_copy.empty()) {
    Point2D p = path_copy.top();
    path_copy.pop();
    this->maze[p.x + p.y * this->cols] = ' ';
  }
}