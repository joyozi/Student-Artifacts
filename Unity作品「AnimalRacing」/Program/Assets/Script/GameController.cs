using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class GameController : MonoBehaviour {

	//ゲームの現在の状態
	enum GameState
	{
		View ,
		Ready,
		Play,
		Goal,
	};

	public GameObject Player;
	public GameObject ReadyGo;
	public GameObject Ender;
	GameObject GoalObj;
	GameObject GhostObj;
	GameObject Timer;
	GameState  state;
	public Text text;

	
	public RankingTimeSaved RankingTimeSavedObj;
	private GameObject GameInfoObj;

	// Use this for initialization
	void Start () 
    {
        //  BGM再生(環境音)
        AudioManager.Instance.PlayBGM("[bgm]wave");

		GhostObj = GameObject.FindWithTag("Ghost");
		GoalObj  = GameObject.FindWithTag("Goal");
		Timer    = GameObject.FindWithTag("timer");

		
		GameInfoObj = GameObject.FindWithTag ("GameInfo");
		GameInfoObj.GetComponent<GameInfo> ().SetGameInfoData ((int)(GAMEINFOLIST.INFO_SELECTEDSTAGE_NAME),
		                                                       Application.loadedLevelName);
	
		GameObject.Find ("timer").SetActive (false);
		GameObject.Find ("StopButton").SetActive (false);
		GameObject.Find ("ScrollView").SetActive (false);

		//ゲームステート初期化
		View();
	}
	
	// Update is called once per frame
	void Update () {
		GameObject camera = GameObject.FindWithTag("MainCamera");

		switch(state)
		{
			case GameState.Ready:
				//Goが表示されたらスタート
				if (ReadyGo.GetComponent<ReadyGo>().IsGo() == true) GameStart();
				//text.text = "GAMEMODE_READY";
				break;

			case GameState.Play:
				//ゴールフラグが立っていたら
				if (GoalObj.GetComponent<goal>().IsGoal() == true) Goal();
				//text.text = "GAMEMODE_PLAY";
				break;

			case GameState.Goal:
				//クリックで画面遷移
				if (GoalObj.GetComponent<goal>().IsGoResult() == true) Application.LoadLevel("result");
				//text.text = "GAMEMODE_GOAL";
				break;

			case GameState.View:
				//クリックでフェード
				if (Input.GetMouseButtonDown(0))
				{
					Ready();
				}
				else if (camera.GetComponent<StageView>().IsView() == false)
				{
					Ready();
				}

				//text.text = "GAMEMODE_VIEW";
				break;

		}
	
	}

	//ゲームモードをレディ状態にする
	void Ready()
	{
        //  前のBGMをフェードアウト
        AudioManager.Instance.FadeOutBGM(1.0f);

        //  SE再生(スタートコール)
        AudioManager.Instance.PlaySE("[se]startcall");

		state = GameState.Ready;
		Player.GetComponent<player>().EnableOperation(false);
		GameObject camera = GameObject.FindWithTag("MainCamera");
		camera.GetComponent<ChaseCamera>().EnebleChase(true);
		camera.GetComponent<ChaseCamera>().ResetPos();
		camera.GetComponent<StageView>().EnableView(false);
		GameObject.FindWithTag("GameFade").GetComponent<fade>().FadeIn(new Color(0.0f, 0.0f, 0.0f, 1.0f));
		ReadyGo.GetComponent<ReadyGo>().ReadyStart();

		foreach (Transform child in GameObject.Find("Canvas_Touma").transform) {
			// 子の要素をたどる
			if (child.name == "StopButton") {
				// 指定した名前と一致
				// 表示フラグを設定
				child.gameObject.SetActive (true);
			}

			if (child.name == "ScrollView") {
				// 指定した名前と一致
				// 表示フラグを設定
				child.gameObject.SetActive (true);
			}

			if (child.name == "timer") {
				// 指定した名前と一致
				// 表示フラグを設定
				child.gameObject.SetActive (true);
			}
		}
	}

	//ゲームモードをプレイ状態にする
	void GameStart()
	{
		state = GameState.Play;
		Player.GetComponent<player>().EnableOperation(true);
		if(GhostObj.GetComponent<ghost>().IsUseGhost())
		{
			GhostObj.GetComponent<ghost>().EneblePlayGhost(true);
		}
		Timer.GetComponent<timer>().CountStart();

        //  BGM再生(ゲームシーンBGM)
        AudioManager.Instance.PlayBGM("[bgm]game");

	}

	//ゲームモードをゲームオーバー状態にする
	void View()
	{
		state = GameState.View;
		Player.GetComponent<player>().EnableOperation(false);
		GameObject camera = GameObject.FindWithTag("MainCamera");
		camera.GetComponent<StageView>().EnableView(true);
		camera.GetComponent<ChaseCamera>().EnebleChase(false);
		GameObject.FindWithTag("GameFade").GetComponent<fade>().FadeIn(new Color(0.0f, 0.0f, 0.0f, 1.0f));
	}

	//ゲームモードをゴール状態にする
	void Goal()
	{
		state = GameState.Goal;
		Timer.GetComponent<timer>().CountStop();

		//ランキングの更新
		RankingTimeSavedObj.RankingUpdate();
		//リザルトに使うMyTimeの保存
		GameInfoObj.GetComponent<GameInfo>().SetGameInfoData((int)(GAMEINFOLIST.INFO_GOALTIME),
		                                                     Timer.GetComponent<timer>().GetMyTime());

		GameObject.Find("StopButton").SetActive(false);
		GameObject.Find("ScrollView").SetActive(false);

	}
}
