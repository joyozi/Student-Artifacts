using UnityEngine;
using System.Collections;
using System.IO;

public enum GAMEINFOLIST
{
	INFO_SELECTEDSTAGE = 0,		//一番最後に遊ばれたステージ 0から順に入れていく
	INFO_SELECTEDSTAGE_NAME,	//一番最後に遊ばれたステージ 名前
	INFO_GOALTIME,				//ゴールタイム
	INFO_TITLEREADED,			//タイトルがもう読み込まれたか	0で未読1で既読
	INFO_STAGENUM,				//ステージの数。ランキングシーンとかで使う
	INFO_SOUND,					//オプション　０でON、１でOff
	INFO_PLAYSTILE,				//オプション　スマホの傾ける角度
	INFO_GHOSTTYPE,				//オプション　0だと1位のゴーストデータ,だと最後に保存したゴーストデータを使う(予定)
	INFO_GHOSTAPPEARANCE,		//オプション　0でゴーストを出す。1でゲーム中で出さない。2でファイルがない
	INFO_MAX
};

public class GameInfo : MonoBehaviour {

	public  int StageNum = 2;

	private string[] GameInfoData = new string[(int)(GAMEINFOLIST.INFO_MAX)];
	private int GameInfoDataCnt = 0;

	private static bool Created =false;

	//他の処理で利用するから先に呼び出してほしい
	void Awake () {
		//このオブジェクトを最後まで破壊しない
		//シーンを呼ぶごとに複製されるので2度目以降はデストロイ！
		if (Created == false) {
			DontDestroyOnLoad (this);
			Created = true;
		


			//読み込む前に初期化
			for(int i = 0;i < (int)(GAMEINFOLIST.INFO_MAX);i++){
				GameInfoData[i] = "0";
			}
			GameInfoData [(int)(GAMEINFOLIST.INFO_PLAYSTILE)] = "25";

			if (Application.isEditor) {
				
				//ファイルがあるかどうかのチェック
				string filePass = Application.streamingAssetsPath + "/GameInfo.txt";
				if(File.Exists(filePass) == false){
					GameInfoInit_A();
				}
				
			} else {
				//ファイルがあるかどうかのチェック
				string filePass = Application.persistentDataPath + "/GameInfo2.txt";
				if(File.Exists(filePass) == false){
					GameInfoInit_A();
				}
			}


			//StreamingAssetsから参照可能な位置にコピーする
			initializeFileCopy();
			GameInforead ();

			//始めた瞬間はタイトルをちゃんと表示
			GameInfoData [(int)(GAMEINFOLIST.INFO_TITLEREADED)] = "0";
			GameInfoData [(int)(GAMEINFOLIST.INFO_STAGENUM)] = StageNum.ToString();

		} else {
			Destroy(this);
			return;
		}
	}

	// Update is called once per frame
	void Update () {
	
	}

	public void SetGameInfoData(int DataNum,string Data){
		GameInfoData[DataNum] = Data;

		GameInfoSaved ();
	}

	public string GetGameInfoData(int DataNum){
		return GameInfoData[DataNum];
	}



	void GameInfoSaved(){
		//Unityエディタと実機で処理を分ける
		if (Application.isEditor)
		{
			using (StreamWriter w = new StreamWriter(Application.streamingAssetsPath + "/GameInfo.txt"))
			{
				for(int i = 0;i < (int)(GAMEINFOLIST.INFO_MAX);i++){
					w.WriteLine(GameInfoData[i]);
				}
			}
		}
		else
		{
			//いったんファイルに保存
			string path = Application.persistentDataPath + "/GameInfo2.txt";
			using (StreamWriter sw = new StreamWriter(path))
			{
				for(int i = 0;i < (int)(GAMEINFOLIST.INFO_MAX);i++){
					sw.WriteLine(GameInfoData[i]);
				}
			}
		}
	}



	void GameInforead(){
		//Unityエディタと実機で処理を分ける
		if (Application.isEditor)
		{
			FileStream f = new FileStream(Application.streamingAssetsPath + "/GameInfo.txt", FileMode.Open, FileAccess.Read);
			StreamReader reader = new StreamReader(f);
			
			if (reader != null)
			{
				GameInfoDataCnt = 0;
				while (!reader.EndOfStream)
				{
					GameInfoData[GameInfoDataCnt] = reader.ReadLine();
					GameInfoDataCnt++;
				}
				
				reader.Close();
			}
		}
		else
		{
			FileStream f;
			StreamReader reader;
			
			{
				f = new FileStream(Application.persistentDataPath + "/GameInfo2.txt", FileMode.Open, FileAccess.Read);
				reader = new StreamReader(f);
			}
			//			StreamReader reader = new StreamReader("jar:file://" + Application.dataPath + "!/assets/" + "test.txt");
			
			if (reader != null)
			{
				GameInfoDataCnt = 0;
				while (!reader.EndOfStream)
				{
					GameInfoData[GameInfoDataCnt] = reader.ReadLine();
					GameInfoDataCnt++;
				}
				
				reader.Close();
			}
		}		
	}



	//初期化
	void GameInfoInit_A(){

		for(int i = 0;i < (int)(GAMEINFOLIST.INFO_MAX);i++){
			GameInfoData[i] = "0";
		}



		//Unityエディタと実機で処理を分ける
		if (Application.isEditor)
		{
			using (StreamWriter w = new StreamWriter(Application.streamingAssetsPath + "/GameInfo.txt"))
			{
				for(int i = 0;i < (int)(GAMEINFOLIST.INFO_MAX);i++){
					w.WriteLine(GameInfoData[i]);
				}
			}
		}
		else
		{
			//いったんファイルに保存
			string path = Application.persistentDataPath + "/GameInfo2.txt";
			using (StreamWriter sw = new StreamWriter(path))
			{
				for(int i = 0;i < (int)(GAMEINFOLIST.INFO_MAX);i++){
					sw.WriteLine(GameInfoData[i]);
				}
			}
		}
	}



	void initializeFileCopy()
	{
		string path = null;
		//streamingAssets内のパスを指定
		path = Application.streamingAssetsPath + "/GameInfo.txt";
		
		//treamingAssets内のファイル読み出し
		WWW www = new WWW(path);
		while(!www.isDone)
		{
			
		}
		
		//コピー先のパスを指定
		string toPath = Application.persistentDataPath + "/GameInfo.txt";
		
		//コピー
		File.WriteAllBytes(toPath, www.bytes);
	}

}
