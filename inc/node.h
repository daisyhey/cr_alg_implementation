

#ifndef _NODE_H_
#define _NODE_H_

#include <list>

#include "package.h"

using std::list;

class node
{
    public:
        node(){}

        void enqueue_package(const package& p)
        {
            package_q.push_front(p);
        }

        package dequeue_package()
        {
            package temp;
            temp = package_q.back();
            package_q.pop_back();
            return (temp);
        }

        double calculate_node_cost() const
        {
            double cost = 0.0;
            for (list<package>::const_iterator iter = package_q.begin(); iter != package_q.end(); ++iter)
            {
                cost += iter->get_package_cost();
            }
            return (cost);
        }

    private:
        list<package> package_q;
};


#endif /* _NODE_H_ */
