using UnityEngine;
using System.Collections;

public enum PAUSEMENUACT
{
	PAUSE_NONE = 0,
	PAUSE_RESTART,
	PAUSE_TITLE,
	PAUSE_MAX
};

public class PauseMenu : MonoBehaviour {


	public fade fadeObj;

	private PAUSEMENUACT PauseAct = PAUSEMENUACT.PAUSE_NONE;
	private bool FadeOutJudge = false;

	void Update(){

		if (FadeOutJudge == true && fadeObj.GetFadeState () == (int)(STARTFADE.FADE_NONE)) {
			switch(PauseAct){
			case PAUSEMENUACT.PAUSE_RESTART:
				Application.LoadLevel (Application.loadedLevel);
				break;

			case PAUSEMENUACT.PAUSE_TITLE:
				Application.LoadLevel ("title");
				break;
			}		
		}
	}

	public void PushContinue()
    {
        //  SE再生(メニュープッシュ音)
        AudioManager.Instance.PlaySE("[se]menu");

		//ストップボタンを押したときと同じ処理
		if (FadeOutJudge == false) 
        {
			GameObject.Find ("StopButton").SendMessage ("PushStopButton");
		}
	}
	
	public void PushRestart()
    {
        //  SE再生(メニュープッシュ音)
        AudioManager.Instance.PlaySE("[se]menu");

		if (FadeOutJudge == false) 
        {
			Time.timeScale = 1;
			FadeOutJudge = true;
			PauseAct = PAUSEMENUACT.PAUSE_RESTART;
			fadeObj.FadeOut(Color.black);
		}
	}
	
	public void PushStageSelect()
    {
        //  SE再生(メニュープッシュ音)
        AudioManager.Instance.PlaySE("[se]menu");

		if (FadeOutJudge == false) 
        {
			Time.timeScale = 1;
			FadeOutJudge = true;
			PauseAct = PAUSEMENUACT.PAUSE_TITLE;
			fadeObj.FadeOut(Color.black);
		}

	}
	
	public void PushOption()
    {
        //  SE再生(メニュープッシュ音)
        AudioManager.Instance.PlaySE("[se]menu");

		if (FadeOutJudge == false) 
        {
			Application.LoadLevelAdditive ("Option");
		}
	}
}
