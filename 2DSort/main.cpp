// main.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include <iostream>
#include <iomanip>
#include <time.h>
#include <vector>
using namespace std;

#include "2DSort.h"

extern void TwoDSort(vector<CUSTOM_POS>& vecPos, const int iType, const double dTol);

int main()
{
	int iSize = 11;
	vector<CUSTOM_POS> vecPos;
	vecPos.resize(iSize * iSize);
	for (int i = 0; i < iSize; i++)
		for (int j = 0; j < iSize; j++)
			vecPos[i * iSize + j] = CUSTOM_POS(i / double(iSize - 1), j / double(iSize - 1));

	srand((unsigned int)time(NULL));
	for (int i = 0; i < iSize * iSize; i++)
	{
		int iPos1 = rand() % (iSize * iSize);
		int iPos2 = rand() % (iSize * iSize);

		CUSTOM_POS posTmp = vecPos[iPos1];
		vecPos[iPos1] = vecPos[iPos2];
		vecPos[iPos2] = posTmp;
	}

	bool bDispPnt = true;

	if (bDispPnt)
	{
		cout << "Input points:" << fixed << setprecision(2);
		for (int i = 0; i < (int)vecPos.size(); i++)
		{
			if (i % iSize == 0)
				cout << "\n";
			cout << "(" << vecPos[i].m_dX << ", " << vecPos[i].m_dY << ") ";
		}
		cout << "\n";
	}

	clock_t tTime = clock();
	TwoDSort(vecPos, 3, 1.e-6);
	cout << "\nSorting time: " << (clock() - tTime) / 1000. << " sec\n";

	if (bDispPnt)
	{
		cout << "\nSorted points:" << fixed << setprecision(2);
		for (int i = 0; i < (int)vecPos.size(); i++)
		{
			if (i % iSize == 0)
				cout << "\n";
			cout << "(" << vecPos[i].m_dX << ", " << vecPos[i].m_dY << ") ";
		}
		cout << "\n\n\n\n";
	}

	return 0;
}

// 執行程式: Ctrl + F5 或 [偵錯] > [啟動但不偵錯] 功能表
// 偵錯程式: F5 或 [偵錯] > [啟動偵錯] 功能表

// 開始使用的提示: 
//   1. 使用 [方案總管] 視窗，新增/管理檔案
//   2. 使用 [Team Explorer] 視窗，連線到原始檔控制
//   3. 使用 [輸出] 視窗，參閱組建輸出與其他訊息
//   4. 使用 [錯誤清單] 視窗，檢視錯誤
//   5. 前往 [專案] > [新增項目]，建立新的程式碼檔案，或是前往 [專案] > [新增現有項目]，將現有程式碼檔案新增至專案
//   6. 之後要再次開啟此專案時，請前往 [檔案] > [開啟] > [專案]，然後選取 .sln 檔案
