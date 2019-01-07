//◇-------------------------------------------------------------------------◇
//
//	File	:メッシュスカイヘッダーファイル[meshsky.h]
//	Author	:当摩好弘
//
//◇-------------------------------------------------------------------------◇
void InitMeshsky(void);
void UninitMeshsky(void);
void UpdateMeshsky(void);
void DrawMeshsky(void);

//#define MESHSKY_DANSUU_NUM		(20)															//何段のメッシュフィールドか これを変えるとポリゴン表示数が変わる

#define MESHSKY_POYGON_WIDTH		(300)															//ポリゴンの横幅
#define MESHSKY_POYGON_HEIGHT		(600)															//ポリゴンの縦幅

#define MESHSKY_DIAMETER			(2000)															//空の横の直径。
#define MESHSKY_HEIGHT				(2000)															//空の高さ	できればMESHSKY_POYGON_HEIGHT*(4の倍数)にしてほしい

#define MESHSKY_YOKO_VTX			((int)(MESHSKY_DIAMETER * D3DX_PI / MESHSKY_POYGON_WIDTH))		//横の頂点の個数。円の大きさ÷ポリゴンの横幅
#define MESHSKY_TATE_VTX			((int)(MESHSKY_HEIGHT / MESHSKY_POYGON_HEIGHT))					//縦の頂点の個数。

#define MESHSKY_VTX_NUM				((MESHSKY_YOKO_VTX + 1) * (MESHSKY_TATE_VTX + 1))				//頂点の数　単品
#define MESHSKY_POLYGON_NUM			(2 * MESHSKY_YOKO_VTX * MESHSKY_TATE_VTX + ((MESHSKY_TATE_VTX - 1) * 4))				//ポリゴンの数。三角形ポリゴン 透明ポリゴンも含める
#define MESHSKY_INDEX_NUM			(MESHSKY_POLYGON_NUM + 2)										//頂点インデックスの数 ポリゴンの数＋２


//#define MESHSKY_POLYGON_NUM_OUT		


