


#include <iostream>
#include <utility>

#include "../inc/graph.h"
#include "../inc/node.h"
#include "../inc/path_generator.h"

using std::cout;
using std::endl;
using std::pair;


Graph<node, unsigned int>* create_graph_from_paths(unsigned int num_of_path, 
                                                  unsigned int graph_nodes,
                                                  pair<unsigned int, unsigned int> path_len_range)
{
    Graph<node, unsigned int>* r_val;
    list<pair<unsigned int, unsigned int> > vertex_pairs;
    list<list<unsigned int > >paths;
    path_generator pg(num_of_path, graph_nodes, path_len_range);
    
    paths = pg.generate_paths();
    
    for (list<list<unsigned int > >::iterator i = paths.begin(); i != paths.end(); ++i)
    {
        unsigned char first = 0x01;
        pair<unsigned int, unsigned int> temp;
        for (list<unsigned int>::iterator k = i->begin(); k != i->end(); ++k)
        {
            if (first)
            {
                temp.first = *k;
                first = 0x00;
            }
            else
            {
                temp.second = temp.first;
                temp.first = *k;
                vertex_pairs.push_back(temp);
            }
        }
    }

    vertex_pairs.unique();
    
    r_val = new Graph<node, unsigned int>(vertex_pairs);
    
    return (r_val);
}


int main(int argc, char* argv[])
{
    Graph<node, unsigned int>* graph_ptr;
    
    graph_ptr = create_graph_from_paths(5, 20, pair<unsigned int, unsigned int>(5,10));
    
    if (!graph_ptr)
    {
        cout << "unable to create graph!" << endl;
    }
    
    cout << *graph_ptr;
    
    delete graph_ptr;
    
    return (0);
}
