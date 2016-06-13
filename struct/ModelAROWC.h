#ifndef MODELAROWC_H
#define MODELAROWC_H

#include "Model.h"
class CModelAROWC :
	public CModel
{
public:
	CModelAROWC();
	~CModelAROWC();
	void Learning(CResult *result, CData *data, CParameter *par);
};

#endif