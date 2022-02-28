
#ifndef DECODER_SOFTWARE_IMPL_HPP
#define DECODER_SOFTWARE_IMPL_HPP

#include <iostream>

#include "DecoderInterface.hpp"

class DecoderSoftware : public IDecoder
{
    public:
        ~DecoderSoftware() {};

        void DecodeData(const std::vector<uint16_t>& data) override
        {
            std::cout << "Software decoding... input data: 0x" << std::hex << data[0] << "..." << std::endl;
        }
};

#endif
