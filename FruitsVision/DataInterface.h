#pragma once
#include "FruitData.h"


class DataInterface
{
public:
	bool Open(CString FilePath);
	void Add(FruitData Info);
	void Del(int index);
	void Amend(int index, FruitData Info);
	FruitData Find(int id);
	bool Save();

	vector<FruitData> Info;






};

