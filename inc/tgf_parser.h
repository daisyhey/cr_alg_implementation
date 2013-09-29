

#ifndef _TGF_PARSER_H_
#define _TGF_PARSER_H_

#include <stdio.h>

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <utility>

using std::cout;
using std::endl;
using std::string;
using std::list;
using std::pair;
using std::ifstream;

class tgf_parser
{
    public:

        tgf_parser(string filename):f_name(filename){}

        int parse_tgf()
        {
            char buf[255];
            bool sharp_detected;
            pair<unsigned int, unsigned int> tmp;
            ifstream in;

            in.open(f_name.c_str());

            sharp_detected = false;

            while (1)
            {
                in.getline(buf, 255);
                if (!in.gcount())
                {
                    break;
                }

                if (sharp_detected)
                {
                    if (2 != sscanf(buf, "%d %d", &(tmp.first), &(tmp.second)))
                    {
                        cout << "error during edge parsing." << endl;
                        return (-1);
                    }

                    pairs.push_back(tmp);
                }
                else
                {
                    if (string(buf) == string("#"))
                    {
                        sharp_detected = true;;
                    }
                    else
                    {
                        if (2 != sscanf(buf, "%d %d", &(tmp.first), &(tmp.second)))
                        {
                            cout << "error during edge parsing." << endl;
                            return (-1);
                        }

                        if (tmp.first != tmp.second)
                        {
                            cout << "node number and label dont match." << endl;
                        }

                        if (string::npos == string(buf).find("src"))
                        {
                            source.push_back(pair<unsigned int, bool>(tmp.first,false));
                        }
                        else
                        {
                            source.push_back(pair<unsigned int, bool>(tmp.first,true));
                        }
                    }
                }
            }

            in.close();
            return (0);
        }

        list<pair<unsigned int, unsigned int> >& get_pairs()
        {
            return (pairs);
        }

        list<pair<unsigned int, bool> >& get_source()
        {
            return (source);
        }

    private:
        string f_name;
        list<pair<unsigned int, unsigned int> > pairs;
        list<pair<unsigned int, bool> > source;
};


#endif /* _TGF_PARSER_H_ */
