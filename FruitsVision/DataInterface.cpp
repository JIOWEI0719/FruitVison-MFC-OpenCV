#include "pch.h"
#include "DataInterface.h"

bool DataInterface::Open(CString FilePath)
{
    ifstream in(FilePath,ios::in);
    
    if (in.is_open())
    {

    }


    return false;
}
