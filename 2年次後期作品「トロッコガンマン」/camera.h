//��-------------------------------------------------------------------------��
//
//	File	:�J�����w�b�_�[�t�@�C��[camera.h]
//	Author	:�����D�O
//
//��-------------------------------------------------------------------------��
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);

void SetCamera(void);

D3DXVECTOR3 GetposCamera(void);
D3DXVECTOR3 GetRotCamera(void);
D3DXVECTOR3 GetsclCamera(void);

D3DXMATRIX GetMtxView(void);

#define CAMERA_LONG		(3000.0f)		//�J�����ł݂���ō����� �O�㍇�킹��Ƃ���̓�{

