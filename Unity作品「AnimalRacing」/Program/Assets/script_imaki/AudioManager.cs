using UnityEngine;
using System.Collections;
using System.Collections.Generic;

////////////////////////////////////////////////////////////////////////////////////////////////////
///	オーディオマネージャークラス(シングルトンでの運用)
////////////////////////////////////////////////////////////////////////////////////////////////////
public class AudioManager : SingletonMonoBehaviour<AudioManager>
{

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// 各種定数・変数の宣言
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    //	ボリューム保存用のkeyとデフォルト値
    private const string BGM_VOLUME_KEY = "BGM_VOLUME_KEY";
    private const string SE_VOLUME_KEY = "SE_VOLUME_KEY";
    private const float BGM_VOLUME_DEFAULT = 0.3f;
    private const float SE_VOLUME_DEFAULT = 1.0f;

    //	BGMがフェードするのにかかる時間
    public const float BGM_FADE_SPEED_RATE_HIGH = 0.9f;
    public const float BGM_FADE_SPED_RATE_LOW = 0.3f;
    private float fBgmFadeSpeedRate = BGM_FADE_SPEED_RATE_HIGH;

    //	次に流すBGM・SE名
    private string nextBGMName;
    private string nextSEName;

    //	BGMフェードアウトフラグ
    private bool isFadeOut = false;

    //	BGM・SE用のオーディオソースをそれぞれ用意する
    public AudioSource AttachBGMSource, AttachSESource;

    //	全Audioを保持
    private Dictionary<string, AudioClip> bgmDic, seDic;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    ///  #END_OF_VARIABLE_DECLATION
    ////////////////////////////////////////////////////////////////////////////////////////////////////


    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// リソースファイルの検索・操作する処理
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    private void Awake()
    {
        if (this != Instance)
        {
            Destroy(this);
            return;
        }

        //  このメソッドを記述することでシーンを跨いでも消えることのないオブジェクトにできる。
        DontDestroyOnLoad(this.gameObject);

        //	リソースフォルダから全SE・BGMのファイルを読み込み設定する
        bgmDic = new Dictionary<string, AudioClip>();
        seDic = new Dictionary<string, AudioClip>();

        //	リストというなのコレクション			↓フォルダパスはここ
        //  Resources以下にあるファイル全てを持ってこれる
        object[] bgmList = Resources.LoadAll("Audio/BGM");
        object[] seList = Resources.LoadAll("Audio/SE");

        //	コレクションを一個ずつ読む(forループのようなもの)
        //	BGMのファイルパスをリスト(コレクション)から検索し代入
        foreach (AudioClip bgm in bgmList)
        {
            bgmDic[bgm.name] = bgm;
        }

        //	SEのファイルパスをリスト(コレクション)から検索し代入
        foreach (AudioClip se in seList)
        {
            seDic[se.name] = se;
        }

    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    ///  #END_OF_AWAKE
    ////////////////////////////////////////////////////////////////////////////////////////////////////


    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// 初期化処理
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    private void Start()
    {
        //	PlayerPrefクラス：int型,float型,string型のデータを各端末に保存する
        //	BGM・SEそれぞれの音量を取得し代入
        AttachBGMSource.volume = PlayerPrefs.GetFloat(BGM_VOLUME_KEY, BGM_VOLUME_DEFAULT);
        AttachSESource.volume = PlayerPrefs.GetFloat(SE_VOLUME_KEY, SE_VOLUME_DEFAULT);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    ///  #END_OF_START
    ////////////////////////////////////////////////////////////////////////////////////////////////////




    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// SE処理
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    //　指定されたSEを再生。　第二引数のdelayに指定した時間だけ再生までの間隔を空ける
    public void PlaySE(string seName, float delay = 0.0f)
    {
        //	SEファイルチェック処理
        if (!seDic.ContainsKey(seName))
        {
            Debug.Log(seName + "という名前のSEがありません＞＜");
            return;
        }

        //	次にお再生するSEを代入
        nextSEName = seName;

        //	指定したメソッド(第一引数)を指定した秒数(第二引数)遅延して呼び出す
        Invoke("DelayPlaySE", delay);
    }


    private void DelayPlaySE()
    {
        //	SEの再生
        AttachSESource.PlayOneShot(seDic[nextSEName] as AudioClip);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    ///  #END_OF_SE_FUNCTION
    ////////////////////////////////////////////////////////////////////////////////////////////////////



    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// BGM処理
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    //  指定されたBGMを再生する。　ただし、再生中の場合は、前BGMをフェードアウトさせてから再生を開始する。
    //  第二引数の『FadeSpeedRate』はフェードアウトのするスピード。
    public void PlayBGM(string bgmName, float FadeSpeedRate = BGM_FADE_SPEED_RATE_HIGH)
    {
        //  BGMファイルチェック
        if(!bgmDic.ContainsKey(bgmName))
        {
            Debug.Log(bgmName + "という名前のBGMがありません＞＜");
            return;
        }

        //  現在BGMが再生されていない場合はそのまま再生を開始する
        if(!AttachBGMSource.isPlaying)
        {
            nextBGMName = "";                                       //  何も再生されてないので代入しない
            AttachBGMSource.clip = bgmDic[bgmName] as AudioClip;    //  再生するBGMのファイルパスをクリップに代入
            AttachBGMSource.Play();                                 //  指定BGMを再生開始
        }

        //  違うBGMが再生されている場合は、再生しているBGMをフェードアウトし再生する。
        //  同じBGMが再生されている場合はスルーする。
        else if (AttachBGMSource.clip.name != bgmName)
        {
            nextBGMName = bgmName;                  //  次に再生するBGMを代入
            FadeOutBGM(FadeSpeedRate);              //  BGMのフェードアウトをリクエストする。
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    ///  #END_OF_SE_FUNCTION
    ////////////////////////////////////////////////////////////////////////////////////////////////////




    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// フェードアウト処理
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    //  流れている曲をフェードアウトする。
    //  『FadeSpeedRate』に指定した割合でフェードアウトの速度が変わる。

    public void FadeOutBGM(float FadeSpeedRate = BGM_FADE_SPED_RATE_LOW)
    {
        fBgmFadeSpeedRate = FadeSpeedRate;      //  フェードアウトのスピードを代入
        isFadeOut = true;                       //  フェードアウトのフラグON
    }


    //  フェードアウト更新処理
    private void Update()
    {
        //  フェードアウトフラグをチェック
        if (!isFadeOut)
        {
            return;
        }

        //  BGMのボリュームを徐々に下げていき、『０』になったらボリュームをMAXに戻してから次のBGMを再生する。
        AttachBGMSource.volume -= Time.deltaTime * fBgmFadeSpeedRate;

        //  ボリュームが『０』の場合
        if (AttachBGMSource.volume <= 0)
        {
            //  BGM停止
            AttachBGMSource.Stop();

            //  ボリュームをデフォルトの大きさに戻す
            AttachBGMSource.volume = PlayerPrefs.GetFloat(BGM_VOLUME_KEY, BGM_VOLUME_DEFAULT);

            //  フェードアウトのフラグOFF
            isFadeOut = false;

            //  BGMファイルをチェックし、NULLでなければ再生
            if (!string.IsNullOrEmpty(nextBGMName))
            {
                PlayBGM(nextBGMName);
            }
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    ///  #END_OF_FADE_OUT
    ////////////////////////////////////////////////////////////////////////////////////////////////////



    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// 個別ボリューム変更処理
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    public void ChangeVolume(float BGMVolume, float SEVolume)
    {
        AttachBGMSource.volume = BGMVolume;
        AttachSESource.volume = SEVolume;

        PlayerPrefs.SetFloat(BGM_VOLUME_KEY, BGMVolume);
        PlayerPrefs.SetFloat(SE_VOLUME_KEY, SEVolume);

    }


    ////////////////////////////////////////////////////////////////////////////////////////////////////
    ///  #END_OF_CHANGE_VOLUME
    ////////////////////////////////////////////////////////////////////////////////////////////////////


}
