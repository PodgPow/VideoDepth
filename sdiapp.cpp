//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include <tchar.h>

//---------------------------------------------------------------------
USEFORM("SDIMain.cpp", SDIAppForm);
USEFORM("About.cpp", AboutBox);
USERES("sdiapp.res");
#include "SDIMain.h"
//----------------------------------------------------------------------------
WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	Application->Initialize();
	Application->CreateForm(__classid(TSDIAppForm), &SDIAppForm);
	Application->CreateForm(__classid(TAboutBox), &AboutBox);

     Application->Run();



	return 0;
}
//---------------------------------------------------------------------
