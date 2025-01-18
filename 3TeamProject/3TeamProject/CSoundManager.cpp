#include "pch.h"
#include "CSoundManager.h"
CSoundManager* CSoundManager::m_pInstance = nullptr;
CSoundManager::CSoundManager() : m_System(nullptr), m_BGMChannel(nullptr) {
    if (System_Create(&m_System) != FMOD_OK)
    {
       cerr << "FMOD ���� ����" << endl;
        return;
    }

    if (m_System->init(512, FMOD_INIT_NORMAL, nullptr) != FMOD_OK) 
    {
        cerr << "FMOD �ʱ�ȭ ����" << endl;
    }
}

CSoundManager::~CSoundManager() 
{
    Release();
}

void CSoundManager::LoadSound(const string& name, const string& filePath, bool isStream, bool loop) {
    FMOD_MODE mode = FMOD_DEFAULT;
    if (isStream)  // ��Ʈ���� ����
    {
        mode |= FMOD_CREATESTREAM;
    }
    if (loop) 
    {
        mode |= FMOD_LOOP_NORMAL;
    }

   Sound* sound = nullptr;
    if (m_System->createSound(filePath.c_str(), mode, nullptr, &sound) != FMOD_OK) 
    {

        return;
    }

    m_Sounds[name] = sound;
}

void CSoundManager::PlayEffect(const string& name, bool loop) 
{

    auto soundIt = m_Sounds.find(name);
    if (soundIt == m_Sounds.end())
    {
        return;
    }

    Channel* channel = nullptr;

    // ���� ä�� ����
    auto channelIt = m_EffectChannels.find(name);
    if (channelIt != m_EffectChannels.end())
    {
        channelIt->second->stop();
        m_EffectChannels.erase(channelIt);
    }

    // �� ä�� ���� �� ���
    if (m_System->playSound(soundIt->second, nullptr, false, &channel) == FMOD_OK)
    {
        if (loop)
        {
            channel->setMode(FMOD_LOOP_NORMAL);
        }
        else
        {
            channel->setMode(FMOD_LOOP_OFF);
        }
        m_EffectChannels[name] = channel;
    }
}

void CSoundManager::PlayBGM(const string& name, bool loop) {
    auto it = m_Sounds.find(name);
    if (it == m_Sounds.end()) 
    {
        return;
    }

    if (m_System->playSound(it->second, nullptr, false, &m_BGMChannel) != FMOD_OK)
    {
        return;
    }

    if (loop) // ���� ����
    {
        m_BGMChannel->setMode(FMOD_LOOP_NORMAL);
    }
}

bool CSoundManager::IsSoundPlaying(const string& name)
{
    auto it = m_Sounds.find(name);
    if (it == m_Sounds.end())
    {
        return false;
    }

    // �ִ� ä�� ����ŭ ��ȸ
    for (int i = 0; i < 512; i++)  // 512�� init���� ������ ä�� ��
    {
        Channel* channel = nullptr;
        bool isPlaying = false;

        if (m_System->getChannel(i, &channel) == FMOD_OK && channel)
        {
            Sound* currentSound = nullptr;
            if (channel->getCurrentSound(&currentSound) == FMOD_OK &&
                currentSound == it->second)
            {
                channel->isPlaying(&isPlaying);
                if (isPlaying)
                {
                    return true;  // ��� ���� ä���� ã���� true ��ȯ
                }
            }
        }
    }

    return false;  // � ä�ο����� ��� ������ ������ false ��ȯ
}

void CSoundManager::StopBGM() 
{
    if (m_BGMChannel) 
    {
        m_BGMChannel->stop();
        m_BGMChannel = nullptr;
    }
}

void CSoundManager::StopAllSounds()
{
    if (m_System)
    {
        m_System->update();  // ä�ε� ������Ʈ
        ChannelGroup* masterGroup = nullptr; // ��� ä�� ������ ������
        if (m_System->getMasterChannelGroup(&masterGroup) == FMOD_OK) 
        {
            masterGroup->stop();
        }
        else 
        {
            cerr << "���߱� ����" <<endl;
        }
    }
}

void CSoundManager::Update() 
{
    if (m_System)
    {
        m_System->update();
    }
}

void CSoundManager::Initialize()
{
   LoadSound("WaterMelon_BGM", "../Assets/Sound/WaterMelon_BGM.mp3", true,true);
   LoadSound("DropSound", "../Assets/Sound/DropSound.mp3");
   LoadSound("MergeSound", "../Assets/Sound/MergeSound.mp3");
}

void CSoundManager::Release()
{
    for (auto& it : m_Sounds)
    {
        it.second->release();
    }
 
    if (m_System)
    {
        m_System->close();
        m_System->release();
    }

 
}
