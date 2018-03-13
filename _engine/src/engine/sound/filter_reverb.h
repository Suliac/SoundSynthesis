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

	virtual float doFilter(float ech)
	{
		float result = ech;

		////////////////////////////////////
		// Comb filter
		// 1
		//float comb1Res = 0.0f;
		//_CombBuffer.push(result);
		//float offset = 0;

		//if (_CombBuffer.size() > _SizeBuffer)
		//{
		//	offset = _CombBuffer.front();
		//	_CombBuffer.pop();
		//}

		//comb1Res = result + offset * _Gain1;

		//// 2
		//float comb2Res = 0.0f;
		//_CombBuffer2.push(result);
		//offset = 0;

		//if (_CombBuffer2.size() > _SizeBuffer)
		//{
		//	offset = _CombBuffer2.front();
		//	_CombBuffer2.pop();
		//}

		//comb2Res = result + offset * _Gain2;

		//// 3
		//float comb3Res = 0.0f;
		//_CombBuffer3.push(result);
		//offset = 0;

		//if (_CombBuffer3.size() > _SizeBuffer)
		//{
		//	offset = _CombBuffer3.front();
		//	_CombBuffer3.pop();
		//}

		//comb3Res = result + offset * _Gain3;

		//// 4
		//float comb4Res = 0.0f;
		//_CombBuffer4.push(result);
		//offset = 0;

		//if (_CombBuffer4.size() > _SizeBuffer)
		//{
		//	offset = _CombBuffer4.front();
		//	_CombBuffer4.pop();
		//}

		//comb4Res = result + offset * _Gain4;
		//////////////////////////////////////
		//result = comb1Res + comb2Res + comb3Res + comb4Res;
		////////////////////////////////////
		// All-pass filter
		// 1
		float tmpResult = result * (_Gain5*-1);
		_AllPassBuffer.push(result);
		float offset = 0;

		if (_AllPassBuffer.size() > _SizeBuffer)
		{
			offset = _AllPassBuffer.front();
			_AllPassBuffer.pop();
		}

		result += offset * _Gain5 + tmpResult;

		//// 2
		//tmpResult = result * (_Gain6*-1);
		//_AllPassBuffer2.push(result);
		//offset = 0;

		//if (_AllPassBuffer2.size() > _SizeBuffer)
		//{
		//	offset = _AllPassBuffer2.front();
		//	_AllPassBuffer2.pop();
		//}

		//result += offset * _Gain6 + tmpResult;

		////////////////////////


		return ech * _Reverb + result * _Reverb;
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

	float _Gain1 = 1.f;
	float _Gain2 = 0.9f;
	float _Gain3 = 0.8f;
	float _Gain4 = 0.7f;
	float _Gain5 = 0.6f;
	float _Gain6 = 0.5f;
};


#endif
