#ifndef __SINUS_SOUND__
#define __SINUS_SOUND__

/**
* Synthé sinusoidal.
*/
#include "continuous_sound.h"

class SinusSound : public ContinuousSound
{
public:

	SinusSound() : ContinuousSound()
	{

	}

	void setFreq(float freq, float stepFreqPerPeriod)
	{
		_FreqWanted = freq;
		_FreqChange = _Freq;
		_ElapsedChange = _Elapsed;

	}
private:
	//float _Counter = 0.f;
	float _Freq = 0.f;
	//float _LastFreq = 0.f;

	//float _LastEchant = 0.f;
	float _FreqWanted = 0.f;
	//float _OldFreq = 0.f;
	//float _CurrentPercentage = 0.0f;

	float _Elapsed = 0.f;
	float _ElapsedChange = 0.f;
	float _FreqChange = 0.f;
	float _LerpDuration = 0.2f;

	float phi = 0;
protected:
	virtual void init()
	{

	}

	/**
	  * Remplissage du buffer de synthèse, jusqu'au pointeur de lecture
	  */
	virtual float getNextSample()
	{
		////float t = _Counter / _Frequency;
		//_Elapsed += 1 / _Frequency;

		//if (_Freq != _FreqWanted)
		//{
		//	/*if (_CurrentPercentage = 0.0f)
		//		_OldFreq = _Freq;
		//		
		//	if (_OldFreq < _FreqWanted)
		//		_Freq = lerp(_OldFreq, _FreqWanted, _CurrentPercentage);

		//	if (_Freq == _FreqWanted)
		//		_CurrentPercentage = 0.0f;*/

		//	float lerpRatio = min((_Elapsed - _ElapsedChange) / _LerpDuration, 1);
		//	float nextFreq = lerp(_FreqChange, _FreqWanted, lerpRatio);
		//
		//	float oldEchantillon = sin(_Elapsed * 2 * M_PI * _Freq+phi);
		//	phi = asin(oldEchantillon) - (_Elapsed * 2 * M_PI * nextFreq);
		//	_Freq = nextFreq;
		//}

		//float echant = sin(_Elapsed * 2 * M_PI * _Freq + phi);

		////_Counter++;
		////_LastEchant = echant;
		//return echant * 0.8;


		_Elapsed += 1.f / _Frequency;

		float asinf = _Elapsed * _Freq * 2.f * M_PI + phi;

		if (_Freq != _FreqWanted)
		{
			float lerpRatio = min((_Elapsed - _ElapsedChange) / _LerpDuration, 1);
			float nextFreq = lerp(_FreqChange, _FreqWanted, lerpRatio);

			phi = asinf - nextFreq * _Elapsed * 2.f * M_PI;
			_Freq = nextFreq;
			asinf = _Elapsed * _Freq * 2.f * M_PI + phi;
		}

		return sin(asinf) * 0.9f;

	}

	// Precise method, which guarantees v = v1 when t = 1.
	float lerp(float v0, float v1, float t) {
		return (1 - t) * v0 + t * v1;
	}
};


#endif
