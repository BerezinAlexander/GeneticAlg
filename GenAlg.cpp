//---------------------------------------------------------------------------

#pragma hdrstop

#include "GenAlg.h"

#include <boost/bind.hpp>
#include <CodeSiteLogging.hpp>

#include "FormMain.h"

using boost::bind;

//---------------------------------------------------------------------------
int TGeneticAlg::run()
{
	randomize();
	int result = 0;
	len = input.length();
	// коэфф мутации редко превышает 1%
	// обычно выбирают 1/len или 1/OFFSPRINGS_MAX
//	coefMutation = 9; //1/len;
	// начальна€ попул€ци€
	initPopulation();

	//  цикл мутации/скрещевани€/отбора
	for(;;)
	{
		// отбор сильных особей
		int iResCompare = naturalSelection();
		// скрещивание
		crossing();
		// мутаци€
		PopulMutation();
		// вывод в мемо
		AnsiString strRes;
		strRes = IntToStr(result) + ":   " + survivors[0].c_str();
		frmMain->mmText->Lines->Add(strRes.c_str());
		// счетчик поколений
		++result;
		// проверка на полное совпадение с исходной строкой
		if(iResCompare == len)	break;
		// ограничение в 20000 поколений
		if(result > 20000) break;
	}

	return result;
}
//---------------------------------------------------------------------------
// √енераци€ начальной попул€ции
//---------------------------------------------------------------------------
void TGeneticAlg::initPopulation()
{
	CodeSite->EnterMethod("initPopulation");
	string str = "";
	// заполнение начальной попул€ции
	for(int i=0; i<OFFSPRINGS_MAX; ++i)
	{
		str = "";
		for(int i = 0; i< len; i++)
			str += generationSymbol();
		CodeSite->Send("offsprings[i]: " + IntToStr(i) + " " + "   " + (AnsiString)str.c_str());
		offsprings[i] = str;
	}
	CodeSite->ExitMethod("initPopulation");
}
//---------------------------------------------------------------------------
// —равнение строки с исходной на схожесть
//---------------------------------------------------------------------------
int TGeneticAlg::compare(string str)
{
	int count = 0;
	for(size_t i = 0; i < len; ++i)
	{
		if(input[i] == str[i])
			++count;
	}
	return count;
}
//---------------------------------------------------------------------------
// ќтбор сильнейших особей
//---------------------------------------------------------------------------
int TGeneticAlg::naturalSelection()
{
	// пары соответстви€ ( номер особи, схожесть с исходной строкой )
	vector< pair<int, int> > vResCompare;
	for(int i=0; i<OFFSPRINGS_MAX; ++i)
	{
		vResCompare.push_back( make_pair(i, compare(offsprings[i]) ));
	}
	// —ортировка вектора по убыванию второго параметра пары
	sortVec(vResCompare);
	// ќтбор сильнейших особей
	vector< pair<int, int> >::iterator it = vResCompare.begin();
	for(int i = 0; i< SURVIVORS_MAX; i++)
	{
		survivors[i] = offsprings[it->first];
		++it;
	}
	return vResCompare.begin()->second;
}
//---------------------------------------------------------------------------
// —крещивание (метод скрещивани€ - точечный)
//---------------------------------------------------------------------------
void TGeneticAlg::crossing()
{
	vector< pair<string, int> > vResCrossing;
	for(int i = 0; i < SURVIVORS_MAX - 1; i++)
	{
		for(int j = 1; j < SURVIVORS_MAX; j++)
		{
			int pointCrossing = random(len); // точка скрещивани€
			int lenSecond = len - pointCrossing; // длина второй часть строки
			string temp;
			// склеивание первой половины первой строки с второй половиной второй строки
			temp = survivors[i].substr(0, pointCrossing);
			temp += survivors[j].substr(pointCrossing, lenSecond);
			vResCrossing.push_back( make_pair(temp, compare(temp) ));
			// склеивание первой половины второй строки с второй половиной первой строки
			temp = survivors[j].substr(0, pointCrossing);
			temp += survivors[i].substr(pointCrossing, lenSecond);
			vResCrossing.push_back( make_pair(temp, compare(temp) ));
		}
	}
	// —ортировка вектора по убыванию второго параметра пары
	sortVecStr(vResCrossing);
	// ‘ормировани€ потомства
	vector< pair<string, int> >::iterator it = vResCrossing.begin();
	for(int i = 0; i< SURVIVORS_MAX; i++)
	{
		offsprings[i] = it->first;
		++it;
	}
}
//---------------------------------------------------------------------------
// ћутаци€ одной особи
//---------------------------------------------------------------------------
string TGeneticAlg::mutation(string str)
{
	// коэфф мутации редко превышает 1%
	// обычно выбирают 1/len или 1/OFFSPRINGS_MAX
	//float koefMut = 1/len;
	for(size_t i = 0; i < len; ++i)
	{
		float randRes = (float)random(10000) / 100;
		if(randRes < coefMutation)
			str[i] = generationSymbol();
	}
	return str;
}
//---------------------------------------------------------------------------
// ћутаци€ поколени€
//---------------------------------------------------------------------------
void TGeneticAlg::PopulMutation()
{
	for(int i = 0; i< OFFSPRINGS_MAX; i++)
		offsprings[i] = mutation(offsprings[i]);
}
//---------------------------------------------------------------------------
// —ортировка вектора по убыванию второго параметра пары
//---------------------------------------------------------------------------
void TGeneticAlg::sortVec(vector< pair<int, int> > &v)
{
	std::sort(v.begin(),
			  v.end(),
			  boost::bind(std::greater<int>(),
					boost::bind(&std::pair<int, int>::second, _1),
					boost::bind(&std::pair<int, int>::second, _2))
			 );
}
//---------------------------------------------------------------------------
// —ортировка вектора по убыванию второго параметра пары
//---------------------------------------------------------------------------
void TGeneticAlg::sortVecStr(vector< pair<string, int> > &v)
{
	std::sort(v.begin(),
			  v.end(),
			  boost::bind(std::greater<int>(),
					boost::bind(&std::pair<string, int>::second, _1),
					boost::bind(&std::pair<string, int>::second, _2))
			 );
}
//---------------------------------------------------------------------------
// √енераци€ допустимого символа
//---------------------------------------------------------------------------
char TGeneticAlg::generationSymbol()
{
	int Char_Code;
	Char_Code = random(27)+97; // символы [a-z]
	if (Char_Code == 123)
		Char_Code = 32; // пробел
	return char(Char_Code);
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
