#include "pch.h"
#include "HashMap.h"

FileModel::FileModel(string szDir, string szFileName)
	: m_szDir(szDir)
	, m_szFileName(szFileName)
	, m_pNext(nullptr)
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
	//int nIdx = szDir[0] % m_nSize;
	int nIdx = szDir[0];
	if (m_mapFileModel.find(nIdx) != m_mapFileModel.end())
	{
		FileModel* pFileModel = new FileModel(szDir, szFileName);
		pFileModel->m_pNext = m_mapFileModel[nIdx];
		m_mapFileModel[nIdx] = pFileModel;
	}
	else
	{
		m_mapFileModel[nIdx] = new FileModel(szDir, szFileName);
	}
}

bool CHashMap::FindFile(string szDir, string szFileName)
{
	//int nIdx = szDir[0] % m_nSize;
	int nIdx = szDir[0];
	if (m_mapFileModel.find(nIdx) == m_mapFileModel.end())
	{
		return false;
	}

	return FindFile(m_mapFileModel[nIdx], szDir, szFileName);
}

bool CHashMap::FindFile(FileModel * pNode, string szDir, string szFileName)
{
	FileModel* pTemp = pNode;

	while (pTemp)
	{
		//if ((szFileName.front() != pTemp->m_szFileName.front()) || (szFileName.back() != pTemp->m_szFileName.back()))
		//{
		//	pTemp = pTemp->m_pNext;
		//	continue;
		//}
		//if (szDir.compare(pTemp->m_szDir) != 0)
		//{
		//	pTemp = pTemp->m_pNext;
		//	continue;
		//}

		const char* str1 = szFileName.c_str();
		const char* str2 = pTemp->m_szFileName.c_str();

		if (strcmp(str1, str2) != 0)
		{
			pTemp = pTemp->m_pNext;
			continue;
		}

		//if (szFileName.compare(pTemp->m_szFileName) != 0)
		//{
		//	pTemp = pTemp->m_pNext;
		//	continue;
		//}
		return true;
	}

	return false;
}

