using UnityEngine;
using System.Collections;

public class BackGroundScroller : MonoBehaviour {
	public float speed = 50;
	public Vector2 OwnBgVector;

	private Vector3 OriginPos;

	void Start(){
		OriginPos = transform.localPosition;
	}

	void Update () {
		// 左下へ移動
		transform.localPosition -= new Vector3 (speed * Time.deltaTime, speed * Time.deltaTime);


		if (transform.localPosition.x <= -OwnBgVector.x * 3/2) {
				transform.localPosition = new Vector3(OwnBgVector.x / 2,OriginPos.y,0.0f);
		}
	}
}