using UnityEngine;
using System.Collections;

public class sai : MonoBehaviour {

	public float SaiPower = 3000.0f;

	// Use this for initialization
	void Start () {
	
	}

	// Update is called once per frame
	void Update () {
		
	}

	private void OnTriggerEnter(Collider other)
	{
		Vector3 AddVec = new Vector3(Mathf.Sign(transform.rotation.y) * SaiPower, SaiPower, Mathf.Cos(transform.rotation.y) * SaiPower);
		if (other.tag == "Player")
		{
			other.GetComponent<Rigidbody>().AddForce(AddVec);
		}
	}
}
