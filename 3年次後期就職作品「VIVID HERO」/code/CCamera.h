//◇-------------------------------------------------------------------------◇
//
//	File:CCameraのヘッダーファイル[CCamera.h]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇
#ifndef _CAMERA_A_H_
#define _CAMERA_A_H_

//◇-----------------------------------◇
//インクルードファイル
//◇-----------------------------------◇
#include "main.h"
#include "CItemList.h"

//◇-----------------------------------◇
//クラス設計
//◇-----------------------------------◇
class CCamera
{
public:
	CCamera();
	virtual ~CCamera();
	
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Set(void);
	
	virtual D3DXMATRIX GetMtxView(void);
	virtual void CameraMovePPlus(D3DXVECTOR3 PlusPos);
	virtual void CameraMovePPlus(float x,float y,float z);
	virtual void CameraMovePSet(D3DXVECTOR3 SetPos);
	virtual void CameraMovePSet(float x,float y,float z);
	virtual void CameraMoveRPlus(D3DXVECTOR3 PlusPos);		//数値を加算する
	virtual void CameraMoveRPlus(float x,float y,float z);		//数値を加算する
	virtual void CameraMoveRSet(D3DXVECTOR3 SetPos);			//数値をそのまま代入する
	virtual void CameraMoveRSet(float x,float y,float z);		//数値をそのまま代入する
	
	virtual D3DXVECTOR3 GetCameraP(void);
	virtual D3DXVECTOR3 GetCameraR(void);

	virtual D3DXVECTOR3 GetRotationP(void){return D3DXVECTOR3(0.0f,atan2f(m_posCameraP.z - m_posCameraR.z,m_posCameraP.x - m_posCameraR.x),0.0f);}

	virtual D3DXVECTOR3 GetCameraVector(void);

	virtual void SetCameraResultAdjustment(D3DXVECTOR3 Ajdust){}
	virtual D3DXVECTOR3 GetCameraResultAdjustment(){return D3DXVECTOR3(0.0f,0.0f,0.0f);}


	virtual D3DXVECTOR3 GetCameraPosition(){return m_posCamera;}
	virtual D3DXVECTOR3 GetCameraRotation(){return m_rotCamera;}

	virtual float GetCameraRotationY(){
		return CItemList::VecAngle_2DSimple(m_posCameraR - m_posCameraP);
	}


protected:
	D3DXVECTOR3 m_posCamera;					//位置
	D3DXVECTOR3 m_rotCamera;					//向き
	D3DXVECTOR3 m_sclCamera;					//大きさ（基本変えない）
	D3DXVECTOR3 m_posCameraP;					//カメラの視点
	D3DXVECTOR3 m_posCameraR;					//カメラの注視点
	D3DXVECTOR3 m_posCameraU;					//カメラの上方向ベクトル

	D3DXMATRIX m_mtxProjection;					//プロジェクションマトリックス
	D3DXMATRIX m_mtxView;						//ビューマトリックス
	D3DXMATRIX m_mtxWorld;						//ワールドマトリックス

	D3DXVECTOR3 m_CameraVec;
};



#endif





