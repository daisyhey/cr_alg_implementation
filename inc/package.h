

#ifndef _PACKAGE_H_
#define _PACKAGE_H_

#define WLAN_MAX_PACKAGE_SIZE (7981)

class package
{
    public:
        package(unsigned int size = WLAN_MAX_PACKAGE_SIZE)
            :switching_cost(0.0)
        {
            if (WLAN_MAX_PACKAGE_SIZE < size)
            {
                size = WLAN_MAX_PACKAGE_SIZE;
            }
            this->size_in_bytes = size;
        }

        unsigned int get_package_size() const
        {
            return (this->size_in_bytes);
        }

        double get_package_cost() const
        {
            return (this->switching_cost);
        }

        void add_to_cost(double cost)
        {
            this->switching_cost += cost;
        }

    private:
        unsigned int size_in_bytes;
        double switching_cost;
};

#endif /* _PACKAGE_H_ */
