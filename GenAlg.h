//---------------------------------------------------------------------------

#ifndef GenAlgH
#define GenAlgH

#include <time.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <functional> // std::less
#include <algorithm>    // std::sort

#define OFFSPRINGS_MAX 30
#define SURVIVORS_MAX 6

using namespace std;

class TGeneticAlg
{
private:
	int     len;                        // ������ ������� ������
	string  input; 						// ������� ������
	string  offsprings[OFFSPRINGS_MAX]; // �������
	string  survivors[SURVIVORS_MAX];   // ������� �����
	float   coefMutation;               // ����������� �������

	void   initPopulation();   			// ��������� ��������� ���������
	int    compare(string str);  		// ��������� ������ � �������� �� ��������
	int    naturalSelection(); 			// ������������ ����� ���������� ������
	void   crossing();                  // �����������
	string mutation(string str); 		// ������� ����� �����
	void   PopulMutation();             // ������� ���������

	char generationSymbol(); 			// ��������� ����������� �������
	void sortVec(vector< pair<int, int> > &v);	// ���������� ������� �� �������� ������� ��������� ����
	void sortVecStr(vector< pair<string, int> > &v); // ���������� ������� �� �������� ������� ��������� ����

public:
	TGeneticAlg() { coefMutation = 0; len = 0; };
	TGeneticAlg(string str) : input(str) { coefMutation = 0; len = 0; };

	void setString(string str) { input = str; };
	void setCoefMutation(float coef) { coefMutation = coef; };

	int run();
};

//---------------------------------------------------------------------------
#endif
