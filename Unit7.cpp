//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit7.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm7 *Form7;
//---------------------------------------------------------------------------
__fastcall TForm7::TForm7(TComponent* Owner)
	: TForm(Owner)
{
	mmo1->Clear();
	mmo2->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TForm7::btn_calculateClick(TObject *Sender)
{
	String expr = mmo1->Text;
	std::string str = AnsiString(expr).c_str();
	for(int i=0;i<flwpnl1->ComponentCount;i++){
		TEdit* et = (TEdit *)flwpnl1->Components[i];
		std::string name = AnsiString(et->Hint).c_str();
		std::string value = AnsiString(et->Text).c_str();
		int index = str.find_first_of(name);
		//str+="                                                         ";
        if(index>0)
		str.replace(index,name.length(),value);
	}
	mmo1->Text = str.c_str();
	//;//"(5+(12+633/3*2)/3)/11");
	mmo2->Text = FloatToStr(GetResult(mmo1->Text));
}
//---------------------------------------------------------------------------
double TForm7::GetResult(String expr)
{
	//���ҵ���һ��������

	std::string z1=AnsiString(expr).c_str();
	String z2 = expr;
	//z1.f
	if(expr.Pos("(")>0&&expr.Pos(")")>0){
		int x1 = z1.find_last_of("(");
		std::string div ;
		int i=x1+1;
		while(i<z1.length()){
			if(z1.at(i)==')') break;
			div.append(1,z1.at(i));
			i++;
		}
		//int x2 = z1.find_first_of(")");
		//String div =  z2.SubString(z1.find_last_of("(")+2,z1.find_first_of(")")-z1.find_last_of("(")-1);
		if(!div.empty()){
			String div2 = divResult(div.c_str());
			std::string div3 = AnsiString(div2).c_str();
			z1.replace(x1,i-x1+1,div3);
			return GetResult(z1.c_str());
		}else{
			return StrToFloat(divResult(z2));
		}
	}else{
		String result = divResult(expr);
        std::string res = AnsiString(result).c_str();
		if(result.Pos("x")>0)
		{
			res.replace(res.find_first_of("x"),1,"-");
		}
		bool absolute = false;
		if(result.Pos("|")>0){
			res.replace(res.find_first_of("|"),1,"");
			res.replace(res.find_first_of("|"),1,"");
			absolute = true;
		}
        double resul = StrToFloat(res.c_str());
		if(resul<0&&absolute){
			resul = -resul;
		}
		return resul;
	}
}
String TForm7::divResult(String expr)
{
	double m;
	std::string tmp = AnsiString(expr).c_str();
	//�ȳ˳� ,��Ӽ�
	if(expr.Pos("*")>0){   //�Ƿ��г˷�
		int mul_index = tmp.find_first_of("*");
		if(expr.Pos("/")>0)            //�Ƿ��г���
		{
			int divied_index = tmp.find_first_of("/");
			if(mul_index>divied_index)             //�ȳ˻����ȳ�
			{
				return divResult(resolveReduce(tmp.c_str(),opDiv));
			}else{

				return divResult(resolveReduce(tmp.c_str(),opMul));
			}
		}else{
			return divResult(resolveReduce(tmp.c_str(),opMul));
		}
	}
	if(expr.Pos("/")>0){
		int divied_index = tmp.find_first_of("/");
		if(expr.Pos("*")>0)            //�Ƿ��г���
		{
			int mul_index = tmp.find_first_of("*");
			if(mul_index>divied_index)             //�ȳ˻����ȳ�
			{
				return divResult(resolveReduce(tmp.c_str(),opDiv));
			}else{

				return divResult(resolveReduce(tmp.c_str(),opMul));
			}
		}else{
			return divResult(resolveReduce(tmp.c_str(),opDiv));
		}
	}
	if(expr.Pos("+")>0){
		int add_index = tmp.find_first_of("+");
		if(expr.Pos("-")>0)            //�Ƿ��м���
		{
			int minu_index = tmp.find_first_of("-");
			if(add_index>minu_index)             //�ȼӻ����ȼ�
			{
				return divResult(resolveReduce(tmp.c_str(),opMinus));  //�ȼ�
			}else{

				return divResult(resolveReduce(tmp.c_str(),opAdd));   //�ȼ�
			}
		}else{
			return divResult(resolveReduce(tmp.c_str(),opAdd)); //ֱ�Ӽ�
		}
	}
	if(expr.Pos("-")>0){
		int minu_index = tmp.find_first_of("-");
		if(expr.Pos("+")>0)            //�Ƿ��м���
		{
			int add_index = tmp.find_first_of("+");
			if(add_index>minu_index)             //�ȼӻ����ȼ�
			{
				return divResult(resolveReduce(tmp.c_str(),opMinus));  //�ȼ�
			}else{

				return divResult(resolveReduce(tmp.c_str(),opAdd));   //�ȼ�
			}
		}else{
			return divResult(resolveReduce(tmp.c_str(),opMinus)); //ֱ�Ӽ�
		}
	}
	return expr;
}

String TForm7::resolveReduce(String str,int opera)
{
	std::string tmp = AnsiString(str).c_str();
	int divied_index;
	switch(opera){
		case opAdd:{
			divied_index = tmp.find_first_of("+");
			break;
		}
		case opMinus:{
			divied_index = tmp.find_first_of("-");
			break;
		}
		case opDiv:{
			divied_index = tmp.find_first_of("/");
			break;
		}
		case opMul:{
			divied_index = tmp.find_first_of("*");
			break;
		}
	}
	std::string res_left ;
	std::string res_right ;
	int i =1;
	//��������
	//ȡ��ֵ
	while(divied_index-i>=0&&tmp.at(divied_index-i)!='*'&&tmp.at(divied_index-i)!='/'&&tmp.at(divied_index-i)!='+'&&tmp.at(divied_index-i)!='-'&&tmp.at(divied_index-i)!=' '){
		res_left.insert(0,tmp.at(divied_index-i));
		i++;
	}
	//ȡ��ֵ
	int j=1;
	while(divied_index+j<tmp.length()&&tmp.at(divied_index+j)!='*'&&tmp.at(divied_index+j)!='/'&&tmp.at(divied_index+j)!='+'&&tmp.at(divied_index+j)!='-'&&tmp.at(divied_index+j)!=' '){
		res_right+=tmp.at(divied_index+j);
		j++;
	}
	double result=0;
	String fake_result = "";
	//�ж��������Ƿ�Ϊ����  ������x��־����
	String x1 = res_left.c_str();
	String x2 = res_right.c_str();
    //�����־����
	bool leftIsM =(x1.Pos("x")>0)?true:false;
	if(leftIsM) res_left.replace(res_left.find_first_of('x'),1,"");
	bool rightIsM = (x2.Pos("x")>0)?true:false;
	if(rightIsM) res_right.replace(res_right.find_first_of('x'),1,"");
	//�Ƿ��о���ֵ��� ,�п����ǵ�������ֵ���㣬Ҳ�������������ֵ����
	bool doubleAbsolute =false;
	if(x1.Pos("|")>0)//��
	{
		res_left.replace(res_left.find_first_of('|'),1,"");
		if(AnsiString(res_left.c_str()).Pos("|")>0){ //��ֵ����ֵ
			res_left.replace(res_left.find_first_of('|'),1,"");
			leftIsM = false;
		}else{
			doubleAbsolute=true;
		}

	}
	if(x2.Pos("|")>0)//��
	{
		res_right.replace(res_right.find_first_of('|'),1,"");
		if(AnsiString(res_right.c_str()).Pos("|")>0){
			res_right.replace(res_right.find_first_of('|'),1,"");
			rightIsM = false;
		}else{
            doubleAbsolute=true;
		}

	}
	//ת����С��
	double left=0,right=0;
	try{
		if(!res_left.empty())
		left = StrToFloat(res_left.c_str());
		if(!res_right.empty())
		right = StrToFloat(res_right.c_str());
	}catch(EConvertError &e){
		ShowMessage("����ת��ʧ��"+AnsiString(res_left.c_str())+" & "+AnsiString(res_right.c_str()));
		return "";
	}
	switch(opera){
		case opAdd:{
			if(leftIsM&&rightIsM){
				result = -left-right;
			}
			else if(leftIsM&&!rightIsM){
				result = right-left;
			}else if(!leftIsM&&rightIsM){
                result = left-right;
			}else{
                result = left+right;
			}
			break;
		}
		case opMinus:{
			if(leftIsM&&rightIsM){
				result = right-left;
			}
			else if(leftIsM&&!rightIsM){
				result = -left-right;
			}else if(!leftIsM&&rightIsM){
				result = left+right;
			}else{
				result = left-right;
			}
			break;
		}
		case opDiv:{
			if(right==0){
                ShowMessage("��������Ϊ0");
                break;
			}
			if(leftIsM&&rightIsM){
				result = left/right;
			}
			else if(leftIsM&&!rightIsM){
				result = -left/right;
			}else if(!leftIsM&&rightIsM){
				result = -left/right;
			}else{
				result = left/right;
			}
			break;
		}
		case opMul:{
			if(leftIsM&&rightIsM){
				result = left*right;
			}
			else if(leftIsM&&!rightIsM){
				result = -right*left;
			}else if(!leftIsM&&rightIsM){
				result = -left*right;
			}else{
				result = left*right;
			}
			break;
		}
	}
	if(result<0){
		if(doubleAbsolute){
            fake_result = FloatToStr(-result);
		}else{
			fake_result = "x"+FloatToStr(-result);
		}
	}else{
		fake_result = FloatToStr(result);
	}

	std::string result_str = AnsiString(fake_result).c_str();
	tmp.replace(divied_index-i+1,i+j-1,result_str);
	return tmp.c_str();


}

String TForm7::tanslateToReduce()
{
	String expr = edt1->Text;
	TStringList* list = new TStringList();
	std::string s = AnsiString(expr).c_str();
	for(int x=0 ;x<s.length();x++){
		//int index = s.find_first_of("&");
		//��&xxx&�滻Ϊ(xxx)
        std::string param;
		if(s.at(x)=='&'){        //�ҵ���ͷ
			s.replace(x,1,"(");

			x++;
			for(;;x++){ //����������
				if(s.at(x)=='&'){	s.replace(x,1,")");    break;     }
				param.append(1,s.at(x));
			}
           list->Add(param.c_str());
		}
	}
	mmo1->Text = s.c_str();

	for(int i=flwpnl1->ComponentCount-1;i>=0;i--){
		delete flwpnl1->Components[i];
	}
	for(int i= 0;i<list->Count;i++){
		TEdit* et = new TEdit(flwpnl1);
		et->Hint = list->Strings[i];
		et->Text = i+1;
		//et->ShowHint = true;
		et->Parent = flwpnl1;
	}
	ShowMessage("�����·����������������(*�ִ���)");



}

void __fastcall TForm7::btn1Click(TObject *Sender)
{
    tanslateToReduce();
}
//---------------------------------------------------------------------------
String TForm7::preproccess(String expr)
{

	std::string s = AnsiString(expr).c_str();
	int index = s.find_first_of("|");
	while(index<s.length()){
		if(s.at(index)=='|'){
			s.replace(index,1,"(|");
            index+=2;
			for(;index<s.length();index++){
				if(s.at(index)=='|'){
					s.replace(index,1,"|)");
					break;
				}
			}
		}
        index++;
	}
    return s.c_str();
	//s.rfind("|",);
}
void __fastcall TForm7::btn2Click(TObject *Sender)
{
	String s = edt1->Text;
	edt1->Text = preproccess(s);
}
//---------------------------------------------------------------------------

