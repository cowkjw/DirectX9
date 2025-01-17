class CSoundManager
{
private:
    static CSoundManager* m_pInstance;
    CSoundManager();
    virtual ~CSoundManager();

public:
    static CSoundManager* GetInstance()
    {
        if (nullptr == m_pInstance)
        {
            m_pInstance = new CSoundManager;
            m_pInstance->Initialize();
        }
        return m_pInstance;
    }

    static void Destroy_Instance()
    {
        if (m_pInstance)
        {
            delete m_pInstance;
            m_pInstance = nullptr;
        }
    }

    void LoadSound(const string& name, const string& filePath, bool isStream = false, bool loop = false);
    void PlayEffect(const string& name, bool loop = false);
    void PlayBGM(const string& name, bool loop = true);
    bool IsSoundPlaying(const string& name);
    void StopBGM();
    void StopAllSounds();
    void Update();
    void Initialize();
    void Release();

private:
    System* m_System;
    unordered_map<string, Sound*> m_Sounds;
    Channel* m_BGMChannel;
};