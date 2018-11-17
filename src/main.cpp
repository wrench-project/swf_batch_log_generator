#include "BatchLogGenerator.h"


int main(int argc, char **argv) {

  wrench::BatchLogGenerator *generator = new wrench::BatchLogGenerator();
  return generator->generate(argc, argv);
}
