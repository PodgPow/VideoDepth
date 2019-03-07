//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "while.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "cgauges"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
HRGN  hRgn = CreateEllipticRgn(0,0,185,185);
SetWindowRgn(Handle,hRgn,false);
}
//---------------------------------------------------------------------------
