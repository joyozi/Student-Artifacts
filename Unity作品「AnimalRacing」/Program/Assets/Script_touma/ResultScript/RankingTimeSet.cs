using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class RankingTimeSet : MonoBehaviour {

	public int RankingNum = 1;		//順位は何番目か
	public Text RankTImeObj;
	public RankingTimeSaved RankingTimeSavedObj;

	// Use this for initialization
	void Start () {
		if (RankingNum > 0 && RankingNum <= 5) {
			RankTImeObj.text = RankingTimeSavedObj.GetRankingTime (RankingNum - 1);
		}
	}
}
