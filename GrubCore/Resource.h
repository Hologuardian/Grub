#ifndef GRUB_RESOURCE_H
#define GRUB_RESOURCE_H
#include <string>

template<typename T> class Resource
{
public:
	virtual T Load(std::string file) = 0;
};

#endif