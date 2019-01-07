using UnityEngine;
using System.Collections;
using System.IO;
using UnityEngine.UI;

public class RankingViewer : MonoBehaviour {

	private const int RANKINGTIME_NUM = 5;

	public Text StageNumberText;
	public Text[] RankingText = new Text[RANKINGTIME_NUM];

	private string[] RankingIreko = new string[RANKINGTIME_NUM];
	private int RankingTimeNum = 0;								//ランキングの数値がどれくらいはいってるか	
	private string TextFilename;
	private int StageNum;

	private int ViewStageRanking;
	private int ViewStageRanking_Old;
	private GameObject GameInfoObj;
	private bool FadeOutJudge = false;

	private int[] RankingExistNumber = new int[64];		//ランキングのファイルが存在するステージのナンバーの入れ子
	private int RankingExistCnt;


	//読み取りやすいように初めにするようにする
	void Start () 
    {
        //  BGM再生(リザルトシーンBGM)
        AudioManager.Instance.PlayBGM("[bgm]result");

		//ランキングリセットファイナルアンサーボタンの消去
		GameObject.Find ("RankingResetFinalAnswer").SetActive (false);

		//テキストネームの設定
		ViewStageRanking  = ViewStageRanking_Old = 0;

		for (int i = 0; i < int.Parse(GameObject.FindWithTag("GameInfo").GetComponent<GameInfo>().GetGameInfoData((int)(GAMEINFOLIST.INFO_STAGENUM))); i++) {

			TextFilename = "Stage" + i.ToString();

			string path = null;
			//streamingAssets内のパスを指定
			path = Application.streamingAssetsPath + "/" + TextFilename + ".txt";
			
			//コピー先のパスを指定
			string toPath = Application.persistentDataPath + "/" + TextFilename + ".txt";



			if (Application.isEditor) {
				
				//ファイルがあるかどうかのチェック
				string filePass = Application.streamingAssetsPath + "/" + TextFilename + ".txt";
				if(File.Exists(filePass) == false){
					//なかったら作る！
					RankingAllInit();
				}
				
			} else {
				//ファイルがあるかどうかのチェック
				string filePass = Application.persistentDataPath + "/" + TextFilename + "_2.txt";
				if(File.Exists(filePass) == false){
					//なかったら作る！
					RankingAllInit();
				}
			}
		}

		ViewStageRanking  = ViewStageRanking_Old = 0;
		TextFilename = "Stage" + ViewStageRanking.ToString();
		
		//StreamingAssetsから参照可能な位置にコピーする
		initializeFileCopy();
		RankingTimeLoad ();

		SetRankingTime ();
	
		//ステージの数の取得
		GameInfoObj = GameObject.FindWithTag ("GameInfo");
		StageNum = int.Parse(GameInfoObj.GetComponent<GameInfo> ().GetGameInfoData ((int)(GAMEINFOLIST.INFO_STAGENUM)));
	}

	void Update(){
		if (ViewStageRanking_Old != ViewStageRanking) {
			//ランキングのリセット作業
			TextFilename = "Stage" + ViewStageRanking.ToString ();
			initializeFileCopy ();
			RankingTimeLoad ();
			SetRankingTime ();
		}

		ViewStageRanking_Old = ViewStageRanking;

		if (FadeOutJudge && GameObject.Find ("RankingScript").GetComponent<fade> ().GetFadeState() == 0){
			Application.LoadLevel("title");
		}
	}

	public void ReturnTitleButton()
    {
        //  SE再生(メニュープッシュ音)
        AudioManager.Instance.PlaySE("[se]menu");

		if (FadeOutJudge == false) 
        {
			GameObject.Find("RankingScript").GetComponent<fade>().FadeOut(Color.black);
			FadeOutJudge = true;
		}
	}



	void SetRankingTime(){
		//上の数字のセット
		StageNumberText.text = (ViewStageRanking + 1).ToString();
		
		for(int i = 0;i < RANKINGTIME_NUM;i++){
			RankingText[i].text = RankingIreko[i];
		}
	}






	//ランキングの切り替え
	public void RankingChangeButtonL()
    {
        //  SE再生(メニュープッシュ音)
        AudioManager.Instance.PlaySE("[se]menu");

		if (ViewStageRanking >= 0 && ViewStageRanking < StageNum) 
        {
			ViewStageRanking--;

			if (ViewStageRanking < 0)
            {
				ViewStageRanking = StageNum - 1;
			}
		}
	}



	public void RankingChangeButtonR()
    {
        //  SE再生(メニュープッシュ音)
        AudioManager.Instance.PlaySE("[se]menu");

		if (ViewStageRanking >= 0 && ViewStageRanking < StageNum) 
        {
			ViewStageRanking++;
			
			if (ViewStageRanking >= StageNum)
            {
				ViewStageRanking = 0;
			}
		}
	}



	public void RankingResetButton_Push()
    {
        //  SE再生(メニュープッシュ音)
        AudioManager.Instance.PlaySE("[se]menu");

		//ボタンを呼び出す
		foreach (Transform child in GameObject.Find("Canvas_ToumaRanking").transform) 
        {
			// 子の要素をたどる
			if(child.name == "RankingResetFinalAnswer")
            {
				// 指定した名前と一致
				// 表示フラグを設定
				child.gameObject.SetActive(true);
				// おしまい
				return;
			}
		}
	}

	public void RankingResetbutton_Yes()
    {
        //  SE再生(メニュープッシュ音)
        AudioManager.Instance.PlaySE("[se]menu");

		RankingAllInit ();
		RankingTimeLoad ();
		SetRankingTime();
		GameObject.Find ("RankingResetFinalAnswer").SetActive (false);
	}

	public void RankingResetbutton_No()
    {
        //  SE再生(メニュープッシュ音)
        AudioManager.Instance.PlaySE("[se]menu");

		GameObject.Find ("RankingResetFinalAnswer").SetActive (false);
	}



	//らんきんぐをすべてよびだす
	public void RankingTimeLoad()
	{
		//時間の初期化
		int SampleTime;
		for(int i = 0;i < RANKINGTIME_NUM;i++){
			SampleTime = (i * 20) + 60;
			
			if(SampleTime < 100){
				RankingIreko[i] = "0" + SampleTime.ToString() + ".00";
			}
			else{
				RankingIreko[i] = SampleTime.ToString() + ".00";
			}
		}
		
		
		//Unityエディタと実機で処理を分ける
		if (Application.isEditor)
		{
			FileStream f = new FileStream(Application.streamingAssetsPath + "/" + TextFilename + ".txt", FileMode.Open, FileAccess.Read);
			StreamReader reader = new StreamReader(f);
			
			if (reader != null)
			{
				RankingTimeNum = 0;
				while (!reader.EndOfStream)
				{
					RankingIreko[RankingTimeNum] = reader.ReadLine();
					RankingTimeNum++;
				}
				
				reader.Close();
			}
		}
		else
		{
			FileStream f;
			StreamReader reader;
			
			{
				f = new FileStream(Application.persistentDataPath + "/" + TextFilename + "_2.txt", FileMode.Open, FileAccess.Read);
				reader = new StreamReader(f);
			}
			//			StreamReader reader = new StreamReader("jar:file://" + Application.dataPath + "!/assets/" + "test.txt");
			
			if (reader != null)
			{
				RankingTimeNum = 0;
				while (!reader.EndOfStream)
				{
					RankingIreko[RankingTimeNum] = reader.ReadLine();
					RankingTimeNum++;
				}
				reader.Close();
			}
		}
	}
	
	void initializeFileCopy()
	{
		//streamingAssets内のパスを指定
		string path = Application.streamingAssetsPath + "/" + TextFilename + ".txt";
		
		//treamingAssets内のファイル読み出し
		WWW www = new WWW(path);
		while(!www.isDone)
		{
			
		}
		
		//コピー先のパスを指定
		string toPath = Application.persistentDataPath + "/" + TextFilename + ".txt";
		
		//コピー
		File.WriteAllBytes(toPath, www.bytes);
	}

	//	ランキングの初期化
	public void RankingAllInit()
	{
		//Unityエディタと実機で処理を分ける
		if (Application.isEditor)
		{
			using (StreamWriter w = new StreamWriter(Application.streamingAssetsPath + "/" + TextFilename + ".txt"))
			{
				for(int i = 0;i < RANKINGTIME_NUM;i++){
					int SampleTime = (i * 20) + 120;
					w.WriteLine(SampleTime.ToString() + ".00");
				}
			}
		}
		else
		{
			//いったんファイルに保存
			string path = Application.persistentDataPath + "/" + TextFilename + "_2.txt";
			using (StreamWriter sw = new StreamWriter(path))
			{
				for(int i = 0;i < RANKINGTIME_NUM;i++){
					int SampleTime = (i * 20) + 120;
					sw.WriteLine(SampleTime.ToString() + ".00");
				}
			}
		}
	}
}
