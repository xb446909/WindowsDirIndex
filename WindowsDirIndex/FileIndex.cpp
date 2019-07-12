#include "pch.h"
#include "FileIndex.h"
#include <string>
#include <vector>

using namespace std;


CFileIndex::CFileIndex()
{
	m_dwTotalSize = GetDiskSize("C:\\");
}


CFileIndex::~CFileIndex()
{
}

void CFileIndex::CreateIndex(const char * szPath)
{
	SearchFile(szPath, false);
}


WIN32_FIND_DATAA findData;//����һ���ļ��������ݽṹ

void CFileIndex::SearchFile(const char* szPath, bool bCompare)
{
	std::string szTmp(szPath);
	if (szTmp[strlen(szTmp.c_str()) - 1] != '\\')//��Ŀ¼�ԡ�\\*.*����ʽ��β
	{
		szTmp += "\\*.*";
	}
	else
	{
		szTmp += "*.*";
	}
	memset(&findData, 0, sizeof(WIN32_FIND_DATA));
	HANDLE hFind = FindFirstFileA(szTmp.c_str(), &findData);//��ʼ�����ļ�
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

				SearchFile(szFileName.c_str(), bCompare);//�ݹ����
			}
		}
		else
		{
			DWORD dwFileSize = (findData.nFileSizeHigh * (MAXDWORD + 1) + findData.nFileSizeLow) / (1024);//��ȡ�ļ���С,��λΪKB
			m_dwScanSize += dwFileSize;
			double dbScanProgress = (double)m_dwScanSize / (double)m_dwTotalSize;

			std::string szFileName(szPath);
			if (szFileName[strlen(szFileName.c_str()) - 1] != '\\')
			{
				szFileName += "\\";
			}
			szFileName += (char *)findData.cFileName;

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