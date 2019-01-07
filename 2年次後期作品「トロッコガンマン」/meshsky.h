//��-------------------------------------------------------------------------��
//
//	File	:���b�V���X�J�C�w�b�_�[�t�@�C��[meshsky.h]
//	Author	:�����D�O
//
//��-------------------------------------------------------------------------��
void InitMeshsky(void);
void UninitMeshsky(void);
void UpdateMeshsky(void);
void DrawMeshsky(void);

//#define MESHSKY_DANSUU_NUM		(20)															//���i�̃��b�V���t�B�[���h�� �����ς���ƃ|���S���\�������ς��

#define MESHSKY_POYGON_WIDTH		(300)															//�|���S���̉���
#define MESHSKY_POYGON_HEIGHT		(600)															//�|���S���̏c��

#define MESHSKY_DIAMETER			(2000)															//��̉��̒��a�B
#define MESHSKY_HEIGHT				(2000)															//��̍���	�ł����MESHSKY_POYGON_HEIGHT*(4�̔{��)�ɂ��Ăق���

#define MESHSKY_YOKO_VTX			((int)(MESHSKY_DIAMETER * D3DX_PI / MESHSKY_POYGON_WIDTH))		//���̒��_�̌��B�~�̑傫�����|���S���̉���
#define MESHSKY_TATE_VTX			((int)(MESHSKY_HEIGHT / MESHSKY_POYGON_HEIGHT))					//�c�̒��_�̌��B

#define MESHSKY_VTX_NUM				((MESHSKY_YOKO_VTX + 1) * (MESHSKY_TATE_VTX + 1))				//���_�̐��@�P�i
#define MESHSKY_POLYGON_NUM			(2 * MESHSKY_YOKO_VTX * MESHSKY_TATE_VTX + ((MESHSKY_TATE_VTX - 1) * 4))				//�|���S���̐��B�O�p�`�|���S�� �����|���S�����܂߂�
#define MESHSKY_INDEX_NUM			(MESHSKY_POLYGON_NUM + 2)										//���_�C���f�b�N�X�̐� �|���S���̐��{�Q


//#define MESHSKY_POLYGON_NUM_OUT		


