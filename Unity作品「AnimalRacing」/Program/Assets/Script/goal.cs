using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class goal : MonoBehaviour {

	enum GOAL_STATE
	{
		GOAL_IN,
		GOAL_PAUSE,
		GOAL_END
	};

	bool         bGoal;
	public Image GoalImage;
	public Image ClearImage;
	public Image TapToResultImage;
	bool         bGoResult;
	bool         bEnd;
	int          nCount;
	public int   nGoResultFrame = 720;
	public int   nPauseFrame = 300;
	int          nFinishDispFrame = 420;
	GOAL_STATE   state;
	float        alpha = 0.0f;
	bool         bFadeIn = true;
	bool         bShake;
	float        fTime;
	float        Rotation;

	// Use this for initialization
	void Start () {
		bGoResult = false;
		nCount = 0;
		bGoal = false;
		bEnd = false;
		GoalImage.color = new Color(1.0f,1.0f,1.0f,0.0f);
		ClearImage.color = new Color(1.0f, 1.0f, 1.0f, 0.0f);
		alpha = 0.0f;
		TapToResultImage.color = new Color(1.0f, 1.0f, 1.0f, alpha);
		state = GOAL_STATE.GOAL_IN;
		bFadeIn = true;
		bShake  = false;
		fTime   = 0.0f;
		Rotation = 0.0f;
	}
	
	// Update is called once per frame
	void Update () {

		if (bGoal == true)
		{
			nCount++;

			if(bShake == true)
			{
				Rotation = (1.0f - fTime) * (1.0f - fTime) * (1.0f - fTime) * 0.0f +
						3.0f * (1.0f - fTime) * (1.0f - fTime) * fTime * 30.0f +
						3.0f * (1.0f - fTime) * fTime * fTime * -30.0f +
						fTime * fTime * fTime * 0.0f;
				fTime += 0.03f;
				if(fTime >= 1.0f)
				{
					fTime = 0.0f;
					bShake = false;
					Rotation = 0.0f;
				}
			}
			ClearImage.transform.rotation = Quaternion.Euler(new Vector3(0.0f, 0.0f, Rotation));

			switch (state)
			{
				case GOAL_STATE.GOAL_IN:

				if(nCount > 60)
				{
					GoalImage.transform.position = new Vector3(GoalImage.transform.position.x + 10.0f, GoalImage.transform.position.y, GoalImage.transform.position.z);
				}

				if (nCount > nFinishDispFrame)
				{
					Destroy(GoalImage);
					ClearImage.color = new Color(1.0f, 1.0f, 1.0f, 1.0f);
					nCount = 0;
					state = GOAL_STATE.GOAL_PAUSE;

					//  BGM再生(ゲームクリアシーンBGM)
					AudioManager.Instance.PlayBGM("[bgm]gameclear");
				}
				break;

				case GOAL_STATE.GOAL_PAUSE:
				GameObject.FindWithTag("MainCamera").GetComponent<ChaseCamera>().EnebleChase(false);
				if (nCount % 60 == 0 && nCount != 0)
				{
					GameObject.FindWithTag("Player").GetComponent<Rigidbody>().AddForce(0.0f, 1000.0f, 0.0f);
					bShake = true;
				}
				if (nCount > nPauseFrame)
				{
					state = GOAL_STATE.GOAL_END;
					nCount = 0;
				}

				break;

				case GOAL_STATE.GOAL_END:

				if (bEnd)
				{
					if (GameObject.FindWithTag("GameFade").GetComponent<fade>().GetFadeState() == 0)
					{
						//フェードが終わったらリザルトに
						bGoResult = true;
					}
				}

				if (nCount % 60 == 0 && nCount != 0)
				{
					GameObject.FindWithTag("Player").GetComponent<Rigidbody>().AddForce(0.0f, 1000.0f, 0.0f);
					bShake = true;
				}

				if (bEnd == false)
				{
					if(Input.GetMouseButtonUp(0) && GameObject.FindWithTag("GameFade").GetComponent<fade>().GetFadeState() == 0)
					{
						//  SE再生(メニュープッシュ音)
						AudioManager.Instance.PlaySE("[se]menu");
						GameObject.FindWithTag("GameFade").GetComponent<fade>().FadeOut(new Color(0.0f, 0.0f, 0.0f, 1.0f));
						bEnd = true;
					}
					else if(nCount == nGoResultFrame && GameObject.FindWithTag("GameFade").GetComponent<fade>().GetFadeState() == 0)
					{
						GameObject.FindWithTag("GameFade").GetComponent<fade>().FadeOut(new Color(0.0f, 0.0f, 0.0f, 1.0f));
						bEnd = true;
					}
				}

				if (bFadeIn == true)
					alpha += 0.05f;
				else
					alpha -= 0.05f;

				if(alpha >= 1.0f)
				{
					bFadeIn = false;
				}
				else if(alpha <= 0.0f)
				{
					bFadeIn = true;
				}

				TapToResultImage.color = new Color(1.0f, 1.0f, 1.0f, alpha);
				break;
			}
		}
	}


	// プレイヤーが当たった時の処理
	//----------------------------------------------------------------
	private void OnTriggerEnter(Collider other)
	{
		if (other.tag == "Player")
		{
			bGoal = true;
			other.GetComponent<player>().GhostWriter();
			GoalImage.color = new Color(1.0f, 1.0f, 1.0f, 1.0f);
			GameObject camera = GameObject.FindWithTag("MainCamera");
			camera.GetComponent<ChaseCamera>().SetOffset(new Vector3(0.0f, 2.0f, -3.0f));
		}
	}

	//ゴールしたかどうかを返す
	public bool IsGoal()
	{
		return bGoal;
	}

	public bool IsGoResult()
	{
		return bGoResult;
	}

}
