
class ISyncTcpConn
{
    shared_ptr<IMsg> getMsg(bool);
    bool writeMsg();
};
