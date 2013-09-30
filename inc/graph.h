

#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <iostream>
#include <list>
#include <vector>
#include <utility>

#include "node.h"
#include "frequency_informer.h"

using std::ostream;
using std::cout;
using std::endl;
using std::list;
using std::vector;
using std::pair;

class Graph
{
    public:
        
        friend ostream& operator<< (ostream& os, const Graph& g)
        {
            for (list <pair<unsigned int, list<unsigned int> > >::const_iterator iter = g.key_list.begin();
                 iter != g.key_list.end(); 
                 ++iter)
            {
                os << iter->first;
                if (g.nodes[iter->first].is_source())
                {
                    os << " [src]:";
                }
                else
                {
                    os << "      :";
                }

                for (list<unsigned int>::const_iterator k = iter->second.begin(); k != iter->second.end(); ++k)
                {
                    os << *k << " ";
                }
                os << endl;
            }
            os << endl;

            return (os);
        }
        
        Graph(list <pair <unsigned int,unsigned int> >& vertex_pairs, frequency_informer& freq_informer)
        {
            for (list <pair <unsigned int,unsigned int> >::iterator iter = vertex_pairs.begin(); iter != vertex_pairs.end(); ++iter)
            {
                list <pair<unsigned int, list<unsigned int> > >::iterator vertex;

                /* if not in the graph list, add it pls */
                if (!find_in_graph_list(iter->first))
                {
                    pair<unsigned int, list<unsigned int> > new_key;
                    pair<unsigned int, node> new_node;

                    new_key.first = iter->first;
                    new_node.first = iter->first;

                    key_list.push_back(new_key);
                    nodes.push_back(node(new_key,freq_informer));
                }

                /* no worries here .... */
                vertex = get_graph_elem_iter(iter->first);
                if (vertex == key_list.end())
                {
                    /* something really bad happened here ... */;
                    cout << "how could it be happened!\n";
                    throw ("iterator cannot be found.");
                }

                /* safe zone */
                vertex->second.push_back(iter->second);
            }
        }

        node& get_node_ref_with_key(const unsigned int& key)
        {
            if (key > nodes.size())
            {
                throw ("key is out of range");
            }

            return (nodes[key]);
        }
        
        vector<node>& get_nodes()
        {
            return (nodes);
        }
        
    private:

        list <pair<unsigned int, list<unsigned int> > >::iterator get_graph_elem_iter(const unsigned int& key)
        {
            for (list <pair<unsigned int, list<unsigned int> > >::iterator iter = key_list.begin(); iter != key_list.end(); ++iter)
            {
                if (iter->first == key)
                {
                    return (iter);
                }
            }
            return (key_list.end());
        }


        bool find_in_graph_list(const unsigned int& key) const
        {
            for (list <pair<unsigned int, list<unsigned int> > >::const_iterator iter = key_list.begin(); iter != key_list.end(); ++iter)
            {
                if (iter->first == key)
                {
                    return (true);
                }
            }
            return (false);
        }

        list <pair<unsigned int, list<unsigned int> > > key_list;
        vector <node> nodes;
};

#endif /* _GRAPH_H_ */
