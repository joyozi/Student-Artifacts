using UnityEngine;
using System.Collections;
using UnityEngine.EventSystems;

public class GameStopButton : MonoBehaviour {

	private bool PauseJudge;
	private GameObject PauseMenuCanvas;

	void Awake(){
		PauseMenuCanvas = GameObject.Find ("PauseMenu");
		PauseMenuCanvas.SetActive (false);
	}

	public void PushStopButton()
    {

        //  SE再生(メニュープッシュ音)
        AudioManager.Instance.PlaySE("[se]menu");

		if(GameObject.FindWithTag("GameFade").GetComponent<fade>().GetFadeState() == 0){

			if (PauseJudge) 
            {
				PauseJudge = false;
				Time.timeScale = 1;
			}
            else
            {
				PauseJudge = true;
				Time.timeScale = 0;
			}

			foreach (Transform child in GameObject.Find("Canvas_Touma").transform) {
				// 子の要素をたどる
				if (child.name == "PauseMenu") {
					// 指定した名前と一致
					// 表示フラグを設定
					child.gameObject.SetActive (PauseJudge);
					// おしまい
					return;
				}
			}
		}
	}
}





