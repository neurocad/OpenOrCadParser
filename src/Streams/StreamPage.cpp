#include <cstdint>
#include <string>

#include <nameof.hpp>
#include <spdlog/spdlog.h>

#include "General.hpp"
#include "Streams/StreamPage.hpp"


void StreamPage::read(FileFormatVersion /* aVersion */)
{
    spdlog::debug(getOpeningMsg(getMethodName(this, __func__), mDs.get().getCurrentOffset()));

    auto_read_prefixes();

    readPreamble();

    std::string name = mDs.get().readStringLenZeroTerm();

    std::string pageSize = mDs.get().readStringLenZeroTerm();

    time_t createDateTime = static_cast<time_t>(mDs.get().readUint32());
    time_t modifyDateTime = static_cast<time_t>(mDs.get().readUint32());

    spdlog::debug("createDateTime = {} | modifyDateTime = {}", DateTimeToStr(createDateTime), DateTimeToStr(modifyDateTime));

    mDs.get().printUnknownData(16, std::string(__func__) + " - 1");

    uint32_t width  = mDs.get().readUint32();
    uint32_t height = mDs.get().readUint32();

    spdlog::debug("width = {} | height = {}", width, height);

    uint32_t pinToPin = mDs.get().readUint32(); //!< Pin-to-pin spacing

    spdlog::debug("pinToPin = {}", pinToPin);

    mDs.get().printUnknownData(2, std::string(__func__) + " - 2");

    uint16_t horizontalCount = mDs.get().readUint16(); //!< See 'Schematic Page Properties' -> 'Grid Reference'
    uint16_t verticalCount   = mDs.get().readUint16(); //!< See 'Schematic Page Properties' -> 'Grid Reference'

    spdlog::debug("horizontalCount = {} | verticalCount = {}", horizontalCount, verticalCount);

    mDs.get().printUnknownData(2, std::string(__func__) + " - 3");

    uint32_t horizontalWidth = mDs.get().readUint32(); //!< See 'Schematic Page Properties' -> 'Grid Reference'
    uint32_t verticalWidth   = mDs.get().readUint32(); //!< See 'Schematic Page Properties' -> 'Grid Reference'

    spdlog::debug("horizontalWidth = {} | verticalWidth = {}", horizontalWidth, verticalWidth);

    mDs.get().printUnknownData(48, std::string(__func__) + " - 4");

    uint32_t horizontalChar = mDs.get().readUint32(); //!<       See 'Schematic Page Properties' -> 'Grid Reference' ->
                                             //             'Horizontal' -> 'Alphabetic' = 1
                                             //                             'Numeric'    = 0

    spdlog::debug("horizontalChar = {}", horizontalChar);

    mDs.get().printUnknownData(4, std::string(__func__) + " - 5");

    uint32_t horizontalAscending = mDs.get().readUint32(); //!<       See 'Schematic Page Properties' -> 'Grid Reference' ->
                                                  //         'Horizontal'
                                                  //         Select 'ascending' (1) or 'decending' (0).

    spdlog::debug("horizontalAscending = {}", horizontalAscending);

    uint32_t verticalChar   = mDs.get().readUint32(); //!< See 'Schematic Page Properties' -> 'Grid Reference' ->
                                             //       'Vertical' -> 'Alphabetic' = 1
                                             //                     'Numeric'    = 0

    spdlog::debug("verticalChar = {}", verticalChar);

    mDs.get().printUnknownData(4, std::string(__func__) + " - 6");


    uint32_t verticalAscending = mDs.get().readUint32(); //!<       See 'Schematic Page Properties' -> 'Grid Reference' ->
                                                  //         'Vertical'
                                                  //         Select 'ascending' (1) or 'decending' (0).

    spdlog::debug("verticalAscending = {}", verticalAscending);

    uint32_t isMetric            = mDs.get().readUint32();
    uint32_t borderDisplayed     = mDs.get().readUint32();
    uint32_t borderPrinted       = mDs.get().readUint32();
    uint32_t gridRefDisplayed    = mDs.get().readUint32();
    uint32_t gridRefPrinted      = mDs.get().readUint32();
    uint32_t titleblockDisplayed = mDs.get().readUint32();
    uint32_t titleblockPrinted   = mDs.get().readUint32();
    // @todo XML is always 1, maybe a bug in OrCad?
    uint32_t ansiGridRefs = mDs.get().readUint32(); //!< Use ANSI grid references.
                                              //   See 'Schematic Page Properties' -> 'Grid Reference'

    spdlog::debug("isMetric            = {}", isMetric);
    spdlog::debug("borderDisplayed     = {}", borderDisplayed);
    spdlog::debug("borderPrinted       = {}", borderPrinted);
    spdlog::debug("gridRefDisplayed    = {}", gridRefDisplayed);
    spdlog::debug("gridRefPrinted      = {}", gridRefPrinted);
    spdlog::debug("titleblockDisplayed = {}", titleblockDisplayed);
    spdlog::debug("titleblockPrinted   = {}", titleblockPrinted);
    spdlog::debug("ansiGridRefs        = {}", ansiGridRefs);

    // Probably Title Blocks
    const uint16_t lenA = mDs.get().readUint16();

    spdlog::debug("lenA = {}", lenA);

    for(size_t i = 0u; i < lenA; ++i)
    {
        readStructure(); // @todo push structure
    }

    // Probably Bus
    const uint16_t len0 = mDs.get().readUint16();

    spdlog::debug("len0 = {}", len0);

    for(size_t i = 0u; i < len0; ++i)
    {
        readStructure(); // @todo push structure
    }

    const uint16_t len1 = mDs.get().readUint16();

    spdlog::debug("len1 = {}", len1);

    for(size_t i = 0u; i < len1; ++i)
    {
        readStructure(); // @todo push structure
    }

    const uint16_t lenB = mDs.get().readUint16();

    spdlog::debug("lenB = {}", lenB);

    for(size_t i = 0; i < lenB; ++i)
    {
        const std::string net = mDs.get().readStringLenZeroTerm();
        const uint32_t id = mDs.get().readUint32();

        spdlog::debug("net = {}", net);
        spdlog::debug("id  = {}", id);
    }

    const uint16_t len2 = mDs.get().readUint16();

    spdlog::debug("len2 = {}", len2);

    for(size_t i = 0u; i < len2; ++i)
    {
        readStructure(); // @todo push structure
    }

    const uint16_t len3 = mDs.get().readUint16();

    spdlog::debug("len3 = {}", len3);

    for(size_t i = 0u; i < len3; ++i)
    {
        readStructure(); // @todo push structure
    }

    const uint16_t len4 = mDs.get().readUint16();

    spdlog::debug("len4 = {}", len4);

    for(size_t i = 0u; i < len4; ++i)
    {
        readStructure(); // @todo push structure
    }

    const uint16_t len5 = mDs.get().readUint16();

    spdlog::debug("len5 = {}", len5);

    for(size_t i = 0u; i < len5; ++i)
    {
        readStructure(); // @todo push structure
    }

    const uint16_t len6 = mDs.get().readUint16();

    spdlog::debug("len6 = {}", len6);

    for(size_t i = 0u; i < len6; ++i)
    {
        readStructure(); // @todo push structure
    }

    const uint16_t len7 = mDs.get().readUint16();

    spdlog::debug("len7 = {}", len7);

    for(size_t i = 0u; i < len7; ++i)
    {
        readStructure(); // @todo push structure
    }

    const uint16_t len8 = mDs.get().readUint16();

    spdlog::debug("len8 = {}", len8);

    for(size_t i = 0u; i < len8; ++i)
    {
        readStructure(); // @todo push structure
    }

    const uint16_t len9 = mDs.get().readUint16();

    spdlog::debug("len9 = {}", len9);

    for(size_t i = 0u; i < len9; ++i)
    {
        readStructure(); // @todo push structure
    }

    const uint16_t len10 = mDs.get().readUint16();

    spdlog::debug("len10 = {}", len10);

    for(size_t i = 0u; i < len10; ++i)
    {
        readStructure(); // @todo push structure
    }

    const uint16_t len11 = mDs.get().readUint16();

    spdlog::debug("len11 = {}", len11);

    for(size_t i = 0u; i < len11; ++i)
    {
        readStructure(); // @todo push structure
    }

    if(!mDs.get().isEoF())
    {
        throw std::runtime_error("Expected EoF but did not reach it!");
    }

    spdlog::debug(getClosingMsg(getMethodName(this, __func__), mDs.get().getCurrentOffset()));
    spdlog::info(to_string());
}