using UnityEngine;
using System.Collections;

public class Credit : MonoBehaviour {

	// Update is called once per frame
	void Update () {
		if(Input.GetMouseButtonUp(0)){
			Destroy(this.gameObject);
		}
	}
}
