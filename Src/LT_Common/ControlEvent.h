#pragma once
#include "bass.h"

class AFX_EXT_CLASS ControlEvent
{
public:
	HSTREAM stream;
	ControlEvent(HWND hwnd);
	~ControlEvent(void);
	void MusicPlay();
	static UINT  MusicPlayLink(LPVOID pParam);

};
