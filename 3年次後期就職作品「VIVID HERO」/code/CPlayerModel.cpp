//��-------------------------------------------------------------------------��
//
//	File:CPlayerModel�̃t�@�C��[CPlayerModel.cpp]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include "CPlayerModel.h"

#include "CPlayerMotionPatternNormal.h"
#include "CPlayerMotionChanger.h"
#include "CManager.h"
#include "input.h"
#include "CItemList.h"
#include "CItemList.h"
#include "CParticleEngine.h"
#include "CTextureManager.h"
#include "CBulletPatternHoming.h"
#include "CBulletPatternDegeneracyShot.h"
#include "joystick.h"
#include "CScore.h"
#include "CDebugProc.h"
#include "CSceneMeshOrbit.h"
#include "CPlayerMotionPatternDie.h"
#include "CPhaseResult.h"
#include "CPhaseChange.h"

//��-------------------------------------------------------------------------��
//�ÓI�����o�ϐ��̏�����
//��-------------------------------------------------------------------------��

//��-----------------------------------��
//CPlayerModel�̃R���X�g���N�^
//��-----------------------------------��
CPlayerModel::CPlayerModel(int nPriority) : CSceneModelParts(nPriority)
{
	m_Type = CTYPE_PLAYERMODEL;
	m_Rot = D3DXVECTOR3(0.0f,D3DX_PI,0.0f);

	m_OldPos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_OldRot = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_GoRot = D3DXVECTOR3(0.0f,0.0f,0.0f);

	for(int i = 0;i < PLAYER_ENGINENUM;i++)
		m_pParticleSystem[i] = NULL;

	m_EnemyAimJudge = false;
	m_EnemyAimNum = 0;

	m_pBulletPattern[0] = new CBulletPatternDegeneracyShot;
	m_pBulletPattern[1] = new CBulletPatternHoming;
	m_pPatternChanger = new CPlayerMotionChanger(new CPlayerMotionPatternNormal);
	
	m_CameraRStartPos = CManager::GetCameraPointer()->GetCameraR();
	m_PlayerLife = 8000;

	float ScoreSizeX = 70.0f;
	float ScoreSizeY = 130.0f;

	//�X�R�A�̉E��̈ʒu
	D3DXVECTOR3 ScoreUpRightPos = D3DXVECTOR3(ScoreSizeX * 4.0f + 30.0f,SCREEN_HEIGHT - ScoreSizeY - 30.0f,0.0f);

	CScene2D::Create("./data/TEXTURE/Game/UI/Frame000.png",D3DXVECTOR3(ScoreUpRightPos.x - (ScoreSizeX * 2.0f),ScoreUpRightPos.y + ScoreSizeY/2 - 10.0f,0.0f),D3DXVECTOR3(330.0f,220.0f,0.0f));

	m_pPlayerScore = CScore::Create("./data/TEXTURE/Game/UI/text000.png",4,ScoreUpRightPos.x,ScoreUpRightPos.y,ScoreSizeX,ScoreSizeY,m_PlayerLife);

	m_UpJudge = 0;			//0�Œ�� 1�ŏ㏸ 2�ŉ��~
	m_AccelSpeed = 0.0f;
	m_UpSeed = 0.0f;
	m_MoveSpeed = D3DXVECTOR3(0.0f,0.0f,0.0f);

	m_BulletTrigger = false;
	m_pTargetEnemyPointer = NULL;
	m_pMeshOrbit = NULL;
	m_ResultChangeCnt = 0;
	m_CameraRPos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_NowTargetNum = 0;

	SetCollisionHitNum(2);
}

//��----------------------------------��
//CPlayerModel�̏���������
//��----------------------------------��
HRESULT CPlayerModel::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	
	m_pSceneModelMotion = CSceneModelMotion::Create("./data/TEXTDATA/motion_HRobo.txt");
	m_pModelParts = m_pSceneModelMotion->GetPart_Info();


	float EngineSpeed = 15.0f;

	float RadiusL = 40.0f;
	float RadiusS = 20.0f;

	int Life = 12;

	for(int i = 0;i < PLAYER_ENGINENUM;i++)
	{
		if(i < 2)
		{
			m_pParticleSystem[i] = CParticleEngine::Create("./data/TEXTURE/Game/shadow002.jpg",m_Pos,D3DXVECTOR3(D3DX_PI,0.0f,0.0f),40.0f,40.0f,
															Life,0,360,D3DXVECTOR3(0.0f,0.0f,0.0f),EngineSpeed,true,
															-(/*D3DX_PI/2 - atan2f(Life*EngineSpeed,RadiusL/2)*/ + D3DX_PI / 24),RadiusL);
		}
		else
		{
			m_pParticleSystem[i] = CParticleEngine::Create("./data/TEXTURE/Game/shadow000.jpg",m_Pos,D3DXVECTOR3(D3DX_PI,0.0f,0.0f),30.0f,30.0f,
															Life,0,300,D3DXVECTOR3(0.0f,0.0f,0.0f),EngineSpeed * 2/3,true,
															-(/*D3DX_PI/2 - atan2f(Life*EngineSpeed,RadiusL/2)*/ + D3DX_PI / 18),RadiusS);
		}
	}


	m_pMeshOrbit = CSceneMeshOrbit::Create(D3DXVECTOR3(0.0f,-3.0f,-110.0f),D3DXVECTOR3(0.0f,-3.0f,-20.0f),
											D3DXCOLOR(1.0f,0.0f,0.0f,1.0f),D3DXCOLOR(1.0f,0.0f,0.0f,0.3f));

	



	m_pmtxWorld = new D3DXMATRIX[m_pSceneModelMotion->GetPart_Num()];

	for(int i = 0;i < m_pSceneModelMotion->GetPart_Num();i++)
	{
		//***�e�N�X�e���̓ǂݍ���***
		if(m_pModelParts[i].TexName[0] != NULL && strcmp(m_pModelParts[i].TexName,"NULL") != 0)
		{
			m_Texture[i] = CManager::GetTextureManagerPointer()->GetTexture(CManager::GetTextureManagerPointer() -> Load(m_pModelParts[i].TexName));
		}

		//���f���̃��[�h
		if(m_pModelParts[i].ModelName != NULL)
		{
			m_XFile_Info[i] = CManager::GetXFileManagerPointer()->GetXFile(CManager::GetXFileManagerPointer()->Load(m_pModelParts[i].ModelName));
		}
	}

	return S_OK;
}

//��----------------------------------��
//CPlayerModel�̏I������
//��----------------------------------��
void CPlayerModel::Uninit(void)
{
	Release();

	SAFE_DELETE_ARRY(m_pmtxWorld);
	
	for(int i = 0;i < PLAYER_BULLETNUM;i++)
		SAFE_DELETE(m_pBulletPattern[i]);

	SAFE_DELETE(m_pPatternChanger);
}

//��-----------------------------------��
//CPlayerModel�̍X�V����
//��-----------------------------------��
void CPlayerModel::Update(void)
{
	int EnemyMax = 16;

	CScene *pEnemy[16] = {NULL};
	CScene::SearchLinkList(pEnemy,CTYPE_ENEMY);

	for(int i = 0;i < EnemyMax;i++)
	{
		//�G���Z�b�g����ĂȂ������炷��
		if(m_pTargetEnemyPointer == NULL)
		{
			m_pTargetEnemyPointer = pEnemy[0];
			m_NowTargetNum = 0;
			break;
		}

		//�G���Z�b�g����Ă����猻�݂̃^�[�Q�b�g�̔ԍ����X�V����
		if(m_pTargetEnemyPointer == pEnemy[i])
		{
			m_NowTargetNum = i;
			break;
		}

		//�����ԍ��ɓG�����Ȃ�������l��ς���
		if(i == EnemyMax - 1)
		{
			if(pEnemy[m_NowTargetNum + 1] != NULL)
			{
				m_pTargetEnemyPointer = pEnemy[m_NowTargetNum + 1];
				m_NowTargetNum++;
			}
			else
			{
				m_pTargetEnemyPointer = pEnemy[0];
				m_NowTargetNum = 0;
			}
		}
	}

	if(CInput::GetKeyboardTrigger(DIK_H))
	{
		//���������N�������Ȃ炻�����^�[�Q�b�g�ɐݒ�
		if(pEnemy[m_NowTargetNum + 1] != NULL && m_NowTargetNum != EnemyMax - 1)
		{
			m_pTargetEnemyPointer = pEnemy[m_NowTargetNum + 1];
			m_NowTargetNum++;
		}
		else if(pEnemy[m_NowTargetNum + 1] == NULL && m_NowTargetNum != EnemyMax - 1)
		{
			m_pTargetEnemyPointer = pEnemy[0];
			m_NowTargetNum = 0;
		}
		else if(m_NowTargetNum == EnemyMax - 1)		//�ԍ����Ōゾ������O��
		{
			m_pTargetEnemyPointer = pEnemy[0];
		}
	}

	if(m_pTargetEnemyPointer != NULL)
	{
		m_CameraRPos = CItemList::Vec3lerp(m_CameraRPos,m_pTargetEnemyPointer->GetPosition(),0.1f);
		CManager::GetCameraPointer()->CameraMoveRSet(m_CameraRPos);
	}



	m_OldPos = m_Pos;

	//���[�V�����ɂ��ړ�
	m_pPatternChanger->Update(this,m_pSceneModelMotion);

	//�͈͊O���̐ݒ�
	if(m_Pos.x <= -STAGE_LENGTH_X || m_Pos.x >= STAGE_LENGTH_X)m_Pos.x = m_OldPos.x;
	if(m_Pos.y <= -STAGE_LENGTH_Y || m_Pos.y >= STAGE_LENGTH_Y)m_Pos.y = m_OldPos.y;
	if(m_Pos.z <= -STAGE_LENGTH_Z || m_Pos.z >= STAGE_LENGTH_Z)m_Pos.z = m_OldPos.z;
	



	//�����_�Ƃ̂����蔻��
	D3DXVECTOR3 CameraPosR = CManager::GetCameraPointer()->GetCameraR();

	float CameraRCollisionSize = 30.0f;


	int GameOverChangeTime = 180;

	if(m_PlayerLife <= 0)
	{
		if(m_ResultChangeCnt == 0)			//0�̎��Ƀ��[�V������ς���
		{
			MotionPatternChange(new CPlayerMotionPatternDie(m_pSceneModelMotion));
			m_ResultChangeCnt++;
		}
		else if(m_ResultChangeCnt >= GameOverChangeTime && m_ResultChangeCnt <= GameOverChangeTime + 100)		//
		{
			CManager::GetPhaseChangePointer()->PhaseChange(new CPhaseResult(PHASE_RESULT,RESULT_GAMEOVER));
			m_ResultChangeCnt = GameOverChangeTime + 101;		//����ł��̂������if�𖳌���
		}
		else if(m_ResultChangeCnt <= GameOverChangeTime)
		{
			m_ResultChangeCnt++;
		}
	}

	//��������ɂ����Ń}�g���b�N�X���W�ϊ����s��
	MatrixUpdate();

	//�e�̔��˂ƃp�[�e�B�N���ʒu�̕ύX
	for(int i = 0;i < PLAYER_BULLETNUM;i++)
	{
		//�̗͂��Ȃ������猂�ĂȂ�
		if(m_PlayerLife > 0)
		{
		m_pBulletPattern[i]->Update_Player(this);
		}
	}

	//�G���W���̃p�[�e�B�N��
	D3DXVECTOR3 EnginePos[2] = {D3DXVECTOR3(-9.5f,-13.0f,44.0f),D3DXVECTOR3(+9.5f,-13.0f,42.0f)};

	D3DXVec3TransformCoord(&EnginePos[0],&EnginePos[0],&m_pmtxWorld[0]);
	D3DXVec3TransformCoord(&EnginePos[1],&EnginePos[1],&m_pmtxWorld[0]);

	for(int i = 0;i < PLAYER_ENGINENUM;i++)
	{
		m_pParticleSystem[i]->SetPosition(EnginePos[i%2]);
		m_pParticleSystem[i]->SetParticleChangeRotation(D3DXVECTOR3(m_MotionParentPartsRot.x + D3DX_PI * 4/5,
																	m_MotionParentPartsRot.y,
																	-m_MotionParentPartsRot.z));
	}

	m_pMeshOrbit->SetOrbitMatrix(m_pmtxWorld[5]);



	CDebugProc::Print("�v���C���[�̈ʒu X = %f\n",m_Pos.x);
	CDebugProc::Print("�v���C���[�̈ʒu Y = %f\n",m_Pos.y);
	CDebugProc::Print("�v���C���[�̈ʒu Z = %f\n",m_Pos.z);
	CDebugProc::Print("�v���C���[�̊p�x Y = %f\n",m_Rot.y);
	CDebugProc::Print("�v���C���[�̃��C�t = %d\n",(int)m_PlayerLife);
	CDebugProc::Print("�J������Y����]�� : %f\n",CManager::GetCameraPointer()->GetCameraRotationY());
}


//��-----------------------------------��
//CPlayerModel�̕`�揈��
//��-----------------------------------��
void CPlayerModel::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	D3DXMATERIAL *pMat;
	D3DMATERIAL9 matDef;		//�}�b�g�̃f�t�H���g
	
//	pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE);

	for(int i = 0;i < m_pSceneModelMotion->GetPart_Num();i++)
	{
		pDevice -> SetTransform(D3DTS_WORLD,&m_pmtxWorld[i]);	//�ݒ�

		//���f���̕`��
		pDevice -> GetMaterial(&matDef);
		pMat = (D3DXMATERIAL*)m_XFile_Info[i].BuffMat->GetBufferPointer();

		for(int nCntMat = 0;nCntMat < (int)m_XFile_Info[i].numMat;nCntMat++)
		{
			pDevice -> SetMaterial(&pMat[nCntMat].MatD3D);
			pDevice -> SetTexture(0,m_Texture[i]);
			m_XFile_Info[i].Mesh->DrawSubset(nCntMat);
		}

		pDevice -> SetMaterial(&matDef);
	}
	
//	pDevice->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_ADD);

}

//��----------------------------------��
//CPlayerModel�̂����蔻��̃T�C�Y�̑傫��
//��----------------------------------��
float CPlayerModel::GetCollisionRadius(int Num)
{
	if(Num == 2)
		return 500.0f;
	else
		return 120.0f;
}

//��----------------------------------��
//CPlayerModel�̂����蔻��̃T�C�Y�̑傫��
//��----------------------------------��
D3DXVECTOR3 CPlayerModel::GetCollisionCenterPos(int Num)
{
	D3DXVECTOR3 SwordCollisionPos;

	switch(Num)
	{
	case 0:
		return m_Pos + D3DXVECTOR3(0.0f,70.0f,0.0f);
		break;
	case 1:
		return m_Pos + D3DXVECTOR3(0.0f,-100.0f,0.0f);
		break;
	case 2:
		//�\�[�h�̈ʒu
		SwordCollisionPos = D3DXVECTOR3(0.0f,0.0f,-300.0f);
		D3DXVec3TransformCoord(&SwordCollisionPos,&SwordCollisionPos,&m_pmtxWorld[5]);

		return SwordCollisionPos;
		break;

	default:
		return D3DXVECTOR3(0.0f,0.0f,0.0f);
		break;
	}
}

//��----------------------------------��
//CPlayerModel�̂����蔻�莞�̃A�N�V����
//��----------------------------------��
void CPlayerModel::CollisionAction(CLASS_TYPE Type,int Num)
{
	if(Type != CTYPE_ENEMY)
	{
		PlaySound(SOUND_LABEL_Damage);

		//�����̗̑͂�UI�̐��l�����炷
		m_PlayerLife -= PLAYER_DAMAGE;
		m_pPlayerScore->PlusScore(-PLAYER_DAMAGE);

		return;
	}
	
	if(Type == CTYPE_ENEMY && GetCollisionHitNum() == 3)		//�a�������������ꍇ
	{
		SetCollisionHitNum(2);
		return;
	}
}

//��-----------------------------------��
//CPlayerModel�̂����蔻��̃`�F�b�N�V�[�g
//��-----------------------------------��
bool CPlayerModel::CollisionTargetSheet(CLASS_TYPE Type)
{
	switch(Type)
	{
	case CTYPE_ENEMY:	return true;break;

	default:			return false;break;
	}
}

//��----------------------------------��
//CPlayerModel�̃p�[�c�̈ʒu�̃Q�b�g
//��----------------------------------��
D3DXMATRIX CPlayerModel::GetPlayerPartsMatrix(int PartsNum)
{
	return m_pmtxWorld[PartsNum];
}

//��----------------------------------��
//CPlayerModel�̂��[�����̕ύX
//��----------------------------------��
void CPlayerModel::MotionPatternChange(CPlayerMotionPattern *pPattern)
{
	m_pPatternChanger->ChangedPattern(pPattern);
}

//��----------------------------------��
//CPlayerModel�̂��[�����̕ύX
//��----------------------------------��
void CPlayerModel::SetOrbitDrawStartJudge(bool Judge)
{
	m_pMeshOrbit->SetOebitStopJudge(Judge);
}

//��----------------------------------��
//CPlayerModel�̃G���M���X�s�[�h�Z�b�g
//��----------------------------------��
void CPlayerModel::SetEngineSpeed(float Speed)
{
	m_pParticleSystem[0]->SetEngineSpeedUp(Speed);
	m_pParticleSystem[1]->SetEngineSpeedUp(Speed);
	m_pParticleSystem[2]->SetEngineSpeedUp(Speed * 2/3);
	m_pParticleSystem[3]->SetEngineSpeedUp(Speed * 2/3);
}

//��----------------------------------��
//CPlayerModel�̃G���M���X�s�[�h�Q�b�g
//��----------------------------------��
float CPlayerModel::GetEngineSpeed()
{
	return m_pParticleSystem[0]->GetEngineSpeedUp();
}

//��----------------------------------��
//CPlayerModel�̃N���G�C�g(�����t)
//��----------------------------------��
CPlayerModel *CPlayerModel::Create(D3DXVECTOR3 Pos)
{
	CPlayerModel *pPlayerModel;
	pPlayerModel = new CPlayerModel;

	pPlayerModel->m_Pos = Pos;

	pPlayerModel->Init();

	return pPlayerModel;
}

