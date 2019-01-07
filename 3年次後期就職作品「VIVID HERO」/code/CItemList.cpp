//◇---------------------------- ---------------------------------------------◇
//
//	File:CItemListのファイル[CItemList.cpp]
//	Author:当摩好弘
//
//◇-------------------------------------------------------------------------◇

//◇-------------------------------------------------------------------------◇
//インクルードファイル
//◇-------------------------------------------------------------------------◇
#include "CItemList.h"
#include "CHitCheck.h"
#include "input.h"
#include "CCamera.h"

//◇-------------------------------------------------------------------------◇
//静的メンバ変数の初期化
//◇-------------------------------------------------------------------------◇

//◇-----------------------------------◇
//子ベクトルから親ベクトルの位置を元に戻すみたいな
//◇-----------------------------------◇
D3DXVECTOR3 CItemList::MatrixTruePos(int num,...)
{
	D3DXVECTOR3		 ans				 = D3DXVECTOR3(0.0f,0.0f,0.0f);
	D3DXVECTOR3		 Vector3list		 = D3DXVECTOR3(0.0f,0.0f,0.0f);
	va_list			 list;

	va_start(list,num);

	for(int i = 0;i < num;i++)
	{
		ans += va_arg(list,D3DXVECTOR3);
	}

	va_end(list);

	return ans;
}

//◇-----------------------------------◇
//リャープ
//◇-----------------------------------◇
float CItemList::lerp(float FromA,float ToB,float Time)
{
	return (ToB - FromA) * Time + FromA;
}

//◇-----------------------------------◇
//D3DXVECTOR3のリャープ
//◇-----------------------------------◇
D3DXVECTOR3 CItemList::Vec3lerp(D3DXVECTOR3 FromA,D3DXVECTOR3 ToB,float Time)
{
	return D3DXVECTOR3(
	CItemList::lerp(FromA.x,ToB.x,Time),
	CItemList::lerp(FromA.y,ToB.y,Time),
	CItemList::lerp(FromA.z,ToB.z,Time));
}

//◇-----------------------------------◇
//２つのベクトルABのなす角度θを求める
//◇-----------------------------------◇
float CItemList::AngleOf2Vector(D3DXVECTOR3 A, D3DXVECTOR3 B )
{
	//ベクトルAとBの長さを計算する
	float length_A = D3DXVec3Length(&A);
	float length_B = D3DXVec3Length(&B);

	//内積とベクトル長さを使ってcosθを求める
	float cos_sita = CHitCheck::dotProduct(A,B) / ( length_A * length_B );

	//cosθからθを求める
	float sita = acos( cos_sita );	

	return sita;
}


//◇-----------------------------------◇
//角度の調整
//◇-----------------------------------◇
float CItemList::RotationOptisitacion(float Rot)
{
	if(Rot < -D3DX_PI)
	{
		Rot += D3DX_PI * 2;
	}
	else if(Rot > D3DX_PI)
	{
		Rot += -D3DX_PI * 2;
	}

	return Rot;
}

//◇-----------------------------------◇
//角度の調整その2
//◇-----------------------------------◇
float CItemList::RotationOptisitacion(float ChangeRot,float Rot)
{
	float Diffse = ChangeRot - Rot;

	if(Diffse < -D3DX_PI)
	{
		ChangeRot += D3DX_PI * 2;
	}
	else if(Diffse > D3DX_PI)
	{
		ChangeRot += -D3DX_PI * 2;
	}

	return ChangeRot;
}

//◇-----------------------------------◇
//角度の追加の計算
//◇-----------------------------------◇
void CItemList::AddPosition(D3DXVECTOR3 &vec3Pos, D3DXVECTOR3 vec3Move, CCamera* pCamera)
{
	// 平行移動
	float fSinParam = sinf(pCamera->GetRotationP().y + (D3DX_PI / 2));
	float fCosParam = cosf(pCamera->GetRotationP().y + (D3DX_PI / 2));
	D3DXVECTOR3 vecTempMove = D3DXVECTOR3(0.0f, vec3Move.y, 0.0f);
	vecTempMove.x = (vec3Move.x * fCosParam) - (vec3Move.z * fSinParam);
	vecTempMove.z = (vec3Move.x * fSinParam) + (vec3Move.z * fCosParam);

	vec3Pos = vec3Pos + vecTempMove;
};

//◇----------------------------------◇
// 二点間の距離を求める
//◇----------------------------------◇
float CItemList::GetLength(D3DXVECTOR3 vec3A, D3DXVECTOR3 vec3B)
{
	return powf((vec3B.x - vec3A.x)*(vec3B.x - vec3A.x) + (vec3B.y - vec3A.y)*(vec3B.y - vec3A.y) + (vec3B.z - vec3A.z)*(vec3B.z - vec3A.z), 0.5f);
};

//◇----------------------------------◇
//一つのベクトルの長さを求める
//◇----------------------------------◇
float CItemList::GetLengthSimple(D3DXVECTOR3 vec3)
{
	return powf(( vec3.x * vec3.x ) + ( vec3.y * vec3.y ) + ( vec3.z * vec3.z ), 0.5f );
}

//◇----------------------------------◇
// 波動処理
//◇----------------------------------◇
float CItemList::WaveHeight(D3DXVECTOR3 vecBeginWavePos, D3DXVECTOR3& vecPos, float fFrame, float fFrequency, float fDisstanceColl, float fAmplitude)
{
	float fLen = sqrtf(((vecPos.x - vecBeginWavePos.x) * (vecPos.x - vecBeginWavePos.x))
						+((vecPos.z - vecBeginWavePos.z) * (vecPos.z - vecBeginWavePos.z)));

	vecPos.y = sinf(-fFrame * fFrequency + fLen * fDisstanceColl) * fAmplitude;

	return vecPos.y;
}

//◇-----------------------------------◇
//ラジアンから角度に変換
//◇-----------------------------------◇
float CItemList::ConvDegree(float fRad)
{
	return fRad * 180 / D3DX_PI;
}

//◇-----------------------------------◇
//角度からラジアンに変換
//◇-----------------------------------◇
float CItemList::ConvRadian(float fDeg)
{
	return fDeg * D3DX_PI / 180;
}

//◇-----------------------------------◇
//ソート関数
//◇-----------------------------------◇
void CItemList::SortNumber(float *pSub,int Kazu)
{
	float *pCmpPos = new float[Kazu];
	int *CmpNumber = new int[Kazu];

	int MinNum;
	float Temp;

	for(int i = 0;i < Kazu;i++)
	{
		MinNum = i;

		for(int j = i + 1;j < Kazu;j++)
		{
			if(pSub[MinNum] > pSub[j])MinNum = j;
		}

		Temp = pSub[MinNum]; //最小添字min と添字i の配列n[ ] の値を交換する
		pSub[MinNum] = pSub[i];
		pSub[i] = Temp;
	}
}

//◇-----------------------------------◇
//2つのベクトルの角度を求める計算。3Dばん
//◇-----------------------------------◇
float CItemList::VecAngle_3D(D3DXVECTOR3 VecA,D3DXVECTOR3 VecB)
{
	//ベクトルAとBの長さを計算する
	float length_A = GetLengthSimple(VecA);
	float length_B = GetLengthSimple(VecB);

	//内積とベクトル長さを使ってcosθを求める
	float cos_sita;

	if(length_A == 0.0f)
		cos_sita = CHitCheck::dotProduct(VecA,VecB) / ( length_B );

	else if(length_B == 0.0f)
		cos_sita = CHitCheck::dotProduct(VecA,VecB) / ( length_A );

	else
		cos_sita = CHitCheck::dotProduct(VecA,VecB) / ( length_A * length_B );


	//cosθからθを求める
	float sita = acosf( cos_sita );

	return sita;
}

//◇-----------------------------------◇
//2つのベクトルの角度を求める計算。2Dばん
//◇-----------------------------------◇
float CItemList::VecAngle_2D(D3DXVECTOR3 VecA,D3DXVECTOR3 VecB)
{
	//ベクトルAとBの長さを計算する
	float length_A = GetLengthSimple(VecA);
	float length_B = GetLengthSimple(VecB);

	//内積とベクトル長さを使ってcosθを求める
	float cos_sita = CHitCheck::dotProduct(VecA,VecB) / ( length_A * length_B );

	float a = CHitCheck::dotProduct(VecA,VecB);

	//cosθからθを求める
	float sita = acosf( cos_sita );

	return sita;
}

//◇-----------------------------------◇
//2つのベクトルの角度を求める計算。2Dばんその２
//◇-----------------------------------◇
float CItemList::VecAngle_2D(float VecA_X,float VecA_Y,float VecB_X,float VecB_Y)
{
	//　※ベクトルの長さが0だと答えが出ませんので注意してください。

	D3DXVECTOR3 PosA = D3DXVECTOR3(VecA_X,0.0f,VecA_Y);
	D3DXVECTOR3 PosB = D3DXVECTOR3(VecB_X,0.0f,VecB_Y);

	//ベクトルAとBの長さを計算する
	float length_A = GetLengthSimple(PosA);
	float length_B = GetLengthSimple(PosB);

	//内積とベクトル長さを使ってcosθを求める
	float cos_sita = CHitCheck::dotProduct(PosA,PosB) / ( length_A * length_B );

	//cosθからθを求める
	float sita = acosf( cos_sita );

	return sita;
}

//◇-----------------------------------◇
//ベクトルのＹ軸の角度の計算用関数
//D3DXVECTOR3(0.0f,0.0f,1.0f);を基準にして角度を決める
//3DゲームとしてXZ軸で角度を求めるからD3DXVECTOR3にいい感じに入れないといけない
//◇-----------------------------------◇
float CItemList::VecAngle_2DSimple(D3DXVECTOR3 Vec)
{
	D3DXVECTOR3 PosA = D3DXVECTOR3(Vec.x,0.0f,Vec.z);
	D3DXVECTOR3 PosB = D3DXVECTOR3(0.0f,0.0f,1.0f);

	//ベクトルAとBの長さを計算する
	float length_A = GetLengthSimple(PosA);
	float length_B = 1.0f;

	//エラー回避用
	if(PosA == PosB || length_A == 0.0f)
		return 0.0f;

	if(Vec.x == 0.0f)
	{
		if(Vec.z >= 0.0f)
			return 0.0f;
		else
			return D3DX_PI;
	}

	//内積とベクトル長さを使ってcosθを求める
	float cos_sita = CHitCheck::dotProduct(PosA,PosB) / ( length_A * length_B );

	//cosθからθを求める
	float sita = acosf( cos_sita );

	if(Vec.x >= 0.0f)
		return sita;
	else
		return -sita;

	return 0.0f;
}

//◇-----------------------------------◇
//ベクトルのX角度とY角度の計算関数
//◇-----------------------------------◇
D3DXVECTOR3 CItemList::VecAngle_3D_D3DX(D3DXVECTOR3 Vec)
{
	D3DXVECTOR3 Answer = D3DXVECTOR3(0.0f,0.0f,Vec.z);

	D3DXVECTOR3 VecA;
	D3DXVECTOR3 VecB;
	
	float length_A;
	float length_B;
	
	float cos_sita;

	//エラー回避のため
	if(Vec.y <= -0.0001f || Vec.y >= 0.0001f)
	{
		VecA = D3DXVECTOR3(0.0f,Vec.y,0.0f);
		VecB = D3DXVECTOR3(Vec.x,0.0f,Vec.z);



		length_A = GetLengthSimple(VecA);
		length_B = GetLengthSimple(VecB);

		cos_sita = atan2f(length_A,length_B);

		if(Vec.y >= 0.0f)
			Answer.x = cos_sita;//acosf( cos_sita );
		else
			Answer.x = -cos_sita;//acosf( cos_sita );
	}
	else
	{
		Answer.x = 0.0f;
	}

	//Y軸の角度
	VecA = D3DXVECTOR3(Vec.x,0.0f,Vec.z);
	VecB = D3DXVECTOR3(0.0f,0.0f,1.0f);

	Answer.y = VecAngle_2DSimple(VecA);

	return Answer;
}
