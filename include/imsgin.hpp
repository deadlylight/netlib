#pragma once

class IMsgIn
{
public:
    virtual ~IMsgIn() = default;
    virtual uint32_t getSize() = 0;
};
