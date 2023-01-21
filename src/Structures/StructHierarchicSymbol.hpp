#ifndef STRUCTHIERARCHICSYMBOL_HPP
#define STRUCTHIERARCHICSYMBOL_HPP


#include <cstdint>
#include <optional>
#include <ostream>
#include <string>

#include <fmt/core.h>
#include <nameof.hpp>

#include "CommonBase.hpp"
#include "General.hpp"


class StructHierarchicSymbol : public CommonBase
{
public:

    StructHierarchicSymbol(DataStream& aDs) : CommonBase{aDs}
    { }

    std::string to_string() const override;

    void read(FileFormatVersion aVersion = FileFormatVersion::Unknown) override;

};


[[maybe_unused]]
static std::string to_string(const StructHierarchicSymbol& aObj)
{
    std::string str;

    str += fmt::format("{}:\n", nameof::nameof_type<decltype(aObj)>());
    // str += fmt::format("x1     = {}\n", aObj.x1);
    // str += fmt::format("y1     = {}\n", aObj.y1);

    return str;
}


inline std::string StructHierarchicSymbol::to_string() const
{
    return ::to_string(*this);
}


[[maybe_unused]]
static std::ostream& operator<<(std::ostream& aOs, const StructHierarchicSymbol& aVal)
{
    aOs << to_string(aVal);

    return aOs;
}


#endif // STRUCTHIERARCHICSYMBOL_HPP