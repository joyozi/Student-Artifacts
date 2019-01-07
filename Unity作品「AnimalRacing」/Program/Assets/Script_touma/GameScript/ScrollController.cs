using UnityEngine;
using System.Collections;

public class ScrollController : MonoBehaviour {

	//３Dのマップを２Dのテクスチャに反映させるから,
	//Vector2とVector3がごちゃ混ぜで面倒くさい!
	//あとミニマップがローカル変数とかでごちゃごちゃ
	//マップの中心点がこれだけ下だったりしてごちゃごちゃ


	private Vector3 PlayerPos_Interpolation;	//プレイヤーの初期位置の補間場所
	private Vector3 PlayerPos;

	private Vector2 MiniMapPlayerIconPos;
	private Vector2 AddMap;

	private GameObject PlayerObj;



	public GameObject MiniMapObj;
	public GameObject PlayerIconObj;

	public Vector2 MiniMapTextureSize;
	public Vector3 MapSize;
	public float PlayerIconAdjustmentY;			//ミニマップのアイコンの下からの位置の調整

	//クズマップとのズレの調整をこれで行う
	public float IconNormalDistanceX;			//初期位置のX軸の調整
	public float IconNormalDistanceZ;			//初期位置のZ軸の調整
	public float IconNormalLRReduction;			//アイコンの左右位置の動くとどれだけ行けるかの調整

	void Start ()
	{
		PlayerObj = GameObject.FindWithTag("Player");
		PlayerPos_Interpolation = PlayerObj.transform.position;
	}

	void Update(){
		PlayerPos = PlayerObj.transform.position - PlayerPos_Interpolation;

		AddMap = new Vector2(0.0f,0.0f);
		AddMap.y = - ( MiniMapTextureSize.y * (((PlayerPos.z) / MapSize.z))) + PlayerIconAdjustmentY; 

		MiniMapObj.transform.localPosition = AddMap;

		//ミニマップのローカルだから調整数値は加算しない
		AddMap.x = ( (MiniMapTextureSize.x + IconNormalLRReduction) * (((PlayerPos.x) / MapSize.x))) + IconNormalDistanceX; 
		AddMap.y = ( MiniMapTextureSize.y * ((((PlayerPos.z + IconNormalDistanceZ)) / MapSize.z)));

		PlayerIconObj.transform.localPosition = AddMap;
	}
}






