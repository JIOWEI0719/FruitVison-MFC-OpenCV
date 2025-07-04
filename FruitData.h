#pragma once  
class FruitData  
{  
public:  

FruitData();  
FruitData(int id, int len, int diameter, int crossArea); // 修复了逗号语法错误  

int m_id; // 编号  
int m_len; // 长度  
int m_diameter; // 直径  
int m_crossArea; // 横截面积  
};
