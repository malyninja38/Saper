//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit2.cpp"
#include "Unit3.cpp"
#include "Unit4.cpp"

#include "Saper.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;


//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
      Form2 -> ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
      Form3 -> ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{
      Form4 -> ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
      Instrukcja -> Visible = true;
      Button1 -> Visible = false;
      Button2 -> Visible = false;
      Button3 -> Visible = false;
      Button5 -> Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button5Click(TObject *Sender)
{
      Instrukcja -> Visible = false;
      Button1 -> Visible = true;
      Button2 -> Visible = true;
      Button3 -> Visible = true;
      Button5 -> Visible = false;
}
//---------------------------------------------------------------------------

