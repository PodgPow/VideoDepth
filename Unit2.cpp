//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm2::FormCreate(TObject *Sender)
{
        unsigned char x;
SetWindowLong(Handle, GWL_EXSTYLE, GetWindowLong(Handle, GWL_EXSTYLE) | WS_EX_LAYERED);
for (x = 0;x<255;x+=5)
        {
   //     SetLayeredWindowAttributes(Handle, (UINT)0, x, LWA_ALPHA);
        Application->ProcessMessages();
        Sleep(1);
        }
//SetLayeredWindowAttributes(Handle, 0, 255, LWA_ALPHA);
}
//---------------------------------------------------------------------------
