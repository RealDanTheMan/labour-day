#ifndef DEBUGGING_HPP_
#define DEBUGGING_HPP_

#include <iostream>
#include <assert.h>

#ifndef NDEBUG
#define DEBUG
#endif


#ifdef DEBUG
#define D_ERR(x) (std::cerr << "[ERR] " << (x) << " at <" << __func__ << ">" << std::endl)
#define D_MSG(x) (std::cout << "[MSG] " << (x) << " at <" << __func__  << ">" << std::endl)

#else

#define D_ERR(x)
#define D_MSG(x)

#endif

#endif