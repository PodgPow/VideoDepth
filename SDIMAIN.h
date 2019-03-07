//----------------------------------------------------------------------------
#ifndef SDIMainH
#define SDIMainH
//----------------------------------------------------------------------------

#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
//#include <StdCtrls.hpp>
#include <Dialogs.hpp>
#include <Menus.hpp>
#include <Vcl.Controls.hpp>
#include <Forms.hpp>
#include <Graphics.hpp>
#include <Classes.hpp>
//#include <Windows.hpp>
//#include <System.hpp>
#include <ActnList.hpp>
#include <ImgList.hpp>
#include <StdActns.hpp>
#include <ToolWin.hpp>
#include <MPlayer.hpp>

#include "cgauges.h"
#include "Gauges.hpp"

#include <GestureCtrls.hpp>
#include <GestureMgr.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <System.Actions.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.Series.hpp>
#include <VCLTee.TeEngine.hpp>

#include "Vfw.h"
#include <stdio.h>
#include <io.h>
#include <alloc.h>
#include <fcntl.h>
#include <process.h>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <sys\stat.h>
 #include <math.h>
  #include <Math.hpp>
#include "Polyncoeff.cpp"
#include "while.h"
#include "Unit2.h"
#include  <SysUtils.hpp>

 #include <iostream>

#include <Dialogs.hpp>
#include <DateUtils.hpp>

#include <Inifiles.hpp>


//----------------------------------------------------------------------------
class TSDIAppForm : public TForm
{
__published:
    TOpenDialog *OpenDialog;
    TSaveDialog *SaveDialog;
    TToolBar *ToolBar1;
    TToolButton *ToolButton1;
    TToolButton *ToolButton2;
    TActionList *ActionList1;
    TAction *FileNew1;
    TAction *FileOpen1;
    TAction *FileSave1;
    TAction *FileSaveAs1;
    TAction *FileExit1;
    TEditCut *EditCut1;
    TEditCopy *EditCopy1;
    TEditPaste *EditPaste1;
    TAction *HelpAbout1;
    TImageList *ImageList1;
    TMainMenu *MainMenu1;
    TMenuItem *File1;
    TMenuItem *FileOpenItem;
    TMenuItem *N1;
    TMenuItem *FileExitItem;
    TMenuItem *Help1;
    TMenuItem *HelpAboutItem;
	TPanel *Panel1;
	TTimer *Timer1;
	TTimer *Timer2;
	TScrollBox *ScrollBox1;
	TScrollBar *ScrollBar1;
	TOpenDialog *OpenDialog1;
	TMenuItem *N2;
    TEdit *Edit2;
    TComboBox *ComboBox1;
    TMediaPlayer *MediaPlayer1;
    TToolBar *ToolBar2;
    TToolBar *ToolBar3;
    TToolBar *ToolBar4;
    TAction *Action1;
    TMenuItem *Graph1;
    TMenuItem *MinMax1;
    TMenuItem *Mean1;
    TScrollBar *ScrollBar2;
	TChart *Chart1;
	THorizLineSeries *Series1;
	TFastLineSeries *Series2;
    TOpenDialog *OpenDialog2;
    TTimer *Timer3;
    TAction *Action2;
    TAction *Action3;
    TAction *Action4;
    TGestureManager *GestureManager1;
    TLabel *Label1;
    TTimer *Timer4;
    TLabel *Label2;
    TLabel *Label3;
        void __fastcall FileOpen1Execute(TObject *Sender);
        void __fastcall FileSave1Execute(TObject *Sender);
        void __fastcall FileExit1Execute(TObject *Sender);
        void __fastcall HelpAbout1Execute(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);

	void __fastcall Timer2Timer(TObject *Sender);
	void __fastcall ComboBox1Change(TObject *Sender);
    void __fastcall ScrollBar1Change(TObject *Sender);
    void __fastcall ScrollBar1Scroll(TObject *Sender, TScrollCode ScrollCode, int &ScrollPos);
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall RadioButton1Click(TObject *Sender);
    void __fastcall RadioButton2Click(TObject *Sender);
    void __fastcall RadioButton3Click(TObject *Sender);
    void __fastcall MinMax1Click(TObject *Sender);
    void __fastcall Mean1Click(TObject *Sender);
    void __fastcall Chart1MouseEnter(TObject *Sender);
    void __fastcall Chart1MouseLeave(TObject *Sender);
    void __fastcall FormMouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
    void __fastcall FormMouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
    void __fastcall ScrollBar1MouseEnter(TObject *Sender);
    void __fastcall ScrollBar1MouseLeave(TObject *Sender);
    void __fastcall Chart1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
    void __fastcall Chart1MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
    void __fastcall Chart1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
    void __fastcall Timer3Timer(TObject *Sender);
    void __fastcall Chart1Gesture(TObject *Sender, const TGestureEventInfo &EventInfo,
          bool &Handled);
    void __fastcall Timer4Timer(TObject *Sender);




























private:
public:
    virtual __fastcall TSDIAppForm(TComponent *AOwner);
};
//----------------------------------------------------------------------------
extern TSDIAppForm *SDIAppForm;
//----------------------------------------------------------------------------
#endif
