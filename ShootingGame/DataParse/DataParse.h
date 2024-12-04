#pragma once

void OpenFile(const char* const sFilePath, void (*Process)(char* const));

bool ReadInt32(char* const sBufferData, const char* const sSubString, int* pOutData);
bool ReadInt16(char* const sBufferData, const char* const sSubString, short* pOutData);
bool ReadInt8(char* const sBufferData, const char* const sSubString, char* pOutData);

bool ReadString(char* const sBufferData, const char* const sSubString, char* const pOutBufferData, const unsigned int iBufferSize);