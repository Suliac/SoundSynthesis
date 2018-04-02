#ifndef __FILTER_REVERB__
#define __FILTER_REVERB__

/**
*Filtre abstrait
*/
#include "filter.h"
#include <queue>

class FilterReverb : public FilterAudio
{
public:

	void setReverb(float reverb)
	{
		_Reverb = reverb;
	}

	FilterReverb() : FilterAudio()
	{

	}

	void init()
	{

	}

	// Ma reverb : filtre peigne + all-pass + 3 peignes sur le même échantillon + all pass à la fin sur le résultat
	virtual float doFilter(float ech)
	{
		float tmpResult = 0;
		tmpResult += CombFilter(ech, 0.75f, _CombBuffer );
		tmpResult += CombFilter(ech, 0.50f, _CombBuffer2);
		tmpResult += CombFilter(ech, 0.25f, _CombBuffer3);
		tmpResult += CombFilter(ech, 0.85f, _CombBuffer4);


		tmpResult += AllPassFilter(tmpResult, 0.75f, _AllPassBuffer);
		tmpResult += AllPassFilter(tmpResult, 0.6f, _AllPassBuffer2);


		tmpResult = tmpResult * 0.25f + ech * 0.25f;

		return tmpResult * _Reverb * 0.5f;
	}

private:
	std::queue<float> _CombBuffer;
	std::queue<float> _CombBuffer2;
	std::queue<float> _CombBuffer3;
	std::queue<float> _CombBuffer4;

	std::queue<float> _AllPassBuffer;
	std::queue<float> _AllPassBuffer2;

	int _SizeBuffer = 10000;
	float _Reverb = 0.f;

	float CombFilter(float ech, float gain, std::queue<float>& buffer)
	{
		float currentEch = ech;
		float pastEch = 0;

		if (buffer.size() > _SizeBuffer)
		{
			pastEch = buffer.front();
			buffer.pop();
		}

		buffer.push(currentEch + pastEch * gain);

		return pastEch * 0.5f;
	}

	float AllPassFilter(float ech, float gain, std::queue<float>& buffer)
	{
		float currentEch = ech;
		float pastEch = 0;
		float addAtTheEnd = 0;

		if (buffer.size() > _SizeBuffer)
		{
			pastEch = buffer.front();
			buffer.pop();
		}

		float toAddToBuffer = currentEch + pastEch * gain;
		buffer.push(toAddToBuffer);

		return (pastEch + toAddToBuffer * -gain) * 0.5f;
	}
};


#endif
