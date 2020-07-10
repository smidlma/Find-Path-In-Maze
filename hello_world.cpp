#include <iostream>
#include <memory>
#include <stdio.h>
#include <stdlib.h>
#include "Maze.h"

using namespace std;

int main() {
  const char *file_name = "Bludiste.txt";  // "test2.txt"; //"test.txt"; 
  // Ini maze
  unique_ptr<Maze> m(new Maze(file_name));
  m->Show();
  m->FindPath();
  m->Show();

  return 0;
}
