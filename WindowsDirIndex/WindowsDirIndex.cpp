// WindowsDirIndex.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include "FileIndex.h"

using namespace std;

int main()
{
	CFileIndex fileIdx;
	cout << "Start..." << endl;
	DWORD dwStart = GetTickCount();
	fileIdx.CreateIndex("C:\\");
	DWORD dwEnd = GetTickCount();

	cout << "End, Cost: " << dwEnd - dwStart << " ms" << endl;
}

