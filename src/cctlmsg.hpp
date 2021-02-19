#pragma once
#include <memory>
#include <string>

using namespace std;

class IMuxEvent;
class SCtlMsg;
class CMuxGeneral;

class CCtlMsg
{
private:
    CMuxGeneral &mMux;
    int mSk;
    int mPort;
    string mRemoteAddr;
    string mBindAddr;

    void makeClient();
    void makeServer();

public:
    CCtlMsg(CMuxGeneral &);
    ~CCtlMsg();
    void handleCtlMsg(const SCtlMsg &);
    bool makeServerCtlMsg(uint16_t, const string &);
    bool makeClientCtlMsg(uint16_t, const string &, const string &);
};
