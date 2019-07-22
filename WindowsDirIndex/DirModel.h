#pragma once
#include <vector>
#include <string>

using namespace std;

class DirModel
{
public:
	DirModel();
	DirModel(string szDir);
	~DirModel();
	void SetDir(string szDir) { m_szDir = szDir; }
	void AddChildDir(DirModel* pszDir) { m_vecDirs.push_back(pszDir); }
	void AddChildFile(string szFile) { m_vecFiles.push_back(szFile); }
	int Compare(string szDir) { return m_szDir.compare(szDir); }
	DirModel* FindChildDir(string szDir);
	bool FindChildFile(string szFile);
private:
	string m_szDir;
	vector<string> m_vecFiles;
	vector<DirModel*> m_vecDirs;
};
