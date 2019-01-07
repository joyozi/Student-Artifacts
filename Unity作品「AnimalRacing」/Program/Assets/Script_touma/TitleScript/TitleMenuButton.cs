using UnityEngine;
using System.Collections;
using System.IO;
using UnityEngine.UI;



//フェードのための前準備用
public enum TITLEMENUACT
{
	TITLEMENUACT_NONE = 0,
	TITLEMENUACT_GAMESTART,
	TITLEMENUACT_OPTION,
	TITLEMENUACT_RANKING,
	TITLEMENUACT_CREDIT,
	TITLEMENUACT_MAX
};

public class TitleMenuButton : MonoBehaviour {

	public fade FadeScriptObj;
	public Text GhostOnOFFText;
	public GameObject ScrollerVerticalObj;


	private bool StateChangeJudge;
	private TITLEMENUACT StateChangeMenuAct;

	private GameObject GameInfoObj;
	private string GameStageNumber;
	private bool GhostOnOffJudge;
	private bool[] GhostDataExistJudge = new bool[64];


	void Start(){
		GameInfoObj = GameObject.FindWithTag ("GameInfo");

		string TextFilename;

		for (int i = 0; i < int.Parse(GameInfoObj.GetComponent<GameInfo>().GetGameInfoData((int)(GAMEINFOLIST.INFO_STAGENUM))); i++) {

			TextFilename = "GhostLoad_Stage" + i.ToString ();

			string path = null;
			//streamingAssets内のパスを指定
			path = Application.streamingAssetsPath + "/" + TextFilename + ".txt";
			
			//コピー先のパスを指定
			string toPath = Application.persistentDataPath + "/" + TextFilename + ".txt";
		
			if (Application.isEditor) {

				//ファイルがあるかどうかのチェック
				string filePass = Application.streamingAssetsPath + "/" + TextFilename + ".txt";
				if(File.Exists(filePass)){
					GhostDataExistJudge [i] = true;
				}

			} else {
				//ファイルがあるかどうかのチェック
				string filePass = Application.persistentDataPath + "/" + TextFilename + "_2.txt";
				if(File.Exists(filePass)){
					GhostDataExistJudge [i] = true;
				}
			}
		}



		
		if (GameInfoObj.GetComponent<GameInfo> ().GetGameInfoData ((int)(GAMEINFOLIST.INFO_GHOSTAPPEARANCE)) == "0") {
			GhostOnOFFText.text = "ON";
			GhostOnOffJudge = true;
		} else if (GameInfoObj.GetComponent<GameInfo> ().GetGameInfoData ((int)(GAMEINFOLIST.INFO_GHOSTAPPEARANCE)) == "1") {
			GhostOnOFFText.text = "OFF";
			GhostOnOffJudge = false;
		}
	}


	void Update(){
		if (GhostOnOffJudge == false) {
			GhostOnOFFText.text = "OFF";
		} else {
			GhostOnOFFText.text = "ON";
		}





		//もしフェイドがしてなかったら
		if (FadeScriptObj.GetFadeState () == 0 && StateChangeJudge == true) {
			switch (StateChangeMenuAct) {
			case TITLEMENUACT.TITLEMENUACT_GAMESTART:
				GameInfoObj.GetComponent<GameInfo>().SetGameInfoData((int)(GAMEINFOLIST.INFO_SELECTEDSTAGE),GameStageNumber);
				GameInfoObj.GetComponent<GameInfo>().SetGameInfoData((int)(GAMEINFOLIST.INFO_SELECTEDSTAGE_NAME),"Stage" + GameStageNumber);
				Application.LoadLevel ("Stage" + GameStageNumber);
				break;

			case TITLEMENUACT.TITLEMENUACT_RANKING:
				Application.LoadLevel ("Ranking");
				break;

			default:
				break;
			}
		}
	}

	public void PushButton_Stage1(){
		if (FadeScriptObj.GetFadeState () == 0 && StateChangeJudge == false) {
			StateChangeJudge = true;
			FadeScriptObj.FadeOut (Color.black);
			StateChangeMenuAct = TITLEMENUACT.TITLEMENUACT_GAMESTART;

			GameStageNumber = "0";
		}
	}

	public void PushButton_Stage2(){
		if (FadeScriptObj.GetFadeState () == 0 && StateChangeJudge == false) {
			StateChangeJudge = true;
			FadeScriptObj.FadeOut (Color.black);
			StateChangeMenuAct = TITLEMENUACT.TITLEMENUACT_GAMESTART;
			
			GameStageNumber = "1";
		}
	}

	public void PushButton_Stage3(){
		if (FadeScriptObj.GetFadeState () == 0 && StateChangeJudge == false) {
			StateChangeJudge = true;
			FadeScriptObj.FadeOut (Color.black);
			StateChangeMenuAct = TITLEMENUACT.TITLEMENUACT_GAMESTART;
			
			GameStageNumber = "2";
		}
	}

	public void PushButton_Stage4(){
		if (FadeScriptObj.GetFadeState () == 0 && StateChangeJudge == false) {
			StateChangeJudge = true;
			FadeScriptObj.FadeOut (Color.black);
			StateChangeMenuAct = TITLEMENUACT.TITLEMENUACT_GAMESTART;
			
			GameStageNumber = "3";
		}
	}

	public void PushButton_Stage5(){
		if (FadeScriptObj.GetFadeState () == 0 && StateChangeJudge == false) {
			StateChangeJudge = true;
			FadeScriptObj.FadeOut (Color.black);
			StateChangeMenuAct = TITLEMENUACT.TITLEMENUACT_GAMESTART;
			
			GameStageNumber = "4";
		}
	}

	public void PushButton_Stage6(){
		if (FadeScriptObj.GetFadeState () == 0 && StateChangeJudge == false) {
			StateChangeJudge = true;
			FadeScriptObj.FadeOut (Color.black);
			StateChangeMenuAct = TITLEMENUACT.TITLEMENUACT_GAMESTART;
			
			GameStageNumber = "5";
		}
	}

	public void PushButton_Stage7(){
		if (FadeScriptObj.GetFadeState () == 0 && StateChangeJudge == false) {
			StateChangeJudge = true;
			FadeScriptObj.FadeOut (Color.black);
			StateChangeMenuAct = TITLEMENUACT.TITLEMENUACT_GAMESTART;
			
			GameStageNumber = "6";
		}
	}

	public void PushButton_Stage8(){
		if (FadeScriptObj.GetFadeState () == 0 && StateChangeJudge == false) {
			StateChangeJudge = true;
			FadeScriptObj.FadeOut (Color.black);
			StateChangeMenuAct = TITLEMENUACT.TITLEMENUACT_GAMESTART;
			
			GameStageNumber = "7";
		}
	}

	public void PushButton_Stage9(){
		if (FadeScriptObj.GetFadeState () == 0 && StateChangeJudge == false) {
			StateChangeJudge = true;
			FadeScriptObj.FadeOut (Color.black);
			StateChangeMenuAct = TITLEMENUACT.TITLEMENUACT_GAMESTART;
			
			GameStageNumber = "8";
		}
	}


	public void PushButton_GhostAppearance(){
		if (GhostOnOffJudge == false) {
			GhostOnOffJudge = true;
			GameInfoObj.GetComponent<GameInfo>().SetGameInfoData((int)(GAMEINFOLIST.INFO_GHOSTAPPEARANCE),"0");
		} else {
			GhostOnOffJudge = false;
			GameInfoObj.GetComponent<GameInfo>().SetGameInfoData((int)(GAMEINFOLIST.INFO_GHOSTAPPEARANCE),"1");
		}
	}


	public void PushButtonOption(){
		Application.LoadLevelAdditive("Option");
	}

	public void PushButtonRanking(){
		if (FadeScriptObj.GetFadeState () == 0 && StateChangeJudge == false) {
			StateChangeJudge = true;
			FadeScriptObj.FadeOut (Color.black);
			StateChangeMenuAct = TITLEMENUACT.TITLEMENUACT_RANKING;
		}
	}

	public void PushButtonCredit(){
		Application.LoadLevelAdditive("Credit");
	}

}
