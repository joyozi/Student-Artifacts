//=============================================================
//    オブジェクトの追従処理  [Chase.cs]
//
//    Auther: Naoto Kurita
//=============================================================

using UnityEngine;
using System.Collections;

public class Chase : MonoBehaviour {

	public GameObject targetObj;		//追従するオブジェクト
	public Vector3 offSet;				//追従するオブジェクトとの距離

	public bool ChaseX = true;
	public bool ChaseY = true;
	public bool ChaseZ = true;

	bool bChase;

	// Use this for initialization
	void Start () {
		bChase = true;
		UpdatePosition();
	}

	// Update is called once per frame
	void Update()
	{

	}

	// Update is called once per frame
	void FixedUpdate()
	{
		if(bChase == true) UpdatePosition();
	}

	// 追従処理
	//-----------------------------------------------------------------
	void UpdatePosition()
	{
		Vector3 pos = targetObj.transform.localPosition;
		Vector3 oldPos = transform.localPosition;
		transform.localPosition = pos + offSet;

		if (ChaseX == false)
		{
			transform.localPosition = new Vector3(oldPos.x, transform.localPosition.y, transform.localPosition.z);
		}
		if (ChaseY == false)
		{
			transform.localPosition = new Vector3(transform.localPosition.x, oldPos.y, transform.localPosition.z);
		}
		if (ChaseZ == false)
		{
			transform.localPosition = new Vector3(transform.localPosition.x, transform.localPosition.y, oldPos.z);
		}
	}

}
