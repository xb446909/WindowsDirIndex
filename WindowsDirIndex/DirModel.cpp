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

void DirModel::SaveXML(const char * szFile)
{
	tinyxml2::XMLDocument doc;
	auto root = doc.NewElement("Directory");
	root->SetAttribute("Name", m_szDir.c_str());
	for (size_t i = 0; i < m_vecDirs.size(); i++)
	{
		root->InsertEndChild(m_vecDirs[i]->CreateNode(&doc));
	}
	for (size_t i = 0; i < m_vecFiles.size(); i++)
	{
		auto elem = doc.NewElement("File");
		elem->SetAttribute("Name", m_vecFiles[i].c_str());
		root->InsertEndChild(elem);
	}
	doc.InsertEndChild(root);
	doc.SaveFile(szFile);
}

void DirModel::LoadXML(const char * szFile)
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile(szFile);
	auto root = doc.RootElement();
	m_szDir = root->Attribute("Name");
	auto elem = root->FirstChild();
	while (elem)
	{
		if (strcmp(elem->Value(), "Directory") == 0)
		{
			m_vecDirs.push_back(CreateModel(elem->ToElement()));
		}
		if (strcmp(elem->Value(), "File") == 0)
		{
			m_vecFiles.push_back(elem->ToElement()->Attribute("Name"));
		}
		elem = elem->NextSibling();
	}
}

tinyxml2::XMLElement * DirModel::CreateNode(tinyxml2::XMLDocument * pDoc)
{
	auto root = pDoc->NewElement("Directory");
	root->SetAttribute("Name", m_szDir.c_str());
	for (size_t i = 0; i < m_vecDirs.size(); i++)
	{
		root->InsertEndChild(m_vecDirs[i]->CreateNode(pDoc));
	}
	for (size_t i = 0; i < m_vecFiles.size(); i++)
	{
		auto elem = pDoc->NewElement("File");
		elem->SetAttribute("Name", m_vecFiles[i].c_str());
		root->InsertEndChild(elem);
	}
	return root;
}

DirModel * DirModel::CreateModel(tinyxml2::XMLElement * elem)
{
	DirModel* pModel = new DirModel(elem->Attribute("Name"));
	auto child = elem->FirstChild();
	while (child)
	{
		if (strcmp(child->Value(), "Directory") == 0)
		{
			pModel->m_vecDirs.push_back(CreateModel(child->ToElement()));
		}
		if (strcmp(child->Value(), "File") == 0)
		{
			pModel->m_vecFiles.push_back(child->ToElement()->Attribute("Name"));
		}
		child = child->NextSibling();
	}
	return pModel;
}
