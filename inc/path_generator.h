

#ifndef _PATH_GENERATOR_H_
#define _PATH_GENERATOR_H_

#include <stdlib.h>
#include <time.h>

#include <list>
#include <utility>

using std::list;
using std::pair;

class path_generator
{
    public:
        path_generator(unsigned int num_of_paths = 3,
                       unsigned int max_node = 10,
                       pair<unsigned int, unsigned int> path_len_range = pair<unsigned int, unsigned int>(4,4))
            :_num_of_path(num_of_paths), _max_node(max_node), _path_len_range(path_len_range)
        {
            if (this->_path_len_range.first > RAND_MAX)
            {
                this->_path_len_range.first = RAND_MAX;
            }

            if (this->_path_len_range.second > RAND_MAX)
            {
                this->_path_len_range.second = RAND_MAX;
            }

            /* seed selection */
            srand(time(NULL));
        }

        list<list<unsigned int> > generate_paths() const
        {
            list<list<unsigned int> > r_list;

            for(unsigned int i = 0; i < this->_num_of_path; ++i)
            {
                unsigned int l = 0;
                unsigned int path_len = this->get_random_in_range();
                r_list.push_back(list<unsigned int>());


                /* NOTICE: mc - this loop may iterates infinitly.
                 *              in order to avoid that a iteration
                 *              threshold limit may be defined
                 **/
                while (l < path_len)
                {
                    unsigned int r = rand() % this->_max_node;
                    if (this->check_same_exit(r_list.back(), r))
                    {
                        continue;
                    }
                    r_list.back().push_back(r);
                    ++l;
                }
            }

            return (r_list);
        }

    private:

        bool check_same_exit(list<unsigned int>& l, unsigned int key) const
        {
            for(list<unsigned int>::const_iterator iter = l.begin(); iter != l.end(); ++iter)
            {
                if (*iter == key)
                {
                    return (true);
                }
            }

            return (false);
        }

        unsigned int get_random_in_range() const
        {
            return (unsigned int)(((double)rand() * ((double)(_path_len_range.second - _path_len_range.first) / RAND_MAX)) + _path_len_range.first);
        }

        unsigned int _num_of_path;
        unsigned int _max_node;
        pair<unsigned int, unsigned int> _path_len_range;
};

#endif /* _PATH_GENERATOR_H_ */
