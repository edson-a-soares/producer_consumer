#ifndef Foundation_Http_ResourceFactoryRoutingTableInterface_INCLUDED
#define Foundation_Http_ResourceFactoryRoutingTableInterface_INCLUDED

#include <string>
#include <memory>
#include "Foundation/Foundation.h"
#include "Foundation/Http/ResourceFactoryInterface.h"

namespace Foundation {
namespace Http {


    class API ResourceFactoryRoutingTableInterface
    {
    public:
    	virtual ~ResourceFactoryRoutingTableInterface() = default;
        virtual std::unique_ptr<ResourceFactoryInterface> createResourceFactory(const std::string & resourceName) = 0;

    };


} }

#endif
