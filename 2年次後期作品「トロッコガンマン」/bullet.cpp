//��-------------------------------------------------------------------------��
//
//	File	:�e�t�@�C��[bullet.cpp]
//	Author	:�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include "main.h"
#include "bullet.h"
#include "camera.h"
#include "input.h"
#include "model.h"
#include "obstacle.h"
#include "gameUI.h"
#include "explosion.h"
#include "enemy_01.h"
#include "sound.h"
#include "score.h"

//��-------------------------------------------------------------------------��
//�}�N����`
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�v���g�^�C�v�錾
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�O���[�o���ϐ�
//��-------------------------------------------------------------------------��
LPDIRECT3DTEXTURE9 g_pTextureBullet;						//
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet;					//

D3DXMATRIX g_mtxWorldBullet;								//���[���h�}�g���b�N�X
D3DXVECTOR3 g_posBullet[BULLET_MAX];						//�ʒu
D3DXVECTOR3 g_rotBullet[BULLET_MAX];						//����
D3DXVECTOR3 g_sclBullet[BULLET_MAX];						//�傫���i��{�ς��Ȃ��j

bool bullet_hassha[BULLET_MAX];								//���˂̐���
D3DXMATRIX posBullet_Original[BULLET_MAX];					//�^�}�̔��ˎ��̘r�̈ʒu��ۑ����Ă����B��Ɉʒu���ς���Ĉˑ�����Ȃ�����
PLAYER_MODE p_Bullet_shunkan[BULLET_MAX];					//�e�������ꂽ�u�Ԃ̖{�̂̈ʒu�A��Ԃ̕ۑ�������ϐ�
int BulletUpdate_num;										//�e�̍X�V�Ɏg�����B

//��-------------------------------------------------------------------------��
//�o���b�g����������
//��-------------------------------------------------------------------------��
void InitBullet(void)
{
	//����邩�킩��Ȃ�
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	
	VERTEX_3D *pVtx;

	for(int nCnt = 0;nCnt < BULLET_MAX;nCnt++)
	{
		//���E�̒e�̈ʒu�̏�����
		//BAEM_TEXTURE_NUM�̂Ƃ��͍��肩��o�� BAEM_TEXTURE_NUM*2�̂Ƃ��͉E��
		if(nCnt % (BAEM_TEXTURE_NUM*2) >= 0 && nCnt % (BAEM_TEXTURE_NUM*2) < BAEM_TEXTURE_NUM)
		{
			//****�ʒu�A�p�x�A�X�P�[���̏�����****
			g_posBullet[nCnt] = D3DXVECTOR3(-5.0f,2.0f,38.0f);
			g_rotBullet[nCnt] = D3DXVECTOR3(0.0f,0.0f,0.0f);
			g_sclBullet[nCnt] = D3DXVECTOR3(1.0f,1.0f,1.0f);
		}
		else if(nCnt % (BAEM_TEXTURE_NUM*2) >= BAEM_TEXTURE_NUM && nCnt % (BAEM_TEXTURE_NUM*2) < BAEM_TEXTURE_NUM*2)
		{
			//****�ʒu�A�p�x�A�X�P�[���̏�����****
			g_posBullet[nCnt] = D3DXVECTOR3(5.0f,2.0f,38.0f);
			g_rotBullet[nCnt] = D3DXVECTOR3(0.0f,0.0f,0.0f);
			g_sclBullet[nCnt] = D3DXVECTOR3(1.0f,1.0f,1.0f);
		}
		//�e���˂̏�����
		bullet_hassha[nCnt] = false;

		//�e���������u�Ԃ̖{�̂̏��̏�����
		p_Bullet_shunkan[nCnt] = GetModelOriginal();
	}
	
	BulletUpdate_num = 0;

	g_pTextureBullet = NULL;
	g_pVtxBuffBullet = NULL;

	//***�e�N�X�e���̓ǂݍ���***
	D3DXCreateTextureFromFile(pDevice,"./data/TEXTURE/effect000.png",&g_pTextureBullet);

	//***���_���̐ݒ�***
	//****���_�o�b�t�@�̐ݒ�****
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D)*4*BULLET_MAX,D3DUSAGE_WRITEONLY,FVF_VERTEX_3D,D3DPOOL_MANAGED,&g_pVtxBuffBullet,NULL);

	//***���_�f�[�^�����b�N***
	g_pVtxBuffBullet->Lock(0,0,(void**)&pVtx,0);

	for(int nCnt = 0;nCnt < BULLET_MAX;nCnt++)
	{
		//****���_�̈ʒu�̐ݒ�****
		pVtx[0 + nCnt*4].pos = D3DXVECTOR3(-BULLET_SIZE +(nCnt%BAEM_TEXTURE_NUM),BULLET_SIZE -(nCnt%BAEM_TEXTURE_NUM),0.0f);
		pVtx[1 + nCnt*4].pos = D3DXVECTOR3(BULLET_SIZE -(nCnt%BAEM_TEXTURE_NUM),BULLET_SIZE -(nCnt%BAEM_TEXTURE_NUM),0.0f);
		pVtx[2 + nCnt*4].pos = D3DXVECTOR3(-BULLET_SIZE +(nCnt%BAEM_TEXTURE_NUM),-BULLET_SIZE +(nCnt%BAEM_TEXTURE_NUM),0.0f);
		pVtx[3 + nCnt*4].pos = D3DXVECTOR3(BULLET_SIZE -(nCnt%BAEM_TEXTURE_NUM),-BULLET_SIZE +(nCnt%BAEM_TEXTURE_NUM),0.0f);

		//****�����̐ݒ�*****
		pVtx[0 + nCnt*4].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
		pVtx[1 + nCnt*4].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
		pVtx[2 + nCnt*4].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
		pVtx[3 + nCnt*4].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);

		//****�J���[�̐ݒ�****
		pVtx[0 + nCnt*4].col = D3DCOLOR_RGBA(255,125,125,255);
		pVtx[1 + nCnt*4].col = D3DCOLOR_RGBA(255,125,125,255);
		pVtx[2 + nCnt*4].col = D3DCOLOR_RGBA(255,125,125,255);
		pVtx[3 + nCnt*4].col = D3DCOLOR_RGBA(255,125,125,255);

		//****tex�̐ݒ�****
		pVtx[0 + nCnt*4].tex = D3DXVECTOR2(0.0,0.0);
		pVtx[1 + nCnt*4].tex = D3DXVECTOR2(1.0,0.0);
		pVtx[2 + nCnt*4].tex = D3DXVECTOR2(0.0,1.0);
		pVtx[3 + nCnt*4].tex = D3DXVECTOR2(1.0,1.0);
	}
		//****���_�f�[�^�̃��b�N����
		g_pVtxBuffBullet->Unlock();
	
}

//��---------------------------------��
//�o���b�g�I������
//��---------------------------------��
void UninitBullet(void)
{
	if(g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	
	}
	//�e�N�X�`���̏���
	if(g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}
}
//��---------------------------------��
//�o���b�g�̍X�V����
//��---------------------------------��
void UpdateBullet(void)
{
	static int BulletShoot;		//�������ςŌ��Ă�v�Z������

	if(BulletUpdate_num >= BULLET_MAX)
		BulletUpdate_num= 0;
	
	//�^�}�̔��ˊԊu�{�^�����������珉���l�ɖ߂��𐔂���
	if(GetKeyboardPress(DIK_RETURN) == false)
	{
		BulletShoot = BULLET_KANKAKU;
	}

	//=========================
	//�e�̌��u�Ԃ̏���
	//=========================

	//���ݏ�ԈȊO�̂Ƃ��͔��˂ł���
	if(GetModelOriginal().Model_Muteki != 2)
	{
		BulletShoot++;
		if(BulletShoot >= BULLET_KANKAKU)
		{
			//�^�}�̔��˂�����
			if(GetKeyboardPress(DIK_RETURN) == true)
			{
				//�e�Ԋu�̐����n��
				BulletShoot = 0;
				//���˂����u�Ԃ̒e�Ɩ{�̂̊֌W��ۑ�����
				//1���̈�ԑO�̃e�N�X�`���̕������ۑ�����B�ق��͔̂���ɂ͎g��Ȃ�����
				p_Bullet_shunkan[BulletUpdate_num] = GetModelOriginal();
	
				PlaySound(SOUND_LABEL_GUNFIRE);				//�e�̔��ˉ�

				//�^�}�̃e�N�X�e���������J��Ԃ�
				for(int nCnt = 0;nCnt < BAEM_TEXTURE_NUM;nCnt++)
				{
					//�e�̃e�N�X�e��5������L����
					bullet_hassha[BulletUpdate_num] = true;
		
					//�^�}�̔��ˈʒu��ۑ�����
					if(BulletUpdate_num % (BAEM_TEXTURE_NUM*2) >= 0 && BulletUpdate_num % (BAEM_TEXTURE_NUM*2) < BAEM_TEXTURE_NUM)
					{
						//���̏e�̈ʒu��ۑ�
						posBullet_Original[BulletUpdate_num] = GetTranslate_juuL();
					}

					else if(BulletUpdate_num % (BAEM_TEXTURE_NUM*2) >= BAEM_TEXTURE_NUM && BulletUpdate_num % (BAEM_TEXTURE_NUM*2) < BAEM_TEXTURE_NUM*2)
					{
						//�E�̏e�̈ʒu��ۑ�
						posBullet_Original[BulletUpdate_num] = GetTranslate_juuR();
					}

					g_posBullet[BulletUpdate_num].z -= (nCnt * 3);		//�e�̈ʒu���������炷
					BulletUpdate_num++;									//�e�N�X�`�����v���X
				}
			}
		}
	}

	//�L�������ꂽ�e�̈ʒu���ړ�������
	for(int nCnt = 0;nCnt < BULLET_MAX;nCnt++)
	{
		//�L���Ȃ�ʒu���ړ�����
		if(bullet_hassha[nCnt] == true)
		{
			//�ʒu�̃v���X
			g_posBullet[nCnt].z += BULLET_SPEED + GetModel_SpeedUP();

			//�˒������O�ɏo����\������߂�
			//�ʒu��0����Ȃ̂ł����
			if(g_posBullet[nCnt].z > BULLET_LANGE)
			{
				g_posBullet[nCnt].z = 38.0f;
				bullet_hassha[nCnt] = false;
			}
		}
	}


	//�����蔻��
	//�����A�^�}�̐擪�����f���ɓ��������烂�f����������A��������A�_���[�W��^����
}

//��---------------------------------��
//�o���b�g�̕`�揈��
//��---------------------------------��
void DrawBullet(void)
{
	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;

	D3DXMATRIX mtxView;				//�r���[�}�g���b�N�X�@�t�s��̓���q
	
	//****�f�o�C�X�擾****
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//�G�t�F�N�g�����@���鏈��
	pDevice->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE);

	//�^�}�̐������J��Ԃ�
	for(int nCnt = 0;nCnt < BULLET_MAX;nCnt++)
	{
		//�e���L����������`�悷��
		if(bullet_hassha[nCnt] == true)
		{
			mtxView = GetMtxView();

			//------���[���h�}�g���b�N�X�Ƃ��̐ݒ�--------------------------------------------------------------

			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_mtxWorldBullet);

			//�t�s������߂�
			D3DXMatrixInverse(&g_mtxWorldBullet,NULL,&mtxView);

			g_mtxWorldBullet._41 = 0.0f;
			g_mtxWorldBullet._42 = 0.0f;
			g_mtxWorldBullet._43 = 0.0f;

			//****���[���h�̐ݒ�****

			//�X�P�[���̐ݒ�
			D3DXMatrixScaling(&mtxScl,g_sclBullet[nCnt].x,g_sclBullet[nCnt].y,g_sclBullet[nCnt].z);						//�X�P�[���𔽉f
			D3DXMatrixMultiply(&g_mtxWorldBullet,&g_mtxWorldBullet,&mtxScl);
	
			//�p�x�̐ݒ�
			D3DXMatrixRotationYawPitchRoll(&mtxRot,g_rotBullet[nCnt].y,g_rotBullet[nCnt].x,g_rotBullet[nCnt].z);		//���|�@�s�b�`�@���[��
			D3DXMatrixMultiply(&g_mtxWorldBullet,&g_mtxWorldBullet,&mtxRot);
	
			//�ʒu�̐ݒ�
			D3DXMatrixTranslation(&mtxTranslate,g_posBullet[nCnt].x,g_posBullet[nCnt].y,g_posBullet[nCnt].z);			//�ʒu�𔽉f

			//�ʒu�̐ݒ�̑O�ɒe�̈ʒu�Əe�̈ʒu�����Z����
			//�ʒu���������Ă��Ȃ��ƁA�r���{�[�h���������Ȃ��ƂɂȂ��Ă��܂�
			D3DXMatrixMultiply(&mtxTranslate,&mtxTranslate,&posBullet_Original[nCnt]);

			//�����Đݒ�
			D3DXMatrixMultiply(&g_mtxWorldBullet,&g_mtxWorldBullet,&mtxTranslate);

			pDevice -> SetTransform(D3DTS_WORLD,&g_mtxWorldBullet);	//�ݒ�
	
			//------------------------------------------------------------------------------------------

			//****���e�X�g�̊J�n****
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE,TRUE);
			pDevice->SetRenderState(D3DRS_ALPHAREF,100);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC,D3DCMP_GREATER);

			//----------------3D�|���S���̕`��----------------------------------------------------------

			//���_�o�b�t�@���o�C���h
			pDevice->SetStreamSource(0,g_pVtxBuffBullet,0,sizeof(VERTEX_3D));
			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0,g_pTextureBullet);
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,nCnt*4,2);

			//------------------------------------------------------------------------------------------
		}
	}
	//�G�t�F�N�g�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);

	//****���e�X�g�̏I��****
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE,FALSE);
}

void BULLET_HITJUDGE(void)
{
	PLAYER_MODE Hitjudge_ireko;		//�����蔻��̓���q

	//�e�̐������J��Ԃ�
	for(int nCnt = 0;nCnt < BULLET_MAX;nCnt++)
	{
		//�e�����˂��ꂽ�画����n�߂�
		if(bullet_hassha[nCnt] == true)
		{
			//��Q���̐������J��Ԃ�
			for(int ObjectCnt = 0;ObjectCnt < OBSTACLE_NUM;ObjectCnt++)
			{
				//��Q���̈ʒu��������
				Hitjudge_ireko = GetObstacle_info(ObjectCnt);
		
				//���Ȃ画����s��
				if(Hitjudge_ireko.Thing_exist == true)
				{
					//�܂��A��Q���̂����蔻��
					//Z���̔���
					if(p_Bullet_shunkan[nCnt].MOTO_pos.z + g_posBullet[nCnt].z > Hitjudge_ireko.MOTO_pos.z-50.0f
						&& p_Bullet_shunkan[nCnt].MOTO_pos.z + g_posBullet[nCnt].z < Hitjudge_ireko.MOTO_pos.z + 50.0f)
					{
						//X���̂����蔻��
						if(p_Bullet_shunkan[nCnt].LR_Judge == Hitjudge_ireko.LR_Judge)
						{
							//�����ł����蔻�肪�m�肷��B�����̈ʒu�ƗL����������
							PlaySound(SOUND_LABEL_BULLET_EXPLOSION);
							SetExplosion(p_Bullet_shunkan[nCnt].MOTO_pos + g_posBullet[nCnt],nCnt,true,Hitjudge_ireko.LR_Judge);

							//�e�N�X�`���̐�������\���ɂ���
							for(int KekkaCnt = 0;KekkaCnt < BAEM_TEXTURE_NUM;KekkaCnt++)
							{
								g_posBullet[nCnt + KekkaCnt].z = 38.0f;
								bullet_hassha[nCnt + KekkaCnt] = false;
							}
						}
					}
				}
			}

			//�G01�̐������J��Ԃ�
			for(int Enemy01Cnt = 0;Enemy01Cnt < ENEMY01_NUM;Enemy01Cnt++)
			{
				//�G01�̈ʒu��������
				Hitjudge_ireko = GetEnemy01_info(Enemy01Cnt);

				//���Ȃ画����s��
				if(Hitjudge_ireko.Thing_exist == true)
				{
				//�܂��A�G01�̂����蔻��
					//Z���̔���
					if(p_Bullet_shunkan[nCnt].MOTO_pos.z + g_posBullet[nCnt].z > Hitjudge_ireko.MOTO_pos.z-60.0f
						&& p_Bullet_shunkan[nCnt].MOTO_pos.z + g_posBullet[nCnt].z < Hitjudge_ireko.MOTO_pos.z + 60.0f)
					{
						//X���̂����蔻��
						if(p_Bullet_shunkan[nCnt].LR_Judge == Hitjudge_ireko.LR_Judge)
						{
							//�����ł����蔻�肪�m�肷��B�����̈ʒu�ƗL����������
							PlaySound(SOUND_LABEL_BULLET_EXPLOSION);
							SetExplosion(p_Bullet_shunkan[nCnt].MOTO_pos + g_posBullet[nCnt],nCnt,true,Hitjudge_ireko.LR_Judge);

							//�_���[�W��1�^����
							Enemy01_DamageCnt(Enemy01Cnt);

							//�e�N�X�`���̐�������\���ɂ���
							for(int KekkaCnt = 0;KekkaCnt < BAEM_TEXTURE_NUM;KekkaCnt++)
							{
								g_posBullet[nCnt + KekkaCnt].z = 38.0f;
								bullet_hassha[nCnt + KekkaCnt] = false;
							}
						}
					}
				}
			}
		}
	}
}





