
#ifndef VIDEO_PLAYER_HPP
#define VIDEO_PLAYER_HPP

#include <ServiceLocator.hpp>
#include "LoggerInterface.hpp"
#include "DecoderInterface.hpp"

class VideoPlayer
{
    public:
        VideoPlayer()
        {
            ServiceLocator<ILogger>::GetService()->Log("VideoPlayer created");
        }

        ~VideoPlayer()
        {
            ServiceLocator<ILogger>::GetService()->Log("VideoPlayer destroyed");
        }

        void PresentFrame(const std::vector<uint16_t>& frame)
        {
            ServiceLocator<IDecoder>::GetService()->DecodeData(frame);
            ServiceLocator<ILogger>::GetService()->Log("Frame decoded");
        }
};

#endif