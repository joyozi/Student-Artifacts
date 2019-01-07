//��-------------------------------------------------------------------------��
//
//	File	:���b�V���P�[�u�w�b�_�[�t�@�C��[meshcave.h]
//	Author	:�����D�O
//
//��-------------------------------------------------------------------------��
void InitMeshCave(void);
void UninitMeshCave(void);
void UpdateMeshCave(void);
void DrawMeshCave(void);

#define CAVE_MESH_POYGON_LENGTH			(35)										//�|���S���̒���


//�e�N�X�`�����W�Ɍ��E�����邩��o�O��
#define CAVE_MESH_TEXTURE_TYOKKEI		(9)										//���A�̒��a�̃e�N�X�`����
#define CAVE_MESH_TEXTURE_NUM_OKULONG	(2000)										//���s���̃e�N�X�`���̐�

#define CAVE_MESH_TYOKKEI			(CAVE_MESH_POYGON_LENGTH * CAVE_MESH_TEXTURE_TYOKKEI)				//���A�̒��a
#define CAVE_MESH_OKU_LONG			(CAVE_MESH_POYGON_LENGTH * CAVE_MESH_TEXTURE_NUM_OKULONG)			//���A�̓��̒���

#define CAVE_MESH_VTX_NUM			((CAVE_MESH_TEXTURE_TYOKKEI + 1) * (CAVE_MESH_TEXTURE_NUM_OKULONG + 1))			//���_�̐��@�P�i
#define CAVE_MESH_POLYGON_NUM		(2 * CAVE_MESH_TEXTURE_NUM_OKULONG * CAVE_MESH_TEXTURE_TYOKKEI + ((CAVE_MESH_TEXTURE_NUM_OKULONG - 1) * 4))	//�|���S���̐��B�O�p�`�|���S�� �����|���S�����܂߂�
#define CAVE_MESH_INDEX_NUM			(CAVE_MESH_POLYGON_NUM + 2)														//���_�C���f�b�N�X�̐� �|���S���̐��{�Q

#define CAVE_TEXTURE_FILE ("./data/TEXTURE/wall_001.jpg")							//�e�N�X�`���t�@�C���̖��O

#define CAVE_TYOKUSEN	(1)															//���_�̑���Ŏg���A���A�̒[���ǂꂭ�炢�����ɂ��邩�̒l



