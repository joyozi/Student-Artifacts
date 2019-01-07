using UnityEngine;
using System.Collections;
using System.IO;

public class player : MonoBehaviour {

	enum PLAYER_STATE
	{
		PLAYER_STATE_PLAY,
		PLAYER_STATE_RESPAWN,
		PLAYER_STATE_GOAL
	};

	public float   fJumpHeight   = 1000.0f;
	public Vector3       maxSpeed      = new Vector3(50.0f, 0.0f, 80.0f);
	public GameObject    playerObj;
	GameObject           Shadow;

	bool                 bOperation;			//操作可能か
	bool                 bJump;					//ジャンプ中かどうか
	bool                 bDrag;					//動き遅いモードか
	bool                 hitWani;
	int                  jumpCount;				//ジャンプのフラグ切り替え用
	int                  dragCount;
	public const int     DragingTime = 60;		//動き初めのゆっくり移動時間

	Vector3              GoalPosition;
	Vector3              GoaledPosition;
	public const float   GoalBezierLate = 0.01f;

	Vector3              FallPosition;			//落下位置
	Vector3              RespawnPosition;		//リスポーンする位置
	public const float   RespornJumpHeight = 30.0f;
	public const int     RespawnFrame = 90;		//リスポーンするまでの時間
	public const int     RespawnWait = 20;		//リスポーンしてから動けるようになるまでの待機時間
	public const float   RespawnBezierLate = 0.02f;		//リスポーンするまでの時間
	public const float   GoalLate = 0.04f;		//リスポーンするまでの時間
	float BezierTime;
	int                  GoalCount;
	int                  RespawnCount;
	int                  RespawnWaitCount;

	public const int     maxRecordTime = 80;	//ゴーストを記録する時間
	public const int     FPR           = 1;		//何フレーム毎にレコードを記録するか
	Vector3[]            ghostPos      = new Vector3[maxRecordTime * 60 / FPR];			//ゴーストの情報を格納
	int                  nGhostCnt;				//ゴーストの情報数カウント用

	PLAYER_STATE         state;

	public Material[]    Materials = new Material[4];
	Renderer      Renderers;
	Quaternion    AngleGoal;

	// Use this for initialization
	void Start () {
		Renderers = GameObject.FindWithTag("AnimalBall").GetComponent<Renderer>();
		Renderers.material = Materials[Random.Range(0, 4)];
		bJump            = false;
		bOperation       = false;
		nGhostCnt        = 0;
		GhostRecord();
		RespawnPosition  = transform.localPosition;
		state            = PLAYER_STATE.PLAYER_STATE_PLAY;
		jumpCount        = 0;
		RespawnCount     = 0;
		RespawnWaitCount = 0;
		BezierTime       = 0.0f;
		Shadow = GameObject.FindWithTag("Shadow");
		dragCount        = 0;
		bDrag            = false;
		AngleGoal        = transform.rotation;
		hitWani          = false;
	}

	// Update is called once per frame
	void Update () {
		switch (state)
		{
			case PLAYER_STATE.PLAYER_STATE_PLAY:
				UpdatePlay();
				break;

			case PLAYER_STATE.PLAYER_STATE_RESPAWN:
//				UpdateRespawn();
				break;

			case PLAYER_STATE.PLAYER_STATE_GOAL:
				break;
		}
	}

	//状態毎の更新@Play
	//----------------------------------------------------------------
	void UpdatePlay()
	{
		Rigidbody rigidBody = playerObj.GetComponent<Rigidbody>();

		//抵抗をつけている場合
		if(bDrag == true)
		{
			dragCount++;
			if (dragCount > DragingTime)
			{
				EnableDrag(false);
				dragCount = 0;
			}
		}

		//影の位置設定
		SetPosShadow();

		//プレイヤーが操作可能状態になかったらスキップ
		if (bOperation == true)
		{
			//ゴースト情報の記録
			GhostRecord();

			//	マウスのボタン左クリック
			if (Input.GetMouseButtonDown(0) && !bJump)
			{
				bJump = true;
				rigidBody.AddForce(0, fJumpHeight, 0);

				//	SE再生(プレイヤージャンプSE)
				AudioManager.Instance.PlaySE("[se]player_jump");
			}


			//速度制限処理
			if (maxSpeed.x < Mathf.Abs(rigidBody.velocity.x))
			{
				if (rigidBody.velocity.x > 0)
				{
					rigidBody.velocity = new Vector3(maxSpeed.x, rigidBody.velocity.y, rigidBody.velocity.z);
				}
				else
				{
					rigidBody.velocity = new Vector3(-maxSpeed.x, rigidBody.velocity.y, rigidBody.velocity.z);
				}
			}
			if (maxSpeed.z < Mathf.Abs(rigidBody.velocity.z))
			{
				if (rigidBody.velocity.z > 0)
				{
					rigidBody.velocity = new Vector3(rigidBody.velocity.x, rigidBody.velocity.y, maxSpeed.z);
				}
				else
				{
					rigidBody.velocity = new Vector3(rigidBody.velocity.x, rigidBody.velocity.y, -maxSpeed.z);
				}
			}
		}

	}

	//状態毎の更新@Respawn
	//----------------------------------------------------------------
	void UpdateRespawn()
	{
		GameObject GC;	//GravityController

		RespawnCount++;

		//ゴースト情報の記録
		GhostRecord();

		if(RespawnCount == RespawnFrame)
		{
			//落下した場所に位置を移動
			transform.position = FallPosition;
			Rigidbody r = GetComponent<Rigidbody>();
			r.isKinematic = true;
			//カメラの追従オン
			GameObject camera = GameObject.FindWithTag("MainCamera"); ;
			camera.GetComponent<ChaseCamera>().EnebleChase(true);

			GC = GameObject.FindWithTag("GravityController");
			GC.GetComponent<GravityController>().EnebleControll(false);

			//	SE再生(プレイヤーリスポーンSE)
			AudioManager.Instance.PlaySE("[se]respawn");
		}

		if (RespawnCount > RespawnFrame && BezierTime <= 1.0f)
		{
			Vector3 pos;
			//位置更新
			pos.x = (1.0f - BezierTime) * (1.0f - BezierTime) * (1.0f - BezierTime) * FallPosition.x +
					3.0f * (1.0f - BezierTime) * (1.0f - BezierTime) * BezierTime * FallPosition.x +
					3.0f * (1.0f - BezierTime) * BezierTime * BezierTime * RespawnPosition.x +
					BezierTime * BezierTime * BezierTime * RespawnPosition.x;

			pos.y = (1.0f - BezierTime) * (1.0f - BezierTime) * (1.0f - BezierTime) * FallPosition.y +
					3.0f * (1.0f - BezierTime) * (1.0f - BezierTime) * BezierTime * (FallPosition.y + RespornJumpHeight) +
					3.0f * (1.0f - BezierTime) * BezierTime * BezierTime * (FallPosition.y + RespornJumpHeight) +
					BezierTime * BezierTime * BezierTime * RespawnPosition.y;

			pos.z = (1.0f - BezierTime) * (1.0f - BezierTime) * (1.0f - BezierTime) * FallPosition.z +
					3.0f * (1.0f - BezierTime) * (1.0f - BezierTime) * BezierTime * FallPosition.z +
					3.0f * (1.0f - BezierTime) * BezierTime * BezierTime * RespawnPosition.z +
					BezierTime * BezierTime * BezierTime * RespawnPosition.z;

			transform.position = pos;

			//ライフを減らす
			BezierTime += RespawnBezierLate;
		}
		else if (RespawnCount > RespawnFrame && BezierTime >= 1.0f)
		{
			RespawnWaitCount++;

			//指定時間経過で操作可能に
			if (RespawnWait < RespawnWaitCount)
			{
				//各カウント初期化
				RespawnWaitCount = 0;
				BezierTime = 0.0f;
				RespawnCount = 0;

				Rigidbody r = GetComponent<Rigidbody>();
				r.isKinematic = false;
				state = PLAYER_STATE.PLAYER_STATE_PLAY;
				EnableDrag(true);
				GC = GameObject.FindWithTag("GravityController");
				GC.GetComponent<GravityController>().EnebleControll(true);
				GameObject.FindWithTag("GravityController").GetComponent<GravityController>().SetGravityScale(1.0f);
			}
		}
	}

	//状態毎の更新@Goal
	//----------------------------------------------------------------
	void UpdateGoal()
	{
		Vector3 pos;
		if(hitWani == true)
		{
			if (BezierTime <= 1.0f)
			{
				//位置更新
				pos.x = (1.0f - BezierTime) * (1.0f - BezierTime) * (1.0f - BezierTime) * GoalPosition.x +
						3.0f * (1.0f - BezierTime) * (1.0f - BezierTime) * BezierTime * GoalPosition.x +
						3.0f * (1.0f - BezierTime) * BezierTime * BezierTime * GoaledPosition.x +
						BezierTime * BezierTime * BezierTime * GoaledPosition.x;

				pos.y = (1.0f - BezierTime) * (1.0f - BezierTime) * (1.0f - BezierTime) * GoalPosition.y +
						3.0f * (1.0f - BezierTime) * (1.0f - BezierTime) * BezierTime * (GoalPosition.y + 50.0f) +
						3.0f * (1.0f - BezierTime) * BezierTime * BezierTime * (GoaledPosition.y + 50.0f) +
						BezierTime * BezierTime * BezierTime * GoaledPosition.y;

				pos.z = (1.0f - BezierTime) * (1.0f - BezierTime) * (1.0f - BezierTime) * GoalPosition.z +
						3.0f * (1.0f - BezierTime) * (1.0f - BezierTime) * BezierTime * GoalPosition.z +
						3.0f * (1.0f - BezierTime) * BezierTime * BezierTime * GoaledPosition.z +
						BezierTime * BezierTime * BezierTime * GoaledPosition.z;

				transform.position = pos;

				//ライフを減らす
				BezierTime += GoalBezierLate;

			}

			transform.rotation = AngleGoal;
		}
		else
		{
			pos.x = (GoaledPosition.x - transform.position.x) * GoalLate;
			pos.y = (GoaledPosition.y - transform.position.y) * GoalLate;
			pos.z = (GoaledPosition.z - transform.position.z) * GoalLate;
			transform.position += pos;
		}
	}

	//一番先に更新
	//----------------------------------------------------------------
	void FixedUpdate()
	{
		//ジャンプフラグ初期化
		bJump = true;
		//ジャンプフラグを立てる
		Vector3 dir = new Vector3(0.0f, -1.0f, 0.0f);
		if (Physics.Raycast(transform.position, dir, 1.0f))
		{
			bJump = false;
		}

		if (state == PLAYER_STATE.PLAYER_STATE_RESPAWN) UpdateRespawn();
		if (state == PLAYER_STATE.PLAYER_STATE_GOAL)    UpdateGoal();
	}

	//一番後に更新
	//----------------------------------------------------------------
	void LateUpdate()
	{
		//影の位置設定
		SetPosShadow();
	}

	//あたり判定にあたっている間の処理
	//----------------------------------------------------------------
	private void OnCollisionStay(Collision coll)
	{
		//床に当たっている間はジャンプ可能
		if (coll.gameObject.tag == "floor")
		{
			if (bDrag == false)
			{
				GameObject GC = GameObject.FindWithTag("GravityController");
				GC.GetComponent<GravityController>().EnableDragX(false);
			}
		}
	}

	//あたり判定に入った瞬間の距離
	//----------------------------------------------------------------
	private void OnTriggerEnter(Collider coll)
	{
		//スポナーに当たったらスポーン場所更新
		if (coll.gameObject.tag == "Spawner")
		{
			RespawnPosition = coll.gameObject.transform.position;
		}

		//水に当たったらその地点を登録
		if( state == PLAYER_STATE.PLAYER_STATE_PLAY)
		{
			if(coll.gameObject.tag == "water")
			{
				FallPosition = transform.position;
				state = PLAYER_STATE.PLAYER_STATE_RESPAWN;
				GameObject camera = GameObject.FindWithTag("MainCamera");
				camera.GetComponent<ChaseCamera>().EnebleChase(false);

				//	SE再生(ゴールSE)
				AudioManager.Instance.PlaySE("[se]dead");
			}
		}

		if (coll.tag == "Goal")
		{
			//ゴール後の目的地格納
			GoaledPosition = new Vector3(coll.transform.position.x, coll.transform.position.y + 2.0f, coll.transform.position.z + 3.0f);
			state = PLAYER_STATE.PLAYER_STATE_GOAL;
			bOperation = false;
			GameObject GC = GameObject.FindWithTag("GravityController");
			GC.GetComponent<GravityController>().EnebleControll(false);

			//  前のBGMをフェードアウト
			AudioManager.Instance.FadeOutBGM(1.0f);	

			//	SE再生(ゴールSE)
			AudioManager.Instance.PlaySE("[se]goal");
		}

		if (coll.tag == "GoalWani")
		{
			if (hitWani == false)
			{
				hitWani = true;
				GoaledPosition = new Vector3(GameObject.FindWithTag("Goal").transform.position.x, GameObject.FindWithTag("Goal").transform.position.y + 2.0f, GameObject.FindWithTag("Goal").transform.position.z);
				GoalPosition = new Vector3(transform.position.x, transform.position.y, transform.position.z);
				BezierTime = 0.0f;

				GetComponent<Rigidbody>().velocity = new Vector3(0.0f, 0.0f, 0.0f);
				GameObject camera = GameObject.FindWithTag("MainCamera");
				camera.GetComponent<ChaseCamera>().EnebleChase(false);
				camera.GetComponent<ChaseCamera>().SetDirPos(new Vector3(GoaledPosition.x, GoaledPosition.y + 3.0f, GoaledPosition.z - 4.0f));
			}
		}
	}

	//ジャンプできるかを設定
	public void EnableJump(bool Jump)
	{
		bJump = Jump;
	}

	//ゴースト情報を保存
	private void GhostRecord()
	{
		if(nGhostCnt < maxRecordTime * 60 / FPR)
		{
			ghostPos[nGhostCnt] = transform.localPosition;
			nGhostCnt++;
		}
	}

	//ファイルに書き出し
	public void GhostWriter()
	{
		if (nGhostCnt < maxRecordTime * 60 / FPR)
		{

			//Unityエディタと実機で処理を分ける
			if (Application.isEditor)
			{
				using (StreamWriter w = new StreamWriter(Application.streamingAssetsPath + "/test.txt"))
				{
					for(int i = 0; i < nGhostCnt; i++)
					{
						w.WriteLine(ghostPos[i].x.ToString());
						w.WriteLine(ghostPos[i].y.ToString());
						w.WriteLine(ghostPos[i].z.ToString());
					}
				}
			}
			else
			{
				//いったんファイルに保存
				string path = Application.persistentDataPath + "/test2.txt";
				using (StreamWriter sw = new StreamWriter(path))
				{
					for (int i = 0; i < nGhostCnt; i++)
					{
						sw.WriteLine(ghostPos[i].x.ToString());
						sw.WriteLine(ghostPos[i].y.ToString());
						sw.WriteLine(ghostPos[i].z.ToString());
					}
				}
			}
		}
	}

	//操作可能な状態かを示す
	//----------------------------------------------------------------
	public bool IsOperation()
	{
		return bOperation;
	}

	//操作ONOFF切り替え
	//----------------------------------------------------------------
	public void EnableOperation(bool bEnable)
	{
		bOperation = bEnable;
		Rigidbody rigidBody = playerObj.GetComponent<Rigidbody>();

		//動かすよう設定されていたら
		if (bOperation == true)
		{
			rigidBody.isKinematic = false;
		}
		else
		{	//動かないように設定されていたら
			//動きを止めて重力の影響をなくす
			rigidBody.velocity = new Vector3(0, 0, 0);
			rigidBody.isKinematic = true;
		}
	}

	//リスポーン場所設定
	public void SetRespawnPos(Vector3 pos)
	{
		RespawnPosition = pos;
	}

	//影の位置設定関数
	private void SetPosShadow()
	{
		if(Shadow)
		{
			Vector3 vec = transform.localPosition;
			Shadow.transform.localPosition = new Vector3(vec.x, vec.y, vec.z);
		}
	}

	//動き抑制切り替え
	private void EnableDrag(bool bEneble)
	{
		bDrag = bEneble;
		GameObject GC = GameObject.FindWithTag("GravityController");
		GC.GetComponent<GravityController>().EnableDragX(bEneble);
		GC.GetComponent<GravityController>().EnableDragZ(bEneble);
	}
}