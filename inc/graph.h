

#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <iostream>
#include <list>
#include <utility>

using std::cout;
using std::list;
using std::pair;

template <class T>
class Graph
{
    public:
        Graph(){}
        Graph(list <pair <T,T> > vertex_pairs)
        {
            for (typename list <pair <T,T> >::iterator iter = vertex_pairs.begin(); iter != vertex_pairs.end(); ++iter)
            {
                typename list <pair<T, list<T> > >::iterator vertex;

                /* if not in the graph list, add it pls */
                if (!find_in_graph_list(iter->first))
                {
                    pair<T, list<T> > elem;
                    elem.first = iter->first;
                    graph.push_back(elem);
                }

                /* no worries here .... */
                vertex = get_graph_elem_iter(iter->first);
                if (vertex == graph.end())
                {
                    /* something really bad happend here ... */;
                    cout << "how could it be happened!\n";
                    throw (void*)(NULL);
                }

                /* safe zone */
                vertex->second.push_back(iter->second);
            }
        }

    private:

        typename list <pair<T, list<T> > >::iterator get_graph_elem_iter(T elem)
        {
            for (typename list <pair<T, list<T> > >::iterator iter = graph.begin(); iter != iter.end(); ++iter)
            {
                if (iter->first == elem)
                {
                    return (iter);
                }
            }
            return (graph.end());
        }


        bool find_in_graph_list(T elem)
        {
            for (typename list <pair<T, list<T> > >::iterator iter = graph.begin(); iter != iter.end(); ++iter)
            {
                if (iter->first == elem)
                {
                    return (true);
                }
            }
            return (false);
        }
        list <pair<T, list<T> > > graph;
};

#endif /* _GRAPH_H_ */
