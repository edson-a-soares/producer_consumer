#ifndef Foundation_StringVector_INCLUDED
#define Foundation_StringVector_INCLUDED

#include "Foundation/IPC/String.h"
#include "boost/interprocess/containers/vector.hpp"
#include "boost/interprocess/allocators/allocator.hpp"
#include "boost/interprocess/managed_shared_memory.hpp"

namespace Foundation {
namespace IPC {


    typedef boost::interprocess::allocator<String, boost::interprocess::managed_shared_memory::segment_manager> StringAllocator;
    typedef boost::interprocess::vector<String, StringAllocator> StringVector;


} }

#endif
