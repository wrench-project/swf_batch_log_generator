#include <exception>
#include <iostream>
#include "BatchLogGenerator.h"


int main(int argc, char **argv) {

  BatchLogGenerator *generator = new BatchLogGenerator();
  try {
    generator->init(argc, argv);
    generator->generate();
  } catch (std::exception &e) {
    std::cerr << e.what() << "\n";
    return 1;
  }
  return 0;
}
