//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit5.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm5 *Form5;

int liczby[5];
bool gra = false;
int klik = 0;

void kolejnosc()
{
     Form5 -> Button1 -> Enabled = false;
     Form5 -> Button2 -> Enabled = false;
     Form5 -> Button3 -> Enabled = false;
     Form5 -> Button4 -> Enabled = false;
     Form5 -> Button5 -> Enabled = false;

    Application -> ProcessMessages(); Sleep(500);

    for (int i = 0; i<5; i++)
    {
         switch(liczby[i])
         {
             case 0:
             {
                Form5 -> Shape1a -> Visible = true;
             } break;

             case 1:
             {
                Form5 -> Shape2a -> Visible = true;
             } break;

             case 2:
             {
                Form5 -> Shape3a -> Visible = true;
             } break;

             case 3:
             {
                Form5 -> Shape4a -> Visible = true;
             } break;

             case 4:
             {
                Form5 -> Shape5a -> Visible = true;
             } break;
         }

         Application -> ProcessMessages(); Sleep(500);

         Form5 -> Shape1a -> Visible = false;
         Form5 -> Shape2a -> Visible = false;
         Form5 -> Shape3a -> Visible = false;
         Form5 -> Shape4a -> Visible = false;
         Form5 -> Shape5a -> Visible = false;
         Application -> ProcessMessages(); Sleep(500);
    }

     Form5 -> Button1 -> Enabled = true;
     Form5 -> Button2 -> Enabled = true;
     Form5 -> Button3 -> Enabled = true;
     Form5 -> Button4 -> Enabled = true;
     Form5 -> Button5 -> Enabled = true;

}

//---------------------------------------------------------------------------
__fastcall TForm5::TForm5(TComponent* Owner)
        : TForm(Owner)
{


}
//---------------------------------------------------------------------------


void __fastcall TForm5::FormCreate(TObject *Sender)
{

     gra = false;
     klik = 0;

     for(int i=0; i<5; i++)
     {
         int v = ((rand() % 4) + 0);
         liczby[i] = v;
     }

}
//---------------------------------------------------------------------------
void __fastcall TForm5::Button6Click(TObject *Sender)
{
    Form5 -> Button6 -> Enabled = false;

    if (gra == false)
    {
       gra = true;
       kolejnosc();
    }
}
//---------------------------------------------------------------------------


void __fastcall TForm5::Button1Click(TObject *Sender)
{
     if (gra == true)
     {
          klik++;

          if(liczby[klik-1] != 0)            // przegrana  - jesli w tablicy w polu numer 1 nie ma tego koloru, przegrana
          {
              gra = false;
              Form5 -> Image1 -> Visible = false;
              Form5 -> Label3 -> Visible = true;
              Application -> ProcessMessages(); Sleep(1000);
              Form5 -> Close();

          }


         if(klik == 5)                    // wygrana
         {
               Form5 -> Image1 -> Visible = false;
               Form5 -> Label4 -> Visible = true;
               Application -> ProcessMessages(); Sleep(1000);
               Form5 -> Close();

         }
     }
}
//---------------------------------------------------------------------------


void __fastcall TForm5::Button2Click(TObject *Sender)
{
     if (gra == true)
     {
          klik++;

          if(liczby[klik-1] != 1)
          {
              gra = false;
              Form5 -> Image1 -> Visible = false;
              Form5 -> Label3 -> Visible = true;
              Application -> ProcessMessages(); Sleep(1000);
              Form5 -> Close();

          }


         if(klik == 5)
         {
               Form5 -> Image1 -> Visible = false;
               Form5 -> Label4 -> Visible = true;
               Application -> ProcessMessages(); Sleep(1000);
               Form5 -> Close();

         }
     }
}
//---------------------------------------------------------------------------

void __fastcall TForm5::Button3Click(TObject *Sender)
{
      if (gra == true)
     {
          klik++;

          if(liczby[klik-1] != 2)
          {
              gra = false;
              Form5 -> Image1 -> Visible = false;
              Form5 -> Label3 -> Visible = true;
              Application -> ProcessMessages(); Sleep(1000);
              Form5 -> Close();

          }


         if(klik == 5)
         {
               Form5 -> Image1 -> Visible = false;
               Form5 -> Label4 -> Visible = true;
               Application -> ProcessMessages(); Sleep(1000);
               Form5 -> Close();

         }
     }
}
//---------------------------------------------------------------------------

void __fastcall TForm5::Button4Click(TObject *Sender)
{
     if (gra == true)
     {
          klik++;

          if(liczby[klik-1] != 3)
          {
              gra = false;
              Form5 -> Image1 -> Visible = false;
              Form5 -> Label3 -> Visible = true;
              Application -> ProcessMessages(); Sleep(1000);
              Form5 -> Close();

          }


         if(klik == 5)
         {
               Form5 -> Image1 -> Visible = false;
               Form5 -> Label4 -> Visible = true;
               Application -> ProcessMessages(); Sleep(1000);
               Form5 -> Close();

         }
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm5::Button5Click(TObject *Sender)
{
     if (gra == true)
     {
          klik++;

          if(liczby[klik-1] != 4)
          {
              gra = false;
              Form5 -> Image1 -> Visible = false;
              Form5 -> Label3 -> Visible = true;
              Application -> ProcessMessages(); Sleep(1000);
              Form5 -> Close();

          }


         if(klik == 5)
        {
               Form5 -> Image1 -> Visible = false;
               Form5 -> Label4 -> Visible = true;
               Application -> ProcessMessages(); Sleep(1000);
               Form5 -> Close();

         }
     }
}
//---------------------------------------------------------------------------

void __fastcall TForm5::Button1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     Shape1 ->  Brush -> Color = clRed;
     Application -> ProcessMessages(); Sleep(400);
}
//---------------------------------------------------------------------------

void __fastcall TForm5::Button1MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       Shape1 ->  Brush -> Color = clWhite;
}
//---------------------------------------------------------------------------

void __fastcall TForm5::Button2MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      Shape2 ->  Brush -> Color = clHighlight;
      Application -> ProcessMessages(); Sleep(400);
}
//---------------------------------------------------------------------------

void __fastcall TForm5::Button2MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      Shape2 ->  Brush -> Color = clWhite;
}
//---------------------------------------------------------------------------

void __fastcall TForm5::Button3MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     Shape3 ->  Brush -> Color = clYellow;
     Application -> ProcessMessages(); Sleep(400);
}
//---------------------------------------------------------------------------

void __fastcall TForm5::Button3MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      Shape3 ->  Brush -> Color = clWhite;
}
//---------------------------------------------------------------------------

void __fastcall TForm5::Button4MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     Shape4 ->  Brush -> Color = clGreen;
     Application -> ProcessMessages(); Sleep(400);
}
//---------------------------------------------------------------------------

void __fastcall TForm5::Button4MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     Shape4 ->  Brush -> Color = clWhite;
}
//---------------------------------------------------------------------------

void __fastcall TForm5::Button5MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     Shape5 ->  Brush -> Color = clPurple;
     Application -> ProcessMessages(); Sleep(400);
}
//---------------------------------------------------------------------------

void __fastcall TForm5::Button5MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     Shape5 ->  Brush -> Color = clWhite;
}
//---------------------------------------------------------------------------

void __fastcall TForm5::FormClose(TObject *Sender, TCloseAction &Action)
{
     Form5 -> FormCreate(Sender);
     Form5 -> Close();
}
//---------------------------------------------------------------------------

