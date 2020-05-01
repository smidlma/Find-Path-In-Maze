#include <algorithm>
#include <iostream>
#include <list>
#include <memory>
#include <stack>

using namespace std;
/**
 * Just struct to represent point
 * @param x number
 * @param y number
 */
struct Point2D {
  int x;
  int y;

  bool operator==(const Point2D& a) const { return (x == a.x && y == a.y); }
};

/**
 * The Maze class represents a textfile maze input
 */
class Maze {
 private:
  unique_ptr<char[]> maze;
  int rows;
  int cols;
  Point2D start;
  Point2D finish;
  stack<Point2D> path;
  list<Point2D> seen;
  /**
   * Implements DFS alg
   * @param x col possition
   * @param y row possition
   */
  bool Solve(int x, int y);
  
  /**
   * Checks if p is in seen list
   * @param p point
   */
  bool SeenContain(Point2D p);

  /**
   * Checks if next move is valid
   * @param x col possition
   * @param y row possition
   */
  bool isValidMove(int x, int y);

  /**
   * Adds final path to the maze
   */
  void AddPath();

 public:
  /**
   * Contructor creates object and reads given text file
   *
   * @param file_path path to the textfile
   */
  Maze(const char* file_path);

  ~Maze();

  /**
   * Prints out maze to the console
   */
  void Show();

  /**
   * Starts finding the path
   */
  void FindPath();
};
