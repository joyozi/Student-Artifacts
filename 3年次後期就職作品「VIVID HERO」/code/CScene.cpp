//��-------------------------------------------------------------------------��
//
//	File:CSenecpp�t�@�C��[CSene.cpp]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
//#include "CManager.h"
#include "CScene.h"
#include "CItemList.h"
#include <vector>

//��-------------------------------------------------------------------------��
//�N���X�̃X�^�e�B�b�N�ϐ��̏�����
//��-------------------------------------------------------------------------��
CScene *CScene::m_pTop[] = {NULL};
CScene *CScene::m_pCur[] = {NULL};

//��----------------------------------��
//�R���X�g���N�^
//��----------------------------------��
CScene::CScene(int nPriority)
{
	m_Type = CTYPE_NONE;		//�Ƃ肠���������������Ă���
	m_nPriority = nPriority;	//�D�揇�ʂ�������
	m_DeleteFlag = false;		//�f�X�t���O�̏�����

	m_CollisionHitJudge = false;
	m_CollisionHitNum = 0;

	LinkList();
}

//��----------------------------------��
//�f�X�g���N�^
//��----------------------------------��
CScene::~CScene()
{

}

//��----------------------------------��
//�A�b�v�f�[�g�I�[��
//��----------------------------------��
void CScene::UpdateAll(void)
{
	for(int i = 0;i < PRIORITY_NUM;i++)
	{
		//�f�X�t���O�������Ă���UnlinkList���Ă�
		for(CScene * pScene = m_pTop[i]; pScene != NULL;)
		{
			//�|�C���^�̊ԈႢ���Ȃ������߈ꎞ�I��ChangeScene�ɓ���Ă�
			CScene *ChangeScene = pScene;
			pScene = pScene->m_pNext;

			//�f�X�t���O�������Ă���s���|�C���g�ŎE��
			if(ChangeScene->m_DeleteFlag)
			{
				ChangeScene->UnlinkList();
			}
			else
			{
				ChangeScene->Update();

				//Update���Ńt���O����������
				if(ChangeScene->m_DeleteFlag)
				{
					ChangeScene->UnlinkList();
				}
			}
		}
	}

	CollisionHitLoop();
}

//��----------------------------------��
//�h���[�I�[��
//��----------------------------------��
void CScene::DrawAll(void)
{
	for(int i = 0;i < PRIORITY_NUM;i++)
	{
		for(CScene *pScene = m_pTop[i];pScene != NULL;pScene = pScene-> m_pNext)
		{
			pScene->Draw();
		}
	}
}

//��----------------------------------��
//�����[�X�I�[��
//��----------------------------------��
void CScene::ReleaseAll()
{
	for(int i = 0;i < PRIORITY_NUM;i++)
	{
		CScene *pScene = m_pTop[i];

		while(pScene != NULL)
		{
			//������O�Ɏ���ۑ�
			CScene *pNext = pScene->m_pNext;

			pScene->m_DeleteFlag = false;	//�Ƃ肠�����f�X�t���O���Ԃ�
			pScene->Uninit();
			delete pScene;					//�S�������Ă���
			pScene = NULL;
			pScene = pNext;
		}

		m_pTop[i] = NULL;		//��ʑJ�ڗp��
		m_pCur[i] = NULL;		//��ʑJ�ڗp��
	}
}

//��----------------------------------��
//�����[�X	�f�X�t���O�𗧂Ă�
//��----------------------------------��
void CScene::Release(void)
{
	m_DeleteFlag = true;
}

//��-----------------------------------��
//���X�g�ɓo�^
//��-----------------------------------��
void CScene::LinkList(void)
{
	//NULL��������擪�̃|�C���^��ۑ����� ���łɖ�����
	if(m_pTop[m_nPriority] == NULL && m_pCur[m_nPriority] == NULL)
	{
		m_pTop[m_nPriority] = this;
		m_pCur[m_nPriority] = this;
	}

	//�Ō���ɂ��郊�X�g��NULL���
	m_pNext = NULL;

	//�Ō�������݂������烊�X�g�̐擪��NULL?
	if (m_pCur[m_nPriority] == this)
	{
		m_pPrev = NULL;
	}
	else
	{
		m_pPrev = m_pCur[m_nPriority];
		// �Ō���ЂƂ�O�̃��X�g�ɒǉ��������X�g�̃|�C���^��n��
		m_pCur[m_nPriority]->m_pNext = this;

		//�����̃|�C���^������
		m_pCur[m_nPriority] = this;
	}
}

//��----------------------------------��
//CScene�̃��X�g����폜
//��----------------------------------��
void CScene::UnlinkList(void)
{
	//****�O��NEXT,����PREV��ύX����****

	//�����@�O�ɉ��������Ă鎞
	if(m_pPrev != NULL)
	{
		//�O�̃|�C���^��Next�ɍ��̃|�C���^��Next������
		m_pPrev->m_pNext = m_pNext;
	}

	//�����@���ɉ��������Ă鎞
	if(m_pNext != NULL)
	{
		//���̃|�C���^��Prev�ɍ��̃|�C���^��Prev������
		m_pNext->m_pPrev = m_pPrev;
	}

	//�擪�̂Ƃ��̃A�����X�g
	if(m_pTop[m_nPriority] == this)
	{
		//���̃|�C���^������Ƃ��A���̃|�C���^��Prev��NULL��
		m_pTop[m_nPriority] = m_pNext;	//�g�b�v�����ւ���
	}

	//�����̂Ƃ��̃A�����X�g
	if(m_pCur[m_nPriority] == this)
	{
		m_pCur[m_nPriority] = m_pPrev;	//�Ō�������ւ���
	}

	//�f���[�g����
	delete this;
}

//��-----------------------------------��
//���X�g������
//searchType : main.h�ɂ���CTYPE�̃��X�g������
//��-----------------------------------��
CScene *CScene::SearchLinkList(CScene *irekoScene[],int searchType)
{
	int Num = 0;

	//�v���I���e�B�����J��Ԃ�
	for(int i = 0;i < PRIORITY_NUM;i++)
	{
		for(CScene *pScene = m_pTop[i];pScene != NULL;pScene = pScene-> m_pNext)
		{
			//�~�����^�C�v��������ꎞ�I�ɕۑ�
			if(pScene->m_Type == searchType)
			{
				//�ꎞ�I�ɕۑ�
				irekoScene[Num] = pScene;
				Num++;
			}
		}
	}

	return *irekoScene;
}

//��-----------------------------------��
//�����蔻��̔��a���Q�b�g����֐�
//��-----------------------------------��
float CScene::GetCollisionRadius(int Num)
{
	return 0.0f;
}

//��-----------------------------------��
//�����蔻��̔��a���Q�b�g����֐�
//��-----------------------------------��
D3DXVECTOR3 CScene::GetCollisionCenterPos(int Num)
{
	return GetPosition();
}

//��-----------------------------------��
//������Ώۂ̃V�[�g
//��-----------------------------------��
bool CScene::CollisionTargetSheet(CLASS_TYPE Type)
{
	switch(Type)
	{
	case CTYPE_NONE:	return false;break;

	default:		return false;break;
	}
}

//��-----------------------------------��
//�����������̃A�N�V�����p�֐�
//��-----------------------------------��
void CScene::CollisionAction(CLASS_TYPE Type,int Num)
{
	m_CollisionHitJudge = true;
}

//��-----------------------------------��
//�����蔻��̐��Z�b�g
//��-----------------------------------��
void CScene::SetCollisionHitNum(int HitNum)
{
	m_CollisionHitNum = HitNum;
}

//��-----------------------------------��
//�����蔻��̐��擾
//��-----------------------------------��
int CScene::GetCollisionHitNum(void)
{
	return m_CollisionHitNum;
}


//��-----------------------------------��
//�������炱�����ɍ��
//��-----------------------------------��
void CScene::CollisionHitLoop(void)
{
	//�����蔻��̉�����

	// �������̔z����m�ہB
	std::vector<CScene*> aBucket;

	//�����蔻�������V�[�����Z�b�g����
	for(int i = 0;i < PRIORITY_NUM;i++)
	{
		for(CScene * pScene = m_pTop[i]; pScene != NULL;)
		{
			CScene *ChangeScene = pScene;
			pScene = pScene->m_pNext;

			//�����蔻��̃��[�v
			if(ChangeScene->m_CollisionHitNum > 0)
			{
				aBucket.push_back(ChangeScene);
			}
		}
	}

	for(unsigned int i = 0;i < aBucket.size();i++)
	{
		for(unsigned int j = i + 1;j < aBucket.size();j++)
		{
			aBucket[i]->CollisionHitCheckCircle(aBucket[j]);
		}
	}
}

//��-----------------------------------��
//�����蔻��̊֐�
//��-----------------------------------��
void CScene::CollisionHitCheckCircle(CScene *Scene)
{
	//�����̂����蔻��̐��@*�@����̂����蔻��̐������J��Ԃ�

	//�ǂ��������������Ă����悤�ɂ��Ă�Ȃ瓖�Ă�
	if(this->CollisionTargetSheet(Scene->m_Type) || Scene->CollisionTargetSheet(this->m_Type))
	{
		for(int i = 0;i < this->m_CollisionHitNum;i++)
		{
			for(int j = 0;j < Scene->m_CollisionHitNum;j++)
			{
				//���݂��̋������v�Z�����a�ȉ�����r
				float Length = CItemList::GetLength(this->GetCollisionCenterPos(i),Scene->GetCollisionCenterPos(j));

				if(Length <= this->GetCollisionRadius(i) + Scene->GetCollisionRadius(j))
				{
					this->CollisionAction(Scene->m_Type,j);
			
					Scene->CollisionAction(this->m_Type,i);
				}
			}
		}
	}
}

//EOF