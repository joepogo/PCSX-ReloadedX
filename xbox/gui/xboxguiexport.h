#ifndef _H_XBOXGUIEXPORT
#define _H_XBOXGUIEXPORT

#include "..\fakeglx\fakeglx09.h"
#include "..\fakeglx\fakeglx01.h"

#ifdef __cplusplus
extern "C"
{
#endif

int InitializeXBoxGUI();
void RunXBoxGUI();
int CloseXBoxGUI();
void SetGUID3DDevice(LPDIRECT3DDEVICE8 pD3DDevice);
int IsXBoxGUIActive();
void SetXBoxGUIStartWindow(int iStartWindow);

#ifdef __cplusplus
}
#endif

#endif //_H_XBOXGUIEXPORT