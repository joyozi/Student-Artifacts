#ifndef _CENEMYMODEL_H_
#define _CENEMYMODEL_H_
#include "main.h"
#include "CPlayerModel.h"

class CEnemyModel : public CPlayerModel
{
public:
	CEnemyModel(int nPriority = 33);
	~CEnemyModel();
	void Update();

	static CEnemyModel *Create();
private:

};
#endif