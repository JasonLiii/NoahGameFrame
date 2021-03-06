// -------------------------------------------------------------------------
//    @FileName         ��    NFIProxyServerToGameModule.h
//    @Author           ��    LvSheng.Huang
//    @Date             ��    2012-12-15
//    @Module           ��    NFIProxyServerToGameModule
//
// -------------------------------------------------------------------------

#ifndef NFI_PROXYNET_TO_GAME_H
#define NFI_PROXYNET_TO_GAME_H

#include <iostream>
#include "NFILogicModule.h"
#include "NFIClusterClientModule.hpp"

class NFIProxyServerToGameModule
    : public  NFILogicModule
{
public:
	virtual NFIClusterClientModule* GetClusterModule() = 0;
};

#endif