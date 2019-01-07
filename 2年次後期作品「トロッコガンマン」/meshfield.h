//��-------------------------------------------------------------------------��
//
//	File	:���b�V���t�B�[���h�w�b�_�[�t�@�C��[meshfield.h]
//	Author	:�����D�O
//
//��-------------------------------------------------------------------------��
void InitMeshfield(void);
void UninitMeshfield(void);
void UpdateMeshfield(void);
void DrawMeshfield(void);

//#define MESH_DANSUU_NUM			(200)													//���i�̃��b�V���t�B�[���h�� �����ς���ƃ|���S���\�������ς��
#define MESH_POYGON_LENGTH		(100)													//�|���S���̒���

#define MESH_TEXTURE_OKUNUM			(60)											//�e�N�X�`���̉��̖���
#define MESH_TEXTURE_YOKONUM		(3)												//�e�N�X�`���̉��̖���

#define MESH_LENGTH_OKU				(MESH_TEXTURE_OKUNUM * MESH_POYGON_LENGTH)			//�n�ʂ̉��̒���
#define MESH_LENGTH_YOKO			(MESH_TEXTURE_YOKONUM * MESH_POYGON_LENGTH)			//�n�ʂ̉��̒���

#define MESH_VTX_NUM			((MESH_TEXTURE_OKUNUM + 1) * (MESH_TEXTURE_YOKONUM + 1))	//���_�̐��@�P�i
#define MESH_POLYGON_NUM		((2 * MESH_TEXTURE_OKUNUM * MESH_TEXTURE_YOKONUM) + ((MESH_TEXTURE_OKUNUM - 1) * 4))				//�|���S���̐��B�O�p�`�|���S�� �����|���S�����܂߂�
#define MESH_INDEX_NUM			(MESH_POLYGON_NUM + 2)									//���_�C���f�b�N�X�̐� �|���S���̐��{�Q


#define TEXTURE_FILE ("./data/TEXTURE/eye_000.png")		//�e�N�X�`���t�@�C���̖��O

