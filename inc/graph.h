

#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <iostream>
#include <list>
#include <utility>

using std::ostream;
using std::cout;
using std::endl;
using std::list;
using std::pair;

template <class T1, class T2>
class Graph
{
    public:
        
        friend ostream& operator<< (ostream& os, const Graph& g)
        {
            for (typename list <pair<T2, list<T2> > >::const_iterator iter = g.key_list.begin(); 
                 iter != g.key_list.end(); 
                 ++iter)
            {
                os << iter->first << " : ";
                for (typename list<T2>::const_iterator k = iter->second.begin(); k != iter->second.end(); ++k)
                {
                    os << *k << " ";
                }
                os << endl;
            }
            os << endl;

            return (os);
        }
        
        Graph(){}
        Graph(list <pair <T2,T2> >& vertex_pairs)
        {
            for (typename list <pair <T2,T2> >::iterator iter = vertex_pairs.begin(); iter != vertex_pairs.end(); ++iter)
            {
                typename list <pair<T2, list<T2> > >::iterator vertex;

                /* if not in the graph list, add it pls */
                if (!find_in_graph_list(iter->first))
                {
                    pair<T2, list<T2> > new_key;
                    pair<T2, T1> new_node;

                    new_key.first = iter->first;
                    new_node.first = iter->first;

                    key_list.push_back(new_key);
                    node_list.push_back(new_node);
                }

                /* no worries here .... */
                vertex = get_graph_elem_iter(iter->first);
                if (vertex == key_list.end())
                {
                    /* something really bad happend here ... */;
                    cout << "how could it be happened!\n";
                    throw ("iterator cannot be found.");
                }

                /* safe zone */
                vertex->second.push_back(iter->second);
            }
        }

        T1& get_node_ref_with_key(const T2& key)
        {
            for (typename list <pair<T2, T1> >::iterator iter = node_list.begin(); iter != node_list.end(); ++iter)
            {
                if (iter->first == key)
                {
                    return (iter->second);
                }
            }
            throw ("key is not found in key list.");
        }
        
        list<T2> get_node_list() const
        {
            list<T2> r_val;
            
            for (typename list <pair<T2, T1> >::const_iterator i = node_list.begin(); i != node_list.end(); ++i)
            {
                r_val.push_back(i->first);
            }
            
            return (r_val);
        }
        
    private:

        typename list <pair<T2, list<T2> > >::iterator get_graph_elem_iter(const T2& key)
        {
            for (typename list <pair<T2, list<T2> > >::iterator iter = key_list.begin(); iter != key_list.end(); ++iter)
            {
                if (iter->first == key)
                {
                    return (iter);
                }
            }
            return (key_list.end());
        }


        bool find_in_graph_list(const T2& key) const
        {
            for (typename list <pair<T2, list<T2> > >::const_iterator iter = key_list.begin(); iter != key_list.end(); ++iter)
            {
                if (iter->first == key)
                {
                    return (true);
                }
            }
            return (false);
        }
        list <pair<T2, list<T2> > > key_list;
        list <pair<T2, T1> > node_list;
};

#endif /* _GRAPH_H_ */
