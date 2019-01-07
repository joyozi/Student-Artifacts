using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class ResultMyTimeSet : MonoBehaviour {

	public Text MyTimeTextObj;

	private GameObject GameInfoObj;


	// Use this for initialization
	void Start () {
		GameInfoObj = GameObject.Find ("GameInfoScript_Static");

		MyTimeTextObj.text = GameInfoObj.GetComponent<GameInfo> ().GetGameInfoData ((int)(GAMEINFOLIST.INFO_GOALTIME));
	
	
	
	}
}
