using UnityEngine;
using System.Collections;

public class ChaseCamera : MonoBehaviour {

	public GameObject targetObj;		//追従するオブジェクト
	public Vector3    offSet;			//追従するオブジェクトとの距離
	public float      lookFar;			//奥を見ているときの回転

	float   posRZ;
	float   posRX;
	Vector3 dirPos;
	Vector3 pos;
	bool    bChase;

	public float lookSpeedLR = 0.087f;
	public float lookSpeedNF = 0.1f;
	public float lookLenNear = 20;			//追従するものと注視点の距離
	public float lookLenFar  = 9;			//			↓
	public float lookLenLR   = 13;			//			↓
	public int   transRFrame = 10;	//注視点を移動させるフレーム

	public float fInertia;		//慣性の強さ

	// Use this for initialization
	void Start()
	{
		posRZ  = 0;
		posRX  = 0;
		bChase = true;
		UpdatePosition();
		transform.localPosition = dirPos;
	}

	// Update is called once per frame
	void Update()
	{

	}

	// 追従処理
	//-----------------------------------------------------------------
	void UpdatePosition()
	{
		//ポジション取得
		pos = targetObj.transform.localPosition;

		pos = pos + offSet;

		if (bChase == true)
		{
			//重力(移動方向)に合わせてカメラの位置移動
			//-----------------------------------------------------------------↓
			if (Physics.gravity.x > 30.0f)
			{
				if (Physics.gravity.x > 90.0f)
				{
					posRX += (lookLenLR - posRX) * lookSpeedLR;
				}
				else
				{
					posRX += (lookLenLR * 0.5f - posRX) * lookSpeedLR;
				}
			}
			else if (Physics.gravity.x < -30.0f)
			{
				if (Physics.gravity.x < -90.0f)
				{
					posRX += (-lookLenLR - posRX) * lookSpeedLR;
				}
				else
				{
					posRX += (-lookLenLR * 0.5f - posRX) * lookSpeedLR;
				}
			}
			else
			{
				posRX += (0.0f - posRX) * 0.1f;
			}

			if (Physics.gravity.z > 30.0f)
			{
				if (Physics.gravity.z > 90.0f)
				{
					posRZ += (lookLenFar - posRZ) * lookSpeedNF;
				}
				else
				{
					posRZ += (lookLenFar * 0.5f - posRZ) * lookSpeedNF;
				}
			}
			else if (Physics.gravity.z < -30.0f)
			{
				if (Physics.gravity.z < -90.0f)
				{
					posRZ += (-lookLenNear - posRZ) * lookSpeedNF;
				}
				else
				{
					posRZ += (-lookLenNear * 0.5f - posRZ) * lookSpeedNF;
				}
			}
			else
			{
				posRZ += (0.0f - posRZ) * 0.1f;
			}
			//-----------------------------------------------------------------↑

			dirPos = new Vector3(pos.x + posRX, pos.y, pos.z + posRZ);
		}

		transform.localPosition += (dirPos - transform.localPosition) * fInertia;
	}

	void FixedUpdate()
	{
		//場所更新
		UpdatePosition();

		Camera camera = GameObject.FindWithTag("MainCamera").GetComponent<Camera>();
		camera.fieldOfView += (75.0f - camera.fieldOfView) * 0.05f;
	}


	//追尾更新切り替え
	//-----------------------------------------------------------------
	public void EnebleChase(bool bEneble)
	{
		bChase = bEneble;
	}

	//ポジションをキャラの後ろに移動
	public void ResetPos()
	{
		dirPos =
		transform.position = targetObj.transform.localPosition + offSet;
	}

	public void SetOffset(Vector3 vec)
	{
		offSet = vec;
	}

	public void SetDirPos(Vector3 pos)
	{
		dirPos = pos;
	}

}
