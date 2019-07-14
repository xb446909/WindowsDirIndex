// WindowsDirIndex.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include "FileIndex.h"

using namespace std;

int main()
{
	CFileIndex fileIdx;
	cout << "Start create index..." << endl;
	DWORD dwStart = GetTickCount();
	fileIdx.CreateIndex("C:\\Qt");
	DWORD dwEnd = GetTickCount();

	cout << "Create index end, Cost: " << dwEnd - dwStart << " ms" << endl;

	cout << endl;

	cout << "Start compare..." << endl;
	dwStart = GetTickCount();
	fileIdx.CompareIndex("C:\\Qt");
	dwEnd = GetTickCount();
	cout << "Compare end, Cost: " << dwEnd - dwStart << " ms" << endl;
	cout << endl;
	system("pause");
}

