
#include "2DSort.h"
#include <vector>
using namespace std;

double CUSTOM_POS::m_sdTol = 0.;

template <class T>
void Merge(vector<T>& vecI, vector<T>& vecS, const int iL, const int iM, const int iR, bool (*Comp) (const T&, const T&))
{
	int iIndexL = iL;
	int iIndexR = iM + 1;
	int iIndexS = iL;

	while (iIndexL <= iM && iIndexR <= iR)
	{
		if (Comp(vecI[iIndexL], vecI[iIndexR]))
			vecS[iIndexS++] = vecI[iIndexL++];
		else
			vecS[iIndexS++] = vecI[iIndexR++];
	}

	if (iIndexL > iM)
		for (int i = iIndexR; i <= iR; i++)
			vecS[iIndexS + i - iIndexR] = vecI[i];
	else
		for (int i = iIndexL; i <= iM; i++)
			vecS[iIndexS + i - iIndexL] = vecI[i];
}

template <class T>
void MergePass(vector<T>& vecI, vector<T>& vecO, const int iN, const int iL, bool (*Comp) (const T&, const T&))
{
#pragma omp parallel for
	for (int i = 0; i <= iN - 2 * iL; i += 2 * iL)
		Merge(vecI, vecO, i, i + iL - 1, i + 2 * iL - 1, Comp);

	int iIndex;
	for (iIndex = 0; iIndex <= iN - 2 * iL; iIndex += 2 * iL);

	if (iIndex + iL < iN)
		Merge(vecI, vecO, iIndex, iIndex + iL - 1, iN - 1, Comp);
	else
		for (int i = iIndex; i < iN; i++)
			vecO[i] = vecI[i];
}

template <class T>
void MergeSort(vector<T>& vecI, const int iN, bool (*Comp) (const T&, const T&))
{
	vector<T> vecTmp;
	vecTmp.resize(iN);
	for (int iL = 1; iL < iN; iL *= 2)
	{
		MergePass(vecI, vecTmp, iN, iL, Comp);
		iL *= 2;
		MergePass(vecTmp, vecI, iN, iL, Comp);
	}
	vector<T> vecEmpty;
	vecTmp.swap(vecEmpty);
}

bool Less_X(const CUSTOM_POS& pos1, const CUSTOM_POS& pos2);
bool Greater_X(const CUSTOM_POS& pos1, const CUSTOM_POS& pos2);
bool Less_Y(const CUSTOM_POS& pos1, const CUSTOM_POS& pos2);
bool Greater_Y(const CUSTOM_POS& pos1, const CUSTOM_POS& pos2);

void TwoDSort(vector<CUSTOM_POS>& vecPos, const int iType, const double dTol)
{
	CUSTOM_POS::m_sdTol = dTol;
	vector<CUSTOM_POS> vecRev(vecPos);
	bool bRev = false;

	switch (iType)
	{
	case 0:
		MergeSort(vecPos, (int)vecPos.size(), &Less_X);
		MergeSort(vecPos, (int)vecPos.size(), &Less_Y);
		MergeSort(vecRev, (int)vecRev.size(), &Greater_X);
		MergeSort(vecRev, (int)vecRev.size(), &Less_Y);

		for (int i = 0; i < (int)vecPos.size(); i++)
		{
			if (i > 0 && !Less_Y(vecPos[i], vecPos[i - 1]))
				bRev = !bRev;

			if (bRev)
				vecPos[i] = vecRev[i];
		}
		break;
	case 1:
		MergeSort(vecPos, (int)vecPos.size(), &Less_Y);
		MergeSort(vecPos, (int)vecPos.size(), &Less_X);
		MergeSort(vecRev, (int)vecRev.size(), &Greater_Y);
		MergeSort(vecRev, (int)vecRev.size(), &Less_X);

		for (int i = 0; i < (int)vecPos.size(); i++)
		{
			if (i > 0 && !Less_X(vecPos[i], vecPos[i - 1]))
				bRev = !bRev;

			if (bRev)
				vecPos[i] = vecRev[i];
		}
		break;
	case 2:
		MergeSort(vecPos, (int)vecPos.size(), &Less_X);
		MergeSort(vecPos, (int)vecPos.size(), &Less_Y);
		break;
	case 3:
		MergeSort(vecPos, (int)vecPos.size(), &Less_Y);
		MergeSort(vecPos, (int)vecPos.size(), &Less_X);
		break;
	default:
		break;
	}

	vector<CUSTOM_POS> vecEmpty;
	vecRev.swap(vecEmpty);
}

bool Less_X(const CUSTOM_POS& pos1, const CUSTOM_POS& pos2)
{
	if (fabs(pos1.m_dX - pos2.m_dX) < CUSTOM_POS::m_sdTol)
		return true;
	else
		return pos1.m_dX < pos2.m_dX;
}

bool Greater_X(const CUSTOM_POS& pos1, const CUSTOM_POS& pos2)
{
	if (fabs(pos1.m_dX - pos2.m_dX) < CUSTOM_POS::m_sdTol)
		return true;
	else
		return pos1.m_dX > pos2.m_dX;
}

bool Less_Y(const CUSTOM_POS& pos1, const CUSTOM_POS& pos2)
{
	if (fabs(pos1.m_dY - pos2.m_dY) < CUSTOM_POS::m_sdTol)
		return true;
	else
		return pos1.m_dY < pos2.m_dY;
}

bool Greater_Y(const CUSTOM_POS& pos1, const CUSTOM_POS& pos2)
{
	if (fabs(pos1.m_dY - pos2.m_dY) < CUSTOM_POS::m_sdTol)
		return true;
	else
		return pos1.m_dY > pos2.m_dY;
}