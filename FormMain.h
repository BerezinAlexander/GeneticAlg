//---------------------------------------------------------------------------

#ifndef FormMainH
#define FormMainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "GenAlg.h"
//---------------------------------------------------------------------------
#define uint unsigned int
//---------------------------------------------------------------------------
class TfrmMain : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TEdit *edtInput;
	TButton *btnEnter;
	TStaticText *stResult;
	TGroupBox *GroupBox1;
	TMemo *mmText;
	TLabel *Label1;
	TLabel *Label2;
	TEdit *edtMut;
	TLabel *Label3;
	TLabel *Label4;
	void __fastcall btnEnterClick(TObject *Sender);
	void __fastcall edtInputKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall edtMutKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
private:	// User declarations
	TGeneticAlg *gen; // генетический алгоритм
	uint index; // номкр строки мемо
public:		// User declarations
	__fastcall TfrmMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif
