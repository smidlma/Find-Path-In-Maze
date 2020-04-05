#include <iostream>
#include <memory>

#include "Maze.hpp"

using namespace std;

int main() {
  const char *file_name = "Bludiste.txt";  //"test.txt"; ;
  // Ini maze
  Maze m(file_name);
  m.Show();
  m.FindPath();
  m.Show();

  return 0;
}
