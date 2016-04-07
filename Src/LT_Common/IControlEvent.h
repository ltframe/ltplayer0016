#pragma once
#include "UIInfo.h"
class AFX_EXT_CLASS IControlEventS
{
public:
	IControlEventS(void)
	{};
	~IControlEventS(void)
	{

	};
	virtual bool SetButtonContorEvent(UIButtonInfo){return  true;};
	virtual bool SetSliderContorEvent(UISliderInfo){return true;}
	virtual bool SetListContorEvent(UIListInfo,UIFileListInfo){return true;}
};