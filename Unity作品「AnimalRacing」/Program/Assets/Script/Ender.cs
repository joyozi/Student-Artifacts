using UnityEngine;
using System.Collections;

public class Ender : MonoBehaviour {

	bool bEnd;
	bool bGoResult;
	int  nCount;
	public int nGoResultFrame = 600;

	// Use this for initialization
	void Start () {
		bEnd = false;
		bGoResult = false;
		nCount = 0;
	}

	// Update is called once per frame
	void Update () {

		if(bEnd == true)
		{
			nCount++;

			if(Input.GetMouseButtonDown(0))
			{
				GameObject.FindWithTag("GameFade").GetComponent<fade>().FadeOut(new Color(0.0f, 0.0f, 0.0f, 1.0f));
			}

			if (nCount == nGoResultFrame)
			{
				GameObject.FindWithTag("GameFade").GetComponent<fade>().FadeOut(new Color(0.0f, 0.0f, 0.0f, 1.0f));
			}
			else
			if (nCount > nGoResultFrame)
			{
				if (GameObject.FindWithTag("GameFade").GetComponent<fade>().GetFadeState() == 0)
				{
					//フェードが終わったらリザルトに
					bGoResult = true;
				}
			}
		}
	}

	public void EndGame()
	{
		bEnd = true;
	}

	public bool IsGoResult()
	{
		return bGoResult;
	}
}
