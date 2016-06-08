//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FormMain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmMain *frmMain;
//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner)
	: TForm(Owner)
{
	index = 0;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnEnterClick(TObject *Sender)
{
	// �������� ����
	mmText->Clear();
	// ��������� ������� ������
	AnsiString inputAString = edtInput->Text;
	// ����� ������� ������ � ����
	mmText->Lines->Add(inputAString);
	// �������� ������������� ��������� � ��������� ������� ������
	string inputString = inputAString.c_str();
	gen = new TGeneticAlg(inputString);
    gen->setCoefMutation(edtMut->Text.ToDouble()/10);
	stResult->Caption = gen->run();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::edtInputKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key == VK_RETURN)
	{
		btnEnterClick(Sender);
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::edtMutKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)
{
    if(Key == VK_RETURN)
	{
		btnEnterClick(Sender);
	}
}
//---------------------------------------------------------------------------

