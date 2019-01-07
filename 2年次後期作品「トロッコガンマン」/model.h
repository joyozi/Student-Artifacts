//��-------------------------------------------------------------------------��
//
//	File	:���f������[model.h]
//	Author	:�����D�O
//
//��-------------------------------------------------------------------------��

//��-------------------------------------------------------------------------��
//�v���g�^�C�v�錾
//��-------------------------------------------------------------------------��
void InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);

void ModelHITJUDGE(void);

D3DXVECTOR3 Getg_posModel(void);
D3DXVECTOR3 Getg_rotModel(void);

D3DXMATRIX GetTranslate_juuL(void);
D3DXMATRIX GetTranslate_juuR(void);

float GetModel_SpeedUP(void);

//��-------------------------------------------------------------------------��
//�}�N����`
//��-------------------------------------------------------------------------��
#define MODEL_NUM	(9)				//���f���̃p�[�c��

#define MODEL_MOVE (15.0f)			//�L�����̈ړ���
#define MODE_WHEEL_ROT (0.2f)		//�z�C�[���̉�]�̑��x
#define MODEL_KOMA_SAYUU (5)		//���f���̍��E�ړ������R�}�̃A�j���[�V���������邩

#define MODEL_GOAL		(60000.0f-300.0f)		//�S�[���̍��W

//�v���C���[�̍\���̂�main.h�Ɉړ����܂���

//�\���̂̌�ɒ�`����
PLAYER_MODE GetModelOriginal(void);