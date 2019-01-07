using UnityEngine;
using System.Collections;

public enum STARTFADE
{
	FADE_NONE = 0,
	FADE_IN,
	FADE_OUT,
	FADE_MAX
};


public class fade : MonoBehaviour
{
	// フェードイン、フェードアウト
	private Texture2D texture;
	private Color from;
	private Color to;
	private Color now; 
	private float time;
	private float now_time;

	public float FadeinTime;
	public float FadeoutTime;
	public STARTFADE StartFade;

	void Awake()
	{
		texture = new Texture2D( 1, 1, TextureFormat.ARGB32, false );
		texture.SetPixel(0,0, Color.black );
		texture.Apply();
	}
	
	void Start () {
		switch(StartFade)
		{
		case STARTFADE.FADE_IN:
			FadeIn( Color.black );
			break;
			
		case STARTFADE.FADE_OUT:
			FadeOut( Color.black );
			break;
			
		default:
			break;
		}
	}
	
	public void Update () {
		if( Input.GetKeyDown (KeyCode.K)){
			FadeIn( Color.black );
		}
		if( Input.GetKeyDown (KeyCode.L)){
			FadeOut( Color.black );
		}

		if (0 < time && now_time < time) {
			now = Color.Lerp (from, to, now_time / time);

			now_time += 1.0f * Time.deltaTime;

		} else {
			StartFade = STARTFADE.FADE_NONE;
			now = to;
		}
	}


	
	public void OnGUI()
	{
		//たまにフェードが途中で止まるからここで行ってみる
		if (now.a != 0) {
			GUI.color = now;
			GUI.DrawTexture (new Rect (0, 0, Screen.width, Screen.height), texture);
		}
	}

	public void FadeIn( Color t_color)
	{
		to = from = t_color;
		to.a = 0;
		time = FadeinTime;
		StartFade = STARTFADE.FADE_IN;

		now_time = 0;
	}
	
	
	public void FadeOut( Color t_color)
	{
		to = from = t_color;
		from.a = 0;
		time = FadeoutTime;
		StartFade = STARTFADE.FADE_OUT;

		now_time = 0;
	}

	public int GetFadeState()
	{
		return (int)(StartFade);
	}
}


