#ifndef __NOISE_SOUND__
#define __NOISE_SOUND__

/**
* Bruit de variabilité ajustable
*/
#include "continuous_sound.h"

class NoiseSound : public ContinuousSound
{
public:

	NoiseSound() : ContinuousSound()
	{

	}

	void setFreq(float freq)
	{
		_FreqNoise = freq;
	}

private:
	float _FreqNoise;
	float _CurrentNumberSameFreq = 0.0f;
	float _LastEchant = 0.0f;

	int diceValues[8];

	int _CounterEchant = 0;
protected:

	/**
	  * Remplissage du buffer de synthèse, jusqu'au pointeur de lecture
	  */
	virtual float getNextSample()
	{
		if (_CurrentNumberSameFreq > _FreqNoise / 50)
		{
			_CurrentNumberSameFreq = 0;
			float result = 0;
			int nbDices = 8;
			float diceValue[8];
			int defaultMask = 1;

			for (int d = 0; d < nbDices; d++)
			{
				int a = _CounterEchant & defaultMask;
				int b = (_CounterEchant - 1) & defaultMask;
				if (a != b)
				{
					diceValue[d] = randf();
				}			
			}

			for (int i = 0; i < 8; i++)
			{
				result += diceValue[i];
			}

			_LastEchant = (float)(randf()*2.0f - 1)*0.5f;
		}

		_CurrentNumberSameFreq++;
		_CounterEchant++;
		return _LastEchant;

	}

};

#endif
