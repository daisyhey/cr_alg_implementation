

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
    private:
        unsigned int size_in_bytes;
        double switching_cost;
};

#endif /* _PACKAGE_H_ */
