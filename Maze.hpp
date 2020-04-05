#include <algorithm>
#include <iostream>
#include <list>
#include <memory>
#include <stack>

using namespace std;

struct Point2D {
  int x;
  int y;

  bool operator==(const Point2D& a) const { return (x == a.x && y == a.y); }
};

class Maze {
 private:
  unique_ptr<char[]> maze;
  int rows;
  int cols;
  Point2D start;
  Point2D finish;
  stack<Point2D> path;
  list<Point2D> seen;

  void Solve(int x, int y);
  bool SeenContain(Point2D p);
  bool isValidMove(int x, int y);
  void AddPath();

 public:
  Maze(const char* file_path);
  ~Maze();

  void Show();
  void FindPath();
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
      if (this->maze[x + y * this->cols] == '2') {
        this->start.x = x;
        this->start.y = y;
      }
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
  cout << endl << "Finded Path:" << endl;
  this->Solve(this->start.x, this->start.y);
}

void Maze::Solve(int x, int y) {
  // Goal
  if (x == this->finish.x && y == this->finish.y) {
    this->path.push({x, y});
    AddPath();
    return;
  }

  // Choise
  if (this->isValidMove(x + 1, y)) {  // right
    this->path.push({x, y});
    this->seen.push_front({x, y});
    this->Solve(x + 1, y);
  }
  if (this->isValidMove(x, y - 1)) {  // up
    this->path.push({x, y});
    this->seen.push_front({x, y});
    this->Solve(x, y - 1);
  }
  if (this->isValidMove(x - 1, y)) {  // left
    this->path.push({x, y});
    this->seen.push_front({x, y});
    this->Solve(x - 1, y);
  }
  if (this->isValidMove(x, y + 1)) {  // down
    this->path.push({x, y});
    this->seen.push_front({x, y});
    this->Solve(x, y + 1);
  }

  this->path.pop();
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