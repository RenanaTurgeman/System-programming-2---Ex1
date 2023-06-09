#include "AdptArray.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct AdptArray_
{
	int ArrSize;
	PElement* pElemArr;
	DEL_FUNC delFunc;
	COPY_FUNC copyFunc;
    PRINT_FUNC printFunc;
}AdptArray;


PAdptArray CreateAdptArray(COPY_FUNC copyFunc_, DEL_FUNC delFunc_ , PRINT_FUNC printFunc_)
{
	//initialization
	PAdptArray pArr = (PAdptArray)malloc(sizeof(AdptArray));
	if (pArr == NULL)
		return NULL;
	pArr->ArrSize = 0;
	pArr->pElemArr = NULL;
	pArr->delFunc = delFunc_;
	pArr ->copyFunc = copyFunc_;
	pArr->printFunc = printFunc_;
	return pArr;
}


Result SetAdptArrayAt(PAdptArray pArr, int idx, PElement pNewElem)
{
	PElement* newpElemArr;

	if (pArr == NULL) //the pointer is to null
		return FAIL;
	if (idx < 0) //idx should be non nagative
		return FAIL;
	if (idx >= pArr->ArrSize)
	{
		// Extend Array - when the idx is bigger then the arr
		if ((newpElemArr = (PElement*)calloc((idx + 1), sizeof(PElement))) == NULL)
			return FAIL;
		memcpy(newpElemArr, pArr->pElemArr, (pArr->ArrSize) * sizeof(PElement));
		free(pArr->pElemArr); //free the old
		pArr->pElemArr = newpElemArr; //save the new
	}

	// Delete Previous Elem
	if((pArr->pElemArr)[idx] != NULL){
			pArr->delFunc((pArr->pElemArr)[idx]);
	}
	//Save copy of the new Elem
	(pArr->pElemArr)[idx] = pArr->copyFunc(pNewElem);

	// Update Array Size
	pArr->ArrSize = (idx >= pArr->ArrSize) ? (idx + 1) : pArr->ArrSize;
	return SUCCESS;
}


void DeleteAdptArray(PAdptArray pArr)
{
	if (pArr == NULL)
		return;

	for(int i = 0; i < pArr->ArrSize; ++i)
	{
		//we need to del all the elements using the del func
		if ((pArr->pElemArr)[i] != NULL)
			pArr->delFunc((pArr->pElemArr)[i]);
	}
	free(pArr->pElemArr);
	free(pArr);
}

PElement GetAdptArrayAt(PAdptArray pArr, int idx)
{
	// if the index not exsits in the array
	if (pArr == NULL || idx > pArr->ArrSize)
	{
		return NULL;
	}

	PElement copyElem = NULL;
	if((pArr->pElemArr)[idx]!= NULL)
		copyElem = pArr->copyFunc((pArr->pElemArr)[idx]);
	return copyElem;
}

int GetAdptArraySize(PAdptArray pArr)
{
	if (pArr == NULL)
		return -1; //for the case the arr dont initialized in sucsses

	return pArr->ArrSize;
}

void PrintDB(PAdptArray pArr)
{
	if (pArr == NULL)
		return;

	for (int i = 0; i < pArr->ArrSize; i++)
	{
		if ((pArr->pElemArr)[i] != NULL)
			pArr->printFunc((pArr->pElemArr)[i]);
	}	
}