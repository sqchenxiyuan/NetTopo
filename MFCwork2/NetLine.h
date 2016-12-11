#pragma once
class CNetLine
{
public:
	CNetLine(CNetElement* a, CNetElement* b,int type=0);
	~CNetLine();

	CNetElement* m_a;
	CNetElement* m_b;
	int m_type;
};

