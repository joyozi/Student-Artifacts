using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class timer : MonoBehaviour {

		public const int MaxRap = 3;
		public Text  text;							//画面表示用（仮）
		public float time;							//現在タイマーの数値
		bool         bCount;						//タイマーカウントするか
		int          rapNum;						//現在のラップの総数

		float[]      rapTime = new float[MaxRap];	//ラップタイムを格納する

	// Use this for initialization
	void Start () {
		time = 0.0f;
		rapNum = 0;
		bCount = false;
	}

	// Update is called once per frame
	void Update () {
		if (bCount == true)
		{
			time += Time.deltaTime;
		}

		float TimeChanger;
		float TimeMiri;
		
		//カンストの設定
		if (time < 1000.0f) {
			TimeChanger = time;
			TimeMiri = time - Mathf.Floor (TimeChanger);
			
			TimeMiri *= 100.0f;
		} else {
			TimeChanger = 999.0f;
			TimeMiri = 99.0f;
		}
		
		string strSecond = string.Format("{0}", Mathf.Floor(TimeChanger));
		string strMiri = string.Format("{0}", Mathf.Floor(TimeMiri));
		
		//PadLeftで桁数を満たすまで0を入れる
		text.text = strSecond.PadLeft (3, '0')  + "."+ strMiri.PadLeft (2, '0');
	}

	//タイマーカウントスタート
	public void CountStart()
	{
		bCount = true;
	}

	//タイマーカウントストップ
	public void CountStop()
	{
		bCount = false;
	}
	//タイマーゲット
	public string GetMyTime(){
		return text.text;
	}

	//ラップタイムの記録
	public void RapRecord()
	{
		if (rapNum < MaxRap)
		{
			rapTime[rapNum] = time;
			rapNum++;
		}
	}
}
