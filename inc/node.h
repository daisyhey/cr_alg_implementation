

#ifndef _NODE_H_
#define _NODE_H_

#include <vector>
#include "frequency_informer.h"

using std::vector;

class node
{
    public:
        node(unsigned int ident, frequency_informer& f_informer, unsigned int initial_freq = 0)
            :source(false), total_switching_cost(0.0), queue_size(0), freq_informer(f_informer)
        {
            this->ident = ident;
            freq_history.push_back(initial_freq);
        }

        void assign_frequency(unsigned int freq)
        {
            freq_history.push_back(freq);
        }

        double get_total_switching_cost() const
        {
            return (total_switching_cost);
        }

        unsigned int get_queue_size() const
        {
            return (queue_size);
        }

        bool is_source() const
        {
            return (this->source);
        }
        
        void set_as_source()
        {
            source = true;
        }

        node& operator= (const node& n)
        {
            *this = n;
        }
    private:

        bool source;
        unsigned int ident;
        unsigned int queue_size;
        double total_switching_cost;
        frequency_informer& freq_informer;
        vector<unsigned int> freq_history;

};


#endif /* _NODE_H_ */
