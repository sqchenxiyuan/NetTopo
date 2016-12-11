#include "stdafx.h"
#include "NetLine.h"


CNetLine::CNetLine(CNetElement* a, CNetElement* b, int type)
{
	m_a = a;
	m_b = b;
	m_type = type;
}


CNetLine::~CNetLine()
{
}
