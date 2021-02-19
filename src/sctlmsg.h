#pragma once
#include <cstdint>

enum ECtlMsg : uint32_t
{
    ECtlMsgNone,
    ECtlMsgServer,
    ECtlMsgClient,
    ECtlMsgStopMux,
};

struct SCtlMsg
{
    ECtlMsg mType;
    union
    {
        struct SServer
        {
            uint16_t mPort;
            char mBindAddr[64];
        } mServer;
        struct SClient
        {
            uint16_t mPort;
            char mRemoteAddr[64];
            char mBindAddr[64];
        } mClient;
    } mSC;
};
