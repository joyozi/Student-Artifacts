//◇-------------------------------------------------------------------------◇
//
//	File	:	hitCheckファイル[hitcheck.cpp]
//	Author	:	touma yoshihiro
//
//◇-------------------------------------------------------------------------◇
#include "main.h"
#include "CHitCheck.h"

//◇-------------------------------------------------------------------------◇
// 内積
// Contents : 2次元での内積の計算
//◇-------------------------------------------------------------------------◇
float CHitCheck::dotProduct( D3DXVECTOR3 vl, D3DXVECTOR3 vr)
{
	float ans = 0;					//答えのいれる変数

	//vrのほうの底辺を求める
#if 1
	ans = vl.x * vr.x + vl.y * vr.y + vl.z * vr.z;

#else
	ans = D3DXVec3Dot(&vl,&vr);

#endif

	//答えを返す
	return(ans);


}


//◇-------------------------------------------------------------------------◇
// 外積
// Contents : 3Dの外積計算。ポリゴンの向き(法線ベクトル)を求める
//◇-------------------------------------------------------------------------◇
D3DXVECTOR3 CHitCheck::crossProduct( D3DXVECTOR3 vl, D3DXVECTOR3 vr )
{
	D3DXVECTOR3 ret;

#if 1
	ret.x = vl.y * vr.z - vl.z * vr.y;
	ret.y = vl.z * vr.x - vl.x * vr.z;
	ret.z = vl.x * vr.y - vl.y * vr.x;

#else
	D3DXVec3Cross(&ret,&vl,&vr);

#endif

	//求めたベクトル法線を返す
	return(ret);
}


//◇-------------------------------------------------------------------------◇
// ポリゴンと線分との当たり判定（ガチ版）
// p0  :ポリゴンの頂点1
// p1  :ポリゴンの頂点2
// p2  :ポリゴンの頂点3
// pos0:線分の始点（移動前座標）
// pos1:線分の終点（移動後座標）
//◇-------------------------------------------------------------------------◇
int CHitCheck::HitCheck( D3DXVECTOR3 p0, D3DXVECTOR3 p1, D3DXVECTOR3 p2, D3DXVECTOR3 pos0, D3DXVECTOR3 pos1 )
{
	D3DXVECTOR3 nor;								// ポリゴンの法線

	{
		D3DXVECTOR3 vec01 = p1 - p0;
		D3DXVECTOR3 vec02 = p2 - p0;

		// ポリゴンの外積をとって法線を求めておく
		nor = crossProduct(vec01,vec02);


		//法線ベクトルの正規化
		D3DXVec3Normalize(&nor,&nor);
	}


	{	// ①平面と線分の内積をとって衝突している可能性を調べる
		// 求めた法線とベクトル２つ（線分の両端とポリゴン上の任意の点）の
		// 内積をとって衝突している可能性を調べる

		D3DXVECTOR3 vec1 = pos0 - p0;
		D3DXVECTOR3 vec2 = pos1 - p0;

		float a = dotProduct(vec1,nor);
		float b = dotProduct(vec2,nor);

		if((a * b) > 0)
		{	// 結果当たっていなかったら終了
		
			// 当たっている可能性は無い
			return(0);
		}
	}

	{	// ②ポリゴンと線分の交点を求める
		D3DXVECTOR3 vec1 = pos0 - p0;
		D3DXVECTOR3 vec2 = pos1 - p0;

		//内分差を求める
		float comp_d1 = fabs(dotProduct(nor,vec1));
		float comp_d2 = fabs(dotProduct(nor,vec2));

		float comp_a = comp_d1 / (comp_d1 + comp_d2);

#if 1
		D3DXVECTOR3 vec3 = (1- comp_a) * vec1 + comp_a * vec2;
		D3DXVECTOR3 p3 = p0 + vec3;

#else
		D3DXVECTOR3 vec3 = pos1 - pos0;
		D3DXVECTOR3 p3 = pos0 + (vec3 * comp_a);
#endif

		D3DXVECTOR3 v1 = p1 - p0;
		D3DXVECTOR3 v2 = p2 - p1;
		D3DXVECTOR3 v3 = p0 - p2;
		D3DXVECTOR3 v4 = p3 - p1;
		D3DXVECTOR3 v5 = p3 - p2;
		D3DXVECTOR3 v6 = p3 - p0;

		D3DXVECTOR3 n1 = crossProduct(v1,v4);
		D3DXVECTOR3 n2 = crossProduct(v2,v5);
		D3DXVECTOR3 n3 = crossProduct(v3,v6);

#if 1
		if(dotProduct(n1,nor) < 0) return (0);
		if(dotProduct(n2,nor) < 0) return (0);
		if(dotProduct(n3,nor) < 0) return (0);

#else
		if(dotProduct(n1,n2) < 0) return (0);
		if(dotProduct(n2,n3) < 0) return (0);

#endif

	}
	
	// すべてに該当していなかったら当たってるので1を返す
	return(1);
}

//◇-------------------------------------------------------------------------◇
// ポリゴンと線分との交点
// p0  :ポリゴンの頂点1
// p1  :ポリゴンの頂点2
// p2  :ポリゴンの頂点3
// pos0:線分の始点（移動前座標）
// pos1:線分の終点（移動後座標）
//◇-------------------------------------------------------------------------◇
D3DXVECTOR3 CHitCheck::HitIntersection( D3DXVECTOR3 p0, D3DXVECTOR3 p1, D3DXVECTOR3 p2, D3DXVECTOR3 pos0, D3DXVECTOR3 pos1 )
{
	D3DXVECTOR3 nor;								// ポリゴンの法線

	{
		D3DXVECTOR3 vec01 = p1 - p0;
		D3DXVECTOR3 vec02 = p2 - p0;

		// ポリゴンの外積をとって法線を求めておく
		nor = crossProduct(vec01,vec02);


		//法線ベクトルの正規化
		D3DXVec3Normalize(&nor,&nor);
	}


	{	// ①平面と線分の内積をとって衝突している可能性を調べる
		// 求めた法線とベクトル２つ（線分の両端とポリゴン上の任意の点）の
		// 内積をとって衝突している可能性を調べる

		D3DXVECTOR3 vec1 = pos0 - p0;
		D3DXVECTOR3 vec2 = pos1 - p0;

		float a = dotProduct(vec1,nor);
		float b = dotProduct(vec2,nor);

		if((a * b) > 0)
		{	// 結果当たっていなかったら終了
		
			// 当たっている可能性は無い
			return D3DXVECTOR3(0.0f,0.0f,0.0f);
		}
	}

	{	// ②ポリゴンと線分の交点を求める
		D3DXVECTOR3 vec1 = pos0 - p0;
		D3DXVECTOR3 vec2 = pos1 - p0;

		//内分差を求める
		float comp_d1 = fabs(dotProduct(nor,vec1));
		float comp_d2 = fabs(dotProduct(nor,vec2));

		float comp_a = comp_d1 / (comp_d1 + comp_d2);

#if 1
		D3DXVECTOR3 vec3 = (1- comp_a) * vec1 + comp_a * vec2;
		D3DXVECTOR3 p3 = p0 + vec3;

#else
		D3DXVECTOR3 vec3 = pos1 - pos0;
		D3DXVECTOR3 p3 = pos0 + (vec3 * comp_a);
#endif

		D3DXVECTOR3 v1 = p1 - p0;
		D3DXVECTOR3 v2 = p2 - p1;
		D3DXVECTOR3 v3 = p0 - p2;
		D3DXVECTOR3 v4 = p3 - p1;
		D3DXVECTOR3 v5 = p3 - p2;
		D3DXVECTOR3 v6 = p3 - p0;

		D3DXVECTOR3 n1 = crossProduct(v1,v4);
		D3DXVECTOR3 n2 = crossProduct(v2,v5);
		D3DXVECTOR3 n3 = crossProduct(v3,v6);

#if 1
		if(dotProduct(n1,nor) < 0) return (p3);
		if(dotProduct(n2,nor) < 0) return (p3);
		if(dotProduct(n3,nor) < 0) return (p3);

#else
		if(dotProduct(n1,n2) < 0) return (0);
		if(dotProduct(n2,n3) < 0) return (0);

#endif

	}
	
	// すべてに該当していなかったら当たってるので1を返す
	return D3DXVECTOR3(0.0f,0.0f,0.0f);
}

//◇-------------------------------------------------------------------------◇
// ポリゴンと物体の設置しているときのY軸
//Player_Pos	: プレイヤーとかの位置
//Polygon_Pos0	: 計算したいポリゴンの３頂点のうちのどれか一つ
//Polygon_Nor	: ポリゴンの法線。あれば
//◇-------------------------------------------------------------------------◇
float CHitCheck::ConnectYVertex(const D3DXVECTOR3 Player_Pos,const D3DXVECTOR3 Polygon_Pos0,const D3DXVECTOR3 Polygon_Nor)
{
	float VtxY;

	VtxY = (- (Player_Pos.x - Polygon_Pos0.x) * Polygon_Nor.x
			- (Player_Pos.z - Polygon_Pos0.z) * Polygon_Nor.z)
			/ Polygon_Nor.y + Polygon_Pos0.y;


	return VtxY;
}

//◇-------------------------------------------------------------------------◇
// ポリゴンと物体の設置しているときのY軸　その２
//Player_Pos		: プレイヤーとかの位置
//Polygon_Pos0,1,2	: 計算したいポリゴンの３頂点
//◇-------------------------------------------------------------------------◇
float CHitCheck::ConnectYVertex(const D3DXVECTOR3 Player_Pos,const D3DXVECTOR3 Polygon_Pos0,const D3DXVECTOR3 Polygon_Pos1,const D3DXVECTOR3 Polygon_Pos2)
{
	float VtxY;

	D3DXVECTOR3 Vec01 = Polygon_Pos1 - Polygon_Pos0;
	D3DXVECTOR3 Vec02 = Polygon_Pos2 - Polygon_Pos0;

	// ポリゴンの外積をとって法線を求めておく
	D3DXVECTOR3 Nor = crossProduct(Vec01,Vec02);


	VtxY = (- (Player_Pos.x - Polygon_Pos0.x) * Nor.x
			- (Player_Pos.z - Polygon_Pos0.z) * Nor.z)
			/ Nor.y + Polygon_Pos0.y;


	return VtxY;
}
