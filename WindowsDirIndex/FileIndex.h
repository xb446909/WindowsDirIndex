#pragma once
#include <Windows.h>
//#include "HashMap.h"
#include "DirModel.h"

class CFileIndex
{
public:
	CFileIndex();
	~CFileIndex();
	void CreateIndex(const char* szPath);
	void CompareIndex(const char* szPath);
	void SaveXML(const char* szFile) { m_dirModel.SaveXML(szFile); }
	void LoadXML(const char* szFile) { m_dirModel.LoadXML(szFile); }
	void Print();
	int m_nDirNum;
	int m_nFileNum;
private:
	void SearchFile(const char* szPath, string szParentDir, DirModel* pDirModel, bool bCompare);
	DWORD GetDiskSize(const char* szPath);

	DWORD m_dwTotalSize;
	DWORD m_dwScanSize;
	
	//CHashMap* m_pHashMap;

	DirModel m_dirModel;
};

