//◇-------------------------------------------------------------------------◇
//
//	File	:カメラヘッダーファイル[camera.h]
//	Author	:当摩好弘
//
//◇-------------------------------------------------------------------------◇
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);

void SetCamera(void);

D3DXVECTOR3 GetposCamera(void);
D3DXVECTOR3 GetRotCamera(void);
D3DXVECTOR3 GetsclCamera(void);

D3DXMATRIX GetMtxView(void);

#define CAMERA_LONG		(3000.0f)		//カメラでみえる最高距離 前後合わせるとこれの二倍

