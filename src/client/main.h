//==========================================================
//
//  V5C2  --  src/client/main.h
//
//==========================================================


#ifndef V5C2_CLIENT_MAIN_H
#define V5C2_CLIENT_MAIN_H 1


namespace v5c2::client
{
    void InitializeClient();

    void UninitializeClient();

    bool IsRunning();

    void DoCycle();
}

#endif // !V5C2_CLIENT_MAIN_H
