#include "DataParse.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void OpenFile(const char* const sFilePath, void (*Process)(char* const)) {
	FILE* file = NULL;
	if (fopen_s(&file, sFilePath, "rb") == 0) {
		fseek(file, 0, SEEK_END);
		const long dataSize = ftell(file);
		char* sBuffer = (char*)malloc((dataSize * sizeof(char)) + 1);
		memset(sBuffer, 0, (dataSize * sizeof(char)) + 1);

		if (sBuffer) {
			fseek(file, 0, SEEK_SET);
			if (fread(sBuffer, dataSize, 1, file) > 0)
				Process(sBuffer);
			free(sBuffer);
		}
		fclose(file);
	}
}

bool FindValueByKey(char* const sBufferData, const char* const sSubString, char** pValueData) {
	char* pColumnFindResult = strstr(sBufferData, sSubString);

	if (pColumnFindResult != NULL) {
		char* pDataFindResult = strchr(pColumnFindResult, ':');
		if (pDataFindResult != NULL && *(pDataFindResult + 1) != '\0') {
			pDataFindResult++;
			*pValueData = pDataFindResult;
			return true;
		}
	}
	return false;
}

bool ReadInt32(char* const sBufferData, const char* const sSubString, int* pOutData) {
	if (!sBufferData || !sSubString || !pOutData)
		return false;

	 char* pValueData = NULL;
	if (FindValueByKey(sBufferData, sSubString, &pValueData)) {
		*pOutData = atoi(pValueData);
		return true;
	}
	return false;
}

bool ReadInt16(char* const sBufferData, const char* const sSubString, short* pOutData) {
	if (!sBufferData || !sSubString || !pOutData)
		return false;

	char* pValueData = NULL;
	if (FindValueByKey(sBufferData, sSubString, &pValueData)) {
		*pOutData = (short)atoi(pValueData);
		return true;
	}
	return false;
}

bool ReadInt8(char* const sBufferData, const char* const sSubString, char* pOutData) {
	if (!sBufferData || !sSubString || !pOutData)
		return false;

	char* pValueData = NULL;
	if (FindValueByKey(sBufferData, sSubString, &pValueData)) {
		*pOutData = *pValueData;
		return true;
	}
	return false;
}

bool ReadString(char* const sBufferData, const char* const sSubString, char* const pOutBufferData, const unsigned int iBufferSize) {
	if (!sBufferData || !sSubString || !pOutBufferData)
		return false;

	char* pValueData = NULL;
	if (FindValueByKey(sBufferData, sSubString, &pValueData)) {
		char* sStartOffset = strchr(pValueData, '\"');
		if (sStartOffset != NULL) {
			sStartOffset++;
			char* sEndOffset = strchr(sStartOffset, '\"');

			strncpy_s(pOutBufferData, iBufferSize, sStartOffset, (sEndOffset - sStartOffset));
			return true;
		}
	}

	return false;
}
