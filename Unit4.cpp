//---------------------------------------------------------------------------

#include <ctime>
#include <iostream>
#include <cstdlib>
#include <vcl.h>
#pragma hdrstop
#include "mmsystem.h"

#include "Unit4.h"
#include "Unit7.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm4 *Form4;

bool czy_bomba_F4[500];
int licznik_F4 = 0;
bool flaga_F4 = false;
int ktora_bomba_F4 = 0; //do flag
int ruchy_F4 = 500;
int odliczanie_F4 = 0;
int ile_bomb_F4 = 0; //do porownywania z ruchami
bool flaga_tab_F4[500];
bool cokolwiek_tab_F4[500];
bool odwiedzona_F4[500];
bool bonus_flaga_F4[500];
int jednorazowo_F4 = 0;


void zmien_visible_na_true_F4();
void zmien_visible_na_false_F4();
void odkryj_bez_numerkow_F4(int ind);
void czerwona_F4(int indeks);
void bon_flaga_dzialanie_F4(int indeks, TImage* t, int numer);



void sprawdz_czy_wygrana_F4()
 {
     if(ile_bomb_F4 == ruchy_F4 && ktora_bomba_F4 == 100)
     {
        sndPlaySound("snd/win.wav", SND_ASYNC);
        Application -> MessageBox ("Brawo! Wygrana!", "Koniec gry", MB_OK);
        Form4 -> FormCreate(Form4);
     }
 }


 void klik_F4(TObject *Sender,
  TMouseButton Button, TShiftState Shift, int X, int Y, int indeks, TImage* t)
 {
     if(Shift.Contains(ssLeft))
    {
      for(int i=0; i<500; i++)
      {
         if(i == indeks)
         {
           if (flaga_tab_F4[i] == false)
           {
              if(czy_bomba_F4[indeks] == true)
             {
                if (jednorazowo_F4 == 0)
                {
                        
                        Form7 = new TForm7(Application);
                        Form7 -> ShowModal();

                        if (Form7 -> Label4 -> Visible == true)
                        {
                            t -> Picture -> LoadFromFile("img/flaga.bmp");
                            flaga_tab_F4[i] = true;
                            ktora_bomba_F4++;
                            Form4 -> ile_flag -> Caption = " ";
                            Form4 -> ile_flag -> Caption = (Form4 -> ile_flag -> Caption + ktora_bomba_F4 + "   ");
                        }
                        else
                        {
                            t -> Visible = false;
                            sndPlaySound("snd/bum.wav", SND_ASYNC);
                            zmien_visible_na_false_F4();
                            czerwona_F4(indeks);
                            Application -> MessageBox ("BUM! Przegrana!", "Koniec gry", MB_OK);
                         }
                        jednorazowo_F4++;
                        delete Form7;
                }
                else
                {
                   t -> Visible = false;
                   sndPlaySound("snd/bum.wav", SND_ASYNC);
                   zmien_visible_na_false_F4();
                   czerwona_F4(indeks);
                   Application -> MessageBox ("BUM! Przegrana!", "Koniec gry", MB_OK);
                }
             }
             else if(czy_bomba_F4[indeks] == false)
             {
                t -> Visible = false;
                odliczanie_F4 ++;
                odkryj_bez_numerkow_F4(indeks);
                if (cokolwiek_tab_F4[indeks] == true && odwiedzona_F4[indeks] == false){ruchy_F4--;}
                Form4 -> ktory_ruch -> Caption = "   ";
                Form4 -> ktory_ruch -> Caption = (Form4 -> ktory_ruch -> Caption + odliczanie_F4 + " ");

                Form4 -> Label1 -> Caption = "   ";
                Form4 -> Label1 -> Caption = Form4 -> Label1 -> Caption + ruchy_F4 + " ";
             }
             } } } // if, if i for
    }

    if(Shift.Contains(ssRight))
    {
      for(int i=0; i<500; i++)
      {
         if(i == indeks)
         {
           if (flaga_tab_F4[i] == false)
           {
              t -> Picture -> LoadFromFile("img/flaga.bmp");
              flaga_tab_F4[i] = true;
              ktora_bomba_F4++;
              Form4 -> ile_flag -> Caption = " ";
              Form4 -> ile_flag -> Caption = (Form4 -> ile_flag -> Caption + ktora_bomba_F4 + "   ");
           }
           else if (flaga_tab_F4[i] == true)
           {
               t -> Picture -> LoadFromFile("img/zakr.bmp");
               flaga_tab_F4[i] = false;
               ktora_bomba_F4--;
               Form4 -> ile_flag -> Caption = " ";
               Form4 -> ile_flag -> Caption = (Form4 -> ile_flag -> Caption + ktora_bomba_F4 + "   ");
           }
         } // if i == indeks
       } // for
    } // if

    sprawdz_czy_wygrana_F4();
 }



 void zmien_visible_na_true_F4()
 {
   TComponent *Temp;
   for (int i=500; i<1005; i++)
   {
      Temp = Form4 -> Components[i];
      if ((dynamic_cast<TImage *>(Temp) != NULL))
      {
          TImage* obj = ((TImage *) Temp);
          obj -> Visible = true;
      }
   }
 }


void zmien_visible_na_false_F4()
 {
   TComponent *Temp;
   for (int i=500; i<1005; i++)
   {
      Temp = Form4 -> Components[i];
      if ((dynamic_cast<TImage *>(Temp) != NULL))
      {
          TImage* obj = ((TImage *) Temp);
          obj -> Visible = false;
      }
   }
 }


 void czerwona_F4(int indeks)
 {
    TComponent *Temp;
    for (int i=0; i<500; i++)
    {
       if(i == indeks)
       {
           Temp = Form4 -> Components[i];
           if ((dynamic_cast<TImage *>(Temp) != NULL))
          {
             TImage* obj = ((TImage *) Temp);
             obj -> Picture -> LoadFromFile("img/kliknieta.bmp");
          }
       }
    }
 }




 void odkryj_bez_numerkow_F4(int ind)
 {
     TComponent *Temp;
     for(int i=0; i<500; i++) // dla tablicy cokolwiek
     {
       if (i == ind)
       {
        for(int j=500; j<1005; j++) // dla komponentów
        {
           if (j == i+505)
           {
             Temp = Form4 -> Components[j];
             if ((dynamic_cast<TImage *>(Temp) != NULL))
             {
               TImage* obj = ((TImage *) Temp);


               if(cokolwiek_tab_F4[i] == false && odwiedzona_F4[i] == false)
               {

                  odwiedzona_F4[i] = true;
                  obj -> Visible = false;
                  ruchy_F4--;


                  if ((i%25) == 0 && i!= 0 && i != 475)
                  {
                      if(i+1 < 500){odkryj_bez_numerkow_F4(ind+1);}
                      if(i-24 >= 0){odkryj_bez_numerkow_F4(ind-24);}
                      if(i-25 >= 0){odkryj_bez_numerkow_F4(ind-25);}
                      if(i+25 < 500){odkryj_bez_numerkow_F4(ind+25);}
                      if(i+26 < 500){odkryj_bez_numerkow_F4(ind+26);}
                  }
                  if (((i+1)%25) == 0 && i!= 24 && i != 499)
                  {
                      if(i-1 >= 0){odkryj_bez_numerkow_F4(ind-1);}
                      if(i-25 >= 0){odkryj_bez_numerkow_F4(ind-25);}
                      if(i-26 >= 0){odkryj_bez_numerkow_F4(ind-26);}
                      if(i+24 < 500){odkryj_bez_numerkow_F4(ind+24);}
                      if(i+25 < 500){odkryj_bez_numerkow_F4(ind+25);}
                  }
                  if (i == 0)
                  {
                      if(i+1 < 500){odkryj_bez_numerkow_F4(ind+1);}
                      if(i+25 < 500){odkryj_bez_numerkow_F4(ind+25);}
                      if(i+26 < 500){odkryj_bez_numerkow_F4(ind+26);}
                  }
                  if (i == 24)
                  {
                      if(i-1 >= 0){odkryj_bez_numerkow_F4(ind-1);}
                      if(i+24 < 500){odkryj_bez_numerkow_F4(ind+24);}
                      if(i+25 < 500){odkryj_bez_numerkow_F4(ind+25);}
                  }
                  if (i == 475)
                  {
                      if(i+1 < 500){odkryj_bez_numerkow_F4(ind+1);}
                      if(i-24 >= 0){odkryj_bez_numerkow_F4(ind-24);}
                      if(i-25 >= 0){odkryj_bez_numerkow_F4(ind-25);}
                  }
                  if (i == 499)
                  {
                      if(i-1 >= 0){odkryj_bez_numerkow_F4(ind-1);}
                      if(i-25 >= 0){odkryj_bez_numerkow_F4(ind-25);}
                      if(i-26 >= 0){odkryj_bez_numerkow_F4(ind-26);}
                  }
                  if (i!=0 && i!=24 && i!=475 && i!=499 && (i%25)!=0 && ((i+1)%25)!=0)
                  {
                      if(i+1 < 500){odkryj_bez_numerkow_F4(ind+1);}
                      if(i-1 >= 0){odkryj_bez_numerkow_F4(ind-1);}
                      if(i-24 >= 0){odkryj_bez_numerkow_F4(ind-24);}
                      if(i-25 >= 0){odkryj_bez_numerkow_F4(ind-25);}
                      if(i-26 >= 0){odkryj_bez_numerkow_F4(ind-26);}
                      if(i+24 < 500){odkryj_bez_numerkow_F4(ind+24);}
                      if(i+25 < 500){odkryj_bez_numerkow_F4(ind+25);}
                      if(i+26 < 500){odkryj_bez_numerkow_F4(ind+26);}
                  }


              } // if


              if(cokolwiek_tab_F4[i] == true && odwiedzona_F4[i] == false)
              {
                  if ((i%25) == 0 && i!= 0 && i != 475)
                  {
                       if(cokolwiek_tab_F4[i-25] == false || cokolwiek_tab_F4[i-24] == false || cokolwiek_tab_F4[i+1] == false
                       || cokolwiek_tab_F4[i+25] == false || cokolwiek_tab_F4[i+26] == false)
                       {
                       odwiedzona_F4[i] = true;
                       obj -> Visible = false;
                       ruchy_F4--;
                       }
                  }
                  if (((i+1)%25) == 0 && i!= 24 && i != 475)
                  {
                      if(cokolwiek_tab_F4[i-26] == false || cokolwiek_tab_F4[i-25] == false || cokolwiek_tab_F4[i-1] == false
                      || cokolwiek_tab_F4[i+24] == false || cokolwiek_tab_F4[i+25] == false)
                      {
                       odwiedzona_F4[i] = true;
                       obj -> Visible = false;
                       ruchy_F4--;
                      }
                  }
                  if (i == 0)
                  {
                      if(cokolwiek_tab_F4[i+1] == false || cokolwiek_tab_F4[i+25] == false || cokolwiek_tab_F4[i+26] == false)
                      {
                       odwiedzona_F4[i] = true;
                       obj -> Visible = false;
                       ruchy_F4--;
                      }
                  }
                  if (i == 24)
                  {
                      if(cokolwiek_tab_F4[i-1] == false ||cokolwiek_tab_F4[i+24] == false || cokolwiek_tab_F4[i+25] == false )
                      {
                       odwiedzona_F4[i] = true;
                       obj -> Visible = false;
                       ruchy_F4--;
                      }
                  }
                  if (i == 475)
                  {
                      if(cokolwiek_tab_F4[i-25] == false || cokolwiek_tab_F4[i-24] == false || cokolwiek_tab_F4[i+1] == false)
                      {
                       odwiedzona_F4[i] = true;
                       obj -> Visible = false;
                       ruchy_F4--;
                      }
                  }
                  if (i == 475)
                  {
                      if(cokolwiek_tab_F4[i-26] == false || cokolwiek_tab_F4[i-25] == false || cokolwiek_tab_F4[i-1] == false)
                      {
                       odwiedzona_F4[i] = true;
                       obj -> Visible = false;
                       ruchy_F4--;
                      }
                  }
                  if (i!=0 && i!=24 && i!=475 && i!=499 && (i%25)!=0 && ((i+1)%25)!=0)
                  {
                      if(cokolwiek_tab_F4[i-26] == false || cokolwiek_tab_F4[i-25] == false || cokolwiek_tab_F4[i-24] == false || cokolwiek_tab_F4[i-1] == false
                      || cokolwiek_tab_F4[i+1] == false || cokolwiek_tab_F4[i+24] == false || cokolwiek_tab_F4[i+25] == false || cokolwiek_tab_F4[i+26] == false)
                      {
                       odwiedzona_F4[i] = true;
                       obj -> Visible = false;
                       ruchy_F4--;
                      }
                  }
              }



            } // if dynamic cast
          } // if i+100 == j
        } // for j
       } // if i == ind
     } // for i
 }



//---------------------------------------------------------------------------
__fastcall TForm4::TForm4(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm4::FormCreate(TObject *Sender)
{
     zmien_visible_na_true_F4();

    ruchy_F4 = 500;
    ile_bomb_F4 = 0;
    ktora_bomba_F4 = 0;
    odliczanie_F4 = 0;
    jednorazowo_F4 = 0;

    for (int i=0; i<500; i++)
    {
       czy_bomba_F4[i] = false;
       odwiedzona_F4[i] = false;
       cokolwiek_tab_F4[i] = false;
       flaga_tab_F4[i] = false;
       bonus_flaga_F4[i] = false;
    }

    ktory_ruch -> Caption = "   0 ";
    ile_flag -> Caption = " 0  ";
    Label1 -> Caption = " 500  ";


     TComponent *Temp;
     for (int i=0; i<500; i++)
     {
       Temp = Components[i];
       if ((dynamic_cast<TImage *>(Temp) != NULL))
       {
          TImage* obj = ((TImage *) Temp);
          obj -> Picture -> LoadFromFile("img/nic.bmp");
       }
     }


    srand(time(NULL));
    for(int i=0; i<100; i++)
    {
        int v = ((rand() % 500) + 0);

        TComponent *Temp;
        for (int j=0; j<500; j++)
        {
           if(j == v)
           {
              if (czy_bomba_F4[j] == false)
              {
                 Temp = Components[j];
                 if ((dynamic_cast<TImage *>(Temp) != NULL))
                 {
                   TImage* obj = ((TImage *) Temp);
                   obj -> Picture -> LoadFromFile("img/bomba.bmp");
                   czy_bomba_F4[j] = true;
                   cokolwiek_tab_F4[j] = true;
                   ile_bomb_F4++;
                 }
               }
               else
               {
                  i--;
               }

            } // if
         } // for j
    } // for i



    for(int i=0; i<500; i++)
    {
     licznik_F4 = 0;
     if (czy_bomba_F4[i] == false)
     {
        if ((i%25) == 0 && i!= 0 && i != 475)
        {
            if ((i+1) >= 0 && (i+1) < 500)
            if (czy_bomba_F4[i+1]==true)
            {
                licznik_F4 ++;
            }

            if ((i-25) >= 0 && (i-25) < 500)
            if (czy_bomba_F4[i-25]==true)
            {
                licznik_F4 ++;
            }

            if ((i-24) >= 0 && (i-24) < 500)
            if (czy_bomba_F4[i-24]==true)
            {
                licznik_F4 ++;
            }

            if ((i+26) >= 0 && (i+26) < 500)
            if (czy_bomba_F4[i+26]==true)
            {
                licznik_F4 ++;
            }

            if ((i+25) >= 0 && (i+25) < 500)
            if (czy_bomba_F4[i+25]==true)
            {
                licznik_F4 ++;
            }
         }


        if (((i+1)%25) == 0 && i!= 24 && i != 499)
        {
            if ((i-1) >= 0 && (i-1) < 500)
            if (czy_bomba_F4[i-1]==true)
            {
                licznik_F4 ++;
            }

            if ((i-26) >= 0 && (i-26) < 500)
            if (czy_bomba_F4[i-26]==true)
            {
                licznik_F4 ++;
            }

            if ((i-25) >= 0 && (i-25) < 500)
            if (czy_bomba_F4[i-25]==true)
            {
                licznik_F4 ++;
            }

            if ((i+25) >= 0 && (i+25) < 500)
            if (czy_bomba_F4[i+25]==true)
            {
                licznik_F4 ++;
            }

            if ((i+24) >= 0 && (i+24) < 500)
            if (czy_bomba_F4[i+24]==true)
            {
                licznik_F4 ++;
            }
        }

        if (i == 0)
        {
            if ((i+1) >= 0 && (i+1) < 500)
            if (czy_bomba_F4[i+1]==true)
            {
                licznik_F4 ++;
            }

            if ((i+25) >= 0 && (i+25) < 500)
            if (czy_bomba_F4[i+25]==true)
            {
                licznik_F4 ++;
            }

            if ((i+26) >= 0 && (i+26) < 500)
            if (czy_bomba_F4[i+26]==true)
            {
                licznik_F4 ++;
            }
        }

        if (i == 24)
        {

            if ((i-1) >= 0 && (i-1) < 500)
            if (czy_bomba_F4[i-1]==true)
            {
                licznik_F4 ++;
            }

            if ((i+24) >= 0 && (i+24) < 500)
            if (czy_bomba_F4[i+24]==true)
            {
                licznik_F4 ++;
            }

            if ((i+25) >= 0 && (i+25) < 500)
            if (czy_bomba_F4[i+25]==true)
            {
                licznik_F4 ++;
            }
        }

        if (i == 475)
        {
            if ((i+1) >= 0 && (i+1) < 500)
            if (czy_bomba_F4[i+1]==true)
            {
                licznik_F4 ++;
            }

            if ((i-24) >= 0 && (i-24) < 500)
            if (czy_bomba_F4[i-24]==true)
            {
                licznik_F4 ++;
            }

            if ((i-25) >= 0 && (i-25) < 500)
            if (czy_bomba_F4[i-25]==true)
            {
                licznik_F4 ++;
            }
        }

        if (i == 499)
        {
            if ((i-1) >= 0 && (i-1) < 500)
            if (czy_bomba_F4[i-1]==true)
            {
                licznik_F4 ++;
            }

            if ((i-25) >= 0 && (i-25) < 500)
            if (czy_bomba_F4[i-25]==true)
            {
                licznik_F4 ++;
            }

            if ((i-26) >= 0 && (i-26) < 500)
            if (czy_bomba_F4[i-26]==true)
            {
                licznik_F4 ++;
            }
        }

        if (i!=0 && i!=24 && i!=475 && i!=499 && (i%25)!=0 && ((i+1)%25)!=0)
        {
            if ((i+1) >= 0 && (i+1) < 500)
            if (czy_bomba_F4[i+1]==true)
            {
                licznik_F4 ++;
            }

            if ((i-1) >= 0 && (i-1) < 500)
            if (czy_bomba_F4[i-1]==true)
            {
                licznik_F4 ++;
            }

            if ((i-24) >= 0 && (i-24) < 500)
            if (czy_bomba_F4[i-24]==true)
            {
                licznik_F4 ++;
            }

            if ((i-25) >= 0 && (i-25) < 500)
            if (czy_bomba_F4[i-25]==true)
            {
                licznik_F4 ++;
            }

            if ((i-26) >= 0 && (i-26) < 500)
            if (czy_bomba_F4[i-26]==true)
            {
                licznik_F4 ++;
            }

            if ((i+24) >= 0 && (i+24) < 500)
            if (czy_bomba_F4[i+24]==true)
            {
                licznik_F4 ++;
            }

            if ((i+25) >= 0 && (i+25) < 500)
            if (czy_bomba_F4[i+25]==true)
            {
                licznik_F4 ++;
            }

            if ((i+26) >= 0 && (i+26) < 500)
            if (czy_bomba_F4[i+26]==true)
            {
                licznik_F4 ++;
            }
        }


             Temp = Components[i];
             if ((dynamic_cast<TImage *>(Temp) != NULL))
             {
                  TImage* obj = ((TImage *) Temp);
                  switch (licznik_F4)
                 {
                    case 1:
                    obj -> Picture -> LoadFromFile("img/1.bmp");
                    cokolwiek_tab_F4[i] = true;
                    break;

                    case 2:
                    obj -> Picture -> LoadFromFile("img/2.bmp");
                    cokolwiek_tab_F4[i] = true;
                    break;

                    case 3:
                    obj -> Picture -> LoadFromFile("img/3.bmp");
                    cokolwiek_tab_F4[i] = true;
                    break;

                    case 4:
                    obj -> Picture -> LoadFromFile("img/4.bmp");
                    cokolwiek_tab_F4[i] = true;
                    break;

                    case 5:
                    obj -> Picture -> LoadFromFile("img/5.bmp");
                    cokolwiek_tab_F4[i] = true;
                    break;

                    case 6:
                    obj -> Picture -> LoadFromFile("img/6.bmp");
                    cokolwiek_tab_F4[i] = true;
                    break;

                    case 7:
                    obj -> Picture -> LoadFromFile("img/7.bmp");
                    cokolwiek_tab_F4[i] = true;
                    break;

                    case 8:
                    obj -> Picture -> LoadFromFile("img/8.bmp");
                    cokolwiek_tab_F4[i] = true;
                    break;

                 }
            }

         } // if
      }// for




      for (int i=500; i<1005; i++)
      {
       Temp = Components[i];
       if ((dynamic_cast<TImage *>(Temp) != NULL))
         {
            TImage* obj = ((TImage *) Temp);
            obj -> Picture -> LoadFromFile("img/zakr.bmp");
         }
       }


}
//---------------------------------------------------------------------------

void __fastcall TForm4::FormClose(TObject *Sender, TCloseAction &Action)
{
      Form4 -> FormCreate(Form4);  
}
//---------------------------------------------------------------------------


void __fastcall TForm4::Image501MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 0, Image501);
}
//---------------------------------------------------------------------------


void __fastcall TForm4::Image502MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 1, Image502);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image503MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 2, Image503);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image504MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 3, Image504);
}
//---------------------------------------------------------------------------


void __fastcall TForm4::Image505MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 4, Image505);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image506MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 5, Image506);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image507MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 6, Image507);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image508MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 7, Image508);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image509MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 8, Image509);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image510MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 9, Image510);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image511MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F4(Sender, Button, Shift, X, Y, 10, Image511);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image512MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 11, Image512);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image513MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 12, Image513);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image514MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 13, Image514);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image515MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 14, Image515);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image516MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 15, Image516);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image517MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 16, Image517);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image518MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 17, Image518);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image519MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 18, Image519);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image520MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 19, Image520);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image521MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 20, Image521);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image522MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 21, Image522);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image523MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    klik_F4(Sender, Button, Shift, X, Y, 22, Image523);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image524MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 23, Image524);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image525MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 24, Image525);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image526MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 25, Image526);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image527MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    klik_F4(Sender, Button, Shift, X, Y, 26, Image527);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image528MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 27, Image528);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image529MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 28, Image529);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image530MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    klik_F4(Sender, Button, Shift, X, Y, 29, Image530);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image531MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 30, Image531);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image532MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    klik_F4(Sender, Button, Shift, X, Y, 31, Image532);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image533MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 32, Image533);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image534MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 33, Image534);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image535MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 34, Image535);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image536MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 35, Image536);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image537MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 36, Image537);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image538MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 37, Image538);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image539MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F4(Sender, Button, Shift, X, Y, 38, Image539);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image540MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 39, Image540);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image541MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 40, Image541);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image542MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 41, Image542);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image543MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 42, Image543);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image544MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 43, Image544);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image545MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 44, Image545);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image546MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 45, Image546);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image547MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 46, Image547);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image548MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 47, Image548);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image549MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 48, Image549);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image550MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 49, Image550);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image551MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 50, Image551);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image552MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 51, Image552);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image553MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 52, Image553);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image554MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 53, Image554);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image555MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 54, Image555);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image556MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 55, Image556);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image557MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 56, Image557);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image558MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 57, Image558);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image559MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 58, Image559);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image560MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F4(Sender, Button, Shift, X, Y, 59, Image560);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image561MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F4(Sender, Button, Shift, X, Y, 60, Image561);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image562MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F4(Sender, Button, Shift, X, Y, 61, Image562);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image563MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 62, Image563);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image564MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 63, Image564);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image565MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 64, Image565);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image566MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F4(Sender, Button, Shift, X, Y, 65, Image566);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image567MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F4(Sender, Button, Shift, X, Y, 66, Image567);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image568MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F4(Sender, Button, Shift, X, Y, 67, Image568);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image569MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F4(Sender, Button, Shift, X, Y, 68, Image569);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image570MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F4(Sender, Button, Shift, X, Y, 69, Image570);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image571MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F4(Sender, Button, Shift, X, Y, 70, Image571);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image572MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F4(Sender, Button, Shift, X, Y, 71, Image572);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image573MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 72, Image573);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image574MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F4(Sender, Button, Shift, X, Y, 73, Image574);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image575MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F4(Sender, Button, Shift, X, Y, 74, Image575);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image576MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F4(Sender, Button, Shift, X, Y, 75, Image576);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image577MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 76, Image577);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image578MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 77, Image578);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image579MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 78, Image579);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image580MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 79, Image580);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image581MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 80, Image581);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image582MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 81, Image582);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image583MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 82, Image583);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image584MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    klik_F4(Sender, Button, Shift, X, Y, 83, Image584);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image585MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 84, Image585);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image586MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 85, Image586);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image587MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 86, Image587);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image588MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 87, Image588);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image589MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 88, Image589);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image590MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 89, Image590);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image591MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 90, Image591);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image592MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 91, Image592);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image593MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 92, Image593);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image594MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 93, Image594);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image595MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 94, Image595);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image596MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 95, Image596);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image597MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 96, Image597);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image598MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 97, Image598);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image599MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 98, Image599);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image600MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 99, Image600);
}
//---------------------------------------------------------------------------


void __fastcall TForm4::Image601MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F4(Sender, Button, Shift, X, Y, 100, Image601);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image602MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 101, Image602);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image603MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 102, Image603);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image604MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 103, Image604);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image605MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 104, Image605);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image606MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 105, Image606);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image607MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F4(Sender, Button, Shift, X, Y, 106, Image607);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image608MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F4(Sender, Button, Shift, X, Y, 107, Image608);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image609MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 108, Image609);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image610MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 109, Image610);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image611MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 110, Image611);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image612MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 111, Image612);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image613MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 112, Image613);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image614MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 113, Image614);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image615MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 114, Image615);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image616MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 115, Image616);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image617MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 116, Image617);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image618MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 117, Image618);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image619MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 118, Image619);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image620MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 119, Image620);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image621MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 120, Image621);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image622MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 121, Image622);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image623MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 122, Image623);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image624MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 123, Image624);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image625MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    klik_F4(Sender, Button, Shift, X, Y, 124, Image625);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image626MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 125, Image626);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image627MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 126, Image627);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image628MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 127, Image628);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image629MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 128, Image629);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image630MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    klik_F4(Sender, Button, Shift, X, Y, 129, Image630);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image631MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    klik_F4(Sender, Button, Shift, X, Y, 130, Image631);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image632MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 131, Image632);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image633MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 132, Image633);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image634MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    klik_F4(Sender, Button, Shift, X, Y, 133, Image634);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image635MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 134, Image635);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image636MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 135, Image636);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image637MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    klik_F4(Sender, Button, Shift, X, Y, 136, Image637);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image638MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    klik_F4(Sender, Button, Shift, X, Y, 137, Image638);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image639MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 138, Image639);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image640MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 139, Image640);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image641MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 140, Image641);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image642MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 141, Image642);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image643MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 142, Image643);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image644MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 143, Image644);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image645MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    klik_F4(Sender, Button, Shift, X, Y, 144, Image645);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image646MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    klik_F4(Sender, Button, Shift, X, Y, 145, Image646);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image647MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 146, Image647);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image648MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 147, Image648);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image649MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 148, Image649);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image650MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 149, Image650);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image651MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 150, Image651);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image652MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 151, Image652);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image653MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 152, Image653);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image654MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    klik_F4(Sender, Button, Shift, X, Y, 153, Image654);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image655MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    klik_F4(Sender, Button, Shift, X, Y, 154, Image655);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image656MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 155, Image656);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image657MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 156, Image657);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image658MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 157, Image658);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image659MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 158, Image659);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image660MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 159, Image660);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image661MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 160, Image661);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image662MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 161, Image662);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image663MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 162, Image663);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image664MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 163, Image664);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image665MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 164, Image665);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image666MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 165, Image666);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image667MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 166, Image667);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image668MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 167, Image668);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image669MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 168, Image669);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image670MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 169, Image670);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image671MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 170, Image671);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image672MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 171, Image672);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image673MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 172, Image673);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image674MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 173, Image674);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image675MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 174, Image675);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image676MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 175, Image676);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image677MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 176, Image677);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image678MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 177, Image678);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image679MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 178, Image679);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image680MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 179, Image680);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image681MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    klik_F4(Sender, Button, Shift, X, Y, 180, Image681);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image682MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 181, Image682);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image683MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 182, Image683);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image684MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 183, Image684);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image685MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 184, Image685);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image686MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 185, Image686);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image687MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 186, Image687);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image688MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 187, Image688);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image689MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 188, Image689);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image690MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    klik_F4(Sender, Button, Shift, X, Y, 189, Image690);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image691MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 190, Image691);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image692MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 191, Image692);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image693MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 192, Image693);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image694MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 193, Image694);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image695MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 194, Image695);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image696MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 195, Image696);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image697MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 196, Image697);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image698MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 197, Image698);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image699MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 198, Image699);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image700MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 199, Image700);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image701MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 200, Image701);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image702MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 201, Image702);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image703MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    klik_F4(Sender, Button, Shift, X, Y, 202, Image703);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image704MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 203, Image704);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image705MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 204, Image705);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image706MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 205, Image706);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image707MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 206, Image707);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image708MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 207, Image708);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image709MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 208, Image709);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image710MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 209, Image710);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image711MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 210, Image711);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image712MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 211, Image712);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image713MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 212, Image713);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image714MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 213, Image714);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image715MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 214, Image715);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image716MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 215, Image716);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image717MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F4(Sender, Button, Shift, X, Y, 216, Image717);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image718MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 217, Image718);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image719MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 218, Image719);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image720MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 219, Image720);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image721MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 220, Image721);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image722MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 221, Image722);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image723MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 222, Image723);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image724MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 223, Image724);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image725MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 224, Image725);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image726MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 225, Image726);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image727MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 226, Image727);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image728MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 227, Image728);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image729MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 228, Image729);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image730MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 229, Image730);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image731MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 230, Image731);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image732MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 231, Image732);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image733MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 232, Image733);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image734MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 233, Image734);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image735MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 234, Image735);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image736MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 235, Image736);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image737MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 236, Image737);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image738MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 237, Image738);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image739MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 238, Image739);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image740MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 239, Image740);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image741MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 240, Image741);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image742MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 241, Image742);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image743MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F4(Sender, Button, Shift, X, Y, 242, Image743);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image744MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F4(Sender, Button, Shift, X, Y, 243, Image744);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image745MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 244, Image745);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image746MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 245, Image746);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image747MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 246, Image747);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image748MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 247, Image748);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image749MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 248, Image749);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image750MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 249, Image750);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image751MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 250, Image751);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image752MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 251, Image752);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image753MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 252, Image753);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image754MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 253, Image754);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image755MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 254, Image755);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image756MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 255, Image756);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image757MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 256, Image757);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image758MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 257, Image758);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image759MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 258, Image759);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image760MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 259, Image760);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image761MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 260, Image761);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image762MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 261, Image762);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image763MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 262, Image763);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image764MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 263, Image764);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image765MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    klik_F4(Sender, Button, Shift, X, Y, 264, Image765);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image766MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 265, Image766);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image767MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 266, Image767);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image768MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 267, Image768);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image769MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 268, Image769);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image770MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 269, Image770);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image771MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 270, Image771);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image772MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 271, Image772);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image773MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 272, Image773);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image774MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 273, Image774);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image775MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 274, Image775);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image776MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 275, Image776);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image777MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 276, Image777);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image778MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 277, Image778);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image779MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 278, Image779);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image780MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 279, Image780);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image781MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 280, Image781);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image782MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 281, Image782);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image783MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 282, Image783);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image784MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 283, Image784);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image785MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 284, Image785);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image786MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 285, Image786);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image787MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 286, Image787);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image788MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 287, Image788);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image789MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 288, Image789);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image790MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 289, Image790);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image791MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 290, Image791);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image792MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 291, Image792);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image793MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 292, Image793);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image794MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 293, Image794);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image795MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 294, Image795);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image796MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 295, Image796);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image797MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 296, Image797);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image798MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 297, Image798);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image799MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 298, Image799);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image800MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 299, Image800);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image801MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F4(Sender, Button, Shift, X, Y, 300, Image801);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image802MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F4(Sender, Button, Shift, X, Y, 301, Image802);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image803MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 302, Image803);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image804MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F4(Sender, Button, Shift, X, Y, 303, Image804);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image805MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F4(Sender, Button, Shift, X, Y, 304, Image805);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image806MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 305, Image806);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image807MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F4(Sender, Button, Shift, X, Y, 306, Image807);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image808MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F4(Sender, Button, Shift, X, Y, 307, Image808);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image809MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 308, Image809);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image810MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 309, Image810);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image811MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 310, Image811);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image812MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 311, Image812);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image813MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 312, Image813);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image814MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 313, Image814);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image815MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 314, Image815);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image816MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 315, Image816);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image817MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 316, Image817);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image818MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 317, Image818);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image819MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 318, Image819);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image820MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 319, Image820);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image821MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 320, Image821);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image822MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 321, Image822);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image823MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 322, Image823);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image824MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 323, Image824);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image825MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 324, Image825);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image826MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F4(Sender, Button, Shift, X, Y, 325, Image826);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image827MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F4(Sender, Button, Shift, X, Y, 326, Image827);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image828MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F4(Sender, Button, Shift, X, Y, 327, Image828);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image829MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F4(Sender, Button, Shift, X, Y, 328, Image829);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image830MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F4(Sender, Button, Shift, X, Y, 329, Image830);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image831MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F4(Sender, Button, Shift, X, Y, 330, Image831);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image832MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F4(Sender, Button, Shift, X, Y, 331, Image832);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image833MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 332, Image833);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image834MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F4(Sender, Button, Shift, X, Y, 333, Image834);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image835MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F4(Sender, Button, Shift, X, Y, 334, Image835);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image836MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F4(Sender, Button, Shift, X, Y, 335, Image836);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image837MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F4(Sender, Button, Shift, X, Y, 336, Image837);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image838MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 337, Image838);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image839MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F4(Sender, Button, Shift, X, Y, 338, Image839);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image840MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 339, Image840);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image841MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 340, Image841);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image842MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 341, Image842);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image843MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 342, Image843);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image844MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 343, Image844);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image845MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 344, Image845);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image846MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 345, Image846);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image847MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 346, Image847);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image848MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 347, Image848);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image849MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F4(Sender, Button, Shift, X, Y, 348, Image849);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image850MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 349, Image850);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image851MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    klik_F4(Sender, Button, Shift, X, Y, 350, Image851);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image852MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 351, Image852);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image853MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 352, Image853);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image854MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 353, Image854);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image855MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 354, Image855);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image856MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 355, Image856);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image857MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 356, Image857);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image858MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 357, Image858);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image859MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 358, Image859);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image860MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 359, Image860);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image861MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 360, Image861);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image862MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 361, Image862);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image863MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 362, Image863);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image864MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 363, Image864);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image865MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 364, Image865);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image866MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 365, Image866);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image867MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 366, Image867);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image868MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 367, Image868);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image869MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 368, Image869);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image870MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 369, Image870);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image871MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 370, Image871);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image872MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 371, Image872);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image873MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 372, Image873);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image874MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 373, Image874);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image875MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 374, Image875);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image876MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F4(Sender, Button, Shift, X, Y, 375, Image876);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image877MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F4(Sender, Button, Shift, X, Y, 376, Image877);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image878MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        klik_F4(Sender, Button, Shift, X, Y, 377, Image878);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image879MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F4(Sender, Button, Shift, X, Y, 378, Image879);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image880MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 379, Image880);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image881MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 380, Image881);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image882MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 381, Image882);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image883MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 382, Image883);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image884MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 383, Image884);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image885MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 384, Image885);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image886MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 385, Image886);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image887MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 386, Image887);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image888MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 387, Image888);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image889MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 388, Image889);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image890MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 389, Image890);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image891MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 390, Image891);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image892MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 391, Image892);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image893MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 392, Image893);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image894MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 393, Image894);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image895MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 394, Image895);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image896MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 395, Image896);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image897MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 396, Image897);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image898MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 397, Image898);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image899MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 398, Image899);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image900MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 399, Image900);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image901MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F4(Sender, Button, Shift, X, Y, 400, Image901);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image902MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 401, Image902);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image903MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 402, Image903);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image904MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 403, Image904);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image905MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 404, Image905);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image906MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 405, Image906);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image907MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 406, Image907);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image908MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 407, Image908);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image909MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 408, Image909);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image910MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F4(Sender, Button, Shift, X, Y, 409, Image910);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image911MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F4(Sender, Button, Shift, X, Y, 410, Image911);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image912MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 411, Image912);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image913MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 412, Image913);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image914MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 413, Image914);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image915MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 414, Image915);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image916MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 415, Image916);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image917MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 416, Image917);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image918MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 417, Image918);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image919MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 418, Image919);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image920MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 419, Image920);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image921MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F4(Sender, Button, Shift, X, Y, 420, Image921);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image922MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F4(Sender, Button, Shift, X, Y, 421, Image922);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image923MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F4(Sender, Button, Shift, X, Y, 422, Image923);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image924MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 423, Image924);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image925MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F4(Sender, Button, Shift, X, Y, 424, Image925);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image926MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F4(Sender, Button, Shift, X, Y, 425, Image926);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image927MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 426, Image927);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image928MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F4(Sender, Button, Shift, X, Y, 427, Image928);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image929MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F4(Sender, Button, Shift, X, Y, 428, Image929);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image930MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 429, Image930);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image931MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 430, Image931);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image932MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 431, Image932);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image933MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 432, Image933);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image934MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 433, Image934);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image935MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 434, Image935);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image936MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 435, Image936);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image937MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 436, Image937);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image938MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 437, Image938);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image939MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 438, Image939);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image940MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 439, Image940);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image941MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 440, Image941);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image942MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    klik_F4(Sender, Button, Shift, X, Y, 441, Image942);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image943MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 442, Image943);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image944MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 443, Image944);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image945MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 444, Image945);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image946MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 445, Image946);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image947MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 446, Image947);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image948MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 447, Image948);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image949MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 448, Image949);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image950MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 449, Image950);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image951MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 450, Image951);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image952MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 451, Image952);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image953MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 452, Image953);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image954MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 453, Image954);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image955MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 454, Image955);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image956MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 455, Image956);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image957MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 456, Image957);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image958MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 457, Image958);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image959MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 458, Image959);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image960MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 459, Image960);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image961MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 460, Image961);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image962MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 461, Image962);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image963MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 462, Image963);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image964MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 463, Image964);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image965MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 464, Image965);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image966MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 465, Image966);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image967MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 466, Image967);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image968MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F4(Sender, Button, Shift, X, Y, 467, Image968);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image969MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 468, Image969);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image970MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 469, Image970);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image971MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 470, Image971);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image972MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 471, Image972);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image973MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 472, Image973);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image974MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 473, Image974);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image975MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 474, Image975);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image976MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F4(Sender, Button, Shift, X, Y, 475, Image976);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image977MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 476, Image977);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image978MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 477, Image978);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image979MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 478, Image979);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image980MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 479, Image980);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image981MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 480, Image981);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image982MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F4(Sender, Button, Shift, X, Y, 481, Image982);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image983MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F4(Sender, Button, Shift, X, Y, 482, Image983);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image984MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F4(Sender, Button, Shift, X, Y, 483, Image984);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image985MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 484, Image985);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image986MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 485, Image986);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image987MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 486, Image987);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image988MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 487, Image988);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image989MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 488, Image989);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image990MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 489, Image990);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image991MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 490, Image991);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image992MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 491, Image992);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image993MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F4(Sender, Button, Shift, X, Y, 492, Image993);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image994MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 493, Image994);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image995MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 494, Image995);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image996MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 495, Image996);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image997MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 496, Image997);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image998MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 497, Image998);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image999MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 498, Image999);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image1000MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F4(Sender, Button, Shift, X, Y, 499, Image1000);
}
//---------------------------------------------------------------------------


