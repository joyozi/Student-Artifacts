using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public enum RESULTSTATECHANGE{
	RESULTSTATE_NONE = 0,
	RESULTSTATE_TITLE,
	RESULTSTATE_RETRY,
};

public class ResultButton : MonoBehaviour {

	public Text StageNumberText;

	private GameObject GameInfoObj;
	private RESULTSTATECHANGE ResultChanger = RESULTSTATECHANGE.RESULTSTATE_NONE;
	private bool RetryJudge;
	private GameObject FadeObj;
	
	
	
	void Start()
    {

        // BGM再生(リザルトシーンBGM)
        AudioManager.Instance.PlayBGM("[bgm]result");

		GameInfoObj = GameObject.Find ("GameInfoScript_Static");
		FadeObj = GameObject.Find ("ResultScript");

		string num = GameInfoObj.GetComponent<GameInfo> ().GetGameInfoData ((int)(GAMEINFOLIST.INFO_SELECTEDSTAGE));
		int num2 = int.Parse (num) + 1;
		StageNumberText.text = num2.ToString();

		GameObject.Find ("GhostSavedQuestion").SetActive (false);
	}
	
	
	void Update(){
		if (FadeObj.GetComponent<fade> ().StartFade == STARTFADE.FADE_NONE) {
			switch(ResultChanger){
			case RESULTSTATECHANGE.RESULTSTATE_RETRY:
				Application.LoadLevel (GameInfoObj.GetComponent<GameInfo> ().GetGameInfoData ((int)(GAMEINFOLIST.INFO_SELECTEDSTAGE_NAME)));
				break;
				
			case RESULTSTATECHANGE.RESULTSTATE_TITLE:
				Application.LoadLevel ("title");
				break;
				
			default:
				break;
			}
		}
	}
	
	
	
	public void PushReusltButton_GhostSaved()
    {
        //  SE再生(メニュープッシュ音)
        AudioManager.Instance.PlaySE("[se]menu");

		//ボタンを呼び出す
		foreach (Transform child in GameObject.Find("Canvas_ToumaResult").transform) {
			// 子の要素をたどる
			if(child.name == "GhostSavedQuestion") {
				// 指定した名前と一致
				// 表示フラグを設定
				child.gameObject.SetActive(true);
				// おしまい
				return;
			}
		}
	}
	
	public void PushReusltButton_Yes()
    {
        //  SE再生(メニュープッシュ音)
        AudioManager.Instance.PlaySE("[se]menu");

		GameObject.FindWithTag ("Ghost").GetComponent<ghost> ().GhostSave ();
		
		GameObject.Find ("GhostSavedQuestion").SetActive (false);

		
		GameInfoObj.GetComponent<GameInfo> ().SetGameInfoData ((int)(GAMEINFOLIST.INFO_GHOSTAPPEARANCE),"0");
	}
	
	public void PushReusltButton_No()
    {
        //  SE再生(メニュープッシュ音)
        AudioManager.Instance.PlaySE("[se]menu");
		
		GameObject.Find ("GhostSavedQuestion").SetActive (false);
		
	}
	
	public void PushReusltButton_Retry()
    {
        //  SE再生(メニュープッシュ音)
        AudioManager.Instance.PlaySE("[se]menu");

		if (FadeObj.GetComponent<fade> ().StartFade == STARTFADE.FADE_NONE) {
			FadeObj.GetComponent<fade> ().FadeOut (Color.black);
			ResultChanger = RESULTSTATECHANGE.RESULTSTATE_RETRY;
		}
	}
	
	public void PushReusltButton_Title()
    {
        //  SE再生(メニュープッシュ音)
        AudioManager.Instance.PlaySE("[se]menu");

		if (FadeObj.GetComponent<fade> ().StartFade == STARTFADE.FADE_NONE) {
			FadeObj.GetComponent<fade> ().FadeOut (Color.black);
			ResultChanger = RESULTSTATECHANGE.RESULTSTATE_TITLE;
		}
	}
}
