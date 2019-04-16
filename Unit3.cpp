//---------------------------------------------------------------------------

#include <ctime>
#include <iostream>
#include <cstdlib>
#include <vcl.h>
#pragma hdrstop
#include "mmsystem.h"

#include "Unit3.h"
#include "Unit6.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;


bool czy_bomba_F3[256];
int licznik_F3 = 0;
bool flaga_F3 = false;
int ktora_bomba_F3 = 0; //do flag
int ruchy_F3 = 256;
int odliczanie_F3 = 0;
int ile_bomb_F3 = 0; //do porownywania z ruchami
bool flaga_tab_F3[256];
bool cokolwiek_tab_F3[256];
bool odwiedzona_F3[256];
bool bonus_flaga_F3[256];
int jednorazowo_F3 = 0;


void zmien_visible_na_true_F3();
void zmien_visible_na_false_F3();
void odkryj_bez_numerkow_F3(int ind);
void czerwona_F3(int indeks);
void bon_flaga_dzialanie_F3(int indeks, TImage* t, int numer);



void sprawdz_czy_wygrana_F3()
 {
     if(ile_bomb_F3 == ruchy_F3 && ktora_bomba_F3 == 40)
     {
        sndPlaySound("snd/win.wav", SND_ASYNC);
        Application -> MessageBox ("Brawo! Wygrana!", "Koniec gry", MB_OK);
        Form3 -> FormCreate(Form3);
     }
 }


 void klik_F3(TObject *Sender,
  TMouseButton Button, TShiftState Shift, int X, int Y, int indeks, TImage* t)
 {
     if(Shift.Contains(ssLeft))
    {
      for(int i=0; i<256; i++)
      {
         if(i == indeks)
         {
           if (flaga_tab_F3[i] == false)
           {
              if(czy_bomba_F3[indeks] == true)
             {
                if (jednorazowo_F3 == 0)
                {
                        
                        Form6 = new TForm6(Application);
                        Form6 -> ShowModal();

                        if (Form6 -> Label4 -> Visible == true)
                        {
                            t -> Picture -> LoadFromFile("img/flaga.bmp");
                            flaga_tab_F3[i] = true;
                            ktora_bomba_F3++;
                            Form3 -> ile_flag -> Caption = " ";
                            Form3 -> ile_flag -> Caption = (Form3 -> ile_flag -> Caption + ktora_bomba_F3 + "   ");
                        }
                        else
                        {
                            t -> Visible = false;
                            sndPlaySound("snd/bum.wav", SND_ASYNC);
                            zmien_visible_na_false_F3();
                            czerwona_F3(indeks);
                            Application -> MessageBox ("BUM! Przegrana!", "Koniec gry", MB_OK);
                         }
                        jednorazowo_F3++;
                        delete Form6;
                }
                else
                {
                   t -> Visible = false;
                   sndPlaySound("snd/bum.wav", SND_ASYNC);
                   zmien_visible_na_false_F3();
                   czerwona_F3(indeks);
                   Application -> MessageBox ("BUM! Przegrana!", "Koniec gry", MB_OK);
                }
             }
             else if(czy_bomba_F3[indeks] == false)
             {
                t -> Visible = false;
                odliczanie_F3 ++;
                odkryj_bez_numerkow_F3(indeks);
                if (cokolwiek_tab_F3[indeks] == true && odwiedzona_F3[indeks] == false){ruchy_F3--;}
                Form3 -> ktory_ruch -> Caption = "   ";
                Form3 -> ktory_ruch -> Caption = (Form3 -> ktory_ruch -> Caption + odliczanie_F3 + " ");
                


                Form3 -> Label1 -> Caption = "   ";
                Form3 -> Label1 -> Caption = Form3 -> Label1 -> Caption + ruchy_F3 + " ";
             }
             } } } // if, if i for
    }

    if(Shift.Contains(ssRight))
    {
      for(int i=0; i<256; i++)
      {
         if(i == indeks)
         {
           if (flaga_tab_F3[i] == false)
           {
              t -> Picture -> LoadFromFile("img/flaga.bmp");
              flaga_tab_F3[i] = true;
              ktora_bomba_F3++;
              Form3 -> ile_flag -> Caption = " ";
              Form3 -> ile_flag -> Caption = (Form3 -> ile_flag -> Caption + ktora_bomba_F3 + "   ");
           }
           else if (flaga_tab_F3[i] == true)
           {
               t -> Picture -> LoadFromFile("img/zakr.bmp");
               flaga_tab_F3[i] = false;
               ktora_bomba_F3--;
               Form3 -> ile_flag -> Caption = " ";
               Form3 -> ile_flag -> Caption = (Form3 -> ile_flag -> Caption + ktora_bomba_F3 + "   ");
           }
         } // if i == indeks
       } // for
    } // if

    sprawdz_czy_wygrana_F3();
 }



 void zmien_visible_na_true_F3()
 {
   TComponent *Temp;
   for (int i=256; i<513; i++)
   {
      Temp = Form3 -> Components[i];
      if ((dynamic_cast<TImage *>(Temp) != NULL))
      {
          TImage* obj = ((TImage *) Temp);
          obj -> Visible = true;
      }
   }
 }


void zmien_visible_na_false_F3()
 {
   TComponent *Temp;
   for (int i=256; i<513; i++)
   {
      Temp = Form3 -> Components[i];
      if ((dynamic_cast<TImage *>(Temp) != NULL))
      {
          TImage* obj = ((TImage *) Temp);
          obj -> Visible = false;
      }
   }
 }


 void czerwona_F3(int indeks)
 {
    TComponent *Temp;
    for (int i=0; i<256; i++)
    {
       if(i == indeks)
       {
           Temp = Form3 -> Components[i];
           if ((dynamic_cast<TImage *>(Temp) != NULL))
          {
             TImage* obj = ((TImage *) Temp);
             obj -> Picture -> LoadFromFile("img/kliknieta.bmp");
          }
       }
    }
 }




 void odkryj_bez_numerkow_F3(int ind)
 {
     TComponent *Temp;
     for(int i=0; i<256; i++) // dla tablicy cokolwiek
     {
       if (i == ind)
       {
        for(int j=256; j<513; j++) // dla komponentów
        {
           if (j == i+256)
           {
             Temp = Form3 -> Components[j];
             if ((dynamic_cast<TImage *>(Temp) != NULL))
             {
               TImage* obj = ((TImage *) Temp);


               if(cokolwiek_tab_F3[i] == false && odwiedzona_F3[i] == false)
               {

                  odwiedzona_F3[i] = true;
                  obj -> Visible = false;
                  ruchy_F3--;


                  if ((i%16) == 0 && i!= 0 && i != 240)
                  {
                      if(i+1 < 256){odkryj_bez_numerkow_F3(ind+1);}
                      if(i-15 >= 0){odkryj_bez_numerkow_F3(ind-15);}
                      if(i-16 >= 0){odkryj_bez_numerkow_F3(ind-16);}
                      if(i+16 < 256){odkryj_bez_numerkow_F3(ind+16);}
                      if(i+17 < 256){odkryj_bez_numerkow_F3(ind+17);}
                  }
                  if (((i+1)%16) == 0 && i!= 15 && i != 255)
                  {
                      if(i-1 >= 0){odkryj_bez_numerkow_F3(ind-1);}
                      if(i-16 >= 0){odkryj_bez_numerkow_F3(ind-16);}
                      if(i-17 >= 0){odkryj_bez_numerkow_F3(ind-17);}
                      if(i+15 < 256){odkryj_bez_numerkow_F3(ind+15);}
                      if(i+16 < 256){odkryj_bez_numerkow_F3(ind+16);}
                  }
                  if (i == 0)
                  {
                      if(i+1 < 256){odkryj_bez_numerkow_F3(ind+1);}
                      if(i+16 < 256){odkryj_bez_numerkow_F3(ind+16);}
                      if(i+17 < 256){odkryj_bez_numerkow_F3(ind+17);}
                  }
                  if (i == 15)
                  {
                      if(i-1 >= 0){odkryj_bez_numerkow_F3(ind-1);}
                      if(i+15 < 256){odkryj_bez_numerkow_F3(ind+15);}
                      if(i+16 < 256){odkryj_bez_numerkow_F3(ind+16);}
                  }
                  if (i == 240)
                  {
                      if(i+1 < 256){odkryj_bez_numerkow_F3(ind+1);}
                      if(i-15 >= 0){odkryj_bez_numerkow_F3(ind-15);}
                      if(i-16 >= 0){odkryj_bez_numerkow_F3(ind-16);}
                  }
                  if (i == 255)
                  {
                      if(i-1 >= 0){odkryj_bez_numerkow_F3(ind-1);}
                      if(i-16 >= 0){odkryj_bez_numerkow_F3(ind-16);}
                      if(i-17 >= 0){odkryj_bez_numerkow_F3(ind-17);}
                  }
                  if (i!=0 && i!=15 && i!=240 && i!=255 && (i%16)!=0 && ((i+1)%16)!=0)
                  {
                      if(i+1 < 256){odkryj_bez_numerkow_F3(ind+1);}
                      if(i-1 >= 0){odkryj_bez_numerkow_F3(ind-1);}
                      if(i-15 >= 0){odkryj_bez_numerkow_F3(ind-15);}
                      if(i-16 >= 0){odkryj_bez_numerkow_F3(ind-16);}
                      if(i-17 >= 0){odkryj_bez_numerkow_F3(ind-17);}
                      if(i+15 < 256){odkryj_bez_numerkow_F3(ind+15);}
                      if(i+16 < 256){odkryj_bez_numerkow_F3(ind+16);}
                      if(i+17 < 256){odkryj_bez_numerkow_F3(ind+17);}
                  }


              } // if


              if(cokolwiek_tab_F3[i] == true && odwiedzona_F3[i] == false)
              {
                  if ((i%16) == 0 && i!= 0 && i != 240)
                  {
                       if(cokolwiek_tab_F3[i-16] == false || cokolwiek_tab_F3[i-15] == false || cokolwiek_tab_F3[i+1] == false
                       || cokolwiek_tab_F3[i+16] == false || cokolwiek_tab_F3[i+17] == false)
                       {
                       odwiedzona_F3[i] = true;
                       obj -> Visible = false;
                       ruchy_F3--;
                       }
                  }
                  if (((i+1)%16) == 0 && i!= 15 && i != 255)
                  {
                      if(cokolwiek_tab_F3[i-17] == false || cokolwiek_tab_F3[i-16] == false || cokolwiek_tab_F3[i-1] == false
                      || cokolwiek_tab_F3[i+15] == false || cokolwiek_tab_F3[i+16] == false)
                      {
                       odwiedzona_F3[i] = true;
                       obj -> Visible = false;
                       ruchy_F3--;
                      }
                  }
                  if (i == 0)
                  {
                      if(cokolwiek_tab_F3[i+1] == false || cokolwiek_tab_F3[i+16] == false || cokolwiek_tab_F3[i+17] == false)
                      {
                       odwiedzona_F3[i] = true;
                       obj -> Visible = false;
                       ruchy_F3--;
                      }
                  }
                  if (i == 15)
                  {
                      if(cokolwiek_tab_F3[i-1] == false ||cokolwiek_tab_F3[i+15] == false || cokolwiek_tab_F3[i+16] == false )
                      {
                       odwiedzona_F3[i] = true;
                       obj -> Visible = false;
                       ruchy_F3--;
                      }
                  }
                  if (i == 240)
                  {
                      if(cokolwiek_tab_F3[i-16] == false || cokolwiek_tab_F3[i-15] == false || cokolwiek_tab_F3[i+1] == false)
                      {
                       odwiedzona_F3[i] = true;
                       obj -> Visible = false;
                       ruchy_F3--;
                      }
                  }
                  if (i == 255)
                  {
                      if(cokolwiek_tab_F3[i-17] == false || cokolwiek_tab_F3[i-16] == false || cokolwiek_tab_F3[i-1] == false)
                      {
                       odwiedzona_F3[i] = true;
                       obj -> Visible = false;
                       ruchy_F3--;
                      }
                  }
                  if (i!=0 && i!=15 && i!=240 && i!=255 && (i%16)!=0 && ((i+1)%16)!=0)
                  {
                      if(cokolwiek_tab_F3[i-17] == false || cokolwiek_tab_F3[i-16] == false || cokolwiek_tab_F3[i-15] == false || cokolwiek_tab_F3[i-1] == false
                      || cokolwiek_tab_F3[i+1] == false || cokolwiek_tab_F3[i+15] == false || cokolwiek_tab_F3[i+16] == false || cokolwiek_tab_F3[i+17] == false)
                      {
                       odwiedzona_F3[i] = true;
                       obj -> Visible = false;
                       ruchy_F3--;
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
__fastcall TForm3::TForm3(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------


void __fastcall TForm3::FormCreate(TObject *Sender)
{

    zmien_visible_na_true_F3();

    ruchy_F3 = 256;
    ile_bomb_F3 = 0;
    ktora_bomba_F3 = 0;
    odliczanie_F3 = 0;
    jednorazowo_F3 = 0;

    for (int i=0; i<256; i++)
    {
       czy_bomba_F3[i] = false;
       odwiedzona_F3[i] = false;
       cokolwiek_tab_F3[i] = false;
       flaga_tab_F3[i] = false;
       bonus_flaga_F3[i] = false;
    }

    ktory_ruch -> Caption = "   0 ";
    ile_flag -> Caption = " 0  ";
    Label1 -> Caption = " 256  ";


     TComponent *Temp;
     for (int i=0; i<256; i++)
     {
       Temp = Components[i];
       if ((dynamic_cast<TImage *>(Temp) != NULL))
       {
          TImage* obj = ((TImage *) Temp);
          obj -> Picture -> LoadFromFile("img/nic.bmp");
       }
     }


    srand(time(NULL));
    for(int i=0; i<40; i++)
    {
        int v = ((rand() % 256) + 0);

        TComponent *Temp;
        for (int j=0; j<256; j++)
        {
           if(j == v)
           {
              if (czy_bomba_F3[j] == false)
              {
                 Temp = Components[j];
                 if ((dynamic_cast<TImage *>(Temp) != NULL))
                 {
                   TImage* obj = ((TImage *) Temp);
                   obj -> Picture -> LoadFromFile("img/bomba.bmp");
                   czy_bomba_F3[j] = true;
                   cokolwiek_tab_F3[j] = true;
                   ile_bomb_F3++;
                 }
               }
               else
               {
                  i--;
               }

            } // if
         } // for j
    } // for i



    for(int i=0; i<256; i++)
    {
     licznik_F3 = 0;
     if (czy_bomba_F3[i] == false)
     {
        if ((i%16) == 0 && i!= 0 && i != 240)
        {
            if ((i+1) >= 0 && (i+1) < 256)
            if (czy_bomba_F3[i+1]==true)
            {
                licznik_F3 ++;
            }

            if ((i-16) >= 0 && (i-16) < 256)
            if (czy_bomba_F3[i-16]==true)
            {
                licznik_F3 ++;
            }

            if ((i-15) >= 0 && (i-15) < 256)
            if (czy_bomba_F3[i-15]==true)
            {
                licznik_F3 ++;
            }

            if ((i+17) >= 0 && (i+17) < 256)
            if (czy_bomba_F3[i+17]==true)
            {
                licznik_F3 ++;
            }

            if ((i+16) >= 0 && (i+16) < 256)
            if (czy_bomba_F3[i+16]==true)
            {
                licznik_F3 ++;
            }
         }


        if (((i+1)%16) == 0 && i!= 15 && i != 255)
        {
            if ((i-1) >= 0 && (i-1) < 256)
            if (czy_bomba_F3[i-1]==true)
            {
                licznik_F3 ++;
            }

            if ((i-17) >= 0 && (i-17) < 256)
            if (czy_bomba_F3[i-17]==true)
            {
                licznik_F3 ++;
            }

            if ((i-16) >= 0 && (i-16) < 256)
            if (czy_bomba_F3[i-16]==true)
            {
                licznik_F3 ++;
            }

            if ((i+16) >= 0 && (i+16) < 256)
            if (czy_bomba_F3[i+16]==true)
            {
                licznik_F3 ++;
            }

            if ((i+15) >= 0 && (i+15) < 256)
            if (czy_bomba_F3[i+15]==true)
            {
                licznik_F3 ++;
            }
        }

        if (i == 0)
        {
            if ((i+1) >= 0 && (i+1) < 256)
            if (czy_bomba_F3[i+1]==true)
            {
                licznik_F3 ++;
            }

            if ((i+16) >= 0 && (i+16) < 256)
            if (czy_bomba_F3[i+16]==true)
            {
                licznik_F3 ++;
            }

            if ((i+17) >= 0 && (i+17) < 256)
            if (czy_bomba_F3[i+17]==true)
            {
                licznik_F3 ++;
            }
        }

        if (i == 15)
        {

            if ((i-1) >= 0 && (i-1) < 256)
            if (czy_bomba_F3[i-1]==true)
            {
                licznik_F3 ++;
            }

            if ((i+15) >= 0 && (i+15) < 256)
            if (czy_bomba_F3[i+15]==true)
            {
                licznik_F3 ++;
            }

            if ((i+16) >= 0 && (i+16) < 256)
            if (czy_bomba_F3[i+16]==true)
            {
                licznik_F3 ++;
            }
        }

        if (i == 240)
        {
            if ((i+1) >= 0 && (i+1) < 256)
            if (czy_bomba_F3[i+1]==true)
            {
                licznik_F3 ++;
            }

            if ((i-15) >= 0 && (i-15) < 256)
            if (czy_bomba_F3[i-15]==true)
            {
                licznik_F3 ++;
            }

            if ((i-16) >= 0 && (i-16) < 256)
            if (czy_bomba_F3[i-16]==true)
            {
                licznik_F3 ++;
            }
        }

        if (i == 255)
        {
            if ((i-1) >= 0 && (i-1) < 256)
            if (czy_bomba_F3[i-1]==true)
            {
                licznik_F3 ++;
            }

            if ((i-16) >= 0 && (i-16) < 256)
            if (czy_bomba_F3[i-16]==true)
            {
                licznik_F3 ++;
            }

            if ((i-17) >= 0 && (i-17) < 256)
            if (czy_bomba_F3[i-17]==true)
            {
                licznik_F3 ++;
            }
        }

        if (i!=0 && i!=15 && i!=240 && i!=255 && (i%16)!=0 && ((i+1)%16)!=0)
        {
            if ((i+1) >= 0 && (i+1) < 256)
            if (czy_bomba_F3[i+1]==true)
            {
                licznik_F3 ++;
            }

            if ((i-1) >= 0 && (i-1) < 256)
            if (czy_bomba_F3[i-1]==true)
            {
                licznik_F3 ++;
            }

            if ((i-15) >= 0 && (i-15) < 256)
            if (czy_bomba_F3[i-15]==true)
            {
                licznik_F3 ++;
            }

            if ((i-16) >= 0 && (i-16) < 256)
            if (czy_bomba_F3[i-16]==true)
            {
                licznik_F3 ++;
            }

            if ((i-17) >= 0 && (i-17) < 256)
            if (czy_bomba_F3[i-17]==true)
            {
                licznik_F3 ++;
            }

            if ((i+15) >= 0 && (i+15) < 256)
            if (czy_bomba_F3[i+15]==true)
            {
                licznik_F3 ++;
            }

            if ((i+16) >= 0 && (i+16) < 256)
            if (czy_bomba_F3[i+16]==true)
            {
                licznik_F3 ++;
            }

            if ((i+17) >= 0 && (i+17) < 256)
            if (czy_bomba_F3[i+17]==true)
            {
                licznik_F3 ++;
            }
        }


             Temp = Components[i];
             if ((dynamic_cast<TImage *>(Temp) != NULL))
             {
                  TImage* obj = ((TImage *) Temp);
                  switch (licznik_F3)
                 {
                    case 1:
                    obj -> Picture -> LoadFromFile("img/1.bmp");
                    cokolwiek_tab_F3[i] = true;
                    break;

                    case 2:
                    obj -> Picture -> LoadFromFile("img/2.bmp");
                    cokolwiek_tab_F3[i] = true;
                    break;

                    case 3:
                    obj -> Picture -> LoadFromFile("img/3.bmp");
                    cokolwiek_tab_F3[i] = true;
                    break;

                    case 4:
                    obj -> Picture -> LoadFromFile("img/4.bmp");
                    cokolwiek_tab_F3[i] = true;
                    break;

                    case 5:
                    obj -> Picture -> LoadFromFile("img/5.bmp");
                    cokolwiek_tab_F3[i] = true;
                    break;

                    case 6:
                    obj -> Picture -> LoadFromFile("img/6.bmp");
                    cokolwiek_tab_F3[i] = true;
                    break;

                    case 7:
                    obj -> Picture -> LoadFromFile("img/7.bmp");
                    cokolwiek_tab_F3[i] = true;
                    break;

                    case 8:
                    obj -> Picture -> LoadFromFile("img/8.bmp");
                    cokolwiek_tab_F3[i] = true;
                    break;

                 }
            }

         } // if
      }// for


      //bon_flaga_F3();


      for (int i=256; i<513; i++)
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



void __fastcall TForm3::Image257MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 0, Image257);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image258MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 1, Image258);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image259MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 2, Image259);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image260MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 3, Image260);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image261MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 4, Image261);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image262MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 5, Image262);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image263MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 6, Image263);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image264MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 7, Image264);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image265MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 8, Image265);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image266MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 9, Image266);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image267MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 10, Image267);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image268MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 11, Image268);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image269MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 12, Image269);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image270MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 13, Image270);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image271MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 14, Image271);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image272MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 15, Image272);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image273MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 16, Image273);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image274MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 17, Image274);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image275MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 18, Image275);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image276MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 19, Image276);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image277MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 20, Image277);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image278MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F3(Sender, Button, Shift, X, Y, 21, Image278);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image279MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F3(Sender, Button, Shift, X, Y, 22, Image279);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image280MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 23, Image280);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image281MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F3(Sender, Button, Shift, X, Y, 24, Image281);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image282MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 25, Image282);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image283MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F3(Sender, Button, Shift, X, Y, 26, Image283);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image284MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 27, Image284);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image285MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 28, Image285);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image286MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 29, Image286);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image287MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 30, Image287);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image288MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 31, Image288);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image289MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 32, Image289);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image290MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 33, Image290);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image291MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    klik_F3(Sender, Button, Shift, X, Y, 34, Image291);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image292MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    klik_F3(Sender, Button, Shift, X, Y, 35, Image292);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image293MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 36, Image293);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image294MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    klik_F3(Sender, Button, Shift, X, Y, 37, Image294);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image295MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    klik_F3(Sender, Button, Shift, X, Y, 38, Image295);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image296MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    klik_F3(Sender, Button, Shift, X, Y, 39, Image296);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image297MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 40, Image297);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image298MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 41, Image298);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image299MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 42, Image299);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image300MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 43, Image300);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image301MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 44, Image301);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image302MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 45, Image302);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image303MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 46, Image303);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image304MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 47, Image304);
}
//---------------------------------------------------------------------------


void __fastcall TForm3::Image305MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 48, Image305);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image306MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    klik_F3(Sender, Button, Shift, X, Y, 49, Image306);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image307MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 50, Image307);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image308MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 51, Image308);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image309MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    klik_F3(Sender, Button, Shift, X, Y, 52, Image309);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image310MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    klik_F3(Sender, Button, Shift, X, Y, 53, Image310);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image311MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    klik_F3(Sender, Button, Shift, X, Y, 54, Image311);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image312MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    klik_F3(Sender, Button, Shift, X, Y, 55, Image312);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image313MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    klik_F3(Sender, Button, Shift, X, Y, 56, Image313);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image314MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    klik_F3(Sender, Button, Shift, X, Y, 57, Image314);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image315MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 58, Image315);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image316MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 59, Image316);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image317MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 60, Image317);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image318MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 61, Image318);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image319MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    klik_F3(Sender, Button, Shift, X, Y, 62, Image319);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image320MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    klik_F3(Sender, Button, Shift, X, Y, 63, Image320);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image321MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 64, Image321);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image322MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    klik_F3(Sender, Button, Shift, X, Y, 65, Image322);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image323MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    klik_F3(Sender, Button, Shift, X, Y, 66, Image323);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image324MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    klik_F3(Sender, Button, Shift, X, Y, 67, Image324);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image325MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    klik_F3(Sender, Button, Shift, X, Y, 68, Image325);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image326MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    klik_F3(Sender, Button, Shift, X, Y, 69, Image326);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image327MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    klik_F3(Sender, Button, Shift, X, Y, 70, Image327);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image328MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    klik_F3(Sender, Button, Shift, X, Y, 71, Image328);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image329MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    klik_F3(Sender, Button, Shift, X, Y, 72, Image329);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image330MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    klik_F3(Sender, Button, Shift, X, Y, 73, Image330);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image331MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    klik_F3(Sender, Button, Shift, X, Y, 74, Image331);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image332MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    klik_F3(Sender, Button, Shift, X, Y, 75, Image332);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image333MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 76, Image333);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image334MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 77, Image334);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image335MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 78, Image335);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image336MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 79, Image336);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image337MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 80, Image337);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image338MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 81, Image338);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image339MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 82, Image339);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image340MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 83, Image340);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image341MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 84, Image341);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image342MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F3(Sender, Button, Shift, X, Y, 85, Image342);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image343MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F3(Sender, Button, Shift, X, Y, 86, Image343);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image344MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F3(Sender, Button, Shift, X, Y, 87, Image344);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image345MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 88, Image345);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image346MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 89, Image346);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image347MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 90, Image347);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image348MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 91, Image348);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image349MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 92, Image349);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image350MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 93, Image350);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image351MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 94, Image351);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image352MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 95, Image352);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image353MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 96, Image353);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image354MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 97, Image354);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image355MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 98, Image355);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image356MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 99, Image356);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image357MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 100, Image357);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image358MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 101, Image358);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image359MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    klik_F3(Sender, Button, Shift, X, Y, 102, Image359);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image360MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 103, Image360);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image361MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 104, Image361);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image362MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    klik_F3(Sender, Button, Shift, X, Y, 105, Image362);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image363MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 106, Image363);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image364MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 107, Image364);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image365MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    klik_F3(Sender, Button, Shift, X, Y, 108, Image365);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image366MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 109, Image366);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image367MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 110, Image367);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image368MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 111, Image368);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image369MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 112, Image369);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image370MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    klik_F3(Sender, Button, Shift, X, Y, 113, Image370);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image371MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 114, Image371);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image372MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 115, Image372);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image373MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 116, Image373);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image374MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 117, Image374);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image375MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 118, Image375);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image376MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 119, Image376);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image377MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    klik_F3(Sender, Button, Shift, X, Y, 120, Image377);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image378MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    klik_F3(Sender, Button, Shift, X, Y, 121, Image378);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image379MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 122, Image379);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image380MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 123, Image380);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image381MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    klik_F3(Sender, Button, Shift, X, Y, 124, Image381);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image382MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 125, Image382);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image383MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    klik_F3(Sender, Button, Shift, X, Y, 126, Image383);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image384MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 127, Image384);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image385MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 128, Image385);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image386MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 129, Image386);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image387MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 130, Image387);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image388MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 131, Image388);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image389MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 132, Image389);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image390MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 133, Image390);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image391MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    klik_F3(Sender, Button, Shift, X, Y, 134, Image391);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image392MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 135, Image392);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image393MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 136, Image393);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image394MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 137, Image394);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image395MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 138, Image395);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image396MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 139, Image396);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image397MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 140, Image397);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image398MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 141, Image398);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image399MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 142, Image399);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image400MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 143, Image400);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image401MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 144, Image401);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image402MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 145, Image402);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image403MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 146, Image403);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image404MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 147, Image404);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image405MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 148, Image405);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image406MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 149, Image406);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image407MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 150, Image407);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image408MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 151, Image408);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image409MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 152, Image409);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image410MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 153, Image410);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image411MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 154, Image411);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image412MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 155, Image412);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image413MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F3(Sender, Button, Shift, X, Y, 156, Image413);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image414MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F3(Sender, Button, Shift, X, Y, 157, Image414);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image415MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F3(Sender, Button, Shift, X, Y, 158, Image415);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image416MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F3(Sender, Button, Shift, X, Y, 159, Image416);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image417MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 160, Image417);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image418MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 161, Image418);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image419MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 162, Image419);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image420MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 163, Image420);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image421MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 164, Image421);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image422MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 165, Image422);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image423MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 166, Image423);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image424MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 167, Image424);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image425MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 168, Image425);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image426MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 169, Image426);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image427MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 170, Image427);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image428MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 171, Image428);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image429MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 172, Image429);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image430MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 173, Image430);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image431MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 174, Image431);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image432MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 175, Image432);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image433MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 176, Image433);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image434MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F3(Sender, Button, Shift, X, Y, 177, Image434);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image435MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 178, Image435);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image436MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 179, Image436);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image437MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F3(Sender, Button, Shift, X, Y, 180, Image437);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image438MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F3(Sender, Button, Shift, X, Y, 181, Image438);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image439MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F3(Sender, Button, Shift, X, Y, 182, Image439);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image440MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F3(Sender, Button, Shift, X, Y, 183, Image440);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image441MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F3(Sender, Button, Shift, X, Y, 184, Image441);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image442MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 185, Image442);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image443MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F3(Sender, Button, Shift, X, Y, 186, Image443);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image444MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 187, Image444);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image445MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 188, Image445);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image446MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 189, Image446);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image447MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 190, Image447);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image448MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F3(Sender, Button, Shift, X, Y, 191, Image448);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image449MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F3(Sender, Button, Shift, X, Y, 192, Image449);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image450MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 193, Image450);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image451MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F3(Sender, Button, Shift, X, Y, 194, Image451);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image452MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 195, Image452);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image453MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 196, Image453);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image454MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F3(Sender, Button, Shift, X, Y, 197, Image454);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image455MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F3(Sender, Button, Shift, X, Y, 198, Image455);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image456MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 199, Image456);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image457MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 200, Image457);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image458MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 201, Image458);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image459MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 202, Image459);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image460MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 203, Image460);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image461MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 204, Image461);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image462MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 205, Image462);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image463MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 206, Image463);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image464MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 207, Image464);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image465MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F3(Sender, Button, Shift, X, Y, 208, Image465);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image466MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 209, Image466);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image467MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 210, Image467);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image468MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    klik_F3(Sender, Button, Shift, X, Y, 211, Image468);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image469MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 212, Image469);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image470MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 213, Image470);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image471MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 214, Image471);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image472MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 215, Image472);
}
//---------------------------------------------------------------------------


void __fastcall TForm3::Image473MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 216, Image473);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image474MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 217, Image474);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image475MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 218, Image475);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image476MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 219, Image476);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image477MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 220, Image477);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image478MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F3(Sender, Button, Shift, X, Y, 221, Image478);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image479MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F3(Sender, Button, Shift, X, Y, 222, Image479);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image480MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F3(Sender, Button, Shift, X, Y, 223, Image480);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image481MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 224, Image481);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image482MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 225, Image482);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image483MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 226, Image483);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image484MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 227, Image484);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image485MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 228, Image485);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image486MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 229, Image486);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image487MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 230, Image487);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image488MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 231, Image488);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image489MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 232, Image489);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image490MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 233, Image490);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image491MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 234, Image491);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image492MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 235, Image492);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image493MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 236, Image493);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image494MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 237, Image494);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image495MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 238, Image495);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image496MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 239, Image496);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image497MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 240, Image497);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image498MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 241, Image498);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image499MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 242, Image499);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image500MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 243, Image500);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image501MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 244, Image501);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image502MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 245, Image502);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image503MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 246, Image503);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image504MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik_F3(Sender, Button, Shift, X, Y, 247, Image504);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image505MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 248, Image505);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image506MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 249, Image506);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image507MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 250, Image507);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image508MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 251, Image508);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image509MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 252, Image509);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image510MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik_F3(Sender, Button, Shift, X, Y, 253, Image510);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image511MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 254, Image511);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image512MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik_F3(Sender, Button, Shift, X, Y, 255, Image512);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::FormClose(TObject *Sender, TCloseAction &Action)
{
      Form3 -> FormCreate(Sender);
}
//---------------------------------------------------------------------------





