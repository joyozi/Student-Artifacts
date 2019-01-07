using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class ReadyGo : MonoBehaviour {

	public float ReadyTime = 2.9f;			//Readyの長さ
	public float GoTime = 0.8f;			//Goの長さ
	float fTime;
	public Image Ready;
	public Image Go;
	bool bReady;
	bool bGo;

	// Use this for initialization
	void Start () {
		fTime = 0.0f;
		Ready.color = new Color(1.0f, 1.0f, 1.0f, 0.0f);
		Go.color    = new Color(1.0f, 1.0f, 1.0f, 0.0f);
		bReady = false;
		bGo    = false;
	}

	// Update is called once per frame
	void Update () {
		if(bReady == true)
		{
			fTime += Time.deltaTime;
			if (ReadyTime <= fTime)
			{
				fTime = 0;
				Ready.color = new Color(1.0f, 1.0f, 1.0f, 0.0f);
				Go.color    = new Color(1.0f, 1.0f, 1.0f, 1.0f);
				bReady = false;
				bGo    = true;
			}
		}
		else if (bGo == true)
		{
			fTime += Time.deltaTime;
			if (GoTime <= fTime)
			{
				fTime = 0;
				bGo = false;
				//スプライトの削除
				Destroy(Ready);
				Destroy(Go);
			}
		}
	}

	//ReadyGOの開始
	public void ReadyStart()
	{
		bReady = true;
		Ready.color = new Color(1.0f, 1.0f, 1.0f, 1.0f);
		fTime = 0.0f;
	}

	//Goになったか返す
	public bool IsGo()
	{
		return bGo;
	}

}
