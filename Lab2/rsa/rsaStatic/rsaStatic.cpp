#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include "..\rsa\rsa.h"
#include <locale.h> 
#include <windows.h>
#include<iostream>

using namespace std;


#define MAX_INPUT_LENGTH 50



int _tmain() {

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	TCHAR str[MAX_INPUT_LENGTH];
	int lang;
	const wchar_t *msg1;
	const wchar_t *msg2;
	const wchar_t *msg3;


	printf_s("Choose language: 1 - English, 2 - Russian, 3 - Ukrainian\n");
	scanf_s("%d", &lang);

	if (lang == 1) {
		_tprintf(_T("\nEnter the message to encode:\n"));
		msg1 = _T("\nSource message: ");
		msg2 = _T("\nEncrypted message: ");
		msg3 = _T("\nDecripted message: ");
	}

	if (lang == 2) {
		_tsetlocale(LC_ALL, _T("Russian"));
		_tprintf(_T("\n������� ��������� ��� ����������:\n"));
		msg1 = _T("\n�������� ���������: ");
		msg2 = _T("\n������������� ���������: ");
		msg3 = _T("\n�������������� ���������: ");
	}

	if (lang == 3) {
		_tsetlocale(LC_ALL, _T("Ukrainian"));
		_tprintf(_T("\n������ ����������� ��� ����������:\n"));
		msg1 = _T("\n������� ����������: ");
		msg2 = _T("\n������������ �����������: ");
		msg3 = _T("\n������������� �����������: ");
	}

	_tscanf_s(_T("%s"), str, MAX_INPUT_LENGTH);
	const size_t size = _tcslen(str);




	_tprintf(msg1, str);

	unsigned e, d;
	unsigned n = generateKeys(e, d);

	unsigned* encryptedStr = new unsigned[size];

	_tprintf(msg2);
	for (int i = 0; i < size; i++)
	{
		crypt(str[i], e, n, &encryptedStr[i]);
		_tprintf(_T("%d "), encryptedStr[i]);
	}

	unsigned* decryptedStr = new unsigned[size + 1];


	int counter = 0;
	_tprintf(msg3);
	for (counter = 0; counter < size; counter++)
	{
		unsigned a;
		decrypt(encryptedStr[counter], d, n, &a);
		decrypt(encryptedStr[counter], d, n, &decryptedStr[counter]);
	}

	decryptedStr[counter] = _T('\0');

	for (int i = 0; i < size; i++)
	{
		_tprintf(_T("%c"), decryptedStr[i]);
	}

	_tprintf(_T("\n"));

	delete[] encryptedStr;
	delete[] decryptedStr;

	system("pause");

	return 0;
}
