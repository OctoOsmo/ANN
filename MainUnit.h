//---------------------------------------------------------------------------

#ifndef MainUnitH
#define MainUnitH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ComCtrls.hpp>
//---------------------------------------------------------------------------
class TFormMain : public TForm
{
__published:	// IDE-managed Components
	TOpenDialog *OpenInputDialog;
	TMainMenu *MainMenu;
	TMenuItem *NFile;
	TMenuItem *NOpen;
	TMenuItem *NOpenWeights;
	TMenuItem *NSaveWeights;
	TMenuItem *NExit;
	TTrackBar *TrackBarNeuronCount;
	TLabel *LabelNeuronCount;
	void __fastcall NOpenClick(TObject *Sender);
	void __fastcall TrackBarNeuronCountChange(TObject *Sender);
	void __fastcall NExitClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TFormMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------
#endif
