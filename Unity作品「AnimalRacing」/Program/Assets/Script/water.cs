using UnityEngine;
using System.Collections;

public class water : MonoBehaviour {

	public ParticleSystem SprayWater;

	// Use this for initialization
	void Start () {

	}

	// Update is called once per frame
	void Update () {

	}

	//何かと当たったら判定
	private void OnTriggerEnter(Collider other)
	{
		SprayWater.transform.localPosition = other.transform.localPosition;
		SprayWater.Play();
	}
}
