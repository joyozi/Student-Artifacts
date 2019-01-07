using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class Option : MonoBehaviour {

	public GameObject AndroidRextTex;
	public Text AndroidRextText;
	public Text SoundOnOffText;

	private int AndroidRectRot;

	// Use this for initialization
	void Start () {
		AndroidRectRot = 0;
		AndroidRectRot = int.Parse(GameObject.FindWithTag ("GameInfo").GetComponent<GameInfo> ().GetGameInfoData ((int)(GAMEINFOLIST.INFO_PLAYSTILE)));

		AndroidRextTex.transform.rotation = Quaternion.Euler(0.0f,0.0f,AndroidRectRot);
		AndroidRextText.text = AndroidRectRot.ToString () + "°";

		if(GameObject.FindWithTag ("GameInfo").GetComponent<GameInfo> ().GetGameInfoData ((int)(GAMEINFOLIST.INFO_SOUND)) == "0"){
			SoundOnOffText.text = "ON";		
		}
		else{
			SoundOnOffText.text = "OFF";		
		}
	}
	
	// Update is called once per frame
	void Update () {
	
	}

	public void OptionButton_Close(){
		gameObject.SetActive(false);
		Destroy(this.gameObject);
	}

	public void OptionButton_Sound(){
		if(GameObject.FindWithTag ("GameInfo").GetComponent<GameInfo> ().GetGameInfoData ((int)(GAMEINFOLIST.INFO_SOUND)) == "0"){
			GameObject.FindWithTag ("GameInfo").GetComponent<GameInfo> ().SetGameInfoData ((int)(GAMEINFOLIST.INFO_SOUND),"1");
			SoundOnOffText.text = "OFF";		
		}
		else{
			GameObject.FindWithTag ("GameInfo").GetComponent<GameInfo> ().SetGameInfoData ((int)(GAMEINFOLIST.INFO_SOUND),"0");
			SoundOnOffText.text = "ON";
		}
	}


	public void OptionButton_AndroidRect(){

		switch ((int)(AndroidRectRot)) {
		case 25:
			AndroidRectRot = 90;
			break;
		
		case 45:
			AndroidRectRot = 25;
			break;

		case 90:
			AndroidRectRot = 45;
			break;

		default:
			AndroidRectRot = 45;
			break;
		}

		GameObject.FindWithTag ("GameInfo").GetComponent<GameInfo> ().SetGameInfoData ((int)(GAMEINFOLIST.INFO_PLAYSTILE),AndroidRectRot.ToString());
		AndroidRextTex.transform.rotation = Quaternion.Euler(0,0,AndroidRectRot);
		AndroidRextText.text = AndroidRectRot.ToString () + "°";
	}
}
