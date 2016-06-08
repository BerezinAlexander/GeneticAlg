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
	// ����� ������� ����� ��������� 1%
	// ������ �������� 1/len ��� 1/OFFSPRINGS_MAX
//	coefMutation = 9; //1/len;
	// ��������� ���������
	initPopulation();

	//  ���� �������/�����������/������
	for(;;)
	{
		// ����� ������� ������
		int iResCompare = naturalSelection();
		// �����������
		crossing();
		// �������
		PopulMutation();
		// ����� � ����
		AnsiString strRes;
		strRes = IntToStr(result) + ":   " + survivors[0].c_str();
		frmMain->mmText->Lines->Add(strRes.c_str());
		// ������� ���������
		++result;
		// �������� �� ������ ���������� � �������� �������
		if(iResCompare == len)	break;
		// ����������� � 20000 ���������
		if(result > 20000) break;
	}

	return result;
}
//---------------------------------------------------------------------------
// ��������� ��������� ���������
//---------------------------------------------------------------------------
void TGeneticAlg::initPopulation()
{
	CodeSite->EnterMethod("initPopulation");
	string str = "";
	// ���������� ��������� ���������
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
// ��������� ������ � �������� �� ��������
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
// ����� ���������� ������
//---------------------------------------------------------------------------
int TGeneticAlg::naturalSelection()
{
	// ���� ������������ ( ����� �����, �������� � �������� ������� )
	vector< pair<int, int> > vResCompare;
	for(int i=0; i<OFFSPRINGS_MAX; ++i)
	{
		vResCompare.push_back( make_pair(i, compare(offsprings[i]) ));
	}
	// ���������� ������� �� �������� ������� ��������� ����
	sortVec(vResCompare);
	// ����� ���������� ������
	vector< pair<int, int> >::iterator it = vResCompare.begin();
	for(int i = 0; i< SURVIVORS_MAX; i++)
	{
		survivors[i] = offsprings[it->first];
		++it;
	}
	return vResCompare.begin()->second;
}
//---------------------------------------------------------------------------
// ����������� (����� ����������� - ��������)
//---------------------------------------------------------------------------
void TGeneticAlg::crossing()
{
	vector< pair<string, int> > vResCrossing;
	for(int i = 0; i < SURVIVORS_MAX - 1; i++)
	{
		for(int j = 1; j < SURVIVORS_MAX; j++)
		{
			int pointCrossing = random(len); // ����� �����������
			int lenSecond = len - pointCrossing; // ����� ������ ����� ������
			string temp;
			// ���������� ������ �������� ������ ������ � ������ ��������� ������ ������
			temp = survivors[i].substr(0, pointCrossing);
			temp += survivors[j].substr(pointCrossing, lenSecond);
			vResCrossing.push_back( make_pair(temp, compare(temp) ));
			// ���������� ������ �������� ������ ������ � ������ ��������� ������ ������
			temp = survivors[j].substr(0, pointCrossing);
			temp += survivors[i].substr(pointCrossing, lenSecond);
			vResCrossing.push_back( make_pair(temp, compare(temp) ));
		}
	}
	// ���������� ������� �� �������� ������� ��������� ����
	sortVecStr(vResCrossing);
	// ������������ ���������
	vector< pair<string, int> >::iterator it = vResCrossing.begin();
	for(int i = 0; i< SURVIVORS_MAX; i++)
	{
		offsprings[i] = it->first;
		++it;
	}
}
//---------------------------------------------------------------------------
// ������� ����� �����
//---------------------------------------------------------------------------
string TGeneticAlg::mutation(string str)
{
	// ����� ������� ����� ��������� 1%
	// ������ �������� 1/len ��� 1/OFFSPRINGS_MAX
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
// ������� ���������
//---------------------------------------------------------------------------
void TGeneticAlg::PopulMutation()
{
	for(int i = 0; i< OFFSPRINGS_MAX; i++)
		offsprings[i] = mutation(offsprings[i]);
}
//---------------------------------------------------------------------------
// ���������� ������� �� �������� ������� ��������� ����
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
// ���������� ������� �� �������� ������� ��������� ����
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
// ��������� ����������� �������
//---------------------------------------------------------------------------
char TGeneticAlg::generationSymbol()
{
	int Char_Code;
	Char_Code = random(27)+97; // ������� [a-z]
	if (Char_Code == 123)
		Char_Code = 32; // ������
	return char(Char_Code);
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
