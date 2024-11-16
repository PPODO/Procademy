#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <Windows.h>
#include <fstream>
#include <vector>

struct BITCOLOR_32 {
public:
	unsigned char R;
	unsigned char G;
	unsigned char B;
	unsigned char A;

public:
	BITCOLOR_32() : R(0), G(0), B(0), A(255) {};
	BITCOLOR_32(unsigned char _R, unsigned char _G, unsigned char _B, unsigned char _A) : R(_R), G(_G), B(_B), A(_A) {};
	BITCOLOR_32(const BITCOLOR_32& value) : R(value.R), G(value.G), B(value.B), A(value.A) {};

};

static BITCOLOR_32 operator/(const BITCOLOR_32& lhs, const int rValue) {
	return { static_cast<unsigned char>(lhs.R / 2), static_cast<unsigned char>(lhs.G / 2), static_cast<unsigned char>(lhs.B / 2) , static_cast<unsigned char>(lhs.A / 2) };
}

static BITCOLOR_32 operator+(const BITCOLOR_32& lhs, const BITCOLOR_32& rhs) {
	return { static_cast<unsigned char>(lhs.R + rhs.R), static_cast<unsigned char>(lhs.G + rhs.G), static_cast<unsigned char>(lhs.B + rhs.B), static_cast<unsigned char>(lhs.A + rhs.A) };
}

class CBitmap {
private:
	std::fstream m_fileHandle;

	char* m_pBMPImageBuffer;
	std::vector<BITCOLOR_32> m_bmpPixleDatas;

	BITMAPFILEHEADER m_bitMapFileHeader;
	BITMAPINFOHEADER m_bitMapInfoHeader;

private:
	void ExtractPixleDatas_RGB24() {
		if (!m_pBMPImageBuffer)
			return;

		char* pCachedBMPImageBufferPtr = m_pBMPImageBuffer;

		for (auto& iterator : m_bmpPixleDatas) {
			iterator.R = *(pCachedBMPImageBufferPtr);
			iterator.G = *(pCachedBMPImageBufferPtr + 1);
			iterator.B = *(pCachedBMPImageBufferPtr + 2);

			pCachedBMPImageBufferPtr += (sizeof(char) * 3);
		}
	}
	
	void ExtractPixleDatas_RGB32() {
		if (!m_pBMPImageBuffer)
			return;

		DWORD* pCachedBMPImageBufferPtr = reinterpret_cast<DWORD*>(m_pBMPImageBuffer);

		for (auto& iterator : m_bmpPixleDatas) {
			iterator.R = (*pCachedBMPImageBufferPtr) & 0xff;
			iterator.G = ((*pCachedBMPImageBufferPtr) >> 8) & 0xff;
			iterator.B = ((*pCachedBMPImageBufferPtr) >> 16) & 0xff;
			iterator.A = ((*pCachedBMPImageBufferPtr) >> 24) & 0xff;

			pCachedBMPImageBufferPtr++;
		}
	}

public:
	CBitmap(const char* const sFilePath, const std::ios::openmode openMode) : m_pBMPImageBuffer(nullptr), m_bitMapFileHeader(), m_bitMapInfoHeader() {
		m_fileHandle.open(sFilePath, std::ios::binary | openMode);
		if (!m_fileHandle.is_open())
			throw std::bad_exception();

		if (openMode == std::ios::in) {
			do {
				if (!m_fileHandle.read(reinterpret_cast<char*>(&m_bitMapFileHeader), sizeof(m_bitMapFileHeader)))
					break;

				if (!m_fileHandle.read(reinterpret_cast<char*>(&m_bitMapInfoHeader), sizeof(m_bitMapInfoHeader)))
					break;

				if (m_bitMapInfoHeader.biBitCount != 24 && m_bitMapInfoHeader.biBitCount != 32) {
					std::cout << "Unsupported Bitmap Bit Count! - Current BMP Bit Count : " << m_bitMapInfoHeader.biBitCount << std::endl;
					return;
				}

				const size_t iBMPBufferLength = m_bitMapInfoHeader.biWidth * m_bitMapInfoHeader.biHeight * (m_bitMapInfoHeader.biBitCount / 8);
				m_pBMPImageBuffer = new char[iBMPBufferLength];

				if (!m_fileHandle.read(m_pBMPImageBuffer, iBMPBufferLength))
					break;

				m_bmpPixleDatas.resize(m_bitMapInfoHeader.biWidth * m_bitMapInfoHeader.biHeight);
				if (m_bitMapInfoHeader.biBitCount == 24)
					ExtractPixleDatas_RGB24();
				else
					ExtractPixleDatas_RGB32();

				m_fileHandle.close();

				return;
			} while (0);

			std::cout << sFilePath << " File Read Error! - Readed Bytes : " << m_fileHandle.gcount() << std::endl;
		}
	}

	~CBitmap() {
		if (m_pBMPImageBuffer)
			delete[] m_pBMPImageBuffer;

		if (m_fileHandle.is_open())
			m_fileHandle.close();
	}

public:
	void Blend(const CBitmap& bitMapObject1, const CBitmap& bitMapObject2) {
		size_t iMinPixleDataCount = 0;
		size_t iMaxPixleDataCount = 0;
		LONG iBiggestImageWidth = 0;
		LONG iBiggestImageHeight = 0;
		LONG iSmallImageWidth = 0;
		LONG iSmallImageHeight = 0;
		const std::vector<BITCOLOR_32>* pBiggestBMPPtr = nullptr;

		if (bitMapObject1.m_bmpPixleDatas.size() < bitMapObject2.m_bmpPixleDatas.size()) {
			iMinPixleDataCount = bitMapObject1.m_bmpPixleDatas.size();
			iMaxPixleDataCount = bitMapObject2.m_bmpPixleDatas.size();

			iBiggestImageWidth = bitMapObject2.m_bitMapInfoHeader.biWidth;
			iBiggestImageHeight = bitMapObject2.m_bitMapInfoHeader.biHeight;

			iSmallImageWidth = bitMapObject1.m_bitMapInfoHeader.biWidth;
			iSmallImageHeight = bitMapObject1.m_bitMapInfoHeader.biHeight;

			pBiggestBMPPtr = &bitMapObject2.m_bmpPixleDatas;
		}
		else {
			iMinPixleDataCount = bitMapObject2.m_bmpPixleDatas.size();
			iMaxPixleDataCount = bitMapObject1.m_bmpPixleDatas.size();

			iBiggestImageWidth = bitMapObject1.m_bitMapInfoHeader.biWidth;
			iBiggestImageHeight = bitMapObject1.m_bitMapInfoHeader.biHeight;

			iSmallImageWidth = bitMapObject2.m_bitMapInfoHeader.biWidth;
			iSmallImageHeight = bitMapObject2.m_bitMapInfoHeader.biHeight;

			pBiggestBMPPtr = &bitMapObject1.m_bmpPixleDatas;
		}

		const size_t iTotalImageSize = (iMaxPixleDataCount * 4);

		BITMAPINFOHEADER infoHeader;
		infoHeader.biSize = sizeof(BITMAPINFOHEADER);
		infoHeader.biWidth = iBiggestImageWidth;
		infoHeader.biHeight = iBiggestImageHeight;
		infoHeader.biPlanes = 1;
		infoHeader.biCompression = 0;
		infoHeader.biSizeImage = iTotalImageSize;
		infoHeader.biXPelsPerMeter = 2835;
		infoHeader.biYPelsPerMeter = 2835;
		infoHeader.biClrUsed = 0;
		infoHeader.biClrImportant = 0;
		infoHeader.biBitCount = 32;

		BITMAPFILEHEADER fileHeader;
		fileHeader.bfOffBits = infoHeader.biSize + sizeof(fileHeader);
		fileHeader.bfType = 0x4d42;
		fileHeader.bfSize = fileHeader.bfOffBits + iTotalImageSize;
		fileHeader.bfReserved1 = 0;
		fileHeader.bfReserved2 = 0;


		this->m_bmpPixleDatas.resize(iMaxPixleDataCount);

		LONGLONG iSmallBMPImageIndex = 0;
		for (LONG i = 0; i < iBiggestImageHeight; i++) {
			for (LONG j = 0; j < iBiggestImageWidth; j++) {
				const LONGLONG iIndex = (i * iBiggestImageWidth) + j;

				if (j < iSmallImageWidth && i < iSmallImageHeight) {
					this->m_bmpPixleDatas[iIndex] = (bitMapObject1.m_bmpPixleDatas[iIndex] / 2) + (bitMapObject2.m_bmpPixleDatas[iSmallBMPImageIndex++] / 2);
				}
				else
					this->m_bmpPixleDatas[iIndex] = (*pBiggestBMPPtr)[iIndex];
			}
		}

		if (!m_fileHandle.write(reinterpret_cast<const char*>(&fileHeader), sizeof(fileHeader)))
			std::cout << "BMP File Header Write Error!";

		if (!m_fileHandle.write(reinterpret_cast<const char*>(&infoHeader), sizeof(infoHeader)))
			std::cout << "BMP InfoHeader Write Error!";

		if (!m_fileHandle.write(reinterpret_cast<const char*>(&this->m_bmpPixleDatas[0]), iTotalImageSize))
			std::cout << "File Write Error!";
	}

};

/*
	bmp에서 너비가 4단위로 나누어 떨어지지 않으면 24비트 컬러에선 한 행마다 패딩을 넣어줌.(4로 맞춰 떨어지게 하기 위해..)
	생각해서 작업해야할 듯 
*/

int main() {
/*	CBitmap sample1("sample.bmp", std::ios::in);
	CBitmap sample2("sample3.bmp", std::ios::in);

	CBitmap blendOutput("blended.bmp", std::ios::out);
	blendOutput.Blend(sample1, sample2);*/

	FILE* pFile1 = fopen("sample4.bmp", "rb");
	FILE* pFileB = fopen("blended.bmp", "wb");

	BITMAPFILEHEADER bmpFileHeader;
	BITMAPINFOHEADER bmpInfoHeader;

	if (fread(&bmpFileHeader, sizeof(bmpFileHeader), 1, pFile1) != 1)
		std::cout << "Sample 1 Bmp File Header Error!\n";
	if (fread(&bmpInfoHeader, sizeof(bmpInfoHeader), 1, pFile1) != 1)
		std::cout << "Sample 1 Bmp Info Header Error!\n";

	size_t iBMPBufferLength = bmpInfoHeader.biSizeImage;

	unsigned char* pFile1BMPBuffer = (unsigned char*)malloc(iBMPBufferLength);
	std::vector<unsigned char> buffer;
	buffer.resize(iBMPBufferLength);

	if (fread(pFile1BMPBuffer, iBMPBufferLength, 1, pFile1) != 1)
		std::cout << "Sample 1 Bmp Image File Read Error!\n";

	unsigned char* pCached1Buffer = pFile1BMPBuffer;
	for (int i = 0; i < iBMPBufferLength; i++) 
		pFile1BMPBuffer[i] = 0xff;

	if (fwrite(&bmpFileHeader, sizeof(bmpFileHeader), 1, pFileB) != 1)
		std::cout << "BMP File Header Writing Error!\n";
	fflush(pFileB);

	if (fwrite(&bmpInfoHeader, sizeof(bmpInfoHeader), 1, pFileB) != 1)
		std::cout << "BMP Info Header Writing Error!\n";
	fflush(pFileB);

	if (fwrite(&pFile1BMPBuffer[0], iBMPBufferLength, 1, pFileB) != 1)
		std::cout << "BMP Image File Writing Error!\n";
	fflush(pFileB);

	free(pFile1BMPBuffer);

	fclose(pFile1);
	fclose(pFileB);
	return 0;
}