#pragma once
#include <string>
#include <memory>
#include <vector>

using namespace std;

class IMux;

class CMuxFactoryImpl
{
private:
    const string mName;

private:
    static vector<CMuxFactoryImpl *> &getMuxFactoryList();
    void registerMuxFactory(CMuxFactoryImpl *);

public:
    CMuxFactoryImpl(const string &);
    static shared_ptr<IMux> createMux(const string &);
    virtual shared_ptr<IMux> createMux() = 0;
};