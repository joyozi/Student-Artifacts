using UnityEngine;
using System.Collections;

public class wani : MonoBehaviour {

	bool bPlay = false;
	float fTime = 0.0f;

	// Use this for initialization
	void Start () {
		GetComponent<Animator>().StopPlayback();
		bPlay = false;
		fTime = 0.0f;
		GetComponent<Animator>().speed = 0;
	}
	
	// Update is called once per frame
	void FixedUpdate () {
		if (bPlay == true)
		{
			fTime += Time.deltaTime;

			if (fTime >= 0.5f)
			{
				GetComponent<Animator>().speed = 0;
				bPlay = false;
				fTime = 0.0f;
			}

			if(fTime >= 0.48f)
			{
				fTime = 0.5f;
			}

		}
	}

	void OnTriggerEnter(Collider other)
	{
		if(other.tag == "Player")
		{
			bPlay = true;
			GetComponent<Animator>().speed = 1;
		}
	}
}
