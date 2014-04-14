
#include "Advanced2D.h"

namespace Advanced2D {

    Sample::Sample()
    {
        sound = NULL;
        channel = NULL;
    }
    
    Sample::~Sample()
    {
        if (sound != NULL) {
			sound->release();
            sound = NULL;
        }
    }

    Audio::Audio() : system(NULL)
    {
        
    }
    
    Audio::~Audio()
    {
        //release all samples
        for (Iterator i = samples.begin(); i != samples.end(); ++i)
        {
            (*i) = NULL;
        }
        
		system->release();
		system = NULL;
    }
    
    bool Audio::Init()
    {
		FMOD_RESULT       result;
		unsigned int      version;
		void             *extradriverdata = 0;

        result = FMOD::System_Create(&system);
		ERRCHECK(result);

		result = system->getVersion(&version);
		ERRCHECK(result);

		if (version < FMOD_VERSION)
		{
			Common_Fatal("FMOD lib version %08x doesn't match header version %08x", version, FMOD_VERSION);
		}
    
        result = system->init(32, FMOD_INIT_NORMAL, extradriverdata);
		ERRCHECK(result);
    
        return true;
    }
    
    void Audio::Update()
    {
		system->update();
    }

	void Audio::Release()
	{
		for (Iterator i = samples.begin(); i != samples.end(); ++i)
        {
			(*i)->sound->release();
		}

		system->close();
		system->release();
	}
    
    Sample* Audio::Load(std::string filename)
    {
        if (filename.length() == 0)
			return false;
        
        Sample *sample = new Sample();
    
		FMOD_RESULT result;
		result = system->createSound(filename.c_str(), FMOD_DEFAULT, 0, &sample->sound);
		ERRCHECK(result);

		samples.push_back(sample);
        return sample;
    }
    
    bool Audio::Load(std::string filename, std::string name)
    {
        if (filename.length() == 0 || name.length() == 0) return false;
        
        Sample *sample = new Sample();
        sample->setName(name);
    
        FMOD_RESULT result;
		result = system->createSound(filename.c_str(), FMOD_DEFAULT, 0, &sample->sound);
		ERRCHECK(result);

        samples.push_back(sample);
    
        return true;    
    }
    
    bool Audio::SampleExists(std::string name)
    {
        for (Iterator i = samples.begin(); i != samples.end(); ++i)
        {
            if ((*i)->getName() == name)
            {
                return true;
            }         
        }
    
        return false;
    }
    
    bool Audio::IsPlaying(std::string name)
    {
        Sample *sample = FindSample(name);
		if (sample == NULL || sample->channel == NULL) 
			return false;
        
        int index;
		sample->channel->getIndex(&index);
        
        // FMOD returns 99 if sound is playing, 0 if not
        return (index > 0);
        
    }
        
    Sample *Audio::FindSample(std::string name)
    {
        Sample *sound = NULL;
        for (Iterator i = samples.begin(); i != samples.end(); ++i)
        {
            if ((*i)->getName() == name)
            {
                sound = (*i);
                break;
            }
        }
        return sound;
    }
    
    
    bool Audio::Play(std::string name)
    {
		if (name.size() == 0)
			return false;

		Sample *sample = FindSample(name);

		if (sample)
		{
			FMOD_RESULT result;
			result = system->playSound(sample->sound, 0, false, &sample->channel);
            ERRCHECK(result);
		}
		else
		{
			return false;
		}

        return false;
    }
    
    bool Audio::Play(Sample *sample)
    {
		if (sample)
		{
			FMOD_RESULT result;
			result = system->playSound(sample->sound, 0, false, &sample->channel);
            ERRCHECK(result);
		}
		else
		{
			return false;
		}

        return false;
    }
    
    void Audio::Stop(std::string name)
    {
		if (name.size() == 0)
			return;

		Sample *sample = FindSample(name);

		if (sample && sample->channel)
		{
			FMOD_RESULT result = sample->channel->stop();
            ERRCHECK(result);
		}
    }

	void Audio::Stop(Sample *sample)
    {
		if (sample && sample->channel)
		{
			FMOD_RESULT result = sample->channel->stop();
            ERRCHECK(result);
		}
    }
    
    void Audio::StopAll()
    {
        for (Iterator i = samples.begin(); i != samples.end(); ++i)
        {
			Stop(*i);
        }
    }
    
    void Audio::StopAllExcept(std::string name)
    {
        for (Iterator i = samples.begin(); i != samples.end(); ++i)
        {
            if ((*i)->getName() != name)
            {
                Stop(*i);
            }
        }
    }

};
