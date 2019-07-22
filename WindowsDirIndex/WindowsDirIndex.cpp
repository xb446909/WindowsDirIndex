// WindowsDirIndex.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include "FileIndex.h"

#include "tinyxml2.h"

using namespace std;

int main()
{
	CFileIndex fileIdx;
	cout << "Start create index..." << endl;
	DWORD dwStart = GetTickCount();
	fileIdx.CreateIndex("C:\\");
	DWORD dwEnd = GetTickCount();

	cout << "Create index end, cost: " << dwEnd - dwStart << " ms" << endl;
	cout << "Total: " << fileIdx.m_nFileNum << " files" << endl;

	cout << endl;

	//fileIdx.Print();

	cout << "Start compare..." << endl;
	dwStart = GetTickCount();
	fileIdx.CompareIndex("C:\\");
	dwEnd = GetTickCount();
	cout << "Compare end, Cost: " << dwEnd - dwStart << " ms" << endl;
	cout << endl;
	system("pause");
}

