//��-------------------------------------------------------------------------��
//
//	File	:���C�g�����t�@�C��[light.cpp]
//	Author	:�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include "main.h"
#include "light.h"
#include "model.h"
#include "input.h"
#include "taimatsu.h"
#include "camera.h"

//��-------------------------------------------------------------------------��
//�}�N����`
//��-------------------------------------------------------------------------��
#define DEFFUSE_R (0.3f)			//���C�g�̐F�B��
#define DEFFUSE_G (0.3f)			//���C�g�̐F�B��
#define DEFFUSE_B (0.3f)			//���C�g�̐F�B��
#define DEFFUSE_A (1.0f)			//���C�g�̐F�B�A���t�@

#define LIGHT_NUM ((int)(CAMERA_LONG * 2 / TAIMATSU_KANKAKU))		//���C�g�̐�
#define LIGHTJOUHOU_NUM		(LIGHT_NUM * 3)						//���C�g����[]���̐� (�g���ĂȂ�)
#define LIGHT_RANGE			(1000.0f)
#define LIGHT_ATTENUATION	(0.8f)
//��-------------------------------------------------------------------------��
//�v���g�^�C�v�錾
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�O���[�o���ϐ�
//��-------------------------------------------------------------------------��
D3DLIGHT9 g_aLight[LIGHTJOUHOU_NUM];		//���C�g���		[]���ɂ̓��C�g�̐���3������

float light_POSZ;							//���C�g�̈�Ԍ��̈ʒu
bool Light_sayuu;							//���������E�̂ǂ����ɐݒu���邩�̃W���b�W

bool kisuu_LightOPSION;						//��Ԍ��̏��������E�ǂ���ɂ��邩������B�����̐�����ɂ���Ȃ�g��

//��-------------------------------------------------------------------------��
//���C�g����������
//��-------------------------------------------------------------------------��
void InitLight(void)
{
	//����邩�킩��Ȃ�
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
//	VERTEX_3D *pVtx;
	
	//�����̍��E�̈ʒu�ƑO��̈ʒu�̏�����
	Light_sayuu = true;
	kisuu_LightOPSION = Light_sayuu;	//�����̈�Ԍ��̈ʒu�̏�����
	light_POSZ = -CAMERA_LONG;

	//****���C�g�̏�����****
	D3DXVECTOR3 VecDir[3];
	for(int nCnt = 0;nCnt < LIGHT_NUM;nCnt++)
	{
		//****���C�g1****
		//======================
		ZeroMemory(&g_aLight[0 + (nCnt * 3)],sizeof(D3DLIGHT9));
		g_aLight[0 + (nCnt * 3)].Type = D3DLIGHT_POINT;													//���C�g�̎��
		g_aLight[0 + (nCnt * 3)].Diffuse = D3DXCOLOR(DEFFUSE_R, DEFFUSE_G, DEFFUSE_B, DEFFUSE_A);		//���C�g�̐F

		g_aLight[0 + (nCnt * 3)].Position = D3DXVECTOR3(Getpostaimatsu().x,Getpostaimatsu().y,Getpostaimatsu().z);

		g_aLight[0 + (nCnt * 3)].Attenuation0 =LIGHT_ATTENUATION;
		g_aLight[0 + (nCnt * 3)].Range = LIGHT_RANGE;

		D3DXVec3Normalize((D3DXVECTOR3*)&g_aLight[0 + (nCnt * 3)].Direction,&VecDir[0 + (nCnt * 3)]);

		pDevice -> SetLight(0 + (nCnt * 3),&g_aLight[0 + (nCnt * 3)]);	//���C�g��ݒ�
		pDevice -> LightEnable(0 + (nCnt * 3),TRUE);			//���C�g��L���ɂ���

		//***���C�g2***
		//========================
		ZeroMemory(&g_aLight[1 + (nCnt * 3)],sizeof(D3DLIGHT9));
		g_aLight[1 + (nCnt * 3)].Type = D3DLIGHT_POINT;						//���C�g�̎��
		g_aLight[1 + (nCnt * 3)].Diffuse = D3DXCOLOR(DEFFUSE_R, DEFFUSE_G, DEFFUSE_B, DEFFUSE_A);		//���C�g�̐F

		g_aLight[1 + (nCnt * 3)].Position = D3DXVECTOR3(Getpostaimatsu().x,Getpostaimatsu().y,Getpostaimatsu().z);

		g_aLight[1 + (nCnt * 3)].Attenuation0 =LIGHT_ATTENUATION;
		g_aLight[1 + (nCnt * 3)].Range = LIGHT_RANGE;

		D3DXVec3Normalize((D3DXVECTOR3*)&g_aLight[1 + (nCnt * 3)].Direction,&VecDir[1 + (nCnt * 3)]);

		pDevice -> SetLight(1 + (nCnt * 3),&g_aLight[1 + (nCnt * 3)]);	//���C�g��ݒ�
		pDevice -> LightEnable(1 + (nCnt * 3),TRUE);			//���C�g��L���ɂ���

		//***���C�g3***
		//========================
		ZeroMemory(&g_aLight[2 + (nCnt * 3)],sizeof(D3DLIGHT9));
		g_aLight[2 + (nCnt * 3)].Type = D3DLIGHT_POINT;						//���C�g�̎��
		g_aLight[2 + (nCnt * 3)].Diffuse = D3DXCOLOR(DEFFUSE_R, DEFFUSE_G, DEFFUSE_B, DEFFUSE_A);		//���C�g�̐F

		g_aLight[2 + (nCnt * 3)].Position = D3DXVECTOR3(Getpostaimatsu().x,Getpostaimatsu().y,Getpostaimatsu().z);

		g_aLight[2 + (nCnt * 3)].Attenuation0 =LIGHT_ATTENUATION;
		g_aLight[2 + (nCnt * 3)].Range = LIGHT_RANGE;

		D3DXVec3Normalize((D3DXVECTOR3*)&g_aLight[2 + (nCnt * 3)].Direction,&VecDir[2 + (nCnt * 3)]);

		//****���C�g�̐ݒ�****
		pDevice -> SetLight(2 + (nCnt * 3),&g_aLight[2 + (nCnt * 3)]);	//���C�g��ݒ�
		pDevice -> LightEnable(2,TRUE);			//���C�g��L���ɂ���
	}
}

//��---------------------------------��
//���C�g�I������
//��---------------------------------��
void UninitLight(void)
{

}
//��---------------------------------��
//���C�g�̍X�V����
//��---------------------------------��
void UpdateLight(void)
{
	//����邩�킩��Ȃ�
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	D3DXVECTOR3 LightIti;			//�����̈ʒu���󂯎��ϐ�

	//�����̈ʒu�������Ŏ󂯎��
	LightIti = Getpostaimatsu();

	//������������true����ŏ��ɂ��Ȃ��ƁA�����̈ʒu�����������Ȃ����肷��
//	if((int)(CAMERA_LONG / TAIMATSU_KANKAKU) % 2 == 0)
	{
		Light_sayuu = kisuu_LightOPSION;
	}

	//�{�̂̈ʒu��艓����������v���X�}�C�i�X����
	while(Getg_posModel().z - CAMERA_LONG >= light_POSZ)
	{
		light_POSZ += TAIMATSU_KANKAKU;

		//���E�ړ�
		if(Light_sayuu == true)
			Light_sayuu = false;
		else
			Light_sayuu = true;

		//��Ԍ��̏����̍��E�ʒu�̔���
		if(kisuu_LightOPSION == true)
			kisuu_LightOPSION = false;
		else
			kisuu_LightOPSION = true;

	}

	//������cpp�Ɠ����������s��
	while(Getg_posModel().z + CAMERA_LONG < light_POSZ + CAMERA_LONG * 2)
	{
		light_POSZ -= TAIMATSU_KANKAKU;

		//���E�ړ�
		if(Light_sayuu == true)
			Light_sayuu = false;
		else
			Light_sayuu = true;

		//��Ԍ��̏����̍��E�ʒu�̔���
		if(kisuu_LightOPSION == true)
			kisuu_LightOPSION = false;
		else
			kisuu_LightOPSION = true;
	}
	//�����̈ʒu����Ԍ��ɐݒ�
	LightIti.z = light_POSZ;

	int num = 0;

	for(int nCnt = 0;nCnt < LIGHT_NUM;nCnt++)
	{
		LightIti.z += TAIMATSU_KANKAKU;

		if(Light_sayuu == true)
		{
			//�������������獶���ɏ�����\������
			LightIti.x = TAIMATSU_POSX;
			Light_sayuu = false;
		}
		else
		{
			LightIti.x = -TAIMATSU_POSX;
			Light_sayuu = true;
		}

		g_aLight[0 + (nCnt*3)].Position = D3DXVECTOR3(LightIti.x,LightIti.y,LightIti.z);
		g_aLight[1 + (nCnt*3)].Position = D3DXVECTOR3(LightIti.x,LightIti.y,LightIti.z);
		g_aLight[2 + (nCnt*3)].Position = D3DXVECTOR3(LightIti.x,LightIti.y,LightIti.z);

		pDevice -> SetLight(0 + (nCnt*3),&g_aLight[0 + (nCnt*3)]);	//���C�g��ݒ�
		pDevice -> SetLight(1 + (nCnt*3),&g_aLight[1 + (nCnt*3)]);	//���C�g��ݒ�
		pDevice -> SetLight(2 + (nCnt*3),&g_aLight[2 + (nCnt*3)]);	//���C�g��ݒ�
	}


	static bool judge = true;

	if(GetKeyboardTrigger(DIK_0) == true)
	{
		if(judge == true)
			judge =false;
		else
			judge =true;
	

		if(judge == true)
		{
			g_aLight[0].Type = D3DLIGHT_POINT;						//���C�g�̎��
			g_aLight[1].Type = D3DLIGHT_POINT;						//���C�g�̎��
			g_aLight[2].Type = D3DLIGHT_POINT;						//���C�g�̎��
		}
		else
		{
			g_aLight[0].Type = D3DLIGHT_DIRECTIONAL;						//���C�g�̎��
			g_aLight[1].Type = D3DLIGHT_DIRECTIONAL;						//���C�g�̎��
			g_aLight[2].Type = D3DLIGHT_DIRECTIONAL;						//���C�g�̎��
		}
	}
}

//��---------------------------------��
//���C�g�̕`�揈��
//��---------------------------------��
void DrawLight(void)
{

}
