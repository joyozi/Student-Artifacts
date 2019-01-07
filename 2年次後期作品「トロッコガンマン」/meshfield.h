//◇-------------------------------------------------------------------------◇
//
//	File	:メッシュフィールドヘッダーファイル[meshfield.h]
//	Author	:当摩好弘
//
//◇-------------------------------------------------------------------------◇
void InitMeshfield(void);
void UninitMeshfield(void);
void UpdateMeshfield(void);
void DrawMeshfield(void);

//#define MESH_DANSUU_NUM			(200)													//何段のメッシュフィールドか これを変えるとポリゴン表示数が変わる
#define MESH_POYGON_LENGTH		(100)													//ポリゴンの長さ

#define MESH_TEXTURE_OKUNUM			(60)											//テクスチャの奥の枚数
#define MESH_TEXTURE_YOKONUM		(3)												//テクスチャの横の枚数

#define MESH_LENGTH_OKU				(MESH_TEXTURE_OKUNUM * MESH_POYGON_LENGTH)			//地面の奥の長さ
#define MESH_LENGTH_YOKO			(MESH_TEXTURE_YOKONUM * MESH_POYGON_LENGTH)			//地面の横の長さ

#define MESH_VTX_NUM			((MESH_TEXTURE_OKUNUM + 1) * (MESH_TEXTURE_YOKONUM + 1))	//頂点の数　単品
#define MESH_POLYGON_NUM		((2 * MESH_TEXTURE_OKUNUM * MESH_TEXTURE_YOKONUM) + ((MESH_TEXTURE_OKUNUM - 1) * 4))				//ポリゴンの数。三角形ポリゴン 透明ポリゴンも含める
#define MESH_INDEX_NUM			(MESH_POLYGON_NUM + 2)									//頂点インデックスの数 ポリゴンの数＋２


#define TEXTURE_FILE ("./data/TEXTURE/eye_000.png")		//テクスチャファイルの名前

