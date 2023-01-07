#ifndef STRUCTT0X1F_HPP
#define STRUCTT0X1F_HPP


#include <cstdint>
#include <ostream>
#include <string>

#include <fmt/core.h>
#include <nameof.hpp>


struct StructT0x1f
{
    std::string name;
    std::string refDes;
    std::string pcbFootprint;
};


[[maybe_unused]]
static std::string to_string(const StructT0x1f& aObj)
{
    std::string str;

    str += fmt::format("{}:\n", nameof::nameof_type<decltype(aObj)>());
    str += fmt::format("{}name   = {}\n", indent(1), aObj.name);
    str += fmt::format("{}refDes = {}\n", indent(1), aObj.refDes);
    str += fmt::format("{}pcbFootprint = {}\n", indent(1), aObj.pcbFootprint);

    return str;
}


[[maybe_unused]]
static std::ostream& operator<<(std::ostream& aOs, const StructT0x1f& aVal)
{
    aOs << to_string(aVal);

    return aOs;
}


#endif // STRUCTT0X1F_HPP