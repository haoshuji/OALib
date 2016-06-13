#ifndef MODELAROWD_H
#define MODELAROWD_H

#include "Model.h"
class CModelAROWD :
	public CModel
{
public:
	CModelAROWD();
	~CModelAROWD();
	void Learning(CResult *result, CData *data, CParameter *par);
};

#endif
