#include "pch.h"
#include "FruitData.h"

FruitData::FruitData()
{
}

FruitData::FruitData(int id, int len, int diameter, int crossArea)
{
	this->m_id = id;
	this->m_len = len;
	this->m_diameter = diameter;
	this->m_crossArea = crossArea;
}
