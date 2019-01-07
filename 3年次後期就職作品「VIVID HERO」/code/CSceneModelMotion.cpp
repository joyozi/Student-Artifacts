//��-------------------------------------------------------------------------��
//
//	File:CSceneModelMotion�̃t�@�C��[CSceneModelMotion.cpp]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include "CSceneModelMotion.h"
#include "CItemList.h"
#include "input.h"

//��-------------------------------------------------------------------------��
//�ÓI�����o�ϐ��̏�����
//��-------------------------------------------------------------------------��

//��-----------------------------------��
//CSceneModelMotion�̃R���X�g���N�^
//��-----------------------------------��
CSceneModelMotion::CSceneModelMotion(int nPriority) : CScene(nPriority)
{
	m_Type = CTYPE_SCENEMODELMOTION;
	m_ModelAct = 0;
	m_ModelPartsNum = 0;
	m_ModelTxtName = NULL;

	m_pAnime = NULL;
	m_pModel = NULL;
	m_pModelMove = NULL;
	m_pModelStandard = NULL;


	m_Time = 0;
	m_ModelActNow = 0;						//�O��Ƃ̔�r����悤
	m_MotionNumStart = 0;
	m_pKeyInterpolation = NULL;				//���`��Ԃ��钆�Ԃ̏��
	m_KeyInfterpolationjudge = false;		//���`��Ԃ����Ă��邩���Ă��Ȃ���

	m_MotionNum_deleted = 0;

	m_MotionEndJudge = false;
}

//��-----------------------------------��
//CSceneModelMotion�̃f�X�g���N�^
//��-----------------------------------��
CSceneModelMotion::~CSceneModelMotion()
{

}

//��-----------------------------------��
//CSceneModelMotion�̏���������
//��-----------------------------------��
HRESULT CSceneModelMotion::Init(void)
{
	//motion�e�L�X�g�̓ǂݍ���
	FILE *fp;
	fp = fopen(m_ModelTxtName,"rt");

	if(fp == NULL)
	{	//�G���[����
		printf("�t�@�C���I�[�v���G���[\n",stderr);
		return -1;
	}

	char str[256];
	
	int ModelNameNum = 0;
	int ModelIndexNum = 0;
	int MotionNum = 0;
	int ModelTextureNameNum = 0;
	
	//#------------------------------------------------------------------------------
	//# �L�����N�^�[��� �܂ł̓ǂݍ���
	//#------------------------------------------------------------------------------


	while(1)
	{	//���ꂼ��̐��̌v�Z

		fscanf(fp,"%s",str);

		if(feof(fp) != 0)
		{
			break;
		}

		//���f���̖ڐ��̊m�ہB�ŏ��ɂ��˂΂Ȃ�Ȃ�
		if(strcmp(str,"NUM_MODEL") == 0)
		{
			fscanf(fp,"%s",str);
			fscanf(fp,"%d",&m_ModelPartsNum);

			m_pModel = new PART_INFO[m_ModelPartsNum];
			m_pModelMove = new PART_INFO[m_ModelPartsNum];
			m_pModelStandard = new KEY_DATA[m_ModelPartsNum];

			//���f���̐��`��Ԃ̃������m��
			m_pKeyInterpolation = new KEY_DATA[m_ModelPartsNum];

			//����̂��߂ɍŏ��Ƀk��������
			for(int i = 0;i < m_ModelPartsNum;i++)
			{
				m_pModel[i].TexName[0] = NULL;
			}
		}

		if(strcmp(str,"MODEL_FILENAME") == 0)
		{
			fscanf(fp,"%s",str);
			fscanf(fp,"%s",m_pModel[ModelNameNum].ModelName);
			ModelNameNum++;
		}

		if(strcmp(str,"MODEL_TEXTURENAME") == 0)
		{
			fscanf(fp,"%s",str);
			fscanf(fp,"%s",m_pModel[ModelTextureNameNum].TexName);
			ModelTextureNameNum++;
		}

		if(strcmp(str,"INDEX") == 0)
		{
			fscanf(fp,"%s",str);
			fscanf(fp,"%d",&m_pModel[ModelIndexNum].IndexNumber);
		}

		if(strcmp(str,"PARENT") == 0)
		{
			fscanf(fp,"%s",str);
			fscanf(fp,"%d",&m_pModel[ModelIndexNum].ParentNumber);
		}

		if(strcmp(str,"POS") == 0)
		{
			if(ModelIndexNum < m_ModelPartsNum)
			{
				fscanf(fp,"%s",str);
				fscanf(fp,"%f",&m_pModel[ModelIndexNum].Pos.x);
				fscanf(fp,"%f",&m_pModel[ModelIndexNum].Pos.y);
				fscanf(fp,"%f",&m_pModel[ModelIndexNum].Pos.z);
			}
		}

		if(strcmp(str,"ROT") == 0)
		{
			if(ModelIndexNum < m_ModelPartsNum)
			{
				fscanf(fp,"%s",str);
				fscanf(fp,"%f",&m_pModel[ModelIndexNum].Rot.x);
				fscanf(fp,"%f",&m_pModel[ModelIndexNum].Rot.y);
				fscanf(fp,"%f",&m_pModel[ModelIndexNum].Rot.z);
			}
		}

		if(strcmp(str,"END_PARTSSET") == 0)
		{
			ModelIndexNum++;
		}

		//�������������܂ł��p�[�c�ɂ��ā�������������������������������


		if(strcmp(str,"END_KEYSET") == 0)
		{
			MotionNum++;
		}
	}

	//���̈ʒu�ɖ߂�
	fseek(fp,0,SEEK_SET);

	//#------------------------------------------------------------------------------
	//# ���[�V�������
	//#------------------------------------------------------------------------------

	//�������̊m��
	m_pAnime = new KEY_ANIME[MotionNum];
	m_MotionNum_deleted = MotionNum;

		//�������m��
	for(int i = 0;i < MotionNum;i++)
	{
		m_pAnime[i].key = new KEY_DATA[m_ModelPartsNum];
	}

	MotionNum = 0;
	int KeyNum = 0;
	int LoopNum_KeyNum = 0;

	while(1)
	{
		fscanf(fp,"%s",str);

		if(feof(fp) != 0)
		{
			break;
		}


		if(strcmp(str,"END_KEY") == 0)
		{
			KeyNum++;
		}

		//���[�V�������I������玟�̂Ɉڂ�
		if(strcmp(str,"END_KEYSET") == 0)
		{
			KeyNum = 0;
			MotionNum++;
		}

		if(strcmp(str,"END_MOTIONSET") == 0)
		{
			LoopNum_KeyNum++;
		}

		if(strcmp(str,"LOOP") == 0)
		{	//���ʂɐ��l������
			fscanf(fp,"%s",str);
			fscanf(fp,"%d",&m_pAnime[LoopNum_KeyNum].loopjudge);
		}

		if(strcmp(str,"NUM_KEY") == 0)
		{	//���ʂɐ��l������
			fscanf(fp,"%s",str);
			fscanf(fp,"%d",&m_pAnime[LoopNum_KeyNum].num_key);
		}

		if(strcmp(str,"FRAME") == 0)
		{
			fscanf(fp,"%s",str);
			fscanf(fp,"%d",&m_pAnime[MotionNum].frame);
		}

		if(strcmp(str,"POS") == 0)
		{
			fscanf(fp,"%s",str);
			fscanf(fp,"%f",&m_pAnime[MotionNum].key[KeyNum].keyPos.x);
			fscanf(fp,"%f",&m_pAnime[MotionNum].key[KeyNum].keyPos.y);
			fscanf(fp,"%f",&m_pAnime[MotionNum].key[KeyNum].keyPos.z);
		}

		if(strcmp(str,"ROT") == 0)
		{
			fscanf(fp,"%s",str);
			fscanf(fp,"%f",&m_pAnime[MotionNum].key[KeyNum].keyRot.x);
			fscanf(fp,"%f",&m_pAnime[MotionNum].key[KeyNum].keyRot.y);
			fscanf(fp,"%f",&m_pAnime[MotionNum].key[KeyNum].keyRot.z);
		}
	}

	fclose(fp);



	for(int i = 0;i < m_ModelPartsNum;i++)
	{
		m_pModel[i].Scl = D3DXVECTOR3(1.0f,1.0f,1.0f);
	
		//��b���̕ۑ�
		m_pModelStandard[i].keyPos = m_pModel[i].Pos;
		m_pModelStandard[i].keyRot = m_pModel[i].Rot;
	
		m_pModel[i].Pos += m_pAnime[0].key[i].keyPos;
		m_pModel[i].Rot += m_pAnime[0].key[i].keyRot;
	}



	return S_OK;
}

//��-----------------------------------��
//CSceneModelMotion�̏I������
//��-----------------------------------��
void CSceneModelMotion::Uninit(void)
{
	//���[�V�����̐������J��Ԃ�
	for(int i = 0;i < m_MotionNum_deleted;i++)
	{
		SAFE_DELETE_ARRY(m_pAnime[i].key);
	}

	SAFE_DELETE_ARRY(m_pAnime);
	SAFE_DELETE_ARRY(m_pModel);
	SAFE_DELETE_ARRY(m_pModelMove);
	SAFE_DELETE_ARRY(m_pModelStandard);
	SAFE_DELETE_ARRY(m_pKeyInterpolation);
}

//��-----------------------------------��
//CSceneModelMotion�̍X�V����
//��-----------------------------------��
void CSceneModelMotion::Update(void)
{
	m_MotionEndJudge = false;

	//���[�V�����̑O��ƈ������ύX���鏈��
	if(m_ModelActNow != m_ModelAct)
	{
		m_ModelActNow = m_ModelAct;

		//���`��Ԃ̐ݒ�
		m_KeyInfterpolationjudge = true;	//���`��Ԃ̊J�n

		m_Time = 0.0f;

		m_MotionNumStart = 0;
		for(int i = 0;i < m_ModelActNow;i++)
		{
			m_MotionNumStart += m_pAnime[i].num_key;
		}

		for(int i = 0;i < m_ModelPartsNum;i++)
		{	//�܂����
			m_pKeyInterpolation[i].keyPos = m_pModel[i].Pos - m_pModelStandard[i].keyPos;
			m_pKeyInterpolation[i].keyRot = m_pModel[i].Rot - m_pModelStandard[i].keyRot;
		}
	}

	//�L�[�t���[���̈ړ�
	if(m_KeyInfterpolationjudge == false)
	{	//���`��Ԓ��łȂ���   //���[�V�������P�����Ȃ������炷��������
		for(int i = 0;i < m_ModelPartsNum && m_pAnime[m_ModelActNow].num_key > 1;i++)
		{
			m_pModel[i].Pos = m_pModelStandard[i].keyPos + CItemList::Vec3lerp(m_pAnime[(int)m_Time].key[i].keyPos,
																			m_pAnime[((int)m_Time + 1)].key[i].keyPos,
																			m_Time - (int)m_Time);

			m_pModel[i].Rot = m_pModelStandard[i].keyRot + CItemList::Vec3lerp(m_pAnime[(int)m_Time].key[i].keyRot,
																			m_pAnime[((int)m_Time + 1)].key[i].keyRot,
																			m_Time - (int)m_Time);
		}

		m_Time += 1.0f / (float)m_pAnime[(int)m_Time + 1].frame;

		//���Ԃ𒴂�����
		if(m_Time >= m_MotionNumStart + m_pAnime[m_ModelActNow].num_key - 1)
		{
			//1�t���[�������I������Ɣ���
			m_MotionEndJudge = true;

			if(m_pAnime[m_ModelActNow].loopjudge == 1)				//���������ŏ�����
			{	//���[�v����
				m_Time = (float)m_MotionNumStart;
			}
			else if(m_pAnime[m_ModelActNow].loopjudge == 2)			//����P�[�X�̍쐬
			{
				//�Ƃ肠���������
				m_Time -= 1.0f / (float)m_pAnime[(int)m_Time].frame;
			}
			else
			{	//���[�v���Ȃ�
				m_ModelAct = 0;
			}
		}
	}
	else
	{
		for(int i = 0;i < m_ModelPartsNum;i++)
		{
			m_pModel[i].Pos = m_pModelStandard[i].keyPos + CItemList::Vec3lerp(m_pKeyInterpolation[i].keyPos,
																				m_pAnime[m_MotionNumStart].key[i].keyPos,
																				m_Time - (int)m_Time);

			m_pModel[i].Rot = m_pModelStandard[i].keyRot + CItemList::Vec3lerp(m_pKeyInterpolation[i].keyRot,
																				m_pAnime[m_MotionNumStart].key[i].keyRot,
																				m_Time - (int)m_Time);
		}

		m_Time += 1.0f / (float)m_pAnime[m_MotionNumStart].frame;

		if(m_Time >= 1.0f)
		{
			m_Time = (float)m_MotionNumStart;
			m_KeyInfterpolationjudge = false;
		}
	}
}

//��-----------------------------------��
//CSceneModelMotion�̕`�揈��
//��-----------------------------------��
void CSceneModelMotion::Draw(void)
{

}

//��----------------------------------��
//CSceneModelMotion�̃Z�b�g�|�W�V�������̂P
//��----------------------------------��
void  CSceneModelMotion::SetPosition(float x,float y,float z)
{
	m_Pos.x = x;
	m_Pos.y = y;
	m_Pos.z = z;
}

//��----------------------------------��
//CSceneModelMotion�̃Z�b�g�|�W�V�������̂Q
//��----------------------------------��
void  CSceneModelMotion::SetPosition(D3DXVECTOR3 pos)
{
	m_Pos = pos;
}

//��----------------------------------��
//CSceneModelMotion�̃Q�b�g�|�W�V����
//��----------------------------------��
D3DXVECTOR3  CSceneModelMotion::GetPosition(void)
{
	return m_Pos;
}

//��----------------------------------��
//CSceneModelMotion�̃Z�b�g���[�e�[�V�������̂P
//��----------------------------------��
void CSceneModelMotion::SetRotation(float x,float y,float z)
{
	m_Rot.x = x;
	m_Rot.y = y;
	m_Rot.z = z;
}

//��----------------------------------��
//CSceneModelMotion�̃Z�b�g���[�e�[�V��������2
//��----------------------------------��
void CSceneModelMotion::SetRotation(D3DXVECTOR3 rot)
{
	m_Rot.x = rot.x;
	m_Rot.y = rot.y;
	m_Rot.z = rot.z;
}

//��----------------------------------��
//CSceneModelMotion�̃Q�b�g���[�e�[�V����
//��----------------------------------��
D3DXVECTOR3 CSceneModelMotion::GetRotation(void)
{
	return m_Rot;
}

//��----------------------------------��
//CSceneModelMotion�̃Z�b�g�^�C�v
//��----------------------------------��
void CSceneModelMotion::SetType(int nType)
{

}

//��----------------------------------��
//CSceneModelMotion�̃Z�b�g�^�C�v
//��----------------------------------��
PART_INFO *CSceneModelMotion::GetPart_Info(void)
{
	return &m_pModel[0];
}

//��----------------------------------��
//CSceneModelMotion�̃p�[�c�̐�
//��----------------------------------��
int CSceneModelMotion::GetPart_Num(void)
{
	return m_ModelPartsNum;
}

//��----------------------------------��
//CSceneModelMotion�̂��̃��[�V�����̒��ŉ��Ԗڂ̃��[�V�������̃Q�b�g
//��----------------------------------��
int CSceneModelMotion::GetNowMotionNum()
{
	//���`��Ԓ���������-1��Ԃ�
	if(m_KeyInfterpolationjudge == true)
		return -1;

	int returnNum = (int)m_Time;

	for(int i = 0;i < m_ModelActNow;i++)
	{
		returnNum -= m_pAnime[i].num_key;
	}

	return returnNum;
}

//��----------------------------------��
//CSceneModelMotion�̃N���G�C�g(�����t)
//��----------------------------------��
CSceneModelMotion *CSceneModelMotion::Create(LPCTSTR ModelTxtName)
{
	CSceneModelMotion *pCSceneModelMotion;
	pCSceneModelMotion = new CSceneModelMotion;

	pCSceneModelMotion->m_ModelTxtName = ModelTxtName;
	
	pCSceneModelMotion->Init();
	
	return pCSceneModelMotion;
}
