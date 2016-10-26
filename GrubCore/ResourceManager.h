#ifndef GRUB_RESOURCE_MANAGER_H
#define GRUB_RESOURCE_MANAGER_H
#include "Resource.h"
#include <type_traits>

template<typename T> class ResourceManager
{
	static_assert(std::is_base_of<Resource, T>::value, "T must be a Resource.");
	
}

#endif