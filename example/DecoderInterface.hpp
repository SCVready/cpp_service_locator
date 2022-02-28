
#ifndef DECODER_INTERFACE_HPP
#define DECODER_INTERFACE_HPP

#include <vector>
#include <cstdint>

class IDecoder
{
    public:
        virtual ~IDecoder() {};

        virtual void DecodeData(const std::vector<uint16_t>& data) = 0;
};

#endif
