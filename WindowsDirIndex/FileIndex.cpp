#include "pch.h"
#include "FileIndex.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;


CFileIndex::CFileIndex()
{
	m_dwTotalSize = GetDiskSize("C:\\");
	//m_pHashMap = new CHashMap(40);
}


CFileIndex::~CFileIndex()
{
	//delete m_pHashMap;
}

void CFileIndex::CreateIndex(const char * szPath)
{
	m_nFileNum = 0;
	m_nDirNum = 0;
	m_dwScanSize = 0;
	m_dirModel.SetDir(szPath);
	SearchFile(szPath, szPath, &m_dirModel, false);
}

void CFileIndex::CompareIndex(const char * szPath)
{
	m_dwScanSize = 0;
	SearchFile(szPath, szPath, &m_dirModel, true);
}

void CFileIndex::Print()
{
	//m_pHashMap->Print();
}

WIN32_FIND_DATAA findData;//定义一个文件查找数据结构

void CFileIndex::SearchFile(const char* szPath, string szParentDir, DirModel* pDirModel, bool bCompare)
{
	std::string szTmp(szPath);
	if (szTmp[strlen(szTmp.c_str()) - 1] != '\\')//将目录以“\\*.*”形式结尾
	{
		szTmp += "\\*.*";
	}
	else
	{
		szTmp += "*.*";
	}
	memset(&findData, 0, sizeof(WIN32_FIND_DATAA));
	HANDLE hFind = FindFirstFileA(szTmp.c_str(), &findData);//开始查找文件
	if (hFind == INVALID_HANDLE_VALUE) return;

	while (TRUE)
	{
		if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if ((strcmp((const char *)&findData.cFileName, "...") != 0) &&
				(strcmp((const char *)&findData.cFileName, "..") != 0) &&
				(strcmp((const char *)&findData.cFileName, ".") != 0))
			{
				std::string szFileName(szPath);
				if (szFileName[strlen(szFileName.c_str()) - 1] != '\\')
				{
					szFileName += "\\";
				}
				szFileName += (char *)findData.cFileName;

				DirModel* pModel = nullptr;

				if (bCompare)
				{
					pModel = pDirModel->FindChildDir(findData.cFileName);
					if (pModel == nullptr)
					{
						cout << "Cannot find directory " << szFileName << endl;
						return;
					}
				}
				else
				{
					pModel = new DirModel(findData.cFileName);
					pDirModel->AddChildDir(pModel);
				}
				SearchFile(szFileName.c_str(), string(findData.cFileName), pModel, bCompare);//递归调用
			}
		}
		else
		{
			DWORD dwFileSize = (findData.nFileSizeHigh * (MAXDWORD + 1) + findData.nFileSizeLow) / (1024);//获取文件大小,单位为KB
			m_dwScanSize += dwFileSize;
			double dbScanProgress = (double)m_dwScanSize / (double)m_dwTotalSize;

			std::string szFileName(szPath);
			if (szFileName[strlen(szFileName.c_str()) - 1] != '\\')
			{
				szFileName += "\\";
			}
			szFileName += (char *)findData.cFileName;
			if (bCompare)
			{
				if (!pDirModel->FindChildFile(findData.cFileName))
				{
					cout << "Cannot find file " << szFileName << endl;
				}

				//if (!m_pHashMap->FindFile(szParentDir, szFileName))
				//{
				//	cout << "Can not find: " << szFileName << endl;
				//}
			}
			else
			{
				pDirModel->AddChildFile(findData.cFileName);
				//m_pHashMap->Add(szParentDir, szFileName);
				m_nFileNum++;
			}
		}
		if (!FindNextFileA(hFind, &findData)) break;
	}
	FindClose(hFind);
}

DWORD CFileIndex::GetDiskSize(const char* szPath)
{
	char DiskName[4];
	DiskName[0] = szPath[0];
	DiskName[1] = szPath[1];
	DiskName[2] = szPath[2];
	DiskName[3] = '\0';
	ULARGE_INTEGER lpuse;
	ULARGE_INTEGER lptotal;
	ULARGE_INTEGER lpfree;
	GetDiskFreeSpaceExA(DiskName, &lpuse, &lptotal, &lpfree);
	return (lptotal.QuadPart - lpfree.QuadPart) / 1024.0;
}