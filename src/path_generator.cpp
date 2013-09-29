

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <utility>

#include "../inc/path_generator.h"

static struct option long_options[] =
{
    {"fname",          required_argument, 0, 'f'},
    {"num_of_paths",   required_argument, 0, 'n'},
    {"max_nodes",      required_argument, 0, 'm'},
    {"path_len_range", required_argument, 0, 'r'},
    {0, 0, 0, 0}
};

using std::cout;
using std::endl;
using std::list;
using std::vector;
using std::pair;
using std::ofstream;

void write_nodes(ofstream& out, list<list<unsigned int> >& paths)
{
    vector<bool> source;
    unsigned int max = 0;
    for (list<list<unsigned int > >::iterator i = paths.begin(); i != paths.end(); ++i)
    {
        for (list<unsigned int>::iterator k = i->begin(); k != i->end(); ++k)
        {
            if (*k > max)
            {
                max = *k;
            }
        }
    };

    source.assign(max + 1, false);

    for (list<list<unsigned int > >::iterator i = paths.begin(); i != paths.end(); ++i)
    {
        list<unsigned int>::iterator k = i->begin();
        source[*k] = true;
    };

    for (int i = 0; i < source.size(); ++i)
    {
        out << i << " " << i;
        if (source[i])
        {
            out << " src";
        }
        out << endl;
    }

    return;
}

void write_edges(ofstream& out, list<list<unsigned int> >& paths)
{
    list<pair<unsigned int, unsigned int> > vertex_pairs;

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

    for (list<pair<unsigned int, unsigned int> >::iterator i = vertex_pairs.begin(); i != vertex_pairs.end(); ++i)
    {
        out << i->first << " " << i->second << endl;
    }

    return;
}

int main(int argc, char* argv[])
{
    int c;

    char* fname = NULL;
    int num_of_paths = -1;
    int max_nodes = -1;
    pair<int, int> path_len_range(-1,-1);

    while (1)
    {
        int option_index = 0;

        c = getopt_long(argc, argv, "f:n:m:r:", long_options, &option_index);

        if (c == -1)
        {
            break;
        }

        switch (c)
        {
            case 'f':
                fname = optarg;
                break;
            case 'n':
                sscanf(optarg, "%d", &num_of_paths);
                break;
            case 'm':
                sscanf(optarg, "%d", &max_nodes);
                break;
            case 'r':
                sscanf(optarg, "%d-%d", &(path_len_range.first), &(path_len_range.second));
                break;
            case '?':
                break;
            default:
                abort();
                break;
        }
    }

    /* parameter validations */
    if (NULL == fname)
    {
        cout << "file name is missing." << endl;
        return (1);
    }

    if (0 > num_of_paths)
    {
        cout << "number of paths is missing." << endl;
        return (1);
    }

    if (0 > max_nodes)
    {
        cout << "max nodes is missing." << endl;
        return (1);
    }

    if ((0 > path_len_range.first) || (0 > path_len_range.second))
    {
        cout << "path len range is missing." << endl;
        return (1);
    }

    if (path_len_range.first > path_len_range.second)
    {
        cout << "invalid range." << endl;
        return (1);
    }

    if (path_len_range.second > max_nodes)
    {
        cout << "invalid range. [bigger than max node]" << endl;
        return (1);
    }

    path_generator pg((unsigned int)num_of_paths,
                      (unsigned int)max_nodes,
                      pair<unsigned int, unsigned int>((unsigned int)path_len_range.first, (unsigned int)path_len_range.second));

    list<list<unsigned int> > paths = pg.generate_paths();

    ofstream out;
    out.open(fname);

    write_nodes(out, paths);
    out << "#" << endl;
    write_edges(out, paths);
    out.close();

    return (0);
}
