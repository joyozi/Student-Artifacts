using UnityEngine;
using System.Collections;

public class GoalWani : MonoBehaviour {

	// Use this for initialization
	void Start () {
		GetComponent<Animator>().StopPlayback();
		GetComponent<Animator>().speed = 0;
	}
	
	// Update is called once per frame
	void Update () {
	
	}

	void OnTriggerEnter(Collider other)
	{
		if (other.tag == "Player")
		{
			GetComponent<Animator>().speed = 1;
		}
	}

}
