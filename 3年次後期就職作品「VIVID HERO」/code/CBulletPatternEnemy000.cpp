//��-------------------------------------------------------------------------��
//
//	File:CBulletPatternEnemy000�̃t�@�C��[CBulletPatternEnemy000.cpp]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include "CBulletPatternEnemy000.h"
#include "CEnemyBullet000.h"
#include "input.h"
#include "CManager.h"
#include "CEnemy000.h"

//��-------------------------------------------------------------------------��
//�ÓI�����o�ϐ��̏�����
//��-------------------------------------------------------------------------��

//��-----------------------------------��
//CBulletPatternEnemy000�̃R���X�g���N�^
//��-----------------------------------��
CBulletPatternEnemy000::CBulletPatternEnemy000()
{

}

//��-----------------------------------��
//CBulletPatternEnemy000�̃f�X�g���N�^
//��-----------------------------------��
CBulletPatternEnemy000::~CBulletPatternEnemy000()
{

}

//��-----------------------------------��
//CBulletPatternEnemy000�̍X�V����
//��-----------------------------------��
void CBulletPatternEnemy000::Update_Enemy000(CEnemy000 *Shooter)
{
	CScene *irekoScene = NULL;
	CScene::SearchLinkList(&irekoScene,CTYPE_PLAYERMODEL);

	if(irekoScene != NULL && rand()%180 == 0)
	{
		CEnemyBullet000::Create(Shooter->GetPosition(),irekoScene->GetPosition() );
	}
}
