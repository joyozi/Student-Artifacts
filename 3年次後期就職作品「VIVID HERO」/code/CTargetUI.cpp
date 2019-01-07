//��-------------------------------------------------------------------------��
//
//	File:CTargetUI�̃t�@�C��[CTargetUI.cpp]
//	Author:�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include "CTargetUI.h"
#include "CCamera.h"
#include "CManager.h"
#include "CPlayerModel.h"
#include "CItemList.h"

//��-------------------------------------------------------------------------��
//�ÓI�����o�ϐ��̏�����
//��-------------------------------------------------------------------------��

//��-----------------------------------��
//CTargetUI�̃R���X�g���N�^
//��-----------------------------------��
CTargetUI::CTargetUI(int nPriority) : CSceneBillboard(nPriority)
{
	float TexSize = 400.0f;

	TextureWidth = TexSize;
	TextureHeight = TexSize;

	m_DrawJudge = true;
}

//��-----------------------------------��
//CTargetUI�̃f�X�g���N�^
//��-----------------------------------��
CTargetUI::~CTargetUI()
{

}

//��-----------------------------------��
//CTargetUI�̍X�V����
//��-----------------------------------��
void CTargetUI::Update(void)
{
	float TargetFade_Start = 3000.0f;			//�ǂ̋�������^�[�Q�b�g������Ă�����
	float TargetFade_End = 1500.0f;				//


	CScene *irekoScene = NULL;

	CScene::SearchLinkList(&irekoScene,CTYPE_PLAYERMODEL);

	if(irekoScene != NULL)
	{
		//�_�E���L���X�g
		CPlayerModel *pPlayer = (CPlayerModel*)irekoScene;
		CScene *pTargetEnemy = pPlayer->GetTargetEnemyPointer();

		if(pTargetEnemy != NULL)
		{
			m_DrawJudge = true;
			
			//�^�[�Q�b�g�|�X�̐ݒ�
			D3DXVECTOR3 a = pTargetEnemy->GetCollisionCenterPos(0) - CManager::GetCameraPointer()->GetCameraP();
			D3DXVec3Normalize(&a,&a);

			m_Pos = pTargetEnemy->GetCollisionCenterPos(0) - (a * pTargetEnemy->GetCollisionRadius(0) * 2);



			//�����ɉ����Ăt�h�𓧖��ɂ���
			float Length = CItemList::GetLengthSimple(pPlayer->GetPosition() - pTargetEnemy->GetCollisionCenterPos(0));

			if(Length <= TargetFade_Start)
			{
				if(Length <= TargetFade_End)
				{
					m_DrawJudge = false;
				}
				else
				{
					m_DrawJudge = true;

					//�^�[�Q�b�g�����x�v�Z
					Length -= TargetFade_End;
					float Alpha = Length / (TargetFade_Start - TargetFade_End);

					SetColor(D3DXCOLOR(1.0f,1.0f,1.0f,Alpha));
				}
			}
		}
		else	//�ڕW�����݂��Ȃ���Ε`�悵�Ȃ�
		{
			m_DrawJudge = false;
		}
	}
}

//��----------------------------------��
//CTargetUI�̕`�揈��
//��----------------------------------��
void CTargetUI::Draw(void)
{
	//****�f�o�C�X�擾****
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;
	D3DXMATRIX mtxView;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�r���[�}�g���b�N�X�̎擾
	mtxView = CManager::GetCameraPointer()->GetMtxView();

	//�t�s������߂�
	D3DXMatrixInverse(&m_mtxWorld,NULL,&mtxView);

	m_mtxWorld._41 = 0.0f;
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;

	//****���[���h�̐ݒ�****
	D3DXMatrixScaling(&mtxScl,m_Scl.x,m_Scl.y,m_Scl.z);					//�X�P�[���𔽉f
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxScl);

	//****�ʒu�̐ݒ�****
	D3DXMatrixTranslation(&mtxTranslate,m_Pos.x,m_Pos.y,m_Pos.z);		//�ʒu�𔽉f
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxTranslate);

	pDevice -> SetTransform(D3DTS_WORLD,&m_mtxWorld);	//�ݒ�

	if(m_DrawJudge)
	{
		//����Ń��C�e�B���O�𖳌��ɂ���
		pDevice->SetRenderState(D3DRS_LIGHTING,FALSE);
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE ,FALSE);

		//3D�|���S���̕`��
		pDevice->SetStreamSource(0,m_VtxBuffer,0,sizeof(VERTEX_3D));
		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0,m_Texture);
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);

		pDevice->SetRenderState(D3DRS_ZWRITEENABLE ,TRUE);
		pDevice->SetRenderState(D3DRS_LIGHTING,TRUE);
	}
}

//��----------------------------------��
//CTargetUI�̃N���G�C�g
//��----------------------------------��
CTargetUI *CTargetUI::Create(LPCTSTR TextureName)
{
	CTargetUI *pTargetUI;
	pTargetUI = new CTargetUI;

	pTargetUI->m_TextureName = TextureName;
	
	pTargetUI->Init();

	return pTargetUI;
}
