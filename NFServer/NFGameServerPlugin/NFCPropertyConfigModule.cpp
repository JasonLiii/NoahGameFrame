// -------------------------------------------------------------------------
//    @FileName      :    NFCPropertyConfigModule.cpp
//    @Author           :    LvSheng.Huang
//    @Date             :    2013-09-30
//    @Module           :    NFCPropertyConfigModule
//
// -------------------------------------------------------------------------

#include "NFCPropertyConfigModule.h"
#include "NFComm/NFPluginModule/NFIPluginManager.h"

bool NFCPropertyConfigModule::Init()
{
    return true;
}

bool NFCPropertyConfigModule::Shut()
{
    return true;
}

bool NFCPropertyConfigModule::Execute()
{
    return true;
}

bool NFCPropertyConfigModule::AfterInit()
{
    m_pLogicClassModule = pPluginManager->FindModule<NFILogicClassModule>();
    m_pElementModule = pPluginManager->FindModule<NFIElementModule>();

    Load();

    return true;
}

int NFCPropertyConfigModule::CalculateBaseValue(const NFJobType nJob, const int nLevel, const std::string& strProperty)
{
    if (nJob >= 0 && nJob < NFJobType::NJT_MAX)
    {
        NF_SHARE_PTR<std::string> pstrEffectData = mhtCoefficienData[nJob].GetElement(nLevel);
        if (pstrEffectData.get())
        {
            return m_pElementModule->GetPropertyInt(*pstrEffectData, strProperty);
        }
    }

    return 0;
}

void NFCPropertyConfigModule::Load()
{
    NF_SHARE_PTR<NFILogicClass> pLogicClass = m_pLogicClassModule->GetElement(NFrame::InitProperty::ThisName());
    if (pLogicClass.get())
    {
        NFList<std::string>& xList = pLogicClass->GetConfigNameList();
        std::string strData;
        bool bRet = xList.First(strData);
        while (bRet)
        {
            NF_SHARE_PTR<NFIPropertyManager> pPropertyManager = m_pElementModule->GetPropertyManager(strData);
            if (pPropertyManager.get())
            {
                int nJob = m_pElementModule->GetPropertyInt(strData, NFrame::InitProperty::Job());
                int nLevel = m_pElementModule->GetPropertyInt(strData, NFrame::InitProperty::Level());
                std::string strEffectData = m_pElementModule->GetPropertyString(strData, NFrame::InitProperty::EffectData());
                mhtCoefficienData[nJob].AddElement(nLevel, NF_SHARE_PTR<std::string>(NF_NEW std::string(strEffectData)));
            }

            bRet = xList.Next(strData);
        }
    }
}

bool NFCPropertyConfigModule::LegalLevel(const NFJobType nJob, const int nLevel)
{
    NF_SHARE_PTR<std::string> strEffectData = mhtCoefficienData[nJob].GetElement(nLevel);
    if (strEffectData.get())
    {
        return true;
    }

    return false;
}
