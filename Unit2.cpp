//---------------------------------------------------------------------------
#include <ctime>
#include <iostream>
#include <cstdlib>
#include <vcl.h>
#pragma hdrstop
#include "mmsystem.h"

#include "Unit2.h"
#include "Unit5.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;


bool czy_bomba[100];
int licznik = 0;
bool flaga = false;
int ktora_bomba = 0; //do flag
int ruchy = 100;
int odliczanie = 0;
int ile_bomb = 0; //do porownywania z ruchami
bool flaga_tab[100];
bool cokolwiek_tab[100];
bool odwiedzona[100];
bool bonus_flaga[100];
int jednorazowo = 0;


void zmien_visible_na_true();
void zmien_visible_na_false();
void odkryj_bez_numerkow(int ind);
void czerwona(int indeks);
void bon_flaga_dzialanie(int indeks, TImage* t, int numer);



 void sprawdz_czy_wygrana()
 {
     if(ile_bomb == ruchy && ktora_bomba == 10)
     {
        sndPlaySound("snd/win.wav", SND_ASYNC);
        Application -> MessageBox ("Brawo! Wygrana!", "Koniec gry", MB_OK);
        Form2 -> FormCreate(Form2);
     }
 }


 void klik(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y, int indeks, TImage* t)
 {
     if(Shift.Contains(ssLeft))
    {
      for(int i=0; i<100; i++)
      {
         if(i == indeks)
         {
           if (flaga_tab[i] == false)
           {
              if(czy_bomba[indeks] == true)
             {
                if (jednorazowo == 0)
                {
                        
                        Form5 = new TForm5(Application);
                        Form5 -> ShowModal();

                        if (Form5 -> Label4 -> Visible == true)
                        {
                            t -> Picture -> LoadFromFile("img/flaga.bmp");
                            flaga_tab[i] = true;
                            ktora_bomba++;
                            Form2 -> ile_flag -> Caption = " ";
                            Form2 -> ile_flag -> Caption = (Form2 -> ile_flag -> Caption + ktora_bomba + "   ");
                        }
                        else
                        {
                            t -> Visible = false;
                            sndPlaySound("snd/bum.wav", SND_ASYNC);
                            zmien_visible_na_false();
                            czerwona(indeks);
                            Application -> MessageBox ("BUM! Przegrana!", "Koniec gry", MB_OK);
                         }
                        jednorazowo++;
                        delete Form5;
                }
                else
                {
                   t -> Visible = false;
                   sndPlaySound("snd/bum.wav", SND_ASYNC);
                   zmien_visible_na_false();
                   czerwona(indeks);
                   Application -> MessageBox ("BUM! Przegrana!", "Koniec gry", MB_OK);
                }
             }
             else if(czy_bomba[indeks] == false)
             {
                t -> Visible = false;
                odliczanie ++;
                odkryj_bez_numerkow(indeks);
                if (cokolwiek_tab[indeks] == true && odwiedzona[indeks] == false){ruchy--;}
                Form2 -> ktory_ruch -> Caption = "   ";
                Form2 -> ktory_ruch -> Caption = (Form2 -> ktory_ruch -> Caption + odliczanie + " ");



                Form2 -> Label1 -> Caption = "   ";
                Form2 -> Label1 -> Caption = Form2 -> Label1 -> Caption + ruchy + " ";
             }
             } } } // if, if i for
    }

    if(Shift.Contains(ssRight))
    {
      for(int i=0; i<100; i++)
      {
         if(i == indeks)
         {
           if (flaga_tab[i] == false)
           {
              t -> Picture -> LoadFromFile("img/flaga.bmp");
              flaga_tab[i] = true;
              ktora_bomba++;
              Form2 -> ile_flag -> Caption = " ";
              Form2 -> ile_flag -> Caption = (Form2 -> ile_flag -> Caption + ktora_bomba + "   ");
           }
           else if (flaga_tab[i] == true)
           {
               t -> Picture -> LoadFromFile("img/zakr.bmp");
               flaga_tab[i] = false;
               ktora_bomba--;
               Form2 -> ile_flag -> Caption = " ";
               Form2 -> ile_flag -> Caption = (Form2 -> ile_flag -> Caption + ktora_bomba + "   ");
           }
         } // if i == indeks
       } // for
    } // if

    sprawdz_czy_wygrana();
 }



 void zmien_visible_na_true()
 {
   TComponent *Temp;
   for (int i=100; i<200; i++)
   {
      Temp = Form2 -> Components[i];
      if ((dynamic_cast<TImage *>(Temp) != NULL))
      {
          TImage* obj = ((TImage *) Temp);
          obj -> Visible = true;
      }
   }
 }


void zmien_visible_na_false()
 {
   TComponent *Temp;
   for (int i=100; i<200; i++)
   {
      Temp = Form2 -> Components[i];
      if ((dynamic_cast<TImage *>(Temp) != NULL))
      {
          TImage* obj = ((TImage *) Temp);
          obj -> Visible = false;
      }
   }
 }


 void czerwona(int indeks)
 {
    TComponent *Temp;
    for (int i=0; i<100; i++)
    {
       if(i == indeks)
       {
           Temp = Form2 -> Components[i];
           if ((dynamic_cast<TImage *>(Temp) != NULL))
          {
             TImage* obj = ((TImage *) Temp);
             obj -> Picture -> LoadFromFile("img/kliknieta.bmp");
          }
       }
    }
 }



 void odkryj_bez_numerkow(int ind)
 {
     TComponent *Temp;
     for(int i=0; i<100; i++) // dla tablicy cokolwiek
     {
       if (i == ind)
       {
        for(int j=100; j<200; j++) // dla komponentów
        {
           if (j == i+100)
           {
             Temp = Form2 -> Components[j];
             if ((dynamic_cast<TImage *>(Temp) != NULL))
             {
               TImage* obj = ((TImage *) Temp);


               if(cokolwiek_tab[i] == false && odwiedzona[i] == false)
               {

                  odwiedzona[i] = true;
                  obj -> Visible = false;
                  ruchy--;


                  if ((i%10) == 0 && i!= 0 && i != 90)
                  {
                      if(i+1 < 100){odkryj_bez_numerkow(ind+1);}
                      if(i-9 >= 0){odkryj_bez_numerkow(ind-9);}
                      if(i-10 >= 0){odkryj_bez_numerkow(ind-10);}
                      if(i+10 < 100){odkryj_bez_numerkow(ind+10);}
                      if(i+11 < 100){odkryj_bez_numerkow(ind+11);}
                  }
                  if (((i+1)%10) == 0 && i!= 9 && i != 99)
                  {
                      if(i-1 >= 0){odkryj_bez_numerkow(ind-1);}
                      if(i-10 >= 0){odkryj_bez_numerkow(ind-10);}
                      if(i-11 >= 0){odkryj_bez_numerkow(ind-11);}
                      if(i+9 < 100){odkryj_bez_numerkow(ind+9);}
                      if(i+10 < 100){odkryj_bez_numerkow(ind+10);}
                  }
                  if (i == 0)
                  {
                      if(i+1 < 100){odkryj_bez_numerkow(ind+1);}
                      if(i+10 < 100){odkryj_bez_numerkow(ind+10);}
                      if(i+11 < 100){odkryj_bez_numerkow(ind+11);}
                  }
                  if (i == 9)
                  {
                      if(i-1 >= 0){odkryj_bez_numerkow(ind-1);}
                      if(i+9 < 100){odkryj_bez_numerkow(ind+9);}
                      if(i+10 < 100){odkryj_bez_numerkow(ind+10);}
                  }
                  if (i == 90)
                  {
                      if(i+1 < 100){odkryj_bez_numerkow(ind+1);}
                      if(i-9 >= 0){odkryj_bez_numerkow(ind-9);}
                      if(i-10 >= 0){odkryj_bez_numerkow(ind-10);}
                  }
                  if (i == 99)
                  {
                      if(i-1 >= 0){odkryj_bez_numerkow(ind-1);}
                      if(i-10 >= 0){odkryj_bez_numerkow(ind-10);}
                      if(i-11 >= 0){odkryj_bez_numerkow(ind-11);}
                  }
                  if (i!=0 && i!=9 && i!=90 && i!=99 && (i%10)!=0 && ((i+1)%10)!=0)
                  {
                      if(i+1 < 100){odkryj_bez_numerkow(ind+1);}
                      if(i-1 >= 0){odkryj_bez_numerkow(ind-1);}
                      if(i-9 >= 0){odkryj_bez_numerkow(ind-9);}
                      if(i-10 >= 0){odkryj_bez_numerkow(ind-10);}
                      if(i-11 >= 0){odkryj_bez_numerkow(ind-11);}
                      if(i+9 < 100){odkryj_bez_numerkow(ind+9);}
                      if(i+10 < 100){odkryj_bez_numerkow(ind+10);}
                      if(i+11 < 100){odkryj_bez_numerkow(ind+11);}
                  }


              } // if


              if(cokolwiek_tab[i] == true && odwiedzona[i] == false)
              {
                  if ((i%10) == 0 && i!= 0 && i != 90)
                  {
                       if(cokolwiek_tab[i-10] == false || cokolwiek_tab[i-9] == false || cokolwiek_tab[i+1] == false
                       || cokolwiek_tab[i+10] == false || cokolwiek_tab[i+11] == false)
                       {
                       odwiedzona[i] = true;
                       obj -> Visible = false;
                       ruchy--;
                       }
                  }
                  if (((i+1)%10) == 0 && i!= 9 && i != 99)
                  {
                      if(cokolwiek_tab[i-11] == false || cokolwiek_tab[i-10] == false || cokolwiek_tab[i-1] == false
                      || cokolwiek_tab[i+9] == false || cokolwiek_tab[i+10] == false)
                      {
                       odwiedzona[i] = true;
                       obj -> Visible = false;
                       ruchy--;
                      }
                  }
                  if (i == 0)
                  {
                      if(cokolwiek_tab[i+1] == false || cokolwiek_tab[i+10] == false || cokolwiek_tab[i+11] == false)
                      {
                       odwiedzona[i] = true;
                       obj -> Visible = false;
                       ruchy--;
                      }
                  }
                  if (i == 9)
                  {
                      if(cokolwiek_tab[i-1] == false ||cokolwiek_tab[i+9] == false || cokolwiek_tab[i+10] == false )
                      {
                       odwiedzona[i] = true;
                       obj -> Visible = false;
                       ruchy--;
                      }
                  }
                  if (i == 90)
                  {
                      if(cokolwiek_tab[i-10] == false || cokolwiek_tab[i-9] == false || cokolwiek_tab[i+1] == false)
                      {
                       odwiedzona[i] = true;
                       obj -> Visible = false;
                       ruchy--;
                      }
                  }
                  if (i == 99)
                  {
                      if(cokolwiek_tab[i-11] == false || cokolwiek_tab[i-10] == false || cokolwiek_tab[i-1] == false)
                      {
                       odwiedzona[i] = true;
                       obj -> Visible = false;
                       ruchy--;
                      }
                  }
                  if (i!=0 && i!=9 && i!=90 && i!=99 && (i%10)!=0 && ((i+1)%10)!=0)
                  {
                      if(cokolwiek_tab[i-11] == false || cokolwiek_tab[i-10] == false || cokolwiek_tab[i-9] == false || cokolwiek_tab[i-1] == false
                      || cokolwiek_tab[i+1] == false || cokolwiek_tab[i+9] == false || cokolwiek_tab[i+10] == false || cokolwiek_tab[i+11] == false)
                      {
                       odwiedzona[i] = true;
                       obj -> Visible = false;
                       ruchy--;
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
__fastcall TForm2::TForm2(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm2::FormCreate(TObject *Sender)
{

    zmien_visible_na_true();

    ruchy = 100;
    ile_bomb = 0;
    ktora_bomba = 0;
    odliczanie = 0;
    jednorazowo = 0;

    for (int i=0; i<100; i++)
    {
       czy_bomba[i] = false;
       odwiedzona[i] = false;
       cokolwiek_tab[i] = false;
       flaga_tab[i] = false;
       bonus_flaga[i] = false;
    }

    ktory_ruch -> Caption = "   0 ";
    ile_flag -> Caption = " 0  ";
    Label1 -> Caption = " 100  ";


     TComponent *Temp;
     for (int i=0;i <100; i++)
     {
       Temp = Components[i];
       if ((dynamic_cast<TImage *>(Temp) != NULL))
       {
          TImage* obj = ((TImage *) Temp);
          obj -> Picture -> LoadFromFile("img/nic.bmp");
       }
     }


    srand(time(NULL));
    for(int i=0; i<10; i++)
    {
        int v = ((rand() % 100) + 0);

        TComponent *Temp;
        for (int j=0; j<100; j++)
        {
           if(j == v)
           {
              if (czy_bomba[j] == false)
              {
                 Temp = Components[j];
                 if ((dynamic_cast<TImage *>(Temp) != NULL))
                 {
                   TImage* obj = ((TImage *) Temp);
                   obj -> Picture -> LoadFromFile("img/bomba.bmp");
                   czy_bomba[j] = true;
                   cokolwiek_tab[j] = true;
                   ile_bomb++;
                 }
               }
               else
               {
                  i--;
               }

            } // if
         } // for j
    } // for i



    for(int i=0; i<100; i++)
    {
     licznik = 0;
     if (czy_bomba[i] == false)
     {
        if ((i%10) == 0 && i!= 0 && i != 90)
        {
            if ((i+1) >= 0 && (i+1) < 100)
            if (czy_bomba[i+1]==true)
            {
                licznik ++;
            }

            if ((i-10) >= 0 && (i-10) < 100)
            if (czy_bomba[i-10]==true)
            {
                licznik ++;
            }

            if ((i-9) >= 0 && (i-9) < 100)
            if (czy_bomba[i-9]==true)
            {
                licznik ++;
            }

            if ((i+11) >= 0 && (i+11) < 100)
            if (czy_bomba[i+11]==true)
            {
                licznik ++;
            }

            if ((i+10) >= 0 && (i+10) < 100)
            if (czy_bomba[i+10]==true)
            {
                licznik ++;
            }
         }


        if (((i+1)%10) == 0 && i!= 9 && i != 99)
        {
            if ((i-1) >= 0 && (i-1) < 100)
            if (czy_bomba[i-1]==true)
            {
                licznik ++;
            }

            if ((i-11) >= 0 && (i-11) < 100)
            if (czy_bomba[i-11]==true)
            {
                licznik ++;
            }

            if ((i-10) >= 0 && (i-10) < 100)
            if (czy_bomba[i-10]==true)
            {
                licznik ++;
            }

            if ((i+10) >= 0 && (i+10) < 100)
            if (czy_bomba[i+10]==true)
            {
                licznik ++;
            }

            if ((i+9) >= 0 && (i+9) < 100)
            if (czy_bomba[i+9]==true)
            {
                licznik ++;
            }
        }

        if (i == 0)
        {
            if ((i+1) >= 0 && (i+1) < 100)
            if (czy_bomba[i+1]==true)
            {
                licznik ++;
            }

            if ((i+10) >= 0 && (i+10) < 100)
            if (czy_bomba[i+10]==true)
            {
                licznik ++;
            }

            if ((i+11) >= 0 && (i+11) < 100)
            if (czy_bomba[i+11]==true)
            {
                licznik ++;
            }
        }

        if (i == 9)
        {

            if ((i-1) >= 0 && (i-1) < 100)
            if (czy_bomba[i-1]==true)
            {
                licznik ++;
            }

            if ((i+9) >= 0 && (i+9) < 100)
            if (czy_bomba[i+9]==true)
            {
                licznik ++;
            }

            if ((i+10) >= 0 && (i+10) < 100)
            if (czy_bomba[i+10]==true)
            {
                licznik ++;
            }
        }

        if (i == 90)
        {
            if ((i+1) >= 0 && (i+1) < 100)
            if (czy_bomba[i+1]==true)
            {
                licznik ++;
            }

            if ((i-9) >= 0 && (i-9) < 100)
            if (czy_bomba[i-9]==true)
            {
                licznik ++;
            }

            if ((i-10) >= 0 && (i-10) < 100)
            if (czy_bomba[i-10]==true)
            {
                licznik ++;
            }
        }

        if (i == 99)
        {
            if ((i-1) >= 0 && (i-1) < 100)
            if (czy_bomba[i-1]==true)
            {
                licznik ++;
            }

            if ((i-10) >= 0 && (i-10) < 100)
            if (czy_bomba[i-10]==true)
            {
                licznik ++;
            }

            if ((i-11) >= 0 && (i-11) < 100)
            if (czy_bomba[i-11]==true)
            {
                licznik ++;
            }
        }

        if (i!=0 && i!=9 && i!=90 && i!=99 && (i%10)!=0 && ((i+1)%10)!=0)
        {
            if ((i+1) >= 0 && (i+1) < 100)
            if (czy_bomba[i+1]==true)
            {
                licznik ++;
            }

            if ((i-1) >= 0 && (i-1) < 100)
            if (czy_bomba[i-1]==true)
            {
                licznik ++;
            }

            if ((i-9) >= 0 && (i-9) < 100)
            if (czy_bomba[i-9]==true)
            {
                licznik ++;
            }

            if ((i-10) >= 0 && (i-10) < 100)
            if (czy_bomba[i-10]==true)
            {
                licznik ++;
            }

            if ((i-11) >= 0 && (i-11) < 100)
            if (czy_bomba[i-11]==true)
            {
                licznik ++;
            }

            if ((i+9) >= 0 && (i+9) < 100)
            if (czy_bomba[i+9]==true)
            {
                licznik ++;
            }

            if ((i+10) >= 0 && (i+10) < 100)
            if (czy_bomba[i+10]==true)
            {
                licznik ++;
            }

            if ((i+11) >= 0 && (i+11) < 100)
            if (czy_bomba[i+11]==true)
            {
                licznik ++;
            }
        }


             Temp = Components[i];
             if ((dynamic_cast<TImage *>(Temp) != NULL))
             {
                  TImage* obj = ((TImage *) Temp);
                  switch (licznik)
                 {
                    case 1:
                    obj -> Picture -> LoadFromFile("img/1.bmp");
                    cokolwiek_tab[i] = true;
                    break;

                    case 2:
                    obj -> Picture -> LoadFromFile("img/2.bmp");
                    cokolwiek_tab[i] = true;
                    break;

                    case 3:
                    obj -> Picture -> LoadFromFile("img/3.bmp");
                    cokolwiek_tab[i] = true;
                    break;

                    case 4:
                    obj -> Picture -> LoadFromFile("img/4.bmp");
                    cokolwiek_tab[i] = true;
                    break;

                    case 5:
                    obj -> Picture -> LoadFromFile("img/5.bmp");
                    cokolwiek_tab[i] = true;
                    break;

                    case 6:
                    obj -> Picture -> LoadFromFile("img/6.bmp");
                    cokolwiek_tab[i] = true;
                    break;

                    case 7:
                    obj -> Picture -> LoadFromFile("img/7.bmp");
                    cokolwiek_tab[i] = true;
                    break;

                    case 8:
                    obj -> Picture -> LoadFromFile("img/8.bmp");
                    cokolwiek_tab[i] = true;
                    break;

                 }
            }

         } // if
      }// for


      //bon_flaga();


      for (int i=100; i<200; i++)
      {
       Temp = Components[i];
       if ((dynamic_cast<TImage *>(Temp) != NULL))
       {
            TImage* obj = ((TImage *) Temp);
            obj -> Picture -> LoadFromFile("img/zakr.bmp");
       }
      }


} // funkcja



//---------------------------------------------------------------------------


void __fastcall TForm2::Image1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{

     klik(Sender, Button, Shift, X, Y, 0, Image1);
}

//---------------------------------------------------------------------------

void __fastcall TForm2::Image2MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik(Sender, Button, Shift, X, Y, 1, Image2);
}

//---------------------------------------------------------------------------

void __fastcall TForm2::Image3MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik(Sender, Button, Shift, X, Y, 2, Image3);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image4MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik(Sender, Button, Shift, X, Y, 3, Image4);
}
//---------------------------------------------------------------------------


void __fastcall TForm2::Image5MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik(Sender, Button, Shift, X, Y, 4, Image5);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image6MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik(Sender, Button, Shift, X, Y, 5, Image6);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image7MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik(Sender, Button, Shift, X, Y, 6, Image7);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image8MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik(Sender, Button, Shift, X, Y, 7, Image8);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image9MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik(Sender, Button, Shift, X, Y, 8, Image9);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image10MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik(Sender, Button, Shift, X, Y, 9, Image10);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image17MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik(Sender, Button, Shift, X, Y, 10, Image17);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image18MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik(Sender, Button, Shift, X, Y, 11, Image18);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image19MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik(Sender, Button, Shift, X, Y, 12, Image19);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image20MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik(Sender, Button, Shift, X, Y, 13, Image20);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image21MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik(Sender, Button, Shift, X, Y, 14, Image21);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image22MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik(Sender, Button, Shift, X, Y, 15, Image22);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image23MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik(Sender, Button, Shift, X, Y, 16, Image23);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image24MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        klik(Sender, Button, Shift, X, Y, 17, Image24);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image25MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik(Sender, Button, Shift, X, Y, 18, Image25);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image26MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        klik(Sender, Button, Shift, X, Y, 19, Image26);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image33MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik(Sender, Button, Shift, X, Y, 20, Image33);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image34MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik(Sender, Button, Shift, X, Y, 21, Image34);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image35MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik(Sender, Button, Shift, X, Y, 22, Image35);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image36MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik(Sender, Button, Shift, X, Y, 23, Image36);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image37MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik(Sender, Button, Shift, X, Y, 24, Image37);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image38MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        klik(Sender, Button, Shift, X, Y, 25, Image38);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image39MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik(Sender, Button, Shift, X, Y, 26, Image39);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image40MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik(Sender, Button, Shift, X, Y, 27, Image40);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image41MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik(Sender, Button, Shift, X, Y, 28, Image41);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image42MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik(Sender, Button, Shift, X, Y, 29, Image42);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image49MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik(Sender, Button, Shift, X, Y, 30, Image49);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image50MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik(Sender, Button, Shift, X, Y, 31, Image50);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image51MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik(Sender, Button, Shift, X, Y, 32, Image51);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image52MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik(Sender, Button, Shift, X, Y, 33, Image52);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image53MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik(Sender, Button, Shift, X, Y, 34, Image53);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image54MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik(Sender, Button, Shift, X, Y, 35, Image54);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image55MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik(Sender, Button, Shift, X, Y, 36, Image55);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image56MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik(Sender, Button, Shift, X, Y, 37, Image56);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image57MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik(Sender, Button, Shift, X, Y, 38, Image57);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image58MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik(Sender, Button, Shift, X, Y, 39, Image58);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image65MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik(Sender, Button, Shift, X, Y, 40, Image65);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image66MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik(Sender, Button, Shift, X, Y, 41, Image66);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image67MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik(Sender, Button, Shift, X, Y, 42, Image67);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image68MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik(Sender, Button, Shift, X, Y, 43, Image68);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image69MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik(Sender, Button, Shift, X, Y, 44, Image69);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image70MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik(Sender, Button, Shift, X, Y, 45, Image70);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image71MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik(Sender, Button, Shift, X, Y, 46, Image71);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image72MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik(Sender, Button, Shift, X, Y, 47, Image72);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image73MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik(Sender, Button, Shift, X, Y, 48, Image73);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image74MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik(Sender, Button, Shift, X, Y, 49, Image74);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image81MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik(Sender, Button, Shift, X, Y, 50, Image81);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image82MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik(Sender, Button, Shift, X, Y, 51, Image82);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image83MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        klik(Sender, Button, Shift, X, Y, 52, Image83);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image84MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik(Sender, Button, Shift, X, Y, 53, Image84);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image85MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik(Sender, Button, Shift, X, Y, 54, Image85);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image86MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik(Sender, Button, Shift, X, Y, 55, Image86);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image87MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik(Sender, Button, Shift, X, Y, 56, Image87);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image88MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik(Sender, Button, Shift, X, Y, 57, Image88);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image89MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       klik(Sender, Button, Shift, X, Y, 58, Image89);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image90MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik(Sender, Button, Shift, X, Y, 59, Image90);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image97MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik(Sender, Button, Shift, X, Y, 60, Image97);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image98MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    klik(Sender, Button, Shift, X, Y, 61, Image98);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image99MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik(Sender, Button, Shift, X, Y, 62, Image99);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image100MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    klik(Sender, Button, Shift, X, Y, 63, Image100);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image101MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
   klik(Sender, Button, Shift, X, Y, 64, Image101);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image102MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
   klik(Sender, Button, Shift, X, Y, 65, Image102);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image103MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
   klik(Sender, Button, Shift, X, Y, 66, Image103);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image104MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
   klik(Sender, Button, Shift, X, Y, 67, Image104);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image105MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    klik(Sender, Button, Shift, X, Y, 68, Image105);
}
//---------------------------------------------------------------------------


void __fastcall TForm2::Image106MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    klik(Sender, Button, Shift, X, Y, 69, Image106);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image113MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    klik(Sender, Button, Shift, X, Y, 70, Image113);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image114MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    klik(Sender, Button, Shift, X, Y, 71, Image114);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image115MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik(Sender, Button, Shift, X, Y, 72, Image115);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image116MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik(Sender, Button, Shift, X, Y, 73, Image116);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image117MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik(Sender, Button, Shift, X, Y, 74, Image117);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image118MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik(Sender, Button, Shift, X, Y, 75, Image118);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image119MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik(Sender, Button, Shift, X, Y, 76, Image119);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image120MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik(Sender, Button, Shift, X, Y, 77, Image120);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image121MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik(Sender, Button, Shift, X, Y, 78, Image121);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image122MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik(Sender, Button, Shift, X, Y, 79, Image122);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image129MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik(Sender, Button, Shift, X, Y, 80, Image129);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image130MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik(Sender, Button, Shift, X, Y, 81, Image130);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image131MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik(Sender, Button, Shift, X, Y, 82, Image131);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image132MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik(Sender, Button, Shift, X, Y, 83, Image132);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image133MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik(Sender, Button, Shift, X, Y, 84, Image133);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image134MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik(Sender, Button, Shift, X, Y, 85, Image134);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image135MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      klik(Sender, Button, Shift, X, Y, 86, Image135);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image136MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik(Sender, Button, Shift, X, Y, 87, Image136);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image137MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    klik(Sender, Button, Shift, X, Y, 88, Image137);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image138MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik(Sender, Button, Shift, X, Y, 89, Image138);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image145MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    klik(Sender, Button, Shift, X, Y, 90, Image145);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image146MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    klik(Sender, Button, Shift, X, Y, 91, Image146);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image147MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    klik(Sender, Button, Shift, X, Y, 92, Image147);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image148MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    klik(Sender, Button, Shift, X, Y, 93, Image148);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image149MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik(Sender, Button, Shift, X, Y, 94, Image149);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image150MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    klik(Sender, Button, Shift, X, Y, 95, Image150);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image151MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik(Sender, Button, Shift, X, Y, 96, Image151);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image152MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     klik(Sender, Button, Shift, X, Y, 97, Image152);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image153MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    klik(Sender, Button, Shift, X, Y, 98, Image153);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image154MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    klik(Sender, Button, Shift, X, Y, 99, Image154);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::FormClose(TObject *Sender, TCloseAction &Action)
{
    Form2 -> FormCreate(Sender);
}
//---------------------------------------------------------------------------



