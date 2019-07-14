#pragma once
#include <Windows.h>
#include "HashMap.h"

class CFileIndex
{
public:
	CFileIndex();
	~CFileIndex();
	void CreateIndex(const char* szPath);
	void CompareIndex(const char* szPath);
private:
	void SearchFile(const char* szPath, string szParentDir, bool bCompare);
	DWORD GetDiskSize(const char* szPath);

	DWORD m_dwTotalSize;
	DWORD m_dwScanSize;

	CHashMap* m_pHashMap;
};

