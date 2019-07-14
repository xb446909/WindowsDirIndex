#pragma once
#include <string>
#include <map>

using namespace std;


class FileModel
{
public:
	FileModel(string szDir, string szFileName);
	~FileModel();
	string m_szDir;
	string m_szFileName;
	FileModel* m_pNext;
	
};

class CHashMap
{
public:
	CHashMap(int size);
	~CHashMap();
	void Add(string szDir, string szFileName);
	bool FindFile(string szDir, string szFileName);
private:
	bool FindFile(FileModel* pNode, string szDir, string szFileName);

	int m_nSize;
	map<int, FileModel*> m_mapFileModel;
};

