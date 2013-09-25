


#include <iostream>
#include <utility>

#include "../inc/graph.h"
#include "../inc/node.h"
#include "../inc/path_generator.h"

using std::cout;
using std::endl;
using std::pair;

int main(int argc, char* argv[])
{
    Graph<node, unsigned int> g;
    path_generator pg(5, 20, pair<unsigned int, unsigned int>(3,10));

    list<list<unsigned int> > paths = pg.generate_paths();

    return (0);
}
