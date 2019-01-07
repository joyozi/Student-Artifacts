using UnityEngine;
using System.Collections;
	
public class title : MonoBehaviour
{
	public float TitleLogoDistanceUp;		//タイトルロゴの上との差
	public float TitleLogoMoveTime;			//タイトルロゴの何秒で上につくかの数値

	private GameObject TitleLogoObj;		//obj
	private Vector3 TitleLogoPos;			//動かす値の入れ子
	private bool PushStartMotion;			//最初にタッチした時の判定
	private bool PushStageSelect;
	private float TitleUpDistance;			//タイトルの上までの距離の保管数値
	private float MoveY;					//1秒間に動く距離みたいな

	private GameObject GameInfoObj;

	void Awake(){
		//画面の傾きによる画面の回転を操作する実験
		Screen.orientation = ScreenOrientation.Portrait;
	}

	void Start ()
	{
		//  BGM再生(タイトルBGM)
		AudioManager.Instance.PlayBGM("[bgm]title");


		GameInfoObj = GameObject.FindWithTag ("GameInfo");


		//メニューを移さない
		GameObject.Find("TitleMenu").SetActive (false);

		TitleLogoObj = GameObject.Find("TitleLogo");

		TitleUpDistance = (Screen.height - TitleLogoDistanceUp) - TitleLogoObj.transform.position.y;
		MoveY = TitleUpDistance / TitleLogoMoveTime;
	}
	
	void Update ()
	{
		//マウスの左ボタンをクリック
		if (Input.GetMouseButtonUp (0))
		{
			//  SE再生(メニュープッシュ音)
			AudioManager.Instance.PlaySE("[se]menu");

			PushStartMotion = true;
		}


		//既読か未読かの判定
		if (GameInfoObj.GetComponent<GameInfo> ().GetGameInfoData ((int)(GAMEINFOLIST.INFO_TITLEREADED)) == "0") {

			if (PushStartMotion) {
				if (TitleLogoObj.transform.position.y < Screen.height - TitleLogoDistanceUp) {

					TitleLogoPos.y = MoveY * Time.deltaTime;
					TitleLogoObj.transform.position += TitleLogoPos;			
				}

				//上のif分んに当てはまらなかったり、ロゴが上に飛び行かないように
				if (TitleLogoObj.transform.position.y >= Screen.height - TitleLogoDistanceUp) {
					{	//文字が移動を完了したら
						TitleLogoPos.x = TitleLogoObj.transform.position.x;				//x軸を無理やり保存
						TitleLogoPos.y = Screen.height - TitleLogoDistanceUp;		//
						TitleLogoObj.transform.position = TitleLogoPos;
						PushStageSelect = true;



						//読みましたと教える
						GameInfoObj.GetComponent<GameInfo> ().SetGameInfoData ((int)(GAMEINFOLIST.INFO_TITLEREADED),"1");
					}
				}
			}
		} else {
			TitleLogoPos.x = TitleLogoObj.transform.position.x;				//x軸を無理やり保存
			TitleLogoPos.y = Screen.height - TitleLogoDistanceUp;		//
			TitleLogoObj.transform.position = TitleLogoPos;
			PushStageSelect = true;
		}



		if (PushStageSelect) {
			//ボタンを呼び出す
			foreach (Transform child in GameObject.Find("Canvas_ToumaTitle").transform) {
				// 子の要素をたどる
				if(child.name == "TitleMenu") {
					// 指定した名前と一致
					// 表示フラグを設定
					child.gameObject.SetActive(PushStageSelect);
					// おしまい
					return;
				}
			}
		}
	}
}
