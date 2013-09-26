


#include <iostream>
#include <utility>

#include "../inc/graph.h"
#include "../inc/node.h"
#include "../inc/path_generator.h"

using std::cout;
using std::endl;
using std::pair;

void print_paths(list<list<unsigned int> > paths)
{
    for (list<list<unsigned int > >::iterator i = paths.begin(); i != paths.end(); ++i)
    {
        cout << "path: ";
        for (list<unsigned int>::iterator k = i->begin(); k != i->end(); ++k)
        {
            cout << *k << " ";
        }
        cout << endl;
    }
    cout << endl;
}

Graph<node, unsigned int>* create_graph_from_paths(unsigned int num_of_path, 
                                                  unsigned int graph_nodes,
                                                  pair<unsigned int, unsigned int> path_len_range)
{
    Graph<node, unsigned int>* r_val;
    list<pair<unsigned int, unsigned int> > vertex_pairs;
    list<list<unsigned int > >paths;
    path_generator pg(num_of_path, graph_nodes, path_len_range);
    
    /* adding pairs */
    paths = pg.generate_paths();
    
    for (list<list<unsigned int > >::iterator i = paths.begin(); i != paths.end(); ++i)
    {
        pair<unsigned int, unsigned int> temp;
        list<unsigned int>::iterator k = i->begin();
        
        temp.first = *k++;
        temp.second = *k++;
        vertex_pairs.push_back(temp);
        
        while (k != i->end())
        {
            temp.first = temp.second;
            temp.second = *k;
            vertex_pairs.push_back(temp);
            ++k;
        }
    }
    
    /* removing duplicate node pairs */
    vertex_pairs.sort();    
    vertex_pairs.unique();

    r_val = new Graph<node, unsigned int>(vertex_pairs);
    
    if (!r_val)
    {
        return (NULL);
    }
    
    /* setting source nodes */
    for (list<list<unsigned int > >::iterator i = paths.begin(); i != paths.end(); ++i)
    {
        r_val->get_node_ref_with_key(i->front()).set_as_source();
    }
    
    return (r_val);
}


int main(int argc, char* argv[])
{
    Graph<node, unsigned int>* graph_ptr;
    
    graph_ptr = create_graph_from_paths(10, 20, pair<unsigned int, unsigned int>(11,19));
    
    if (!graph_ptr)
    {
        cout << "unable to create graph!" << endl;
    }
    
    delete graph_ptr;
    
    return (0);
}
