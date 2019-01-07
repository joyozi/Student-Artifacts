using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class GravityController : MonoBehaviour
{

	const float Gravity = 9.81f; // 重力加速度定数


	public float GravityScaleY = 10; // 重力加速度定数

	public float MaxGravityScale = 5; // 重力のスケール
	float GravityScale = 1.0f; // 重力のスケール
	public float GravityRate = 0.02f;

	public float GravityVecZ = 0.7f; // 重力のスケール

	public float SpeedSclZF = 10;
	public float SpeedSclZN = 20;
	public float SpeedSclLR = 10;

	public GameObject Player;

	bool bControll;

	bool bDragX;
	bool bDragZ;

	// Use this for initialization
	void Start()
	{
		bDragX = false;
		bDragZ = false;
		bControll = true;
		GravityScale = 1.0f;
	}

	// Update is called once per frame
	void Update()
	{
		//ベクトル初期化
		Vector3 vector = new Vector3();

		if (bControll == true)
		{
			//Unityエディタと実機で処理を分ける
			if (Application.isEditor)
			{
				//キー入力でベクトル設定
				vector.x = Input.GetAxis("Horizontal") * 5;
				vector.z = Input.GetAxis("Vertical") * 7;

				//高さ方向判定（?）
				if (Input.GetKey("z"))
				{
					vector.y = 1.0f;
				}
				else
				{
					vector.y = -1.0f;
				}
			}
			else
			{
				//加速度センサーの重力をunityの空間軸にマッピング
				if (bDragX)
				{
					vector.x = Input.acceleration.x * SpeedSclLR * 0.3f;
				}
				else
				{
					vector.x = Input.acceleration.x * SpeedSclLR;
				}

				vector.z = (Input.acceleration.y + GravityVecZ);
				vector.y = -1.0f;

				if (bDragZ)
				{
					if (vector.z < 0.0f)
					{
						vector.z = vector.z * SpeedSclZN * 0.3f;
					}
					else
					{
						vector.z = vector.z * SpeedSclZF * 0.3f;
					}
				}
				else
				{
					if (vector.z < 0.0f)
					{
						vector.z = vector.z * SpeedSclZN;
					}
					else
					{
						vector.z = vector.z * SpeedSclZF;
					}
				}
			}
		}
		else
		{
			//操作不可の場合
			vector = new Vector3(0.0f, -1.0f, 0.0f);
		}

		//だんだん加速処理
		if (Mathf.Abs(vector.normalized.x) + Mathf.Abs(vector.normalized.z) > 0.2f)
		{
			GravityScale += GravityRate;
		}

		//最大値を超えないように設定
		if (GravityScale > MaxGravityScale)
		{
			GravityScale = MaxGravityScale;
		}

		//シーンの重力を入力ベクトルの方向に合わせて変化
		Physics.gravity = new Vector3(vector.x * Gravity * GravityScale, vector.y * Gravity * GravityScaleY, vector.z * Gravity * GravityScale);
	}

	//方向別重力の大きさ切り替え
	public void EnableDragX(bool bDrag)
	{
		bDragX = bDrag;
	}
	public void EnableDragZ(bool bDrag)
	{
		bDragZ = bDrag;
	}

	//重力操作ONOFF切り替え
	public void EnebleControll(bool bEneble)
	{
		bControll = bEneble;
	}

	//重力加速度セット
	public void SetGravityScale(float scl)
	{
		GravityScale = scl;
	}
}

