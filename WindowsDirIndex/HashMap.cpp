#include "pch.h"
#include "HashMap.h"
#include <iostream>

using namespace std;

FileModel::FileModel(string szDir, string szFileName)
	: m_szDir(szDir)
	, m_szFileName(szFileName)
	, m_pNext(nullptr)
	, m_nIdx(0)
{
}

FileModel::~FileModel()
{
}

CHashMap::CHashMap(int size)
	: m_nSize(size)
{
}


CHashMap::~CHashMap()
{
}

void CHashMap::Add(string szDir, string szFileName)
{
	int nIdx = szDir[0] % m_nSize;
	//int nIdx = szDir[0];
	//int nIdx = szDir.back();
	if (m_mapFileModel.find(nIdx) != m_mapFileModel.end())
	{
		FileModel* pFileModel = new FileModel(szDir, szFileName);
		pFileModel->m_pNext = m_mapFileModel[nIdx];
		pFileModel->m_nIdx = m_mapFileModel[nIdx]->m_nIdx + 1;
		m_mapFileModel[nIdx] = pFileModel;
	}
	else
	{
		m_mapFileModel[nIdx] = new FileModel(szDir, szFileName);
	}
}

bool CHashMap::FindFile(string szDir, string szFileName)
{
	int nIdx = szDir[0] % m_nSize;
	//int nIdx = szDir[0];
	//int nIdx = szDir.back();
	if (m_mapFileModel.find(nIdx) == m_mapFileModel.end())
	{
		return false;
	}

	return FindFile(m_mapFileModel[nIdx], szDir, szFileName);
}

void CHashMap::Print()
{
	cout << endl;
	cout << "===== Print =====" << endl;

	for (auto it = m_mapFileModel.begin(); it != m_mapFileModel.end(); it++)
	{
		cout << "[" << char(it->first) << "]: " << it->second->m_nIdx << endl;
	}
}

bool CHashMap::FindFile(FileModel * pNode, string szDir, string szFileName)
{
	FileModel* pTemp = pNode;

	while (pTemp)
	{

		if (szFileName.compare(pTemp->m_szFileName) != 0)
		{
			pTemp = pTemp->m_pNext;
			continue;
		}
		return true;
	}

	return false;
}

