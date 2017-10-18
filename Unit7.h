//---------------------------------------------------------------------------

#ifndef Unit7H
#define Unit7H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <System.RegularExpressionsCore.hpp>
//---------------------------------------------------------------------------
class TForm7 : public TForm
{
__published:	// IDE-managed Components
	TMemo *mmo1;
	TMemo *mmo2;
	TBitBtn *btn_calculate;
	TEdit *edt1;
	TLabel *lbl1;
	TFlowPanel *flwpnl1;
	TLabel *lbl2;
	TBitBtn *btn1;
	TBitBtn *btn2;
	TLabel *lbl3;
	void __fastcall btn_calculateClick(TObject *Sender);
	void __fastcall btn1Click(TObject *Sender);
	void __fastcall btn2Click(TObject *Sender);
private:
	double GetResult(String expr);
	enum operate{opAdd,opMinus,opDiv,opMul};
	String divResult(String expr);
	//简单表达式计算
	String resolveReduce(String str,int opera);
	String tanslateToReduce();

	//利用正则表达式对表达式预处理
    String preproccess(String expr);
	// User declarations
public:		// User declarations
	__fastcall TForm7(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm7 *Form7;
//---------------------------------------------------------------------------
#endif
