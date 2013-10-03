

#ifndef _FREQUENCY_DATA_PARSER_H_
#define _FREQUENCY_DATA_PARSER_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "frequency_informer.h"

using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::vector;

class frequency_data_parser : public frequency_informer
{
    public:

        frequency_data_parser(string freq_fname, string avail_fname)
        {
            ifstream freq_in;
            unsigned int num_of_freq;

            ifstream avail_in;
            unsigned int num_of_node;
            unsigned int num_of_avail_freq;

            freq_in.open(freq_fname.c_str());
            freq_in >> num_of_freq;

            unsigned int i = 0;
            for (i = 0; i < num_of_freq * num_of_freq; ++i)
            {
                double d;

                if (!(i % num_of_freq))
                {
                    switching_cost_table.push_back(vector<unsigned int>());
                }

                if (!(freq_in >> d))
                {
                    break;
                }

                switching_cost_table[(unsigned int)(i / num_of_freq)].push_back(d);
            }

            if (i != (num_of_freq * num_of_freq))
            {
                cout << "frequency table fields are missing." << endl;
                throw (0);
            }

            freq_in.close();

            avail_in.open(avail_fname.c_str());
            avail_in >> num_of_node;
            avail_in >> num_of_avail_freq;
            for (i = 0; i < num_of_node * num_of_avail_freq; ++i)
            {
                bool b;

                if (!(i % num_of_node))
                {
                    availability_table.push_back(vector<bool>());
                }

                if (!(avail_in >> b))
                {
                    break;
                }

                availability_table[(unsigned int)(i / num_of_freq)].push_back(b);
            }

            if (i != (num_of_node * num_of_avail_freq))
            {
                cout << "availability table fields are missing." << endl;
                throw (0);
            }

            avail_in.close();

            print_switching_cost_table();
            print_availability_table();
        }

        virtual double calculate_switching_cost(unsigned int f1, unsigned int f2)
        {
            return switching_cost_table[f1][f2];
        }

        virtual double calculate_switching_delay(unsigned int f1, unsigned int f2)
        {
            return (0.0);
        }

        virtual bool is_frequency_available(unsigned int ident, unsigned int f)
        {
            return (availability_table[ident][f]);
        }

        virtual vector<unsigned int> get_available_frequencies(unsigned int ident)
        {
            return (vector<unsigned int>());
        }

    private:

        void print_switching_cost_table()
        {
            cout << "switching_cost_table:" << endl;
            for (int i = 0; i < switching_cost_table.size(); ++i)
            {
                for (int k = 0; k < switching_cost_table[i].size(); ++k)
                {
                    cout << switching_cost_table[i][k] <<  " ";
                }
                cout << endl;
            }
        }

        void print_availability_table()
        {
            cout << "availability_table:" << endl;
            for (int i = 0; i < availability_table.size(); ++i)
            {
                for (int k = 0; k < availability_table[i].size(); ++k)
                {
                    cout << availability_table[i][k] <<  " ";
                }
                cout << endl;
            }
        }

        vector<vector<unsigned int> > switching_cost_table;
        vector<vector<bool> >         availability_table;
};

#endif /* _FREQUENCY_DATA_PARSER_H_ */
