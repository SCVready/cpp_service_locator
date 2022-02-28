
#ifndef DECODER_HARDWARE_IMPL_HPP
#define DECODER_HARDWARE_IMPL_HPP

#include <iostream>

#include "DecoderInterface.hpp"

class DecoderHardware : public IDecoder
{
    public:
        ~DecoderHardware() {};

        void DecodeData(const std::vector<uint16_t>& data) override
        {
            std::cout << "Hardware decoding... input data: 0x" << std::hex << data[0] << "..." << std::endl;
        }
};

#endif
