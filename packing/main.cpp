#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <conio.h>

#define MAX_FILE_NAME 64

struct PACKED_FILE_HEADER {
public:
	uint16_t m_iType;
	uint16_t m_iFileCount;

public:
	PACKED_FILE_HEADER(const uint16_t iFileCount = 0) : m_iType((0x50 << 8) | (0x4B)), m_iFileCount(iFileCount) {};

};

struct PACKED_FILE_INFO_HEADER {
public:
	uint32_t m_iFileSize;
	uint32_t m_iFileOffset;
	char m_sFileName[MAX_FILE_NAME];

public:
	PACKED_FILE_INFO_HEADER() : m_iFileSize(), m_iFileOffset() {
		memset(m_sFileName, 0, MAX_FILE_NAME);
	}

	PACKED_FILE_INFO_HEADER(const uint32_t iFileSize, const uint32_t iFileOffset, const char* const sFileName) : m_iFileSize(iFileSize), m_iFileOffset(iFileOffset) {
		memset(m_sFileName, 0, MAX_FILE_NAME);
		memcpy_s(m_sFileName, MAX_FILE_NAME, sFileName, strlen(sFileName));
	}

public:
	static size_t GetSize() {
		return MAX_FILE_NAME + sizeof(uint32_t) + sizeof(uint32_t);
	}
};

void Packing(const uint16_t iFileCount, const char* const sPackedFileName, const std::vector<std::string>& sFileNames) {
	bool bFileExist = false;
	std::ifstream check(sPackedFileName);
	if (check.is_open()) {
		bFileExist = true;
		check.close();
	}
	else {
		std::ofstream create(sPackedFileName);
		create.close();
	}

	std::fstream packingFileStream(sPackedFileName, std::ios::binary | std::ios::in | std::ios::out | std::ios::ate);
	uint32_t iInfoHeaderOffset = sizeof(PACKED_FILE_HEADER);
	PACKED_FILE_HEADER fileHeader(iFileCount);
	std::vector<PACKED_FILE_INFO_HEADER> fileInfoHeaders;

	if (bFileExist) {
		packingFileStream.seekg(std::ios::beg);
		packingFileStream.read(reinterpret_cast<char*>(&fileHeader), sizeof(PACKED_FILE_HEADER));

		fileInfoHeaders.resize(fileHeader.m_iFileCount);

		iInfoHeaderOffset = packingFileStream.seekg(-static_cast<int32_t>(fileHeader.m_iFileCount * PACKED_FILE_INFO_HEADER::GetSize()), std::ios::end).tellg();
		packingFileStream.read(reinterpret_cast<char*>(&fileInfoHeaders[0]), PACKED_FILE_INFO_HEADER::GetSize() * fileInfoHeaders.size());
		packingFileStream.seekp(iInfoHeaderOffset, std::ios::beg);
	}
	else {
		packingFileStream.seekp(std::ios::beg);
		packingFileStream.write(reinterpret_cast<const char*>(&fileHeader), sizeof(PACKED_FILE_HEADER));
	}

	for (const auto& iterator : sFileNames) {
		std::ifstream fileStream(iterator, std::ios::binary | std::ios::in);
		if (fileStream.is_open()) {
			uint32_t endPos = fileStream.seekg(0, std::ios::end).tellg();
			char* sFileDataBuffer = new char[endPos];

			fileStream.seekg(0, std::ios::beg);
			fileStream.read(sFileDataBuffer, endPos);

			packingFileStream.write(sFileDataBuffer, endPos);

			fileInfoHeaders.emplace_back(endPos, iInfoHeaderOffset, iterator.c_str());
			iInfoHeaderOffset += endPos;

			delete[] sFileDataBuffer;
			fileStream.close();
		}
		else
			std::cout << "파일 " << iterator << " 를 열 수 없습니다. 해당 파일은 작업에서 제외됩니다.\n";
	}

	packingFileStream.seekp(iInfoHeaderOffset, std::ios::beg);
	// add file info header
	packingFileStream.write(reinterpret_cast<const char*>(&fileInfoHeaders[0]), PACKED_FILE_INFO_HEADER::GetSize() * fileInfoHeaders.size());
	packingFileStream.close();
}

void PackingMenu() {
	system("cls");

	uint16_t iFileCount = 0;
	std::cout << "패킹할 파일의 총 갯수를 입력해주세요.\n";
	std::cin >> iFileCount;

	std::vector<std::string> sFileNames;
	for (uint16_t i = 0; i < iFileCount; i++) {
		std::string sFileName;
		std::cout << "\n패킹할 파일의 파일명과 확장자를 입력해주세요.(최대 길이 64)\n";
		std::cin >> sFileName;

		sFileNames.push_back(sFileName);
	}

	std::cout << "\n패킹된 파일명을 입력해주세요.(최대 길이 64)\n";
	char sPackedFileName[MAX_FILE_NAME];
	std::cin >> sPackedFileName;

	Packing(iFileCount, sPackedFileName, sFileNames);
}

void Unpacking(const char* const sPackedFileName) {
	std::ifstream packedFileStream(sPackedFileName, std::ios::in | std::ios::binary);
	if (!packedFileStream.is_open()) {
		std::cout << "존재하지 않는 패킹 파일입니다.";
		return;
	}

	PACKED_FILE_HEADER fileHeader;
	packedFileStream.read(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));

	std::vector<PACKED_FILE_INFO_HEADER> fileInfoHeaders;
	fileInfoHeaders.resize(fileHeader.m_iFileCount);

	packedFileStream.seekg(-static_cast<int32_t>(sizeof(PACKED_FILE_INFO_HEADER) * fileHeader.m_iFileCount), std::ios::end);
	packedFileStream.read(reinterpret_cast<char*>(&fileInfoHeaders[0]), sizeof(PACKED_FILE_INFO_HEADER) * fileHeader.m_iFileCount);

	for (const auto& iterator : fileInfoHeaders) {
		char* sDataBuffer = new char[iterator.m_iFileSize];
		
		packedFileStream.seekg(iterator.m_iFileOffset, std::ios::beg);
		packedFileStream.read(sDataBuffer, iterator.m_iFileSize);

		std::ofstream outDataStream(iterator.m_sFileName, std::ios::out | std::ios::binary);
		
		outDataStream.write(sDataBuffer, iterator.m_iFileSize);

		outDataStream.close();
		delete[] sDataBuffer;
	}
}

void UnpackingMenu() {
	system("cls");

	std::cout << "패킹을 해제할 파일의 이름을 입력해주세요.(최대 길이 64)\n";
	char sPackedFileName[MAX_FILE_NAME];
	std::cin >> sPackedFileName;

	std::cout << "\n1. 전체 언패킹\n";
	std::cout << "2. 선택 언패킹\n";

	int key = _getch();
	switch (key) {
	case '1':
		Unpacking(sPackedFileName);
		break;
	case '2':
	{
		char sSelectUnpackFileName[MAX_FILE_NAME];
		std::cout << "\n언패킹할 파일의 이름과 확장자를 입력해주세요.(최대 길이 64)\n";
		std::cin >> sSelectUnpackFileName;

		//Unpacking();
	}
		break;
	}
}

void MainMenu() {
	system("cls");

	std::cout << "메뉴를 선택해주세요.\n";
	std::cout << "1. 파일 패킹\n";
	std::cout << "2. 패킹 해제\n";

	int key = _getch();
	switch (key) {
	case '1':
		PackingMenu();
		break;
	case '2':
		UnpackingMenu();
		break;
	}
}

int main() {

	while (true)
		MainMenu();

	return 0;
}