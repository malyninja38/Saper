//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit7.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm7 *Form7;

int liczby3[10];
bool gra3 = false;
int klik3 = 0;

void kolejnosc3()
{
     Form7 -> Button1 -> Enabled = false;
     Form7 -> Button2 -> Enabled = false;
     Form7 -> Button3 -> Enabled = false;
     Form7 -> Button4 -> Enabled = false;
     Form7 -> Button5 -> Enabled = false;

    Application -> ProcessMessages(); Sleep(500);

    for (int i = 0; i<10; i++)
    {
         switch(liczby3[i])
         {
             case 0:
             {
                Form7 -> Shape1a -> Visible = true;
             } break;

             case 1:
             {
                Form7 -> Shape2a -> Visible = true;
             } break;

             case 2:
             {
                Form7 -> Shape3a -> Visible = true;
             } break;

             case 3:
             {
                Form7 -> Shape4a -> Visible = true;
             } break;

             case 4:
             {
                Form7 -> Shape5a -> Visible = true;
             } break;
         }

         Application -> ProcessMessages(); Sleep(500);

         Form7 -> Shape1a -> Visible = false;
         Form7 -> Shape2a -> Visible = false;
         Form7 -> Shape3a -> Visible = false;
         Form7 -> Shape4a -> Visible = false;
         Form7 -> Shape5a -> Visible = false;
         Application -> ProcessMessages(); Sleep(500);
    }

     Form7 -> Button1 -> Enabled = true;
     Form7 -> Button2 -> Enabled = true;
     Form7 -> Button3 -> Enabled = true;
     Form7 -> Button4 -> Enabled = true;
     Form7 -> Button5 -> Enabled = true;

}

//---------------------------------------------------------------------------
__fastcall TForm7::TForm7(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm7::FormCreate(TObject *Sender)
{
     gra3 = false;
     klik3 = 0;

     for(int i=0; i<10; i++)
     {
         int v = ((rand() % 4) + 0);
         liczby3[i] = v;
     }
}     
//---------------------------------------------------------------------------

void __fastcall TForm7::Button6Click(TObject *Sender)
{
     Form7 -> Button6 -> Enabled = false;

    if (gra3 == false)
    {
       gra3 = true;
       kolejnosc3();
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm7::Button1Click(TObject *Sender)
{
     if (gra3 == true)
     {
          klik3++;

          if(liczby3[klik3-1] != 0)            // przegrana  - jesli w tablicy w polu numer 1 nie ma tego koloru, przegrana
          {
              gra3 = false;
              Form7 -> Image1 -> Visible = false;
              Form7 -> Label3 -> Visible = true;
              Application -> ProcessMessages(); Sleep(1000);
              Form7 -> Close();

          }


         if(klik3 == 10)                    // wygrana
         {
               Form7 -> Image1 -> Visible = false;
               Form7 -> Label4 -> Visible = true;
               Application -> ProcessMessages(); Sleep(1000);
               Form7 -> Close();

         }
     }
}
//---------------------------------------------------------------------------
void __fastcall TForm7::Button2Click(TObject *Sender)
{
     if (gra3 == true)
     {
          klik3++;

          if(liczby3[klik3-1] != 1)
          {
              gra3 = false;
              Form7 -> Image1 -> Visible = false;
              Form7 -> Label3 -> Visible = true;
              Application -> ProcessMessages(); Sleep(1000);
              Form7 -> Close();

          }


         if(klik3 == 10)
         {
               Form7 -> Image1 -> Visible = false;
               Form7 -> Label4 -> Visible = true;
               Application -> ProcessMessages(); Sleep(1000);
               Form7 -> Close();

         }
     }
}
//---------------------------------------------------------------------------
void __fastcall TForm7::Button3Click(TObject *Sender)
{
      if (gra3 == true)
     {
          klik3++;

          if(liczby3[klik3-1] != 2)
          {
              gra3 = false;
              Form7 -> Image1 -> Visible = false;
              Form7 -> Label3 -> Visible = true;
              Application -> ProcessMessages(); Sleep(1000);
              Form7 -> Close();

          }


         if(klik3 == 10)
         {
               Form7 -> Image1 -> Visible = false;
               Form7 -> Label4 -> Visible = true;
               Application -> ProcessMessages(); Sleep(1000);
               Form7 -> Close();

         }
     }
}
//---------------------------------------------------------------------------
void __fastcall TForm7::Button4Click(TObject *Sender)
{
      if (gra3 == true)
     {
          klik3++;

          if(liczby3[klik3-1] != 3)
          {
              gra3 = false;
              Form7 -> Image1 -> Visible = false;
              Form7 -> Label3 -> Visible = true;
              Application -> ProcessMessages(); Sleep(1000);
              Form7 -> Close();

          }


         if(klik3 == 10)
         {
               Form7 -> Image1 -> Visible = false;
               Form7 -> Label4 -> Visible = true;
               Application -> ProcessMessages(); Sleep(1000);
               Form7 -> Close();

         }
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm7::Button5Click(TObject *Sender)
{
     if (gra3 == true)
     {
          klik3++;

          if(liczby3[klik3-1] != 4)
          {
              gra3 = false;
              Form7 -> Image1 -> Visible = false;
              Form7 -> Label3 -> Visible = true;
              Application -> ProcessMessages(); Sleep(1000);
              Form7 -> Close();

          }


         if(klik3 == 10)
        {
               Form7 -> Image1 -> Visible = false;
               Form7 -> Label4 -> Visible = true;
               Application -> ProcessMessages(); Sleep(1000);
               Form7 -> Close();

         }
     }
}
//---------------------------------------------------------------------------
void __fastcall TForm7::Button1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     Shape1 ->  Brush -> Color = clRed;
     Application -> ProcessMessages(); Sleep(400);
}
//---------------------------------------------------------------------------
void __fastcall TForm7::Button1MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      Shape1 ->  Brush -> Color = clWhite;
}
//---------------------------------------------------------------------------
void __fastcall TForm7::Button2MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      Shape2 ->  Brush -> Color = clHighlight;
      Application -> ProcessMessages(); Sleep(400);
}
//---------------------------------------------------------------------------
void __fastcall TForm7::Button2MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       Shape2 ->  Brush -> Color = clWhite;
}
//---------------------------------------------------------------------------
void __fastcall TForm7::Button3MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     Shape3 ->  Brush -> Color = clYellow;
     Application -> ProcessMessages(); Sleep(400);
}
//---------------------------------------------------------------------------
void __fastcall TForm7::Button3MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       Shape3 ->  Brush -> Color = clWhite;
}
//---------------------------------------------------------------------------
void __fastcall TForm7::Button4MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     Shape4 ->  Brush -> Color = clGreen;
     Application -> ProcessMessages(); Sleep(400);
}
//---------------------------------------------------------------------------
void __fastcall TForm7::Button4MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
      Shape4 ->  Brush -> Color = clWhite;
}
//---------------------------------------------------------------------------
void __fastcall TForm7::Button5MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     Shape5 ->  Brush -> Color = clPurple;
     Application -> ProcessMessages(); Sleep(400);
}
//---------------------------------------------------------------------------
void __fastcall TForm7::Button5MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
       Shape5 ->  Brush -> Color = clWhite;
}
//---------------------------------------------------------------------------
void __fastcall TForm7::FormClose(TObject *Sender, TCloseAction &Action)
{
     Form7 -> FormCreate(Sender);
     Form7 -> Close();
}
//---------------------------------------------------------------------------
