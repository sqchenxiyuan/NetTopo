#pragma once

struct netLine {
	netNode* a;
	netNode* b;
	int type;
};

struct netNode{
	int id = -1;
	float cx = 0;
	float cy = 0;
	float w = 0;
	float h = 0;
	CString title = _T("");
	CString imgpath = _T("");
	//vector<netLine*> links;
};

class CNetData
{
public:
	CNetData();
	~CNetData();

	void initData(vector<netNode*> nodes, vector<netLine*> lines);
	vector<netNode*> getData();

private:
	vector<netNode*> m_data;
	vector<CNetElement*> m_nodes;
	void reflash();
	netNode trans2Data(CNetElement* netElement);
};