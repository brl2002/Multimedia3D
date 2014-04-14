
#include "Advanced2D.h"

namespace Advanced2D {



	Sample::Sample()
	{
	}
	
	Sample::~Sample()
	{
		#ifndef _NOAUDIO
		if (sample != NULL) 
		{
			FMOD_Sound_Release(sample);
			sample = NULL;
		}
		#endif
	}
	
	Audio::Audio()
	{
		#ifndef _NOAUDIO
		system = NULL;
		#endif
	}
	
	Audio::~Audio()
	{
		//release all samples
		for (Iterator i = samples.begin(); i != samples.end(); ++i)
		{
			(*i) = NULL;
		}
		#ifndef _NOAUDIO
		FMOD_System_Release(system);
		#endif
	}
	
	bool Audio::Init()
	{
		#ifndef _NOAUDIO
		if (FMOD_System_Create(&system) != FMOD_OK) {
			return false;
		}
	
		if (FMOD_System_Init(system,100,FMOD_INIT_NORMAL,NULL) != FMOD_OK) {
			return false;
		}
		#endif
		return true;
	}
	
	void Audio::Update()
	{
		#ifndef _NOAUDIO
		FMOD_System_Update(system);
		#endif
	}
	
	
	Sample* Audio::Load(std::string filename)
	{
		if (filename.length() == 0) return false;
		
		Sample *sample = new Sample();
	#ifndef _NOAUDIO
		try {
			FMOD_RESULT res;
			res = FMOD_System_CreateSound(
				system, 			//FMOD system
				filename.c_str(), 	//filename
				FMOD_DEFAULT, 		//default audio
				NULL, 				//n/a
				&sample->sample);	//pointer to sample

			if (res != FMOD_OK) {
				sample = NULL;
			}
		} catch (...) {
			sample = NULL;
		}
	#endif
		return sample;
	}
	
	bool Audio::Load(std::string filename, std::string name)
	{
		if (filename.length() == 0 || name.length() == 0) return false;
		
		Sample *sample = new Sample();
		sample->setName(name);
		#ifndef _NOAUDIO
		try {
			FMOD_RESULT res;
			res = FMOD_System_CreateSound(
				system, 			//FMOD system
				filename.c_str(), 	//filename
				FMOD_DEFAULT, 		//default audio
				NULL, 				//n/a
				&sample->sample);	//pointer to sample

			if (res != FMOD_OK) {
				return false;
			}
		} catch (...) {
			return false;
		}
		#endif
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
		Sample *samp = FindSample(name);
		if (samp == NULL) return false;
		
		int index = 0;
		#ifndef _NOAUDIO
		FMOD_Channel_GetIndex(samp->channel, &index);
		#endif
		// FMOD returns 99 if sample is playing, 0 if not
		return (index > 0);
		
	}
		
	Sample *Audio::FindSample(std::string name)
	{
		Sample *sample = NULL;
		for (Iterator i = samples.begin(); i != samples.end(); ++i)
		{
			if ((*i)->getName() == name)
			{
				sample = (*i);
				break;
			}
		}
		return sample;
	}
	
	
	bool Audio::Play(std::string name)
	{
		#ifndef _NOAUDIO
		FMOD_RESULT res;
		Sample *sample = FindSample(name);
		Play(sample);
		
		#endif
		return true;
	}
	
	bool Audio::Play(Sample *sample)
	{
		#ifndef _NOAUDIO
		FMOD_RESULT res;
		if (sample == NULL) return false;
		if (sample->sample == NULL) return false;
	
		try {
			res = FMOD_System_PlaySound(
				system,
				FMOD_CHANNEL_FREE,
				sample->sample,
				true,
				&sample->channel);

			if (res!= FMOD_OK) return false;
	
			FMOD_Channel_SetLoopCount(sample->channel, -1);
			FMOD_Channel_SetPaused(sample->channel, false);
	
		} catch (...) {
			return false;
		}
		#endif
		return true;
	}
	
	void Audio::Stop(std::string name)
	{
		if (!IsPlaying(name)) return;
	
		Sample *sample = FindSample(name);
		if (sample == NULL) return;
		#ifndef _NOAUDIO
		FMOD_Channel_Stop(sample->channel);
		#endif
	}
	
	void Audio::StopAll()
	{
		for (Iterator i = samples.begin(); i != samples.end(); ++i)
		{
			#ifndef _NOAUDIO
			FMOD_Channel_Stop( (*i)->channel );
			#endif
		}
	}
	
	void Audio::StopAllExcept(std::string name)
	{
		for (Iterator i = samples.begin(); i != samples.end(); ++i)
		{
			if ((*i)->getName() != name)
			{
				#ifndef _NOAUDIO
				FMOD_Channel_Stop( (*i)->channel );
				#endif
			}
		}
	}



};
