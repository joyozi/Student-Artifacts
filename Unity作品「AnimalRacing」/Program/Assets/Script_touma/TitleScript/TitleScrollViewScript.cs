using UnityEngine;
using System.Collections;

public class TitleScrollViewScript : MonoBehaviour {

	//コンポーネントのcontent size fitterが邪魔なので消すかもしれない

	public int PaddingLeft;
	public int PaddingRight;
	public int PaddingSpacing;
	public int ButtonSizeX;

	public float ScrollSetTime = 0.5f;

	private int StageNum;
	private int NowStageFocused;

	private Vector2 ScrollViewPosition;				//画面の左のはじっこの値

	private float ScrollView_TouchEnabledPosX;		//タッチが話された場所の位置の保存
	private float ScrollSetTimeCnt;

	// Use this for initialization
	void Start () {

		//ステージ数と名前の取得
		StageNum = int.Parse(GameObject.FindWithTag ("GameInfo").GetComponent<GameInfo> ().GetGameInfoData ((int)(GAMEINFOLIST.INFO_STAGENUM)));
		NowStageFocused = int.Parse(GameObject.FindWithTag ("GameInfo").GetComponent<GameInfo> ().GetGameInfoData ((int)(GAMEINFOLIST.INFO_SELECTEDSTAGE)));

		//初期位置に配置
		ScrollViewPosition = transform.localPosition;

		if (NowStageFocused == 0) {
			ScrollViewPosition.x = -(PaddingLeft + (ButtonSizeX / 2));
		}
		else {
			ScrollViewPosition.x = -(PaddingLeft + (ButtonSizeX * NowStageFocused) + (PaddingSpacing / 2) * (1 + (NowStageFocused - 1) * 2) + (PaddingSpacing + ButtonSizeX) / 2);
		}

		ScrollView_TouchEnabledPosX = ScrollViewPosition.x;
		transform.localPosition = ScrollViewPosition;

	}



	// Update is called once per frame
	void Update () {
		//transformの値がどこをとってもrecttransformと同じ数値がでないので、
		//それと関係性のある値によるごり押しの処理

//		Debug.Log(GetComponent<RectTransform>().rect.position.x.ToString() + "before");
//		Debug.Log (GetComponent<RectTransform> ().transform.position.x.ToString());
//		Debug.Log (GetComponent<RectTransform> ().localPosition.x.ToString());			//←採用
//		Debug.Log (GetComponent<RectTransform> ().rect.position.x.ToString());
//		Debug.Log (GetComponent<RectTransform> ().position.x.ToString());
//		Debug.Log (transform.position.x.ToString());
//		Debug.Log (GameObject.Find("Vertical").transform.position.x.ToString());



		ScrollViewPosition = transform.localPosition;




		//ボタンが一個しかなかった場合のことは考えません！

		for(int i = 0;i < StageNum;i++){
			//静止した時にどっかの範囲内だったら

			//ボタンとボタンの間だったら
			if(i >= 1 && i < StageNum - 1 && 
			   -(PaddingLeft + (ButtonSizeX * i) + (PaddingSpacing / 2) * (1 + (i - 1) * 2)) >= ScrollViewPosition.x && 
			   -(PaddingLeft + (ButtonSizeX * (i + 1)) + (PaddingSpacing / 2) * (1 + i * 2)) <= ScrollViewPosition.x){

				//もしタッチがされてなかったら
				if(Input.GetMouseButton(0) == false){
						ScrollSetTimeCnt += 1.0f * Time.deltaTime;
						ScrollViewPosition.x = Mathf.Lerp(ScrollView_TouchEnabledPosX,
														-(PaddingLeft + (ButtonSizeX * i) + (PaddingSpacing / 2) * (1 + (i - 1) * 2) + (PaddingSpacing + ButtonSizeX) / 2),
						                                  ScrollSetTimeCnt / ScrollSetTime);

						transform.localPosition = ScrollViewPosition;
				}
				else{
					ScrollSetTimeCnt = 0.0f;
					ScrollView_TouchEnabledPosX = ScrollViewPosition.x;
				}
				NowStageFocused = i;
			}
			//左端だった場合
			else if(i == 0 && 
			        -(PaddingLeft + (ButtonSizeX * 1) + (PaddingSpacing / 2) * (1)) <= ScrollViewPosition.x){

				//もしタッチがされてなかったら
				if(Input.GetMouseButton(0) == false){
						ScrollSetTimeCnt += 1.0f * Time.deltaTime;
						ScrollViewPosition.x = Mathf.Lerp(ScrollView_TouchEnabledPosX,
						                                  -(PaddingLeft + ButtonSizeX / 2),
						                                  ScrollSetTimeCnt / ScrollSetTime);
					
						transform.localPosition = ScrollViewPosition;
				}
				else{
					ScrollSetTimeCnt = 0.0f;
					ScrollView_TouchEnabledPosX = ScrollViewPosition.x;
				}
				NowStageFocused = i;
			}
			//みぎはじだったばあい
			else if(i == StageNum - 1 && 
			        -(PaddingLeft + (ButtonSizeX * i) + (PaddingSpacing / 2) * (1 + (i - 1) * 2)) >= ScrollViewPosition.x){

				//もしタッチがされてなかったら
				if(Input.GetMouseButton(0) == false){
						ScrollSetTimeCnt += 1.0f * Time.deltaTime;
						ScrollViewPosition.x = Mathf.Lerp(ScrollView_TouchEnabledPosX,
						                                  -(PaddingLeft + (ButtonSizeX * i) + (PaddingSpacing / 2) * (1 + (i - 1) * 2) + (ButtonSizeX + PaddingSpacing) / 2),
							                                  ScrollSetTimeCnt / ScrollSetTime);
					
						transform.localPosition = ScrollViewPosition;
				}
				else{
					ScrollSetTimeCnt = 0.0f;
					ScrollView_TouchEnabledPosX = ScrollViewPosition.x;
				}
				NowStageFocused = i;
			}
		}
	}



	public int StageFocusedNum(){
		return NowStageFocused;
	}
}

/*
	public void StageScrollButton_L(){
		NowStageFocused--;

		if(NowStageFocused < 0){
			NowStageFocused = StageNum - 1;
		}

		ScrollViewPosition.x = -(PaddingLeft + (ButtonSizeX * NowStageFocused) + (PaddingSpacing / 2) * (1 + (NowStageFocused - 1) * 2) + (PaddingSpacing + ButtonSizeX) / 2);
		ScrollView_TouchEnabledPosX = ScrollViewPosition.x;
		transform.localPosition = ScrollViewPosition;
	}

	public void StageScrollButton_R(){
		NowStageFocused++;
				
		if (NowStageFocused >= StageNum) {

			NowStageFocused = 0;
		}

		ScrollViewPosition.x = -(PaddingLeft + (ButtonSizeX * NowStageFocused) + (PaddingSpacing / 2) * (1 + (NowStageFocused - 1) * 2) + (PaddingSpacing + ButtonSizeX) / 2);
		ScrollView_TouchEnabledPosX = ScrollViewPosition.x;
		transform.localPosition = ScrollViewPosition;
	}
}

*/



