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
	int     len;                        // Длинна входной строки
	string  input; 						// Входная строка
	string  offsprings[OFFSPRINGS_MAX]; // Потомки
	string  survivors[SURVIVORS_MAX];   // Сильные особи
	float   coefMutation;               // Коэффициент мутации

	void   initPopulation();   			// Генерация начальной популяции
	int    compare(string str);  		// Сравнение строки с исходной на схожесть
	int    naturalSelection(); 			// Естественный отбор сильнейших особей
	void   crossing();                  // Скрещивание
	string mutation(string str); 		// Мутация одной особи
	void   PopulMutation();             // Мутация популяции

	char generationSymbol(); 			// Генерация допустимого символа
	void sortVec(vector< pair<int, int> > &v);	// Сортировка вектора по убыванию второго параметра пары
	void sortVecStr(vector< pair<string, int> > &v); // Сортировка вектора по убыванию второго параметра пары

public:
	TGeneticAlg() { coefMutation = 0; len = 0; };
	TGeneticAlg(string str) : input(str) { coefMutation = 0; len = 0; };

	void setString(string str) { input = str; };
	void setCoefMutation(float coef) { coefMutation = coef; };

	int run();
};

//---------------------------------------------------------------------------
#endif
