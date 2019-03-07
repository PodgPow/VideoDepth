//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include <tchar.h>

//---------------------------------------------------------------------
USEFORM("SDIMAIN.CPP", SDIAppForm);
USEFORM("About.cpp", AboutBox);
//---------------------------------------------------------------------------
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
