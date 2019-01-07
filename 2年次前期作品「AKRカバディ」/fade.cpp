//��-------------------------------------------------------------------------��
//
//	�t�F�C�hcpp�t�@�C��[.fadecpp]
//	Author : touma yoshihiro
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�C���N���[�h�t�@�C��
//��-------------------------------------------------------------------------��
#include"main.h"
#include "fade.h"
#include "input.h"
#include "game.h"
#include "sound.h"

//��-------------------------------------------------------------------------��
//�}�N����`
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�v���g�^�C�v�錾
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�O���[�o���ϐ�
//��-------------------------------------------------------------------------��
LPDIRECT3DTEXTURE9 f_pTexturePolygon = NULL;
LPDIRECT3DVERTEXBUFFER9 f_pVtxBuffPolygon = NULL;
VERTEX_2D *f_pVtx;		//�摜�̍��W�̃|�C���^
//FADE g_fade = FADE_IN;	//fade.h�Ɉړ�
D3DXCOLOR g_colorFade;
FADE g_fade = FADE_IN;

MODE g_modeNext;

//��-------------------------------------------------------------------------��
//�t�F�C�h�̏���������
//��-------------------------------------------------------------------------��
void InitFade(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&f_pVtxBuffPolygon,NULL);

	//�w�i�摜�̏��o�^
	f_pVtxBuffPolygon->Lock(0,0,(void**)&f_pVtx,0);

	//���_���̐ݒ�
	f_pVtx[0].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	f_pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH,0.0f,0.0f);
	f_pVtx[2].pos = D3DXVECTOR3(0.0f,SCREEN_HEIGHT,0.0f);
	f_pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f);

	f_pVtx[0].rhw = 1.0f;
	f_pVtx[1].rhw = 1.0f;
	f_pVtx[2].rhw = 1.0f;
	f_pVtx[3].rhw = 1.0f;

	f_pVtx[0].col = D3DCOLOR_RGBA(255,255,255,0);
	f_pVtx[1].col = D3DCOLOR_RGBA(255,255,255,0);
	f_pVtx[2].col = D3DCOLOR_RGBA(255,255,255,0);
	f_pVtx[3].col = D3DCOLOR_RGBA(255,255,255,0);

	f_pVtx[0].tex = D3DXVECTOR2(0.0,0.0);
	f_pVtx[1].tex = D3DXVECTOR2(1.0,0.0);
	f_pVtx[2].tex = D3DXVECTOR2(0.0,1.0);
	f_pVtx[3].tex = D3DXVECTOR2(1.0,1.0);

	f_pVtxBuffPolygon->Unlock();

}
//-------------------------------------
//�t�F�C�h�I������
//-------------------------------------
void UninitFade(void)
{
	//�o�b�t�@�̏���
	if(f_pVtxBuffPolygon != NULL)
	{
		f_pVtxBuffPolygon->Release();
		f_pVtxBuffPolygon = NULL;
	}
	
	//�e�N�X�`���̏���
	if(f_pTexturePolygon != NULL)
	{
		f_pTexturePolygon->Release();
		f_pTexturePolygon = NULL;
	}
}
//-------------------------------------
//�t�F�C�h�̍X�V����
//-------------------------------------
void UpdateFade(void)
{
	static float color = 1.2f;
//	static FADE fadejudge = FADE_NONE;	//FADE_NONE�̂Ƃ���INOUT�ǂ����ɐ؂�ւ��邩�̑O���� ENTER���������Ƃ��ɂǂ����ɍs����

	switch(g_fade)
	{
	case FADE_NONE:

		switch(GetMode())
			{
			case MODE_TITTLE:
			case MODE_RESULT:

				//�G���^�[����������t�F�[�h�A�E�g���n�܂�܂�
				if(GetKeyboardTrigger(DIK_RETURN) == true)
				{
					SetFade(FADE_OUT);
				}

				break;
				
			default:
				break;
			}
		
		break;

	case FADE_IN:
		color -= FADE_TIME;

		if(color < 0.0f)
		{
			SetFade(FADE_NONE);	//FADENONE�̂Ƃ���INOUT�ǂ����ɐ؂�ւ��邩�̑O����
		}
		break;

	case FADE_OUT:
		color += FADE_TIME;

		//�t�F�[�h�A�E�g�̏I������
		if(color > 1.0f)
		{	
			SetFade(FADE_IN);	//FADENONE�̂Ƃ���INOUT�ǂ����ɐ؂�ւ��邩�̑O����
			//�|�[�Y���ɕύX��v�����ꂽ�炱����|�[�Y���̑I�����̓��e��K�p����
			if(GetPause() == true)
			{
				SetMode(g_modeNext);
			}
			//�t�F�[�h�A�E�g���I���ɂȂ������ʑJ��
			switch(GetMode())
			{
			case MODE_TITTLE:
				SetMode(MODE_GAME);
				break;

			case MODE_GAME:
				SetMode(MODE_RESULT);
				break;

			case MODE_RESULT:
				SetMode(MODE_TITTLE);
				break;

			case MODE_MAX:
				break;
			}
		}
		break;
	}	//switch(g_fade)�I��


	g_colorFade = D3DXCOLOR(0.0f,0.0f,0.0f,color);

	//�w�i�摜�̏��o�^
	f_pVtxBuffPolygon->Lock(0,0,(void**)&f_pVtx,0);

	//���_���̐ݒ�
	f_pVtx[0].col = g_colorFade;
	f_pVtx[1].col = g_colorFade;
	f_pVtx[2].col = g_colorFade;
	f_pVtx[3].col = g_colorFade;

	f_pVtxBuffPolygon->Unlock();

}
//-------------------------------------
//�t�F�C�h�̕`�揈��
//-------------------------------------
void DrawFade(void)
{
	//�w�i�̕`��
	GetDevice()->SetStreamSource(0,f_pVtxBuffPolygon,0,sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	GetDevice()->SetFVF(FVF_VERTEX_2D);
	//�e�N�X�`���̐ݒ�
	GetDevice()->SetTexture(0,f_pTexturePolygon);
	//�|���S���̕`��
	GetDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);
	
}

//-------------------------------------
//�Z�b�g�t�F�C�h����
//-------------------------------------
void SetFade(FADE fade)
{
	g_fade = fade;

	switch(g_fade)
	{
		case FADE_NONE:
			break;
		case FADE_IN:
			break;
		case FADE_OUT:
			break;
		case FADE_MAX:
			break;
	}
}


FADE GetFade(void)
{
	return(g_fade);
}

//modeNext�ɂ͑����\�����������[�h�̂ЂƂO������?
void SetFade_2(FADE fade,MODE modeNext)
{
	g_fade = fade;

	g_modeNext = modeNext;
	
}