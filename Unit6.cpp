//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit6.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm6 *Form6;

int liczby2[7];
bool gra2 = false;
int klik2 = 0;

void kolejnosc2()
{
     Form6 -> Button1 -> Enabled = false;
     Form6 -> Button2 -> Enabled = false;
     Form6 -> Button3 -> Enabled = false;
     Form6 -> Button4 -> Enabled = false;
     Form6 -> Button5 -> Enabled = false;

    Application -> ProcessMessages(); Sleep(500);

    for (int i = 0; i<7; i++)
    {
         switch(liczby2[i])
         {
             case 0:
             {
                Form6 -> Shape1a -> Visible = true;
             } break;

             case 1:
             {
                Form6 -> Shape2a -> Visible = true;
             } break;

             case 2:
             {
                Form6 -> Shape3a -> Visible = true;
             } break;

             case 3:
             {
                Form6 -> Shape4a -> Visible = true;
             } break;

             case 4:
             {
                Form6 -> Shape5a -> Visible = true;
             } break;
         }

         Application -> ProcessMessages(); Sleep(500);

         Form6 -> Shape1a -> Visible = false;
         Form6 -> Shape2a -> Visible = false;
         Form6 -> Shape3a -> Visible = false;
         Form6 -> Shape4a -> Visible = false;
         Form6 -> Shape5a -> Visible = false;
         Application -> ProcessMessages(); Sleep(500);
    }

     Form6 -> Button1 -> Enabled = true;
     Form6 -> Button2 -> Enabled = true;
     Form6 -> Button3 -> Enabled = true;
     Form6 -> Button4 -> Enabled = true;
     Form6 -> Button5 -> Enabled = true;

}

//---------------------------------------------------------------------------
__fastcall TForm6::TForm6(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm6::FormCreate(TObject *Sender)
{
     gra2 = false;
     klik2 = 0;

     for(int i=0; i<7; i++)
     {
         int v = ((rand() % 4) + 0);
         liczby2[i] = v;
     }
}
//---------------------------------------------------------------------------
void __fastcall TForm6::Button6Click(TObject *Sender)
{
     Form6 -> Button6 -> Enabled = false;

    if (gra2 == false)
    {
       gra2 = true;
       kolejnosc2();
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm6::Button1Click(TObject *Sender)
{
     if (gra2 == true)
     {
          klik2++;

          if(liczby2[klik2-1] != 0)            // przegrana  - jesli w tablicy w polu numer 1 nie ma tego koloru, przegrana
          {
              gra2 = false;
              Form6 -> Image1 -> Visible = false;
              Form6 -> Label3 -> Visible = true;
              Application -> ProcessMessages(); Sleep(1000);
              Form6 -> Close();

          }


         if(klik2 == 7)                    // wygrana
         {
               Form6 -> Image1 -> Visible = false;
               Form6 -> Label4 -> Visible = true;
               Application -> ProcessMessages(); Sleep(1000);
               Form6 -> Close();

         }
     }
}
//---------------------------------------------------------------------------
void __fastcall TForm6::Button2Click(TObject *Sender)
{
      if (gra2 == true)
     {
          klik2++;

          if(liczby2[klik2-1] != 1)
          {
              gra2 = false;
              Form6 -> Image1 -> Visible = false;
              Form6 -> Label3 -> Visible = true;
              Application -> ProcessMessages(); Sleep(1000);
              Form6 -> Close();

          }


         if(klik2 == 7)
         {
               Form6 -> Image1 -> Visible = false;
               Form6 -> Label4 -> Visible = true;
               Application -> ProcessMessages(); Sleep(1000);
               Form6 -> Close();

         }
     }
}
//---------------------------------------------------------------------------
void __fastcall TForm6::Button3Click(TObject *Sender)
{
      if (gra2 == true)
     {
          klik2++;

          if(liczby2[klik2-1] != 2)
          {
              gra2 = false;
              Form6 -> Image1 -> Visible = false;
              Form6 -> Label3 -> Visible = true;
              Application -> ProcessMessages(); Sleep(1000);
              Form6 -> Close();

          }


         if(klik2 == 7)
         {
               Form6 -> Image1 -> Visible = false;
               Form6 -> Label4 -> Visible = true;
               Application -> ProcessMessages(); Sleep(1000);
               Form6 -> Close();

         }
     }
}
//---------------------------------------------------------------------------
void __fastcall TForm6::Button4Click(TObject *Sender)
{
     if (gra2 == true)
     {
          klik2++;

          if(liczby2[klik2-1] != 3)
          {
              gra2 = false;
              Form6 -> Image1 -> Visible = false;
              Form6 -> Label3 -> Visible = true;
              Application -> ProcessMessages(); Sleep(1000);
              Form6 -> Close();

          }


         if(klik2 == 7)
         {
               Form6 -> Image1 -> Visible = false;
               Form6 -> Label4 -> Visible = true;
               Application -> ProcessMessages(); Sleep(1000);
               Form6 -> Close();

         }
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm6::Button5Click(TObject *Sender)
{
     if (gra2 == true)
     {
          klik2++;

          if(liczby2[klik2-1] != 4)
          {
              gra2 = false;
              Form6 -> Image1 -> Visible = false;
              Form6 -> Label3 -> Visible = true;
              Application -> ProcessMessages(); Sleep(1000);
              Form6 -> Close();

          }


         if(klik2 == 7)
        {
               Form6 -> Image1 -> Visible = false;
               Form6 -> Label4 -> Visible = true;
               Application -> ProcessMessages(); Sleep(1000);
               Form6 -> Close();

         }
     }
}
//---------------------------------------------------------------------------
void __fastcall TForm6::Button1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     Shape1 ->  Brush -> Color = clRed;
     Application -> ProcessMessages(); Sleep(400);
}
//---------------------------------------------------------------------------
void __fastcall TForm6::Button1MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      Shape1 ->  Brush -> Color = clWhite;
}
//---------------------------------------------------------------------------
void __fastcall TForm6::Button2MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      Shape2 ->  Brush -> Color = clHighlight;
      Application -> ProcessMessages(); Sleep(400);
}
//---------------------------------------------------------------------------
void __fastcall TForm6::Button2MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       Shape2 ->  Brush -> Color = clWhite;
}
//---------------------------------------------------------------------------
void __fastcall TForm6::Button3MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      Shape3 ->  Brush -> Color = clYellow;
      Application -> ProcessMessages(); Sleep(400);
}
//---------------------------------------------------------------------------
void __fastcall TForm6::Button3MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      Shape3 ->  Brush -> Color = clWhite;
}
//---------------------------------------------------------------------------
void __fastcall TForm6::Button4MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      Shape4 ->  Brush -> Color = clGreen;
      Application -> ProcessMessages(); Sleep(400);
}
//---------------------------------------------------------------------------
void __fastcall TForm6::Button4MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      Shape4 ->  Brush -> Color = clWhite;
}
//---------------------------------------------------------------------------
void __fastcall TForm6::Button5MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     Shape5 ->  Brush -> Color = clPurple;
     Application -> ProcessMessages(); Sleep(400);
}
//---------------------------------------------------------------------------
void __fastcall TForm6::Button5MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     Shape5 ->  Brush -> Color = clWhite;
}
//---------------------------------------------------------------------------
void __fastcall TForm6::FormClose(TObject *Sender, TCloseAction &Action)
{
     Form6 -> FormCreate(Sender);
     Form6 -> Close();
}
//---------------------------------------------------------------------------
