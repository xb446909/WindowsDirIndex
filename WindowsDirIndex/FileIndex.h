#pragma once
#include <Windows.h>


class CFileIndex
{
public:
	CFileIndex();
	~CFileIndex();
	void CreateIndex(const char* szPath);
private:
	void SearchFile(const char* szPath, bool bCompare);
	DWORD GetDiskSize(const char* szPath);

	DWORD m_dwTotalSize;
	DWORD m_dwScanSize;
};

