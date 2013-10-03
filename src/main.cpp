


#include <iostream>
#include <string>
#include <list>
#include <utility>

#include "../inc/frequency_informer.h"
#include "../inc/frequency_data_parser.h"
#include "../inc/tgf_parser.h"
#include "../inc/graph.h"
#include "../inc/node.h"

using std::cout;
using std::endl;
using std::string;
using std::list;
using std::pair;

Graph* create_graph_from_file(string fname, frequency_informer& freq_informer)
{
    Graph* r_val;
    list<pair<unsigned int, bool> > sources;

    tgf_parser parser = tgf_parser(fname);
    parser.parse_tgf();

    r_val = new Graph(parser.get_pairs(), freq_informer);

    if (!r_val)
    {
        return (NULL);
    }

    sources = parser.get_source();

    for (list<pair<unsigned int, bool> >::iterator i = sources.begin(); i != sources.end(); ++i)
    {
        if (i->second)
        {
            r_val->get_node_ref_with_key(i->first).set_as_source();
        }
    }

    return (r_val);
}


int main(int argc, char* argv[])
{
    Graph* graph_ptr;
    
    frequency_data_parser freq_dat_parser(string("freq_table.dat"), string("avail_table.dat"));

    graph_ptr = create_graph_from_file(string(argv[1]), freq_dat_parser);
    
    if (!graph_ptr)
    {
        cout << "unable to create graph!" << endl;
    }
    
    cout << *graph_ptr;

    delete graph_ptr;

    return (0);
}
