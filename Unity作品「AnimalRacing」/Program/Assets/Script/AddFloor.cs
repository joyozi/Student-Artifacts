using UnityEngine;
using System.Collections;

public class AddFloor : MonoBehaviour {

	public Vector3 AddVec;			//加速するベクトル
	public float   BlurScl = 0.5f;

	// Use this for initialization
	void Start () {

	}
	
	// Update is called once per frame
	void Update () {
		
	}

	// 当たった時の処理
	//----------------------------------------------------------------
	private void OnTriggerEnter(Collider other)
	{
/*		Vector3 AddRotated;
		Vector3 euler = new Vector3(transform.eulerAngles.x / 360, transform.eulerAngles.y / 360, transform.eulerAngles.z / 360);

		AddRotated = new Vector3(AddVec.x, AddVec.y + AddVec.z * Mathf.Sign(euler.x), AddVec.z * Mathf.Cos(euler.x));*/

		other.GetComponent<Rigidbody>().AddForce(AddVec);
		GameObject GC = GameObject.FindWithTag("GravityController"); ;
		GC.GetComponent<GravityController>().EnableDragX(true);

        //  SE再生(加速音)
        AudioManager.Instance.PlaySE("[se]speedup");

		GameObject MainCamera = GameObject.FindWithTag("MainCamera");
		MainCamera.GetComponent<UnityStandardAssets.ImageEffects.MotionBlur>().SetBlur(BlurScl);

		Camera camera = GameObject.FindWithTag("MainCamera").GetComponent<Camera>();
		camera.fieldOfView = 80;
	}
}
