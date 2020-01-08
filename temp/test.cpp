#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

int main(void) {

  std::string line, token;
  std::vector<std::string> vec;

  // create input filestream
  std::ifstream stream("/proc/1245/stat");
  if (stream.is_open()) {
    // get line from open stream and store in line var
    std::getline(stream, line);
    std::istringstream linestream(line);
    while(linestream >> token) {
      vec.push_back(token);
    }
  }

  int i = 0;
  for( auto elem : vec) {
    std::cout << i << "\t" << elem << "\n";
    i++;
  }

  int idx = 0;
  for( int i=0; i<idx-1; i++ ) {
    std::cout << i << "\n";
  }

  return 0;
}