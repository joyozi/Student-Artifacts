using UnityEngine;
using System.Collections;

public class StageView : MonoBehaviour {

	public const int nMaxPos    = 3;						//何か所見る場所があるか
	public Vector3[] viewPointS = new Vector3[nMaxPos];		//カメラの場所スタート位置
	public Vector3[] viewPointE = new Vector3[nMaxPos];		//            終了位置
	public float fSceneTime     = 1.0f;						//１シーンにかける時間
	float fTimeLate;										//時間のレート調節用
	float fTime;											//時間カウント用
	int              nPosNum    = 0;						//何番目のシーンを見るか
	bool             bView      = false;					//処理を実行するか

	// Use this for initialization
	void Start () {
		//変数初期化
		fTime     = 0.0f;
		fTimeLate = 1.0f / fSceneTime;
		nPosNum   = 0;
		bView     = false;
	}

	// Update is called once per frame
	void Update () {
		fade FadeObj = GameObject.FindWithTag("GameFade").GetComponent<fade>();

		if(bView == true)
		{
			//カメラの位置を線形補間で移動
			transform.position = new Vector3(Mathf.Lerp(viewPointS[nPosNum].x, viewPointE[nPosNum].x, fTime),
											 Mathf.Lerp(viewPointS[nPosNum].y, viewPointE[nPosNum].y, fTime),
											 Mathf.Lerp(viewPointS[nPosNum].z, viewPointE[nPosNum].z, fTime));

			fTime += Time.deltaTime * fTimeLate;

			//指定した時間を超えたら場所切り替えor終了
			if (fTime > 1.0f && FadeObj.GetFadeState() == 0)
			{
				FadeObj.FadeIn(new Color(0.0f, 0.0f, 0.0f));
				fTime = 0.0f;
				nPosNum++;
				if(nPosNum >= nMaxPos)
				{
					EnableView(false);
				}
			}

			//フェードしていなかったら
			if (FadeObj.GetFadeState() == 0)
			{
				if (fTime > 0.75f)
				{
					FadeObj.FadeOut(new Color(0.0f, 0.0f, 0.0f));
				}
			}

		}
	}

	//ビュー切り替え
	public void EnableView(bool bEnable)
	{
		bView = bEnable;
	}

	//処理を行っているか取得する関数
	public bool IsView()
	{
		return bView;
	}
}
