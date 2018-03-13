#ifndef __FILTER_LP__
#define __FILTER_LP__

/**
*Filtre abstrait
*/
#include "filter.h"


class FilterLP : public FilterAudio
{
public:

	void setAlpha(float alpha)
	{
		_Alpha = alpha;
	}

	FilterLP() : FilterAudio()
	{
		
	}

	virtual float doFilter(float ech)
	{
		float newEchantillon = _LastEchantillon + _Alpha * (ech - _LastEchantillon);

		_LastEchantillon = newEchantillon;
		return newEchantillon;
	}	

private :
	float _Alpha = 0.f;
	float _LastEchantillon = 0.f;
};


#endif
