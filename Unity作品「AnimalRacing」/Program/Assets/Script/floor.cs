using UnityEngine;
using System.Collections;

public class floor : MonoBehaviour {

	public const float RespawnHeight = 2.0f;		//リスポーンする高さ
	public bool        IsRespawn     = true;		//触れたらリスポーンするのか

	// Use this for initialization
	void Start () {

	}
	
	// Update is called once per frame
	void Update () {
	
	}

	// 当たっている時の処理
	//----------------------------------------------------------------
	private void OnCollisionStay(Collision coll)
	{
		if (coll.gameObject.tag == "Player")
		{
			Vector3 pos = new Vector3(transform.position.x, transform.position.y + RespawnHeight, transform.position.z);
			if (IsRespawn == true) coll.gameObject.GetComponent<player>().SetRespawnPos(pos);
		}
	}

}
