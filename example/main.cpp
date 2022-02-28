
#include <iostream>
#include <ServiceLocator.hpp>

#include "VideoPlayer.hpp"

#include "LoggerFileImpl.hpp"
#include "LoggerNetworkImpl.hpp"

#include "DecoderHardwareImpl.hpp"
#include "DecoderSoftwareImpl.hpp"

/* Static variables */
template <typename Type>
extern std::function<std::shared_ptr<Type>(void)> ServiceLocator<Type>::m_service_retriever;

int main()
{
    /* Initialise the ServiceLocator */
#if 1
    ServiceLocator<ILogger>::RegisterService([](){ 
        return std::make_shared<NetworkLogger>();
    });
#else
    ServiceLocator<ILogger>::RegisterService([](){ 
        return std::make_shared<LoggerFile>();
    });
#endif

#if 1
    ServiceLocator<IDecoder>::RegisterService([](){ 
        return std::make_shared<DecoderSoftware>();
    });
#else
    ServiceLocator<IDecoder>::RegisterService([](){ 
        return std::make_shared<DecoderHardware>();
    });
#endif

    VideoPlayer video_player;

    video_player.PresentFrame({0x10, 0x11, 0x12, 0x13});

    return 0;
}