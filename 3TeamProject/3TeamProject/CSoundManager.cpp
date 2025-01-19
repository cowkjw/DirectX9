#include "pch.h"
#include "CSoundManager.h"
CSoundManager* CSoundManager::m_pInstance = nullptr;
CSoundManager::CSoundManager() : m_System(nullptr), m_BGMChannel(nullptr) {
    if (System_Create(&m_System) != FMOD_OK)
    {
       cerr << "FMOD 생성 실패" << endl;
        return;
    }

    if (m_System->init(512, FMOD_INIT_NORMAL, nullptr) != FMOD_OK) 
    {
        cerr << "FMOD 초기화 실패" << endl;
    }
}

CSoundManager::~CSoundManager() 
{
    Release();
}

void CSoundManager::LoadSound(const string& name, const string& filePath, bool isStream, bool loop) {
    FMOD_MODE mode = FMOD_DEFAULT;
    if (isStream)  // 스트리밍 형식
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

    // 기존 채널 제거
    auto channelIt = m_EffectChannels.find(name);
    if (channelIt != m_EffectChannels.end())
    {
        channelIt->second->stop();
        m_EffectChannels.erase(channelIt);
    }

    // 새 채널 생성 및 재생
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

    if (loop) // 루프 설정
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

    // 최대 채널 수만큼 순회
    for (int i = 0; i < 512; i++)  // 512는 init에서 설정한 채널 수
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
                    return true;  // 재생 중인 채널을 찾으면 true 반환
                }
            }
        }
    }

    return false;  // 어떤 채널에서도 재생 중이지 않으면 false 반환
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
        m_System->update();  // 채널들 업데이트
        ChannelGroup* masterGroup = nullptr; // 모든 채널 가져올 포인터
        if (m_System->getMasterChannelGroup(&masterGroup) == FMOD_OK) 
        {
            masterGroup->stop();
        }
        else 
        {
            cerr << "멈추기 실패" <<endl;
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
   //JW
   LoadSound("WaterMelon_BGM", "../Assets/Sound/WaterMelon_BGM.mp3", true,true);
   LoadSound("DropSound", "../Assets/Sound/DropSound.mp3");
   LoadSound("MergeSound", "../Assets/Sound/MergeSound.mp3");
   //CY
   LoadSound("CY_BGM", "../Assets/Sound/CY_BGM.mp3", true,true);
   LoadSound("CY_EatFood", "../Assets/Sound/Eat_food.ogg");
   //YG
   LoadSound("YGSurviv_BGM", "../Assets/Sound/YGSurviv_BGM.mp3", true, true);
   LoadSound("YGHit", "../Assets/Sound/YGHit.mp3");
   LoadSound("YGGunPickup", "../Assets/Sound/YGGunPickup.mp3");
   LoadSound("YGfootstep", "../Assets/Sound/YGfootstep.mp3");
   LoadSound("YGFire", "../Assets/Sound/YGFire.mp3");
   LoadSound("YGEmptyfire", "../Assets/Sound/YGEmptyfire.mp3");
   LoadSound("YGBulletPickup", "../Assets/Sound/YGBulletPickup.mp3");
   LoadSound("YGBoxBreak", "../Assets/Sound/YGBoxBreak.mp3");
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
