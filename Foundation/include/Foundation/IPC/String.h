#ifndef Foundation_String_INCLUDED
#define Foundation_String_INCLUDED

#include "boost/interprocess/containers/pair.hpp"
#include "boost/interprocess/containers/string.hpp"
#include "boost/interprocess/allocators/allocator.hpp"
#include "boost/interprocess/managed_shared_memory.hpp"

namespace Foundation {
namespace IPC {


    typedef boost::interprocess::allocator<char, boost::interprocess::managed_shared_memory::segment_manager> CharacterAllocator;
    typedef boost::interprocess::basic_string<char, std::char_traits<char>, CharacterAllocator> String;


} }

#endif
