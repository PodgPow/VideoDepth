//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include <tchar.h>

//---------------------------------------------------------------------
USEFORM("SDIMAIN.CPP", SDIAppForm);
USEFORM("while.cpp", Form1);
USEFORM("About.cpp", AboutBox);
//---------------------------------------------------------------------------
#include "SDIMain.h"
//----------------------------------------------------------------------------
WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	Application->Initialize();
	Application->CreateForm(__classid(TSDIAppForm), &SDIAppForm);
                 Application->CreateForm(__classid(TAboutBox), &AboutBox);
                 Application->CreateForm(__classid(TForm1), &Form1);
                 Application->Run();



	return 0;
}
//---------------------------------------------------------------------
