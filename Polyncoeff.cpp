  #include <stdio.h>
  #include <string.h>
  #include <io.h>
 #include <SysUtils.hpp>

 #include <stdlib.h>
 #include <math.h>
 #include <Math.hpp>
//calculating coeff. polyn. 'COEFF' degree 'n'
  //double *X,*Y;

IndexBegEndArrayForChart(double *Data_In, int Size_Arr, double Data_Begin, double Data_End, int *index_begin, int *index_end)
{
int i=0;

while(Data_In[i]< Data_Begin&&i<Size_Arr)  i++;  *index_begin=i-1;
while(Data_In[i]> Data_End&&i<Size_Arr)  i++;  *index_end=i-1;

}
//----------------------------------------------------------------------------------------------------------------------------
 MinMaxValueIndexDataArray(double *Data_In, int Size_Arr, double *Data_Min, double *Data_Max, int *index_min, int *index_max ) {
 int i;
 *Data_Min = MinValue(Data_In, Size_Arr);
 *Data_Max = MaxValue(Data_In, Size_Arr);

 for(i=0;i<= Size_Arr;i++)

					 {
                       if(*Data_Min==Data_In[i])
                           {
                           *index_min=i;
                           }
                       if(*Data_Max==Data_In[i])
                            {
                           *index_max=i;
                           }
                      }
    }

//---------------------------------------------------------------------------------------------------------------------------------
 MeanDataArray(double *X_In,double *Y_In,double *X_Out,double *Y_Out, int i_min, int i_max, int Scale_Decim) {
			   int i=0, i1=0, i3=0, i_check_max =0;
			   int index_min_data,index_max_data, index_mean_data;
			 int i2=0;
				double *Data_temp;
				double *Data_temp_mean;
				double *Data_temp_1;
				double *Data_temp_mean_1;
			   double Temp_Mean_n, Temp_Mean;
				Data_temp = new double [ Scale_Decim+2 ];
			   Data_temp_mean = new double [ Scale_Decim+2 ];
  //-------------------------------------------
					 for(i=i_min; i<=i_max;i++)
                                            {

                             if(i==i_min)
                             {
                             X_Out[i2]=X_In[i];Y_Out[i2]=Y_In[i]; i1=0;i2++;
							 }
                             if(i>i_min)
							{
							  Data_temp[i1]=X_In[i];
                                 i1++;
								   if((i1-1)==(Scale_Decim))
								{
                              Temp_Mean_n = Mean(Data_temp,Scale_Decim-1);
							for(i3=0;i3<i1;i3++)  Data_temp_mean[i3]=fabs(Data_temp[i3]-Temp_Mean_n);
                               Temp_Mean = MinValue(Data_temp_mean,Scale_Decim-1);

                                for(i3=0;i3<i1;i3++) {
													if(Data_temp_mean[i3]==Temp_Mean) index_mean_data=i3;
                                                    }
                                X_Out[i2]= Data_temp[index_mean_data]; i2++;
								Y_Out[i2-1]=Y_In[(i-(Scale_Decim))+index_mean_data];   i_check_max = (i-(Scale_Decim))+index_mean_data;
                                i1=0;   i=i-1;
								}
                          //-----------------------------------------
							if(i==i_max&&(i1-1)>1) {
							  Data_temp_1 = new double [i1];
                              Data_temp_mean_1 = new double [i1];
                               for(i3=0;i3<i1;i3++) Data_temp_1[i3]=Data_temp[i3];
                               Temp_Mean_n= Mean(Data_temp_1,i1-1);
                                 for(i3=0;i3<i1;i3++)  Data_temp_mean_1[i3]=fabs(Data_temp_1[i3]-Temp_Mean_n);
								Temp_Mean = MinValue(Data_temp_mean_1,i1-1);
                                for(i3=0;i3<i1;i3++) {
                                                    if(Data_temp_mean_1[i3]==Temp_Mean) index_mean_data=i3;
                                                    }
                               X_Out[i2]= Data_temp_1[index_mean_data]; i2++;
							   Y_Out[i2-1]=Y_In[(i-(i1-1))+index_mean_data];  i_check_max = (i-(i1-1))+index_max_data;
								i1=0; // i=i-1;
                                 delete [] Data_temp_1;
                                   delete [] Data_temp_mean_1;
												  }  //if(i==i_max&&i1>1)
                          //---------------------------------------
							  if(i==i_max&&(i1-1)<=1&&i_check_max!=i_max)
							  {
							  X_Out[i2]=X_In[i];Y_Out[i2]=Y_In[i]; i1=0;i2++;
							  }



							 }    //  if(i>i_min)
							               }
 //-----------------------------------end for(i=i_min; i<=i_max;i++)

											delete [] Data_temp;

											delete [] Data_temp_mean;

										   i2=i2-3;

 return *X_Out, *Y_Out, i2;

}

 //---------------------------------------------------------------------------------------------------------------------------------
 DecimDataArray(double *X_In,double *Y_In,double *X_Out,double *Y_Out, int i_min, int i_max, int Scale_Decim) {
			   int i=0, i1=0, i3=0, i_check_max =0;

			 int i2=0;

					 for(i=i_min; i<=i_max;i++)
											{
							   if(i==i_min)
							 {
							X_Out[i2]=X_In[i];Y_Out[i2]=Y_In[i]; i1=0;i2++;
							 }
							 if(i>i_min)
							{

								 i1++;
								   if((i1-1)==(Scale_Decim))
								{
							 X_Out[i2]= X_In[i]; i2++;
								Y_Out[i2-1]=Y_In[i];  i_check_max = i;
								i1=0;   i=i-1;
								}

						  //---------------------------------------
							  if(i==i_max&&(i1-1)<=1&&i_check_max!=i_max)
							  {
							  X_Out[i2]=X_In[i];Y_Out[i2]=Y_In[i]; i1=0;i2++;
							  }
							 }    //  if(i>i_min)
							               }
										   i2=i2-3;

 return *X_Out, *Y_Out, i2;

}


  //-----------------------------------------------------------------------------------



 MinMaxDataArray(double *X_In,double *Y_In,double *X_Out,double *Y_Out, int i_min, int i_max, int Scale_Decim) {
               int i, i1=0, i3=0, i_check_max =0;
               int index_min_data,index_max_data, index_mean_data;
             int i2=0;
                double *Data_temp;
                 double *Data_temp_1;
                 Data_temp = new double [ Scale_Decim*2+2 ];
  //-------------------------------------------
                     for(i=i_min; i<=i_max;i++)
                                            {

                             if(i==i_min)
                             {
                             X_Out[i2]=X_In[i];Y_Out[i2]=Y_In[i]; i1=0;i2++;
                             }
                             if(i>i_min)
                            {
                              Data_temp[i1]=X_In[i];
                                 i1++;

                                if((i1-1)==(Scale_Decim*2))
                                {
                                X_Out[i2]= MinValue(Data_temp,Scale_Decim*2-1);  i2++;
                                X_Out[i2]= MaxValue(Data_temp,Scale_Decim*2-1); i2++;

                                for(i3=0;i3<i1;i3++) {
                                                     if(Data_temp[i3]==X_Out[i2-2]) index_min_data=i3;
                                                     if(Data_temp[i3]==X_Out[i2-1]) index_max_data=i3;
                                                    }

                                Y_Out[i2-2]=Y_In[(i-(Scale_Decim*2))+index_min_data];   i_check_max = (i-(Scale_Decim*2))+index_min_data;
                                Y_Out[i2-1]=Y_In[(i-(Scale_Decim*2))+index_max_data];   i_check_max = (i-(Scale_Decim*2))+index_max_data;
                                i1=0;   i=i-1;
                                }
                          //-----------------------------------------
                              if(i==i_max&&(i1-1)>1) {
                              Data_temp_1 = new double [i1];
                               for(i3=0;i3<i1;i3++) Data_temp_1[i3]=Data_temp[i3];
                               X_Out[i2]= MinValue(Data_temp_1,i1-1);  i2++;
                               X_Out[i2]= MaxValue(Data_temp_1,i1-1);  i2++;
                                for(i3=0;i3<i1;i3++) {
                                                     if(Data_temp_1[i3]==X_Out[i2-2]) index_min_data=i3;
                                                     if(Data_temp_1[i3]==X_Out[i2-1]) index_max_data=i3;
                                                    }
                                Y_Out[i2-2]=Y_In[(i-(i1-1))+index_min_data];  i_check_max = (i-(i1-1))+index_min_data;
                                Y_Out[i2-1]=Y_In[(i-(i1-1))+index_max_data];  i_check_max = (i-(i1-1))+index_max_data;
                                i1=0; // i=i-1;
                                      delete [] Data_temp_1;
                                                  }  //if(i==i_max&&i1>1)
                          //---------------------------------------
                              if(i==i_max&&(i1-1)<=1&&i_check_max!=i_max)
                              {
                              X_Out[i2]=X_In[i];Y_Out[i2]=Y_In[i]; i1=0;i2++;
                              }



                             }    //  if(i>i_min)
							               }
 //-----------------------------------end for(i=i_min; i<=i_max;i++)

                                            delete [] Data_temp;

                                           i2=i2-3;

 return *X_Out, *Y_Out, i2;

}



  //-----------------------------------------------------------------------------------

coeffpolyn(double *X,double *Y,int n, int h,double *COEF) {
 // throw new EOverflow ("nn");
  //row "EOverflow& nn";

  double *b,*c,*c_t;
  double **a;
  h=h-1;

  int i,j,k;
 double X_temp,Y_temp;

  n=n+1;

  a = new double *[n+1];
  for (int j = 0; j < n+1; j++) a[j] = new double[n+1];


  b = new double [n+1];
  c_t = new double [n+1];
  c = new double [2*n+1];

  for(i=0;i<=2*n-1;i++)  c[i]=0;
  for(i=0;i<=n;i++)  b[i]=0;

  double f,hh;

  for(i=1;i<=h;i++)
  {
   f=1; X_temp=X[i];Y_temp=Y[i];
   for(j=1;j<=2*n-1;j++)
   {
   if(j>n) goto m;
   b[j]=b[j]+Y_temp;
   Y_temp=Y_temp*X_temp;
   m:
   c[j]=c[j]+f;
   f=f*X_temp;
   }
  }

   c[2]=c[2] ;
  for(i=1;i<=n;i++)
  {
  k=i;
  for(j=1;j<=n;j++)
   {
   a[i][j]=c[k];
   k=k+1;
   }
  }

  for(i=1;i<=n-1;i++)
  {
   for(j=i+1;j<=n;j++)
   {
    a[j][i]=-a[j][i]/a[i][i];
     for(k=i+1;k<=n;k++)
     {
     a[j][k]= a[j][k]+a[j][i]*a[i][k];
     }
     b[j]=b[j]+a[j][i]*b[i];
   }
  }

  c_t[n]=b[n]/a[n][n];
  for(i=n-1;i>=1;i--)
  {
  hh=b[i];
   for(j=i+1;j<=n;j++)
   {
   hh=hh-c_t[j]*a[i][j];
   }
   c_t[i]=hh/a[i][i];
  }

  for(i=0;i<=n-1;i++) COEF[i]=c_t[i+1];

  for (int j = 0; j < n+1; j++) delete []a[j];
   delete []a;

  delete []b;
  delete []c;
  delete []c_t;
  j=j;
  return  *COEF;
                                                         }
 //----------------------------------------------------------------------------------------------------------------------



// quick sort  quick sort  quick sort    quick sort     quick sort   quick sort

void quick_sort(double A[], int L, int R,int A_num [])

  {
  int i, j;
  double x, t, t_num;

  while (L < R)

    {
    x = A[L];
    i = L, j = R;

    while (i <= j)
      {

      while (A[i] < x) i++;

      while (x < A[j]) j--;

      if (i <= j)
        t = A[i], A[i] = A[j], A[j] = t,
        t_num = A_num [i], A_num [i]= A_num [j], A_num [j]= t_num,
        i++, j--;

      }

    if ((j - L) > (R - i))

      quick_sort(A, i, R,A_num), R = j;

    else

      quick_sort(A, L, j,A_num), L = i;

    }

  }


  // quick sort without  argum  quick sort without  argum quick sort  without  argum  quick sort  without  argum   quick sort   quick sort  without  argum

void quick_sort_w(double A[], int L, int R)

  {
  int i, j;
  double x, t;

  while (L < R)

    {
    x = A[L];
    i = L, j = R;

    while (i <= j)
      {

      while (A[i] < x) i++;

      while (x < A[j]) j--;

      if (i <= j)
        t = A[i], A[i] = A[j], A[j] = t,
        i++, j--;

      }

    if ((j - L) > (R - i))

      quick_sort_w(A, i, R), R = j;

    else

      quick_sort_w(A, L, j), L = i;

    }

  }


 // quick sort  quick sort  quick sort    quick sort     quick sort   quick sort

void quick_sort_n(int A[], int L, int R,double A_num [])

  {
  int i, j;
  int x, t;
  double t_num;

  while (L < R)

    {
    x = A[L];
    i = L, j = R;

    while (i <= j)
      {

      while (A[i] < x) i++;

      while (x < A[j]) j--;

      if (i <= j)
        t = A[i], A[i] = A[j], A[j] = t,
        t_num = A_num [i], A_num [i]= A_num [j], A_num [j]= t_num,
        i++, j--;

      }

    if ((j - L) > (R - i))

      quick_sort_n(A, i, R,A_num), R = j;

    else

      quick_sort_n(A, L, j,A_num), L = i;

    }

  }


