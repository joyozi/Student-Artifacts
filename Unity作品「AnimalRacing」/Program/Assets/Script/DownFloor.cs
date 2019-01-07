using UnityEngine;
using System.Collections;

public class DownFloor : MonoBehaviour {

	public float DownDrag = 3.0f;
	public float Drag     = 1.5f;

	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
	
	}

	// 当たっている時の処理
	//----------------------------------------------------------------
	private void OnTriggerStay(Collider other)
	{
		other.GetComponent<Rigidbody>().drag = DownDrag;
	}

	// 当たり判定から外れた時の処理
	//----------------------------------------------------------------
	private void OnTriggerExit(Collider other)
	{
		other.GetComponent<Rigidbody>().drag = Drag;
	}
}
