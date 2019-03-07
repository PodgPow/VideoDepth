//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "SDIMain.h"
#include "About.h"

#pragma resource "*.dfm"
     unsigned number_char_Name_Well;
   char *NameWell;
	AnsiString Vers_Prog = "Version 1.0";


//---------------------------------------------------------------------
int iFileHandleDepth = -2;

 AnsiString   Depth_data = "";
 AnsiString   DEPTHn = "";
 AnsiString Path_File = "";
  AnsiString Path_FileS = "";
  AnsiString Path_File_AVI = "";

    TIniFile *ini;

  double *Depth_t, *Data_Graph_temp, *Data_temp,*Depth_Graph_temp, *Speed_Graph_temp ;
  double *Time_Sec_t, * NewTime_Sec;
  double *Time_nsec, *Speed;
  double *All_Count_ns_Sum;
  int *Time_Msec;
  int size_arr;
  short int Time_Milsec;
  int index_data;
  int Unix_TimeSecLastWriteFile_AVI;
  int LengthTimeAVI, LengthTimeAVI_TempForBegin, Unix_TimeSecBeginFile_AVI;
  int NunberFrameAVI;
  int IndexForTimeDepth;

    FILETIME  ftCreationTime,ftLastAccessTime,ftLastWriteTime;

  #pragma pack (1)
  struct  Data_FileRVH {
  BYTE Id;
  int Count_Depth;      //для счтетчика меток глуб. в короб.
  int Depth;            // глубина с учетом забиваемой оператором
  unsigned int Time_betw_Depth;
  unsigned int Time_Sec;
  unsigned int Time_Milsec;
   };
 struct Data_FileRVH Data_File_Depth1[1000];
 struct Data_FileRVH Data_File_Depth_RVH;
 #pragma pack (8)

  #pragma pack (1)
 struct head  {
  int numb_well;
  int depth_begin;
};
head head_smd;
  #pragma pack (8)

  #pragma pack (1)
  struct  Data_File {
  int Depth;
  int Time_Sec;
  unsigned int Time_Milsec;
				  };
  Data_File Data_File_Depth;
  #pragma pack (8)


   int index_test_depth=0; int index_test_depth1;

//----------------------------------------------------------------------
 AnsiString File_AVI_Data = "";
  AnsiString File_AVI_Data_1 = "";
   AnsiString PathFileO_SMD = "";
      AnsiString PathFileO_AVI = "";
 PAVIFILE pfile;
 long Result=0;
 //char File_AVI_Data_1 [100];
 long hWndC;

  int ms; // время звучания трека, мсек
  int Tr_leng, Track;
  int Scale_Decim;

  int index_max_data, index_min_data;

 int i=0, i1=0, i2=0, i3=0, i_end, i_max, i_min;
   double Depth_Begin;
   double Pos_scroll_bar;

   double Temp_Hand_Min_Chart, Temp_Hand_Max_Chart;

   double MinBottomAxis, MaxBottomAxis, MinBottomAxis_inc, MaxBottomAxis_inc, MaxBottomAxis_Ish, MinBottomAxis_Ish;

  bool   Flag_Comb_Chang =false;
  bool Flag_Scroll = false;
  bool Flag_Max = false;
  bool Flag_Max_Min = false;
  bool Flag_Chart_Scroll=false;
  bool Flag_ScrBar_Scroll=false;
  bool Flag_Chart1GetAxisLabel = false;
  bool Flag_MouseDown=false;
  bool Flag_Chart1MouseMove=false;
  bool FlagCurPosSeries = false;
  bool   FlagOpenSMD=false;
  bool   FlagOpenAVI=false;
  bool   Flag_SyncTimeEnd = false;
  bool Flag_LeftMouse = false;
  bool Flag_RightMouse =false;
  bool Flag_MiddleMouse = false;

  long int length_f;

  int IndexBeginTimeSec; //begin Time Sec Depth
  int MedPosBegin; // begin posic MediaPlay
  int TimeBeginMediaPlay_ms;
  int DiffForBeginMedPlay;

   int i_n=0;


 double Height_Ch, Height_Ch_Ish;
 double Coef_Scroll;

 int max_number_Data =2000;
 int	Width_Panel, Height_Panel;
 int    Width_Video, Height_Video;
double min_pos, max_pos, min_pos1, max_pos1, min_pos_ish, max_pos_ish;
 double Kef_Scal;
 double Scrol_Pos;

 int indexGet_Cur_Chart;

 double MinValueData;

 double data_min, data_max;
int index_min,index_max;

 double koef;

  double Get_Cur_Chart_X,Get_Cur_Chart_Y;

	SYSTEMTIME  systime;
	UINT16 Milisecond;
	UINT64 All_Time;

  long  double Time_ns_Period;
  bool FLAG_END_DATA_inFILE_RVH = false;

//   #define Time_ns_Period    0.00048088 // 0.00034866 // время периода счетчика процессора в ms для нашего компьютера регистрации
   //(нужно в дальнейшем считывать значение по ситемному таймеру - изменить формат файла smd)

//format - RVH   --------------------------------------------------------------------
// unsigned int numberCharNameWell;
// char *charNameWell;
  // unsigned int Speed_Dev;

	unsigned int Time_Sec;
//--------------------------------------------------------------------
 TDateTime FileTimeToDateTime(FILETIME *lpftime)
{
    FILETIME  localfiletime;
  // SYSTEMTIME  systime;
    FileTimeToLocalFileTime(lpftime,&localfiletime);
    FileTimeToSystemTime(&localfiletime,&systime);
    return(TDateTime(systime.wYear,  systime.wMonth, systime.wDay)+
	TDateTime(systime.wHour,  systime.wMinute,
	systime.wSecond, systime.wMilliseconds));
	}


//--------------------------------------------------------------------
TDateTime __fastcall GetCurrentDateTime()
{
  SYSTEMTIME SystemTime;
  GetLocalTime(&SystemTime);
  return SystemTimeToDateTime(SystemTime);
}
//-----------------------------------------------------------

   AnsiString File_Name = "";
    AnsiString  FileInfo = "";

//---------------------------------------------------------------------
 void __fastcall SetThumbTab()
{
  // Get the minimum (default) size of the thumb tab.
  int MinHeight = GetSystemMetrics(SM_CYVTHUMB);
  // Get the size of the scroll bar track
  int TrackHeight = SDIAppForm->ScrollBar1->ClientHeight - 2*GetSystemMetrics(SM_CYVSCROLL);
  // Set PageSize to represent the visible portion of the scrolling range.
  SDIAppForm->ScrollBar1->PageSize = TrackHeight/(SDIAppForm->ScrollBar1->Max - SDIAppForm->ScrollBar1->Min + 1);
  // Do not let the thumb tab get too small.
  if (SDIAppForm->ScrollBar1->PageSize < MinHeight)
  SDIAppForm->ScrollBar1->PageSize = MinHeight;
}



//----------------------------------------------------------------------


TSDIAppForm *SDIAppForm;
//---------------------------------------------------------------------
__fastcall TSDIAppForm::TSDIAppForm(TComponent *AOwner)
	: TForm(AOwner)
{
 
  SDIAppForm->Visible=false;

  SDIAppForm->Caption = "Video to Depth ("+Vers_Prog+")";

  //ComboBox1->


}
//---------------------------------------------------------------------


void __fastcall TSDIAppForm::FileOpen1Execute(TObject *Sender)
{


///Time_Sec = DateTimeToUnix(GetCurrentDateTime());

FLAG_END_DATA_inFILE_RVH = false;

if(FlagOpenAVI)MediaPlayer1->Stop();
  MediaPlayer1->Enabled=false;
  FlagOpenSMD=false;
  FlagOpenAVI=false;
   Flag_SyncTimeEnd = false;

  Panel1->Visible=false;


  ini = new TIniFile( ChangeFileExt( Application->ExeName, ".INI" ) );

          ini->ReadString ( "Path", "Caption", Caption );
 PathFileO_SMD = ini->ReadString ( "Path", "open_smd", Caption );
// PathFileS = ini->ReadString ( "Path", "save", Caption );

   delete ini;

OpenDialog->InitialDir=PathFileO_SMD;
//OpenDialog->Filter = "SMD Files (*.smd)|*.smd";


  if(OpenDialog->Execute())
  {

  delete [] Depth_t;
  delete [] Time_Sec_t;
  delete [] Time_nsec;
  delete [] Speed;
    delete [] Time_Msec;
     delete []  NewTime_Sec;
      delete []  All_Count_ns_Sum;
//  delete [] Data_Graph_temp;
 // delete [] Depth_Graph_temp;
  //   delete [] Data_temp;

  Flag_Comb_Chang =false;

  Series1->Clear() ;
 // ScrollBar1->Enabled=true;


   Depth_data = OpenDialog -> FileName;

   //-------------------------------------------------
/*
  HANDLE  hAVI_File=(HANDLE)FileOpen(Depth_data,fmOpenRead);


  GetFileTime(hAVI_File,&ftCreationTime,&ftLastAccessTime,&ftLastWriteTime);

FileTimeToDateTime(&ftLastWriteTime);

Unix_TimeSecLastWriteFile_AVI = DateTimeToUnix(TDateTime(systime.wYear,  systime.wMonth, systime.wDay)+TDateTime(systime.wHour,  systime.wMinute,
systime.wSecond, systime.wMilliseconds));

	FileClose((int)  hAVI_File);
  */
   //-------------------------------------------------




   DEPTHn=ExtractFileName(Depth_data);
   Path_File = ExtractFilePath(Depth_data);
	SDIAppForm->Caption = "Video to Depth ("+Vers_Prog+")            "+Depth_data+"";


   ini = new TIniFile(ChangeFileExt( Application->ExeName, ".INI" ) );
   ini->WriteString ( "Path", "open_smd", Path_File );

   delete ini;



  // MaskEdit1->Text="     "+Depth_data;
   iFileHandleDepth = open(Depth_data.c_str(), O_RDONLY|O_BINARY);


    read (iFileHandleDepth, &number_char_Name_Well, sizeof(number_char_Name_Well));
    NameWell=new char [number_char_Name_Well];

    read (iFileHandleDepth, NameWell, number_char_Name_Well);


   //---------------------------------------------------------
 //  ZeroMemory(Data_File_Depth1, sizeof(Data_File_Depth1));
 /*
 index_test_depth=0;
  mark_www:
   read (iFileHandleDepth, &Data_File_Depth1, sizeof(Data_File_Depth1));
   index_test_depth++;
 //  if(index_test_depth>75){
 //  index_test_depth1=index_test_depth/100;

   //}
  // if(eof(iFileHandleDepth)==0) goto mark_www;
   if(eof(iFileHandleDepth)==0) goto mark_www;
   */
	//  if(eof(iFileHandleDepth)==0&&Data_File_Depth1.Id==0x77) goto mark_www;
   //-----------------------------------------------------------
   //    Label1->Caption=index_test_depth1;

      length_f = filelength(iFileHandleDepth);
	  length_f=length_f - sizeof(head_smd);
	if(OpenDialog->FilterIndex==1)   length_f=length_f/sizeof(Data_File_Depth);
		if(OpenDialog->FilterIndex==2)   length_f=length_f/sizeof(Data_File_Depth_RVH);
	  size_arr=length_f-1;



   //----------------------------------------------------------------
 /*
     read (iFileHandleDepth, &head_smd, sizeof(head_smd));
  index_data=0;
   mark_n:
   read (iFileHandleDepth, &Data_File_Depth, sizeof(Data_File_Depth));
	  if(index_data==0)Depth_Begin=Data_File_Depth.Depth/100;
   index_data++;

   if(eof(iFileHandleDepth)==0) goto  mark_n;
	size_arr=index_data-1;
  */

	 Depth_t = new double [size_arr];
	 Time_Sec_t = new double [size_arr];
     NewTime_Sec = new double [size_arr];
	 Time_nsec = new double [size_arr];
	 Speed = new double [size_arr];
	 Time_Msec = new int [size_arr];
      All_Count_ns_Sum = new double [size_arr];

	if(size_arr>Chart1->Height)ScrollBar1->Max=size_arr;//-(Chart1->Height);
	else ScrollBar1->Enabled=false;


ComboBox1->ItemIndex=0;

   Height_Ch=(double)size_arr/100; ScrollBar1->Enabled=false; ScrollBar1->Visible=false;    //all


  // ScrollBar1->PageSize=Height_Ch;


//--------------------------------------------------------------

   Form1->Show() ;

  if(OpenDialog->FilterIndex==1)
  {
 lseek(iFileHandleDepth,0L,SEEK_SET);
  read (iFileHandleDepth, &head_smd, sizeof(head_smd));
   }
	index_data=0;
	All_Count_ns_Sum[index_data]=0;
	  //begin cycle========================================================================================================
   mark_n1:


   if(OpenDialog->FilterIndex==1)
   {
   read (iFileHandleDepth, &Data_File_Depth, sizeof(Data_File_Depth));
	Depth_t[index_data]=Data_File_Depth.Depth; 	Depth_t[index_data]=Depth_t[index_data]/100;

	Time_Sec_t[index_data]=Data_File_Depth.Time_Sec;
	NewTime_Sec[index_data]=Time_Sec_t[index_data]-Time_Sec_t[0];
	Time_nsec[index_data]=Data_File_Depth.Time_Milsec;
	}

	if(OpenDialog->FilterIndex==2)
   {
   read (iFileHandleDepth, &Data_File_Depth_RVH, sizeof(Data_File_Depth_RVH));
   if(Data_File_Depth_RVH.Id==0x77)
	{
	 Depth_t[index_data]=Data_File_Depth_RVH.Depth; 	Depth_t[index_data]=Depth_t[index_data]/100;
	 Time_Sec_t[index_data]=Data_File_Depth_RVH.Time_Sec;
	 NewTime_Sec[index_data]=Time_Sec_t[index_data]-Time_Sec_t[0];
	 Time_nsec[index_data]=Data_File_Depth_RVH.Time_Milsec;
	 Speed[index_data] = 0.01*3600000/((double)Data_File_Depth_RVH.Time_betw_Depth/250);
	 }
	 else
		{
		FLAG_END_DATA_inFILE_RVH=true;
		}
	}
//формирование массива милисекунд с начала записи первой метки
	if(index_data>0)
		 {
		   if(Time_Sec_t[index_data]>= Time_Sec_t[index_data-1])
		   {
		   if(Time_nsec[index_data]>Time_nsec[index_data-1])
			   {
			   All_Count_ns_Sum[index_data] = 1000*(Time_Sec_t[index_data]- Time_Sec_t[index_data-1]) +    //ЕСЛИ прошло между метками больше секунды
			   All_Count_ns_Sum[index_data-1] +(Time_nsec[index_data]-Time_nsec[index_data-1]);

			   //Speed[index_data] = (double)(0.01*3600/(double)((double)(Time_nsec[index_data]-Time_nsec[index_data-1])/1000)) ;
			//   Time_Msec[index_data]=Time_Msec[index_data-1]+(Time_nsec[index_data]-Time_nsec[index_data-1])*Time_ns_Period;
			   }
			   else
				   {
			  //     Time_Msec[index_data] = Time_Msec[index_data-1]+((4294967296L - Time_nsec[index_data-1])+Time_nsec[index_data])*Time_ns_Period;
				  if(OpenDialog->FilterIndex==1) All_Count_ns_Sum[index_data] = All_Count_ns_Sum[index_data-1] + ((4294967296L - Time_nsec[index_data-1])+Time_nsec[index_data]);
			  if(OpenDialog->FilterIndex==2)
										  {
										  All_Count_ns_Sum[index_data] = 1000*(Time_Sec_t[index_data]- Time_Sec_t[index_data-1]-1) +   //ЕСЛИ прошло между метками больше секунды
										  All_Count_ns_Sum[index_data-1] + ((1000 - Time_nsec[index_data-1])+Time_nsec[index_data]);
										  //Speed[index_data] = (double)(0.01*3600/(double)( (double)((1000 - Time_nsec[index_data-1])+Time_nsec[index_data])/1000));
										  }
				   }
			}
			else FLAG_END_DATA_inFILE_RVH=true;
		 }
		 else Time_Msec[index_data]=0;


 //  size_arr=index_data-1;
 if(index_data>2998)
 {
	 index_data=index_data;
 }
  index_data++;
 //ProgressBar1->Position=(100 * index_data)/size_arr;

  Form1->CGauge1->Progress=(100 * index_data)/size_arr;
  //if(eof(iFileHandleDepth)==0) goto  mark_n1;
   if(eof(iFileHandleDepth)==0&&!FLAG_END_DATA_inFILE_RVH) goto  mark_n1;
   index_data -=2;
   //if(FLAG_END_DATA_inFILE_RVH)
   size_arr =  index_data;
   //end cycle========================================================================================================

 // Form1->CGauge1->Visible=false;
 //для каждого компьютера период внутреннего таймера процессора индивидуален, поэтому определяем:
if(OpenDialog->FilterIndex==1) {
			   Time_ns_Period = (Time_Sec_t[index_data-1]-Time_Sec_t[0])/All_Count_ns_Sum[index_data-1];
			  for(i=0;i<=index_data-1;i++)  Time_Msec[i]= All_Count_ns_Sum[i]*(Time_ns_Period*1000);
							   }
if(OpenDialog->FilterIndex==2) for(i=0;i<=index_data;i++)  Time_Msec[i]= All_Count_ns_Sum[i];
  Form1->Close() ;



	  Mean1->Enabled=true;
 MinMax1->Enabled=true;

//Chart1->BottomAxis->Maximum = MaxValue(Time_nsec,size_arr);
// Chart1->BottomAxis->Minimum = MinValue(Time_nsec,size_arr);



 if(OpenDialog->FilterIndex==1)
 {
MinBottomAxis_Ish=MinValue(Time_nsec,size_arr);
MaxBottomAxis_Ish=MaxValue(Time_nsec,size_arr);

MinBottomAxis=MinBottomAxis_Ish;
MaxBottomAxis=MaxBottomAxis_Ish;

MinBottomAxis_inc=MinBottomAxis/100;
MaxBottomAxis_inc=MaxBottomAxis/100;
 }
 if(OpenDialog->FilterIndex==2)
 {
MinBottomAxis_Ish=0;
MaxBottomAxis_Ish=10000;

MinBottomAxis=MinBottomAxis_Ish;
MaxBottomAxis=MaxBottomAxis_Ish;

//MinBottomAxis_inc=MinBottomAxis/100;
//MaxBottomAxis_inc=MaxBottomAxis/100;
 }
 Chart1->BottomAxis-> SetMinMax(MinBottomAxis,MaxBottomAxis);

          Coef_Scroll =((Height_Ch*100)/Height_Ch_Ish);
          Scale_Decim =ceil(Coef_Scroll);

     i_max = size_arr;
  i_min = 0;

        i_end=0;

  if(OpenDialog->FilterIndex==1)
  {
   if(MinMax1->Checked)i_end = MinMaxDataArray(Time_nsec,Depth_t,Data_Graph_temp,Depth_Graph_temp,i_min,i_max,Scale_Decim);
   if(Mean1->Checked)i_end = DecimDataArray(Time_nsec,Depth_t,Data_Graph_temp,Depth_Graph_temp,i_min,i_max,Scale_Decim);
  }

  if(OpenDialog->FilterIndex==2)
  {
   if(MinMax1->Checked)i_end = MinMaxDataArray(Speed,Depth_t,Data_Graph_temp,Depth_Graph_temp,i_min,i_max,Scale_Decim);
   if(Mean1->Checked)i_end = DecimDataArray(Speed,Depth_t,Data_Graph_temp,Depth_Graph_temp,i_min,i_max,Scale_Decim);
  }

 Series1->Clear() ;

Chart1->LeftAxis->SetMinMax(Depth_t[i_min],Depth_t[i_max]);

																		   //     for(i=0; i<=i2-1;i++)  Series1->AddXY(Data_Graph_temp[i],Depth_Graph_temp[i]);
		Series1->AddArray(Data_Graph_temp,(i_end),Depth_Graph_temp,(i_end));



ComboBox1->Enabled=true;
Flag_Comb_Chang =false;
FlagOpenSMD=true;

  }   //   if(OpenDialog->Execute())
	   else
     {
     Application->MessageBox(L"File SMD can't open", L"Message", MB_OK);
     return;
     }




 //--------------------------------------------------------------------------------
   ini = new TIniFile( ChangeFileExt( Application->ExeName, ".INI" ) );

          ini->ReadString ( "Path", "Caption", Caption );
          ini->ReadString ( "Path", "open_smd", Caption );
   PathFileO_AVI = ini->ReadString ( "Path", "open_avi", Caption );
   delete ini;

  OpenDialog2->InitialDir=PathFileO_AVI;
  OpenDialog2->Filter = "AVI Files (*.avi)|*.avi";
 //--------------------------------------------------------------------------------



  if(OpenDialog2->Execute())
  {
       	MediaPlayer1->Close();
	   MediaPlayer1->AutoEnable = false;
	   MediaPlayer1->EnabledButtons = TButtonSet();
	File_AVI_Data = OpenDialog2 -> FileName;
       Path_File_AVI = ExtractFilePath(File_AVI_Data);
 //--
       ini = new TIniFile(ChangeFileExt( Application->ExeName, ".INI" ) );
      ini->WriteString ( "Path", "open_avi", Path_File_AVI );
        delete ini;

 //--

  //-------------------------------------------------------------------------------------

  HANDLE  hAVI_File=(HANDLE)FileOpen(File_AVI_Data,fmOpenRead);

  if((int)hAVI_File!=0xFFFFFFFF)
  {
  GetFileTime(hAVI_File,&ftCreationTime,&ftLastAccessTime,&ftLastWriteTime);
    /*
    FileInfo=File_AVI_Data;
	FileInfo+="\nCreation  Time:"+ FormatDateTime("c",FileTimeToDateTime(&ftCreationTime));
 	FileInfo+="\nCreation  Time (ms):"+FormatDateTime("zzz",FileTimeToDateTime(&ftCreationTime));

	FileInfo+="\nLast  Access  Time:"+
	FormatDateTime("c",FileTimeToDateTime(&ftLastAccessTime));
	FileInfo+="\nLast  Access  Time (ms):"+
	FormatDateTime("zzz",FileTimeToDateTime(&ftLastAccessTime));
	FileInfo+="\nLast  Write  Time:"+
	FormatDateTime("c",FileTimeToDateTime(&ftLastWriteTime));
	FileInfo+="\nLast  Write  Time (ms):"+
	FormatDateTime("zzz",FileTimeToDateTime(&ftLastWriteTime));
 	Label1->Caption=FileInfo;
      */



FileTimeToDateTime(&ftLastWriteTime);

Unix_TimeSecLastWriteFile_AVI = DateTimeToUnix(TDateTime(systime.wYear,  systime.wMonth, systime.wDay)+TDateTime(systime.wHour,  systime.wMinute,
systime.wSecond, systime.wMilliseconds));
//Unix_TimeSecLastWriteFile_AVI +=  4191;// temp for test

// Milisecond = systime.wMilliseconds;
//  All_Time=All_Time+Milisecond;


	FileClose((int)  hAVI_File);


	 MediaPlayer1->FileName=File_AVI_Data;

	MediaPlayer1->Open();
	MediaPlayer1->Wait = true;


	Width_Video = MediaPlayer1->DisplayRect.Width();
	Height_Video = MediaPlayer1->DisplayRect.Height();

	koef=(double)Width_Video/(double)Height_Video;
	Panel1->Align=alCustom;

	Panel1->Width=(double)Height_Panel*koef - ScrollBar1->Width;
	Panel1->Height=Height_Panel;
	//Panel1->Left=Panel2->Width;
	Panel1->Left=ScrollBox1->Width;
	Panel1->Top=ToolBar1->Height;



	ScrollBox1->Repaint();
  	Panel1->Repaint();

   ScrollBox1->Width=SDIAppForm->Width-Panel1->Width;
   //Panel2->Width=SDIAppForm->Width-Panel1->Width;
   Panel1->Align=alClient;



	//MediaPlayer1->DisplayRect=Panel1->ClientRect.Normalize(); //fitting on the form
	MediaPlayer1->DisplayRect=Panel1->ClientRect;

	Timer1->Enabled=true;
		MediaPlayer1->Wait = false;


	/*
	MediaPlayer1->EnabledButtons =
				TButtonSet() <<
				TMPBtnType::btPause <<
				TMPBtnType::btStop <<
				TMPBtnType::btPlay;
	  */


 MediaPlayer1->AutoEnable = true;
 MediaPlayer1->TimeFormat = tfMilliseconds;//tfTMSF; tfFrames

LengthTimeAVI = MediaPlayer1->Length;
LengthTimeAVI_TempForBegin=ceil(((double)LengthTimeAVI/1000));

Unix_TimeSecBeginFile_AVI = (Unix_TimeSecLastWriteFile_AVI - LengthTimeAVI_TempForBegin);


MediaPlayer1->TimeFormat = tfFrames;
//LengthTimeAVI = MediaPlayer1->Length;  //не совпадает с фактич. у брелка (у фонарика совпад) - видимо в брелке обрез. посекундно, а в фонарике не обрез.
MediaPlayer1->Next();     //	Timer3->Enabled=true;      // поэтому эта строка
//NunberFrameAVI = MediaPlayer1->Position;

//MediaPlayer1->TimeFormat = tfMilliseconds;

//Label2->Caption = LengthTimeAVI;

 //Label3->Caption = NunberFrameAVI;

 FlagOpenAVI=true;

    } //  if(hFile!=0xFFFFFFFF)
     else
     {
     Application->MessageBox(L"File AVI is already open in another application", L"Message", MB_ICONSTOP);
     return;
	 }

  }

 //------------------------------------------------------------------------------------

  if(FlagOpenAVI&&FlagOpenSMD)
 {
  if (
  (Time_Sec_t[0]<Unix_TimeSecBeginFile_AVI&&Time_Sec_t[size_arr]>Unix_TimeSecBeginFile_AVI)||
  (Time_Sec_t[0]>Unix_TimeSecBeginFile_AVI&&Time_Sec_t[0]<Unix_TimeSecLastWriteFile_AVI)||
  (Time_Sec_t[0]<Unix_TimeSecBeginFile_AVI&&Time_Sec_t[size_arr]>Unix_TimeSecLastWriteFile_AVI)||
  (Time_Sec_t[size_arr]>Unix_TimeSecBeginFile_AVI&&Time_Sec_t[size_arr]<Unix_TimeSecLastWriteFile_AVI) )
   {
 Panel1->Visible=true;

  MediaPlayer1->Enabled=true;
  //	Panel1->Repaint();

  if(Time_Sec_t[0]< Unix_TimeSecBeginFile_AVI)
	 {
	   i=0;
	   while(Time_Sec_t[i]< Unix_TimeSecBeginFile_AVI&&i<size_arr) i++ ;
	   IndexForTimeDepth=i;
	   i=0;
	 }
    //Time_ns_Period;
   if(Time_Sec_t[0]== Unix_TimeSecBeginFile_AVI) IndexForTimeDepth =0;



    //---------------while change sec
	 i=IndexForTimeDepth;
    while((Time_Sec_t[i+1]-Time_Sec_t[i])==0&&i<size_arr) i++ ;
	 if(i<size_arr&&Time_Msec[i]<500) IndexBeginTimeSec=i+1;   // если меньше 0.5 секунды начинаем со следующей секунды
     else IndexBeginTimeSec = IndexForTimeDepth;

	Timer3->Enabled=true;
	 //----------------

  } //   if((Time_Sec_t[0]<Unix_TimeSecBeginFile_AVI&&Time_Sec_t[size_arr]>Unix_TimeSecBeginFile_AVI)||
         else
	 {
     Panel1->Visible=false;
	 MediaPlayer1->Enabled=false;
	 Application->MessageBox(L"Files SMD and AVI do not correspond to each other!\nSelect another files, please.", L"Error select files", MB_ICONSTOP);
     return;
	 }

  }
 	Panel1->Repaint();
//------------------------------------------------------------------------------------


  /*
  if(OpenDialog->Execute())
  {
			File_AVI_Data = OpenDialog -> FileName;
	 //		AVIFileInit();
	 /*		AVIFileInit();    CoInitialize(NULL);
			i=AVIERR_BADFORMAT;
			i1=AVIERR_MEMORY;
			i2=AVIERR_FILEREAD;
			i3=AVIERR_FILEOPEN;
			i4=REGDB_E_CLASSNOTREG;
			i5=i+i1+i2+i3+i4;    */


 /*
			Result = AVIFileOpenA(&pfile, File_AVI_Data.c_str(), OF_SHARE_DENY_READ, NULL);
  }
	*/
}
//---------------------------------------------------------------------------

void __fastcall TSDIAppForm::FileSave1Execute(TObject *Sender)
{
 for(i=0;i<=max_number_Data;i++)
 {
Series1->AddXY(i,i1);i1++; //  ScrollBar1->Max = Series1->Count()-5;
 }

  //SaveDialog->Execute();
}
//---------------------------------------------------------------------------


void __fastcall TSDIAppForm::FileExit1Execute(TObject *Sender)
{
  Close();        
}
//---------------------------------------------------------------------------

void __fastcall TSDIAppForm::HelpAbout1Execute(TObject *Sender)
{
  AboutBox->ShowModal();
}
//---------------------------------------------------------------------------


void __fastcall TSDIAppForm::Timer3Timer(TObject *Sender)
{
  	Timer3->Enabled=false;
 NunberFrameAVI = MediaPlayer1->Position;
 MediaPlayer1->Previous();
// 	Panel1->Repaint();

 if(FlagOpenAVI&&FlagOpenSMD)
 {

 //  )
 // if((Time_Sec_t[0]<Unix_TimeSecBeginFile_AVI&&Time_Sec_t[size_arr]>Unix_TimeSecBeginFile_AVI)||
 // (Time_Sec_t[0]>Unix_TimeSecBeginFile_AVI&&Time_Sec_t[size_arr]<Unix_TimeSecLastWriteFile_AVI))
  // {
	if(Time_Sec_t[0]>Unix_TimeSecBeginFile_AVI)
	TimeBeginMediaPlay_ms = 1000*(Time_Sec_t[IndexBeginTimeSec]-Unix_TimeSecBeginFile_AVI);
  //  MedPosBegin =TimeBeginMediaPlay_ms/(LengthTimeAVI/NunberFrameAVI);
	 MediaPlayer1->TimeFormat = tfMilliseconds;
	 MediaPlayer1->Position = TimeBeginMediaPlay_ms;
   // MediaPlayer1->Position = MedPosBegin;

   Flag_SyncTimeEnd = true;
 //  }

 }

i=i;
}
//---------------------------------------------------------------------------



void __fastcall TSDIAppForm::Timer1Timer(TObject *Sender)
{

   if(Flag_SyncTimeEnd)
 {
   if(MediaPlayer1->Position==0)MediaPlayer1->Position = TimeBeginMediaPlay_ms;
 i_n=IndexBeginTimeSec;
  DiffForBeginMedPlay = abs(MediaPlayer1->Position - TimeBeginMediaPlay_ms);
  if(DiffForBeginMedPlay<Time_Msec[size_arr])
  {
  while(DiffForBeginMedPlay>(Time_Msec[i_n]-Time_Msec[IndexBeginTimeSec])&&i_n<size_arr)i_n++;
 //   if(ScrollBar1->Enabled&&(i_n-(Height_Ch*100)/2)>0) ScrollBar1->Position=i_n-(Height_Ch*100)/2;
// if(ScrollBar1->Enabled&&(size_arr-i_n)>((int)Height_Ch*100)) ScrollBar1->Position=i_n;
  Series2->Clear();

 if(OpenDialog->FilterIndex==1)Series2->AddXY(Time_nsec[i_n],Depth_t[i_n]);
 if(OpenDialog->FilterIndex==2)Series2->AddXY((UINT)Speed[i_n],Depth_t[i_n]);
// Edit2->Text = Depth_t[i_n];
  }
  else
  {
  //  Series2->Clear();
   // Series2->AddXY(Time_nsec[i_n],Depth_t[i_n]);
	 MediaPlayer1->Position =  Time_Msec[size_arr]+ TimeBeginMediaPlay_ms;
	MediaPlayer1->Stop();
  }
 }



 //MediaPlayer1->TimeFormat = tfMilliseconds;
// - TimeBeginMediaPlay_ms;


  //	 if (max_pos>Chart1->LeftAxis->Minimum) {Chart1->LeftAxis->Maximum=max_pos; Flag_Max=true;}
  //   if (min_pos<Chart1->LeftAxis->Maximum) {Chart1->LeftAxis->Minimum=min_pos; Flag_Max=false;}

 //  Chart1->LeftAxis->SetMinMax(min_pos,max_pos);

//Edit3->Text =  FormatDateTime(tfMSF, MediaPlayer1->Position );
// Edit3->Text =MCI_TMSF_SECOND(MediaPlayer1->Position);
 //Edit3->Text = MCI_TMSF_TRACK(MediaPlayer1->Position);

	  if(ComboBox1->Enabled)//&&Flag_Chart1MouseMove)
   {
 //  Series2->Clear();
 if(Flag_MouseDown&&FlagCurPosSeries)
				  {
                       MediaPlayer1->Position =  Time_Msec[indexGet_Cur_Chart]+ TimeBeginMediaPlay_ms;
                   Series2->Clear();

				   if(OpenDialog->FilterIndex==1)Series2->AddXY(Time_nsec[indexGet_Cur_Chart],Depth_t[indexGet_Cur_Chart]);
				   if(OpenDialog->FilterIndex==2)Series2->AddXY((UINT)Speed[indexGet_Cur_Chart],Depth_t[indexGet_Cur_Chart]);
				  }
	}
}
//---------------------------------------------------------------------------




//------------------------------------------------------------------------

void __fastcall TSDIAppForm::Timer2Timer(TObject *Sender)
{

   	Timer2->Enabled=false;
    ComboBox1->ItemIndex=0;

  	ScrollBox1->Align=alLeft;
     ScrollBox1->Repaint();
 //	//SDIAppForm->Panel2->Align=alLeft;
  	Panel1->Align=alClient;
    	Panel1->Repaint();

	//Panel2->Repaint();


   //	if(max_number_Data>Chart1->Height)ScrollBar1->Max=max_number_Data;//-Chart1->Height;
   //	else ScrollBar1->Enabled=false;

	Width_Panel=Panel1->Width;
	Height_Panel=Panel1->Height;


	Chart1->LeftAxis->Maximum=Chart1->Height;
	Chart1->LeftAxis->Maximum=1;

	//Panel2->Height=max_number_Data;
	//Chart1->LeftAxis->Maximum=max_number_Data;
	//Chart1->Height = max_number_Data;

	  // ScrollBar1->Max=10;
	  // ScrollBar1->Min=0;



 //ScrollBox1->Align=alLeft;
 //SDIAppForm->Panel2->Align=alLeft;
  ScrollBar1->PageSize=Chart1->Height-1;



 //ScrollBox1->Repaint();
 //Panel2->Repaint();
 //Panel1->Repaint();

Height_Ch_Ish = Chart1->Height;
Height_Ch = Chart1->Height;

	 Data_Graph_temp = new double [(int)(Height_Ch_Ish*2)];
	 Depth_Graph_temp = new double [(int)(Height_Ch_Ish*2)];
	 Speed_Graph_temp = new double [(int)(Height_Ch_Ish*2)];

 	AboutBox->ProductName->Caption="Video to Depth";
	AboutBox->Version->Caption=Vers_Prog;
	AboutBox->Copyright->Caption="2011 NIIGT, All Rights Reserved.";
	AboutBox->Comments->Caption="Laboratory gas-dynamic research (Ivanov O.)";

//SDIAppForm->Visible=true;


}
//---------------------------------------------------------------------------



void __fastcall TSDIAppForm::ComboBox1Change(TObject *Sender)
{
     Flag_Scroll=true;

   if(ComboBox1->ItemIndex==0)
   {
   Height_Ch=size_arr/100; ScrollBar1->Enabled=false; //ScrollBar1->Visible=false;    //all
          Coef_Scroll =((Height_Ch*100)/Height_Ch_Ish);
          Scale_Decim =ceil(Coef_Scroll);

     i_max = size_arr;
  i_min = 0;

        i_end=0;
 if(OpenDialog->FilterIndex==1)
  {
   if(MinMax1->Checked)i_end = MinMaxDataArray(Time_nsec,Depth_t,Data_Graph_temp,Depth_Graph_temp,i_min,i_max,Scale_Decim);
   if(Mean1->Checked)i_end = DecimDataArray(Time_nsec,Depth_t,Data_Graph_temp,Depth_Graph_temp,i_min,i_max,Scale_Decim);
  }

  if(OpenDialog->FilterIndex==2)
  {
   if(MinMax1->Checked)i_end = MinMaxDataArray(Speed,Depth_t,Data_Graph_temp,Depth_Graph_temp,i_min,i_max,Scale_Decim);
   if(Mean1->Checked)i_end = DecimDataArray(Speed,Depth_t,Data_Graph_temp,Depth_Graph_temp,i_min,i_max,Scale_Decim);
  }

  Series1->Clear() ;

Chart1->LeftAxis->SetMinMax(Depth_t[i_min],Depth_t[i_max]);
		 Series1->AddArray(Data_Graph_temp,(i_end),Depth_Graph_temp,(i_end));
      //	 Data_temp = new double [ Scale_Decim*2+2 ];
   }
   //---
   if(ComboBox1->ItemIndex==1)
   {
	 if(size_arr>100000L)  {
	 Height_Ch = 1000L; ScrollBar1->Enabled=true;ScrollBar1->Visible=true;
   //	 Kef_Scal=(double)size_arr/(Height_Ch*100);
          Coef_Scroll =((Height_Ch*100)/Height_Ch_Ish);
          Scale_Decim =ceil(Coef_Scroll);
     	// Data_temp = new double [ Scale_Decim*2+2 ];

	 }
   else {
           Height_Ch =size_arr/100; ScrollBar1->Enabled=false;
                    Coef_Scroll =((Height_Ch*100)/Height_Ch_Ish);
          Scale_Decim =ceil(Coef_Scroll);
                i_max = size_arr;
  i_min = 0;

        i_end=0;
 if(OpenDialog->FilterIndex==1)
  {
   if(MinMax1->Checked)i_end = MinMaxDataArray(Time_nsec,Depth_t,Data_Graph_temp,Depth_Graph_temp,i_min,i_max,Scale_Decim);
   if(Mean1->Checked)i_end = DecimDataArray(Time_nsec,Depth_t,Data_Graph_temp,Depth_Graph_temp,i_min,i_max,Scale_Decim);
  }

  if(OpenDialog->FilterIndex==2)
  {
   if(MinMax1->Checked)i_end = MinMaxDataArray(Speed,Depth_t,Data_Graph_temp,Depth_Graph_temp,i_min,i_max,Scale_Decim);
   if(Mean1->Checked)i_end = DecimDataArray(Speed,Depth_t,Data_Graph_temp,Depth_Graph_temp,i_min,i_max,Scale_Decim);
  }

  Series1->Clear() ;

Chart1->LeftAxis->SetMinMax(Depth_t[i_min],Depth_t[i_max]);
		 Series1->AddArray(Data_Graph_temp,(i_end),Depth_Graph_temp,(i_end));
        }
   }

   //--
	  if(ComboBox1->ItemIndex==2)
   {
	 if(size_arr>50000L)  {
     Height_Ch = 500L; ScrollBar1->Enabled=true;  ScrollBar1->Visible=true;
		 //Kef_Scal=(double)size_arr/(Height_Ch*100);
          Coef_Scroll =((Height_Ch*100)/Height_Ch_Ish);
          Scale_Decim =ceil(Coef_Scroll);
       //	 Data_temp = new double [ Scale_Decim*2+2 ];
         }
   else {
   Height_Ch =size_arr/100; ScrollBar1->Enabled=false;
            Coef_Scroll =((Height_Ch*100)/Height_Ch_Ish);
          Scale_Decim =ceil(Coef_Scroll);
        i_max = size_arr;
  i_min = 0;

        i_end=0;
 if(OpenDialog->FilterIndex==1)
  {
   if(MinMax1->Checked)i_end = MinMaxDataArray(Time_nsec,Depth_t,Data_Graph_temp,Depth_Graph_temp,i_min,i_max,Scale_Decim);
   if(Mean1->Checked)i_end = DecimDataArray(Time_nsec,Depth_t,Data_Graph_temp,Depth_Graph_temp,i_min,i_max,Scale_Decim);
  }

  if(OpenDialog->FilterIndex==2)
  {
   if(MinMax1->Checked)i_end = MinMaxDataArray(Speed,Depth_t,Data_Graph_temp,Depth_Graph_temp,i_min,i_max,Scale_Decim);
   if(Mean1->Checked)i_end = DecimDataArray(Speed,Depth_t,Data_Graph_temp,Depth_Graph_temp,i_min,i_max,Scale_Decim);
  }

  Series1->Clear() ;

Chart1->LeftAxis->SetMinMax(Depth_t[i_min],Depth_t[i_max]);
		 Series1->AddArray(Data_Graph_temp,(i_end),Depth_Graph_temp,(i_end));
        }

   }

   //--
	  if(ComboBox1->ItemIndex==3)
   {
	 if(size_arr>10000L)  {
         Height_Ch = 100L; ScrollBar1->Enabled=true; ScrollBar1->Visible=true;
	 //	 Kef_Scal=(double)size_arr/(Height_Ch*100);
          Coef_Scroll =((Height_Ch*100)/Height_Ch_Ish);
          Scale_Decim =ceil(Coef_Scroll);
      //	 Data_temp = new double [ Scale_Decim*2+2 ];
         }
   else {
   Height_Ch =size_arr/100; ScrollBar1->Enabled=false;
            Coef_Scroll =((Height_Ch*100)/Height_Ch_Ish);
          Scale_Decim =ceil(Coef_Scroll);
        i_max = size_arr;
  i_min = 0;

        i_end=0;
 if(OpenDialog->FilterIndex==1)
  {
   if(MinMax1->Checked)i_end = MinMaxDataArray(Time_nsec,Depth_t,Data_Graph_temp,Depth_Graph_temp,i_min,i_max,Scale_Decim);
   if(Mean1->Checked)i_end = DecimDataArray(Time_nsec,Depth_t,Data_Graph_temp,Depth_Graph_temp,i_min,i_max,Scale_Decim);
  }

  if(OpenDialog->FilterIndex==2)
  {
   if(MinMax1->Checked)i_end = MinMaxDataArray(Speed,Depth_t,Data_Graph_temp,Depth_Graph_temp,i_min,i_max,Scale_Decim);
   if(Mean1->Checked)i_end = DecimDataArray(Speed,Depth_t,Data_Graph_temp,Depth_Graph_temp,i_min,i_max,Scale_Decim);
  }

  Series1->Clear() ;

Chart1->LeftAxis->SetMinMax(Depth_t[i_min],Depth_t[i_max]);
         Series1->AddArray(Data_Graph_temp,(i_end),Depth_Graph_temp,(i_end));
        }
   }

   //--
	  if(ComboBox1->ItemIndex==4)
   {
	 if(size_arr>1000L){
	 Height_Ch = 10L; ScrollBar1->Enabled=true;  ScrollBar1->Visible=true;
     Scale_Decim = Height_Ch;
	 //	 Kef_Scal=(double)size_arr/(Height_Ch*100);
          }
   else {
        Height_Ch =size_arr/100; ScrollBar1->Enabled=false;
                 Coef_Scroll =((Height_Ch*100)/Height_Ch_Ish);
          Scale_Decim =ceil(Coef_Scroll);
             i_max = size_arr;
  i_min = 0;

        i_end=0;
 if(OpenDialog->FilterIndex==1)
  {
   if(MinMax1->Checked)i_end = MinMaxDataArray(Time_nsec,Depth_t,Data_Graph_temp,Depth_Graph_temp,i_min,i_max,Scale_Decim);
   if(Mean1->Checked)i_end = DecimDataArray(Time_nsec,Depth_t,Data_Graph_temp,Depth_Graph_temp,i_min,i_max,Scale_Decim);
  }

  if(OpenDialog->FilterIndex==2)
  {
   if(MinMax1->Checked)i_end = MinMaxDataArray(Speed,Depth_t,Data_Graph_temp,Depth_Graph_temp,i_min,i_max,Scale_Decim);
   if(Mean1->Checked)i_end = DecimDataArray(Speed,Depth_t,Data_Graph_temp,Depth_Graph_temp,i_min,i_max,Scale_Decim);
  }

  Series1->Clear() ;

Chart1->LeftAxis->SetMinMax(Depth_t[i_min],Depth_t[i_max]);
         Series1->AddArray(Data_Graph_temp,(i_end),Depth_Graph_temp,(i_end));
        }
   }

  //--
	  if(ComboBox1->ItemIndex==5)
   {
	 if(size_arr>100L)  {
	 Height_Ch = 1L; ScrollBar1->Enabled=true;  ScrollBar1->Visible=true;
     Scale_Decim = Height_Ch;
		 //Kef_Scal=(double)size_arr/(Height_Ch*100);
         }
   else {
         Height_Ch =size_arr/100; ScrollBar1->Enabled=false;
                  Coef_Scroll =((Height_Ch*100)/Height_Ch_Ish);
          Scale_Decim =ceil(Coef_Scroll);
              i_max = size_arr;
  i_min = 0;

        i_end=0;
 if(OpenDialog->FilterIndex==1)
  {
   if(MinMax1->Checked)i_end = MinMaxDataArray(Time_nsec,Depth_t,Data_Graph_temp,Depth_Graph_temp,i_min,i_max,Scale_Decim);
   if(Mean1->Checked)i_end = DecimDataArray(Time_nsec,Depth_t,Data_Graph_temp,Depth_Graph_temp,i_min,i_max,Scale_Decim);
  }

  if(OpenDialog->FilterIndex==2)
  {
   if(MinMax1->Checked)i_end = MinMaxDataArray(Speed,Depth_t,Data_Graph_temp,Depth_Graph_temp,i_min,i_max,Scale_Decim);
   if(Mean1->Checked)i_end = DecimDataArray(Speed,Depth_t,Data_Graph_temp,Depth_Graph_temp,i_min,i_max,Scale_Decim);
  }

  Series1->Clear() ;

Chart1->LeftAxis->SetMinMax(Depth_t[i_min],Depth_t[i_max]);
         Series1->AddArray(Data_Graph_temp,(i_end),Depth_Graph_temp,(i_end));
         }
   }

  // Height_Ch = Height_Ch/100;

  //	Chart1->LeftAxis->Maximum=Height_Ch;
   if(ScrollBar1->Enabled==false)Kef_Scal=1;
   else
   {

   ScrollBar1->Max=size_arr-(Height_Ch*100);
 //  ScrollBar1->PageSize = ceil((double)ScrollBar1->Max/(Height_Ch*100));
 //   ScrollBar1->PageSize = ScrollBar1->Max/(ScrollBar1->PageSize );


if(Flag_Comb_Chang ==false) {
if(Depth_t[0]>Depth_t[size_arr]) Pos_scroll_bar=size_arr-(Height_Ch*100);
else Pos_scroll_bar=0;
 //Pos_scroll_bar=size_arr-(Height_Ch*100);

ScrollBar1->Position= Pos_scroll_bar;
Flag_Comb_Chang=true;
}
   /*
   Pos_scroll_bar = ScrollBar1->Max-ScrollBar1->Position;
   Scrol_Pos = Pos_scroll_bar/100;//*Kef_Scal;


   			  Height_Ch=Height_Ch+Depth_Begin;
	   max_pos=(Height_Ch+Scrol_Pos);
	   min_pos=Depth_Begin+max_pos -Height_Ch ;


   Chart1->LeftAxis->SetMinMax(min_pos,max_pos);
     */
  if(Depth_t[0]>Depth_t[size_arr])
  {
   i_max = (ScrollBar1->Max-ScrollBar1->Position)+ (int)Height_Ch*100;
  i_min = ScrollBar1->Max-ScrollBar1->Position;
   }
   else
   {
    i_max = ScrollBar1->Position+ (int)Height_Ch*100;
    i_min = ScrollBar1->Position;
   }

     Series1->Clear() ;

      if(Height_Ch>10)
         {
     i_end=0;
 if(OpenDialog->FilterIndex==1)
  {
   if(MinMax1->Checked)i_end = MinMaxDataArray(Time_nsec,Depth_t,Data_Graph_temp,Depth_Graph_temp,i_min,i_max,Scale_Decim);
   if(Mean1->Checked)i_end = DecimDataArray(Time_nsec,Depth_t,Data_Graph_temp,Depth_Graph_temp,i_min,i_max,Scale_Decim);
  }

  if(OpenDialog->FilterIndex==2)
  {
   if(MinMax1->Checked)i_end = MinMaxDataArray(Speed,Depth_t,Data_Graph_temp,Depth_Graph_temp,i_min,i_max,Scale_Decim);
   if(Mean1->Checked)i_end = DecimDataArray(Speed,Depth_t,Data_Graph_temp,Depth_Graph_temp,i_min,i_max,Scale_Decim);
  }

  Chart1->LeftAxis->SetMinMax(Depth_Graph_temp[0],Depth_Graph_temp[i_end]);
   //Chart1->LeftAxis->SetMinMax(Depth_t[i_min],Depth_t[i_max]);

       //     for(i=0; i<=i2-1;i++)  Series1->AddXY(Data_Graph_temp[i],Depth_Graph_temp[i]);
		 Series1->AddArray(Data_Graph_temp,(i_end),Depth_Graph_temp,(i_end));

  /*  i1=0; i2=0;
       for(i=i_min; i<=i_max;i++)
       {
    if(i==i_min||i1>Scale_Decim)
     {
		 Series1->AddXY(Data_Graph_temp[i2],Depth_Graph_temp[i2]);
        i2++; i1=0;
       }
        i1++;
       }
    */
          }
              else
              {
                      Chart1->LeftAxis->SetMinMax(Depth_t[i_min],Depth_t[i_max]);
                     for(i=i_min; i<=i_max;i++) Series1->AddXY(Time_nsec[i],Depth_t[i]);  //  i++;
                }



	}

 Flag_Scroll=false;

 	Panel1->Repaint();

}
//---------------------------------------------------------------------------





void __fastcall TSDIAppForm::ScrollBar1Change(TObject *Sender)
{


//
    if(Depth_t[0]>Depth_t[size_arr])
  {
   i_max = (ScrollBar1->Max-ScrollBar1->Position)+ (int)Height_Ch*100;
  i_min = ScrollBar1->Max-ScrollBar1->Position;
   }
   else
   {
    i_max = ScrollBar1->Position+ (int)Height_Ch*100;
    i_min = ScrollBar1->Position;
   }
     Series1->Clear() ;

      if(Height_Ch>10)
         {

   i_end=0;


 if(OpenDialog->FilterIndex==1)
  {
   if(MinMax1->Checked)i_end = MinMaxDataArray(Time_nsec,Depth_t,Data_Graph_temp,Depth_Graph_temp,i_min,i_max,Scale_Decim);
   if(Mean1->Checked)i_end = DecimDataArray(Time_nsec,Depth_t,Data_Graph_temp,Depth_Graph_temp,i_min,i_max,Scale_Decim);
  }

  if(OpenDialog->FilterIndex==2)
  {
   if(MinMax1->Checked)i_end = MinMaxDataArray(Speed,Depth_t,Data_Graph_temp,Depth_Graph_temp,i_min,i_max,Scale_Decim);
   if(Mean1->Checked)i_end = DecimDataArray(Speed,Depth_t,Data_Graph_temp,Depth_Graph_temp,i_min,i_max,Scale_Decim);
  }


   Chart1->LeftAxis->SetMinMax(Depth_Graph_temp[0],Depth_Graph_temp[i_end]);
// Chart1->LeftAxis->SetMinMax(Depth_t[i_min],Depth_t[i_max]);

	   //     for(i=0; i<=i2-1;i++)  Series1->AddXY(Data_Graph_temp[i],Depth_Graph_temp[i]);
		 Series1->AddArray(Data_Graph_temp,i_end,Depth_Graph_temp,i_end);


          }
              else
              {
                    Chart1->LeftAxis->SetMinMax(Depth_t[i_min],Depth_t[i_max]);
                     for(i=i_min; i<=i_max;i++) Series1->AddXY(Time_nsec[i],Depth_t[i]);  //  i++;
                }



}
//---------------------------------------------------------------------------

void __fastcall TSDIAppForm::ScrollBar1Scroll(TObject *Sender, TScrollCode ScrollCode,
          int &ScrollPos)
{


//Edit3->Text= Temp_Hand_Min_Chart;
//Edit4->Text= Temp_Hand_Max_Chart;

//IndexBegEndArrayForChart(Depth_t,size_arr,Temp_Hand_Min_Chart,Temp_Hand_Max_Chart, &ind_beg, &ind_end);
i=i;
 /*
    if(!Flag_Scroll)
    {

  if(ScrollBar1->Enabled==false)Kef_Scal=1;
   else
   {
   Pos_scroll_bar = ScrollBar1->Max-ScrollBar1->Position;

	Scrol_Pos = (Pos_scroll_bar/100);//*Kef_Scal;

	}

      max_pos=(Height_Ch+Scrol_Pos);
      min_pos=Depth_Begin+max_pos - Height_Ch;
   Chart1->LeftAxis->SetMinMax(min_pos,max_pos);
    }//   if(!Flag_Scroll)
 */

//ScrollBar1->Cursor=crHahdPoint;


}
//---------------------------------------------------------------------------

void __fastcall TSDIAppForm::Button1Click(TObject *Sender)
{
  //ScrollBar1->Position=StrToInt(Edit2->Text);
 // Form2->Show() ;


}
//---------------------------------------------------------------------------




void __fastcall TSDIAppForm::RadioButton1Click(TObject *Sender)
{
ScrollBar1->SmallChange=1;

}
//---------------------------------------------------------------------------

void __fastcall TSDIAppForm::RadioButton2Click(TObject *Sender)
{
ScrollBar1->SmallChange=100;
}
//---------------------------------------------------------------------------

void __fastcall TSDIAppForm::RadioButton3Click(TObject *Sender)
{
  ScrollBar1->LargeChange=1000;
}
//---------------------------------------------------------------------------






void __fastcall TSDIAppForm::MinMax1Click(TObject *Sender)
{


 Mean1->Checked=false;
 MinMax1->Checked=true;
   Series1->Clear() ;
 if(ScrollBar1->Enabled){
  if(Depth_t[0]>Depth_t[size_arr])
  {
   i_max = (ScrollBar1->Max-ScrollBar1->Position)+ (int)Height_Ch*100;
  i_min = ScrollBar1->Max-ScrollBar1->Position;
   }
   else
   {
    i_max = ScrollBar1->Position+ (int)Height_Ch*100;
    i_min = ScrollBar1->Position;
   }
                         }
                         else {i_max = size_arr; i_min = 0;}


      if(Height_Ch>10)
         {

   i_end=0;


 if(OpenDialog->FilterIndex==1)
  {
   if(MinMax1->Checked)i_end = MinMaxDataArray(Time_nsec,Depth_t,Data_Graph_temp,Depth_Graph_temp,i_min,i_max,Scale_Decim);
   if(Mean1->Checked)i_end = DecimDataArray(Time_nsec,Depth_t,Data_Graph_temp,Depth_Graph_temp,i_min,i_max,Scale_Decim);
  }

  if(OpenDialog->FilterIndex==2)
  {
   if(MinMax1->Checked)i_end = MinMaxDataArray(Speed,Depth_t,Data_Graph_temp,Depth_Graph_temp,i_min,i_max,Scale_Decim);
   if(Mean1->Checked)i_end = DecimDataArray(Speed,Depth_t,Data_Graph_temp,Depth_Graph_temp,i_min,i_max,Scale_Decim);
  }

   Chart1->LeftAxis->SetMinMax(Depth_Graph_temp[0],Depth_Graph_temp[i_end]);
         Series1->AddArray(Data_Graph_temp,i_end,Depth_Graph_temp,i_end);
                  }
                else
              {
                    Chart1->LeftAxis->SetMinMax(Depth_t[i_min],Depth_t[i_max]);
                     for(i=i_min; i<=i_max;i++) Series1->AddXY(Time_nsec[i],Depth_t[i]);  //  i++;
                }

}
//---------------------------------------------------------------------------

void __fastcall TSDIAppForm::Mean1Click(TObject *Sender)
{


 
 MinMax1->Checked=false;
Mean1->Checked=true;
      Series1->Clear() ;
 if(ScrollBar1->Enabled){
  if(Depth_t[0]>Depth_t[size_arr])
  {
   i_max = (ScrollBar1->Max-ScrollBar1->Position)+ (int)Height_Ch*100;
  i_min = ScrollBar1->Max-ScrollBar1->Position;
   }
   else
   {
    i_max = ScrollBar1->Position+ (int)Height_Ch*100;
    i_min = ScrollBar1->Position;
   }
                         }
                         else {i_max = size_arr; i_min = 0;}


      if(Height_Ch>10)
         {

   i_end=0;


 if(OpenDialog->FilterIndex==1)
  {
   if(MinMax1->Checked)i_end = MinMaxDataArray(Time_nsec,Depth_t,Data_Graph_temp,Depth_Graph_temp,i_min,i_max,Scale_Decim);
   if(Mean1->Checked)i_end = DecimDataArray(Time_nsec,Depth_t,Data_Graph_temp,Depth_Graph_temp,i_min,i_max,Scale_Decim);
  }

  if(OpenDialog->FilterIndex==2)
  {
   if(MinMax1->Checked)i_end = MinMaxDataArray(Speed,Depth_t,Data_Graph_temp,Depth_Graph_temp,i_min,i_max,Scale_Decim);
   if(Mean1->Checked)i_end = DecimDataArray(Speed,Depth_t,Data_Graph_temp,Depth_Graph_temp,i_min,i_max,Scale_Decim);
  }

   Chart1->LeftAxis->SetMinMax(Depth_Graph_temp[0],Depth_Graph_temp[i_end]);
		 Series1->AddArray(Data_Graph_temp,i_end,Depth_Graph_temp,i_end);
         }
                else
              {
                    Chart1->LeftAxis->SetMinMax(Depth_t[i_min],Depth_t[i_max]);
                     for(i=i_min; i<=i_max;i++) Series1->AddXY(Time_nsec[i],Depth_t[i]);  //  i++;
                }



}
//---------------------------------------------------------------------------




void __fastcall TSDIAppForm::Chart1MouseEnter(TObject *Sender)
{
Flag_Chart_Scroll=true;  Chart1->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TSDIAppForm::Chart1MouseLeave(TObject *Sender)
{
Flag_Chart_Scroll=false;
Flag_Chart1MouseMove=false;
}
//---------------------------------------------------------------------------

void __fastcall TSDIAppForm::FormMouseWheelDown(TObject *Sender, TShiftState Shift,
          TPoint &MousePos, bool &Handled)
{
 if(ScrollBar1->Enabled)
   {
       if(Flag_Chart_Scroll||Flag_ScrBar_Scroll)
       {
         if((ScrollBar1->Position+Scale_Decim)<=size_arr)ScrollBar1->Position+=Scale_Decim;
       }
   }
}
//---------------------------------------------------------------------------

void __fastcall TSDIAppForm::FormMouseWheelUp(TObject *Sender, TShiftState Shift,
          TPoint &MousePos, bool &Handled)
{
 if(ScrollBar1->Enabled)
   {
       if(Flag_Chart_Scroll||Flag_ScrBar_Scroll)
       {
         if((ScrollBar1->Position-Scale_Decim)>=0)ScrollBar1->Position-=Scale_Decim;
       }
   }
}
//---------------------------------------------------------------------------





void __fastcall TSDIAppForm::ScrollBar1MouseEnter(TObject *Sender)
{
Flag_ScrBar_Scroll=true;
}
//---------------------------------------------------------------------------

void __fastcall TSDIAppForm::ScrollBar1MouseLeave(TObject *Sender)
{
 Flag_ScrBar_Scroll=false;
}
//---------------------------------------------------------------------------





















void __fastcall TSDIAppForm::Chart1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{

Flag_MouseDown=false;

//Flag_LeftMouse =false; Flag_RightMouse =false; Flag_MiddleMouse = false;
//double temp_max_d;
//if(ComboBox1->Enabled) temp_max_d = MaxValue(Depth_t,size_arr);
//Temp_Hand_Min_Chart = Chart1->LeftAxis->Minimum;
//Temp_Hand_Max_Chart = Chart1->LeftAxis->Maximum;
 //Edit3->Text= Temp_Hand_Min_Chart;
//Edit4->Text= Temp_Hand_Max_Chart;
if (Button == mbLeft) {Flag_LeftMouse =true; Flag_RightMouse =false;Flag_MiddleMouse = false;}
if (Button == mbRight) {Flag_LeftMouse =false; Flag_RightMouse=true; Flag_MiddleMouse = false;}
if (Button == mbMiddle) {Flag_MiddleMouse = true, Flag_LeftMouse =false; Flag_RightMouse=false; }

}
//---------------------------------------------------------------------------






void __fastcall TSDIAppForm::Chart1MouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y)
{
//Flag_Chart1MouseMove=true;

if(ComboBox1->Enabled)
 {
 Chart1->Series[0]->GetCursorValues(Get_Cur_Chart_X,Get_Cur_Chart_Y);
Edit2->Text=FloatToStrF(Get_Cur_Chart_Y,ffNumber,6,2);
i=0;
if(Depth_t[0]<Depth_t[size_arr])while(Depth_t[i]< Get_Cur_Chart_Y&&i<size_arr) i++; else
while(Depth_t[i]> Get_Cur_Chart_Y&&i<size_arr) i++;
indexGet_Cur_Chart=i;
if(fabs(Time_nsec[indexGet_Cur_Chart]-Get_Cur_Chart_X)<500000000) FlagCurPosSeries = true;
else   FlagCurPosSeries = false;


  }



}
//---------------------------------------------------------------------------

void __fastcall TSDIAppForm::Chart1MouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
// Flag_MouseDown=true;

 if((Chart1->Height - Y)<45)  Series2->Marks->ArrowLength=8;
 else Series2->Marks->ArrowLength = -45;

if (Button == mbLeft) {Flag_LeftMouse =true; Flag_RightMouse =false;Flag_MouseDown=true; Flag_MiddleMouse = false;}
if (Button == mbRight) {Flag_LeftMouse =false; Flag_RightMouse=true; Flag_MiddleMouse = false;}
if (Button == mbMiddle) {Flag_MiddleMouse = true, Flag_LeftMouse =false; Flag_RightMouse=false; }

}



void __fastcall TSDIAppForm::Chart1Gesture(TObject *Sender, const TGestureEventInfo &EventInfo,
          bool &Handled)
{


 if(ComboBox1->Enabled&&Flag_RightMouse)
                      {
 if(EventInfo.GestureID==sgiLeft)    // for work correct comment in Vcl.Controls.hpp str. 'sgiLeft'
 {
 MinBottomAxis=MinBottomAxis - MinBottomAxis_inc;
  MaxBottomAxis=MaxBottomAxis + MaxBottomAxis_inc;
  Chart1->BottomAxis-> SetMinMax(MinBottomAxis,MaxBottomAxis);
	Label2->Visible=true; Timer4->Enabled=true;
 }

 if(EventInfo.GestureID==sgiRight) // for work correct comment in Vcl.Controls.hpp str. 'sgiRight'
 {
 MinBottomAxis=MinBottomAxis + MinBottomAxis_inc;
  MaxBottomAxis=MaxBottomAxis - MaxBottomAxis_inc;
  Chart1->BottomAxis-> SetMinMax(MinBottomAxis,MaxBottomAxis);
  Label1->Visible=true; Timer4->Enabled=true;
 }
  if(EventInfo.GestureID==sgiDown) // for work correct comment in Vcl.Controls.hpp str. 'sgiDown'
 {
 MinBottomAxis=MinBottomAxis_Ish;
MaxBottomAxis=MaxBottomAxis_Ish;
  Chart1->BottomAxis-> SetMinMax(MinBottomAxis,MaxBottomAxis);
    Label3->Visible=true; Timer4->Enabled=true;
 }


					  }
}
//---------------------------------------------------------------------------

void __fastcall TSDIAppForm::Timer4Timer(TObject *Sender)
{
Timer4->Enabled=false;
  Label1->Visible=false;
  Label2->Visible =false;
  Label3->Visible =false;
}
//---------------------------------------------------------------------------



