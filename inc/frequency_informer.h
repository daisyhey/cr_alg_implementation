

#ifndef _FREQUENCY_INFORMER_H_
#define _FREQUENCY_INFORMER_H_

#include <vector>

using std::vector;

class frequency_informer
{
    public:

        virtual double calculate_switching_cost(unsigned int f1, unsigned int f2) = 0;

        virtual double calculate_switching_delay(unsigned int f1, unsigned int f2) = 0;

        virtual bool is_frequency_available(unsigned int ident, unsigned int f) = 0;

        virtual vector<unsigned int> get_available_frequencies(unsigned int ident) = 0;

        virtual ~frequency_informer()
        {
            ;
        }
};

#endif /* _FREQUENCY_INFORMER_H_ */
