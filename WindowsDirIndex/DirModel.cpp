#include "pch.h"
#include "DirModel.h"


DirModel::DirModel()
{
}

DirModel::DirModel(string szDir)
	: m_szDir(szDir)
{
}


DirModel::~DirModel()
{
}

DirModel * DirModel::FindChildDir(string szDir)
{
	DirModel* pModel = nullptr;
	for (size_t i = 0; i < m_vecDirs.size(); i++)
	{
		DirModel* pDirModel = m_vecDirs[i];
		if (pDirModel->Compare(szDir) == 0)
		{
			return pDirModel;
		}
	}
	return pModel;
}

bool DirModel::FindChildFile(string szFile)
{
	for (size_t i = 0; i < m_vecFiles.size(); i++)
	{
		if (m_vecFiles[i].compare(szFile) == 0)
		{
			return true;
		}
	}
	return false;
}
