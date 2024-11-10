#include <iostream>

int my_strlen(const char* const str) {
	int length = 0;

	while (str[length] != '\0')
		length++;

	return length;
}

void my_strcpy(char* const dest, int dest_size, const char* const source) {
	const int iSourceLength = (strlen(source) >= dest_size ? dest_size - 1 : strlen(source));

	for (int i = 0; i < iSourceLength; i++)
		dest[i] = source[i];

	dest[iSourceLength] = '\0';
}

int my_strcmp(const char* const string1, const char* const string2) {
	if (strlen(string1) > strlen(string2))
		return 1;
	else if (strlen(string1) < strlen(string2))
		return -1;

	for (int i = 0; i < strlen(string1); i++) {
		if (string1[i] > string2[i])
			return 1;
		else if (string1[i] < string2[i])
			return -1;
	}
	return 0;
}

void my_strcat(char* const dest, const int dest_size, const char* const add) {
	if ((strlen(dest) + strlen(add) + 1) > dest_size)
		return;

	const int iStartIndex = strlen(dest);
	for (int i = 0; i < strlen(add); i++)
		dest[iStartIndex + i] = add[i];

	dest[dest_size - 1] = '\0';
}

char* my_strchr(const char* const string, int c) {
	int len = strlen(string);

	for (int i = 0; i < len; i++)
		if (string[i] == c)
			return (char*)(string + i);

	return nullptr;
}

char* my_strstr(const char* const string, const char* const search) {
	int len = strlen(string);
	int searchLength = strlen(search);

	if (searchLength > len)
		return nullptr;

	for (int i = 0; i < len; i++) {
		if (string[i] == search[0]) {
			int j = 0;
			for (j = 1; j < searchLength; j++)
				if (string[i + j] != search[j])
					break;

			if (j >= searchLength)
				return (char*)(string + i);
		}
	}
	return nullptr;
}

char* my_strlwr(char* const string) {
	for (int i = 0; i < strlen(string); i++)
		if (string[i] >= 65 && string[i] <= 90)
			string[i] = string[i] + 32;

	return string;
}

char* my_strhir(char* const string) {
	for (int i = 0; i < strlen(string); i++)
		if (string[i] >= 97 && string[i] <= 122)
			string[i] = string[i] - 32;

	return string;
}

int main() {
	int result;
	char* pdest;
	char string[] = "ABcdEFGHIJKlMN";
	pdest = my_strlwr(string);

	std::cout << pdest;

	return 0;
}