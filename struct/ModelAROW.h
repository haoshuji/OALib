#ifndef MODELAROW_H
#define MODELAROW_H

#include "Model.h"
class CModelAROW :
	public CModel
{
public:
	CModelAROW();
	~CModelAROW();
	void Learning(CResult *result, CData *data, CParameter *par);
};

#endif