
#include <iostream>
#include "NodeGenerator.hpp"
#include "CircularDetector.hpp"

// CHANGE 01
// CHANGE 02

static void f_test02(const char * fname)
{
  NodeGenerator g;
  if (! g.LoadFile(fname))
    std::cout << "File " << fname << " loading failure" << std::endl;
  else g.Dump();


	CircularDetector cd(g.GetNodes());
	if (cd.HasCircularDependency())
		std::cout << "## Circular Dependency DETECTED ##\n";
	else
		std::cout << "No Circular Dependency Detected\n";

}

int main(const int argc, const char *argv[])
{
  const char * fname = (argc > 1 ? argv[1] : 0);
  if (fname)
    f_test02(fname);
  else
    std::cout << "Usage: " << argv[0] << " <filename>\n";

  return 0;
}



