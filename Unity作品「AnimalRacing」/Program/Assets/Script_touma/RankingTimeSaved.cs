using UnityEngine;
using System.Collections;
using System.IO;
using UnityEngine.UI;

public class RankingTimeSaved : MonoBehaviour {

	private const int RANKINGTIME_NUM = 5;
	public Text MYTimeTextObj;

	private int CntRanking;
	private string[] RankingIreko = new string[RANKINGTIME_NUM];
	private int RankingTimeNum = 0;								//ランキングの数値がどれくらいはいってるか

	private string TextFilename;
	private GameObject GameInfoObj;
	
	//読み取りやすいように初めにするようにする
	void Awake () {
		//テキストネームの設定
		GameInfoObj = GameObject.Find ("GameInfoScript_Static");
		TextFilename = "Stage" + GameInfoObj.GetComponent<GameInfo> ().GetGameInfoData ((int)(GAMEINFOLIST.INFO_SELECTEDSTAGE));

		//StreamingAssetsから参照可能な位置にコピーする
		initializeFileCopy_Ranking();

		RankingTimeLoad ();
	}



	//ランキングの数値の呼び出し
	public string GetRankingTime(int Rank){
		return RankingIreko[Rank];
	}



	//ランキングを他のと比較して食い込むかを確認してから書き込む
	public void RankingUpdate()
	{
		float[] RankingTime = new float[RANKINGTIME_NUM];		//floatの入れ子
		float MyTime;

		//文字列中の'.'を削除する
		string[] StrMytime = MYTimeTextObj.text.Split ('.');
		MyTime = (float.Parse(StrMytime[0]) * 100.0f) + float.Parse(StrMytime[1]);

		for (int i = 0; i < RANKINGTIME_NUM; i++) {

			//文字列中の'.'を削除する
			string[] StrRanking = RankingIreko[i].Split ('.');

			RankingTime[i] = (float.Parse(StrRanking[0]) * 100.0f) + float.Parse(StrRanking[1]);
		}

		int RankNum = -1;		//何番目に入るか。

		//RankNumが何番かを調べる
		for (int i = 0; (i < RANKINGTIME_NUM) && (RankNum == -1); i++) {
			if(i == 0){
				if(MyTime <= RankingTime[i]){
					RankNum = i;
				}
			}
			else{
				if(MyTime > RankingTime[i - 1] && MyTime <= RankingTime[i]){
					RankNum = i;
				}
			}				
		}

		//最後に順番を入れ替える  もしランキングに入ってたら
		if (RankNum < RANKINGTIME_NUM && RankNum >= 0) {
			for(int i = RANKINGTIME_NUM - 1;i > RankNum;i--){
				RankingIreko[i] = RankingIreko[i - 1];
			}
			//空いたところにツッコむ
			RankingIreko[RankNum] = MYTimeTextObj.text;
		}

		//Unityエディタと実機で処理を分ける
		if (Application.isEditor)
		{
			using (StreamWriter w = new StreamWriter(Application.streamingAssetsPath + "/" + TextFilename + ".txt"))
			{
				for(int i = 0;i < RANKINGTIME_NUM;i++){
					w.WriteLine(RankingIreko[i]);
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
					sw.WriteLine(RankingIreko[i]);
				}
			}
		}
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

	void initializeFileCopy_Ranking()
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
					if(SampleTime < 100){
					w.WriteLine("0" + SampleTime.ToString() + ".00");
					}
					else{
						w.WriteLine(SampleTime.ToString() + ".00");
					}
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
					if(SampleTime < 100){
						sw.WriteLine("0" + SampleTime.ToString() + ".00");
					}
					else{
						sw.WriteLine(SampleTime.ToString() + ".00");
					}
				}
			}
		}
	}
}
