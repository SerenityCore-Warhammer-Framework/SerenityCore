#ifndef SERENITY_SERVER_DATABASE
#define SERENITY_SERVER_DATABASE

#include "Defines.hpp"

class DatabaseLoader {
    DatabaseLoader(std::string const& logger, uint32 const defaultUpdateMask);
};

#endif //SERENITY_SERVER_DATABASE