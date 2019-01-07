using UnityEngine;
using System.Collections;
using System.IO;
using UnityEngine.UI;

public class ghost : MonoBehaviour {

	Vector3[]    pos = new Vector3[4800];
	int          cntPos;
	int          maxPosNum;
	float        x,y,z;
	string       sX, sY, sZ;
	bool         bPlay = false;

	bool  bUseGhost = false;

	private string FileName;

	// Use this for initialization
	void Start () {
		cntPos = 0;
		bUseGhost = false;
		
		FileName = "GhostLoad_" + GameObject.FindWithTag ("GameInfo").GetComponent<GameInfo> ().GetGameInfoData ((int)(GAMEINFOLIST.INFO_SELECTEDSTAGE_NAME));
		//再生するかしないかの処理
		if (GameObject.FindWithTag ("GameInfo").GetComponent<GameInfo> ().GetGameInfoData ((int)(GAMEINFOLIST.INFO_GHOSTAPPEARANCE)) == "0") {

			bUseGhost = false;

			if (Application.isEditor) {
				
				//ファイルがあるかどうかのチェック
				string filePass = Application.streamingAssetsPath + "/" + FileName + ".txt";
				if(File.Exists(filePass)){
					bUseGhost = true;
				}
				
			} else {
				//ファイルがあるかどうかのチェック
				string filePass = Application.persistentDataPath + "/" + FileName + "_2.txt";
				if(File.Exists(filePass)){
					bUseGhost = true;
				}
			}
		}


		FileName = "GhostLoad_" + GameObject.FindWithTag ("GameInfo").GetComponent<GameInfo> ().GetGameInfoData ((int)(GAMEINFOLIST.INFO_SELECTEDSTAGE_NAME));

		//StreamingAssetsから参照可能な位置にコピーする
		//initializeFileCopy_WritedGhost();

		if(bUseGhost == true)
		{
			//位置情報コピー
			initializeFileCopy_WritedGhost();
			LoadText();
			transform.localPosition = pos[0];
		}
		else
		{
			transform.localPosition = new Vector3(0.0f, 300.0f, 0.0f);
			bPlay = false;
		}
	}
	
	// Update is called once per frame
	void Update () {
		//プレイフラグが立っていたら
		if(bPlay == true)
		{
			if ( cntPos <= maxPosNum)
			{
				transform.localPosition = pos[cntPos];
				cntPos++;
			}
		}
	}
	
	//ゴーストを保存する関数
	public void GhostSave(){
		initializeFileCopy ();
		LoadText_OriginalGhost();
		initializeFileCopy_WritedGhost ();
		GhostWrite ();
		initializeFileCopy ();
	}

	//ゴーストの再生＆停止
	public void EneblePlayGhost(bool bEneble)
	{
		bPlay = bEneble;
	}



	//ファイルに書き出し
	void GhostWrite()
	{
		//Unityエディタと実機で処理を分ける
		if (Application.isEditor)
		{
			using (StreamWriter w = new StreamWriter(Application.streamingAssetsPath + "/" + FileName + ".txt"))
			{
				for(int i = 0; i < 4800; i++)
				{
					w.WriteLine(pos[i].x.ToString());
					w.WriteLine(pos[i].y.ToString());
					w.WriteLine(pos[i].z.ToString());
				}
			}
		}
		else
		{
			//いったんファイルに保存
			string path = Application.persistentDataPath + "/" + FileName + "_2.txt";
			using (StreamWriter sw = new StreamWriter(path))
			{
				for (int i = 0; i < 4800; i++)
				{
					sw.WriteLine(pos[i].x.ToString());
					sw.WriteLine(pos[i].y.ToString());
					sw.WriteLine(pos[i].z.ToString());
				}
			}
		}
	}



	void LoadText()
	{
		//Unityエディタと実機で処理を分ける
		if (Application.isEditor)
		{
			FileStream f = new FileStream(Application.streamingAssetsPath + "/" + FileName + ".txt", FileMode.Open, FileAccess.Read);
			StreamReader reader = new StreamReader(f);

			if (reader != null)
			{
				while (!reader.EndOfStream)
				{
					sX = reader.ReadLine();
					sY = reader.ReadLine();
					sZ = reader.ReadLine();

					x = float.Parse(sX);
					y = float.Parse(sY);
					z = float.Parse(sZ);
					pos[cntPos] = new Vector3(x, y, z);
					cntPos++;
				}
				reader.Close();
			}
			maxPosNum = cntPos;
			cntPos = 0;
		}
		else
		{
			FileStream f;
			StreamReader reader;

			f = new FileStream(Application.persistentDataPath + "/" + FileName + "_2.txt", FileMode.Open, FileAccess.Read);
			reader = new StreamReader(f);

			if (reader != null)
			{
				while (!reader.EndOfStream)
				{
					sX = reader.ReadLine();
					sY = reader.ReadLine();
					sZ = reader.ReadLine();
					x = float.Parse(sX);
					y = float.Parse(sY);
					z = float.Parse(sZ);
					pos[cntPos] = new Vector3(x, y, z);
					cntPos++;
				}
			}
			maxPosNum = cntPos;
			cntPos = 0;
			reader.Close();
		}
	}




	void LoadText_OriginalGhost()
	{
		//Unityエディタと実機で処理を分ける
		if (Application.isEditor)
		{
			FileStream f = new FileStream(Application.streamingAssetsPath + "/test.txt", FileMode.Open, FileAccess.Read);
			StreamReader reader = new StreamReader(f);
			
			if (reader != null)
			{
				while (!reader.EndOfStream)
				{
					sX = reader.ReadLine();
					sY = reader.ReadLine();
					sZ = reader.ReadLine();
					
					x = float.Parse(sX);
					y = float.Parse(sY);
					z = float.Parse(sZ);
					pos[cntPos] = new Vector3(x, y, z);
					cntPos++;
				}
				reader.Close();
			}
			maxPosNum = cntPos;
			cntPos = 0;
		}
		else
		{
			FileStream f;
			StreamReader reader;
			
			f = new FileStream(Application.persistentDataPath + "/test2.txt", FileMode.Open, FileAccess.Read);
			reader = new StreamReader(f);
			
			if (reader != null)
			{
				while (!reader.EndOfStream)
				{
					sX = reader.ReadLine();
					sY = reader.ReadLine();
					sZ = reader.ReadLine();
					x = float.Parse(sX);
					y = float.Parse(sY);
					z = float.Parse(sZ);
					pos[cntPos] = new Vector3(x, y, z);
					cntPos++;
				}
			}
			maxPosNum = cntPos;
			cntPos = 0;
			reader.Close();
		}
	}



	//書き込まれるほう
	void initializeFileCopy_WritedGhost()
	{
		string path = null;
		//streamingAssets内のパスを指定
		path = Application.streamingAssetsPath + "/" + FileName + ".txt";

		//treamingAssets内のファイル読み出し
		WWW www = new WWW(path);
		while(!www.isDone)
		{
			
		}

		//コピー先のパスを指定
		string toPath = Application.persistentDataPath + "/" + FileName + ".txt";

		//コピー
		File.WriteAllBytes(toPath, www.bytes);
	}
	
	
	
	void initializeFileCopy()
	{
		//streamingAssets内のパスを指定
		string path = null;
		//streamingAssets内のパスを指定
		path = Application.streamingAssetsPath + "/test.txt";

		if(path != null)
		{
			//treamingAssets内のファイル読み出し
			WWW www = new WWW(path);
			while(!www.isDone)
			{
			
			}

			//コピー先のパスを指定
			string toPath = Application.persistentDataPath + "/test.txt";

			//コピー
			File.WriteAllBytes(toPath, www.bytes);
		}
	}

	public bool IsUseGhost()
	{
		return bUseGhost;
	}

	public void EnableGhost(bool bEnable)
	{
		bUseGhost = bEnable;
	}
}
