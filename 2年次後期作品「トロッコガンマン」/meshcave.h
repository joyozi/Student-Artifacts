//◇-------------------------------------------------------------------------◇
//
//	File	:メッシュケーブヘッダーファイル[meshcave.h]
//	Author	:当摩好弘
//
//◇-------------------------------------------------------------------------◇
void InitMeshCave(void);
void UninitMeshCave(void);
void UpdateMeshCave(void);
void DrawMeshCave(void);

#define CAVE_MESH_POYGON_LENGTH			(35)										//ポリゴンの長さ


//テクスチャ座標に限界があるからバグる
#define CAVE_MESH_TEXTURE_TYOKKEI		(9)										//洞窟の直径のテクスチャ数
#define CAVE_MESH_TEXTURE_NUM_OKULONG	(2000)										//奥行きのテクスチャの数

#define CAVE_MESH_TYOKKEI			(CAVE_MESH_POYGON_LENGTH * CAVE_MESH_TEXTURE_TYOKKEI)				//洞窟の直径
#define CAVE_MESH_OKU_LONG			(CAVE_MESH_POYGON_LENGTH * CAVE_MESH_TEXTURE_NUM_OKULONG)			//洞窟の道の長さ

#define CAVE_MESH_VTX_NUM			((CAVE_MESH_TEXTURE_TYOKKEI + 1) * (CAVE_MESH_TEXTURE_NUM_OKULONG + 1))			//頂点の数　単品
#define CAVE_MESH_POLYGON_NUM		(2 * CAVE_MESH_TEXTURE_NUM_OKULONG * CAVE_MESH_TEXTURE_TYOKKEI + ((CAVE_MESH_TEXTURE_NUM_OKULONG - 1) * 4))	//ポリゴンの数。三角形ポリゴン 透明ポリゴンも含める
#define CAVE_MESH_INDEX_NUM			(CAVE_MESH_POLYGON_NUM + 2)														//頂点インデックスの数 ポリゴンの数＋２

#define CAVE_TEXTURE_FILE ("./data/TEXTURE/wall_001.jpg")							//テクスチャファイルの名前

#define CAVE_TYOKUSEN	(1)															//頂点の代入で使う、洞窟の端をどれくらい直線にするかの値



