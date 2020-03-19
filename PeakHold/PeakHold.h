//================================================================
//
//  tbd
//
//  (c) Dietmar Krause, DL2SBA 2017
//
//  License see https://creativecommons.org/licenses/by/4.0/

#ifndef _PEAKHOLD_H
#define _PEAKHOLD_H

class MinOrMaxHold {
  public:
    MinOrMaxHold(uint16_t pPeakHoldTime, uint16_t pDecayTime, uint16_t pDecayStep);

  public:
    virtual void consume(uint16_t pVal);
    
	inline uint16_t getPeak(void) { return mPeak; }
	
	inline void setPeakHoldTime ( uint16_t x ) { mPeakHoldTime = x; }
	inline void setDecayTime    ( uint16_t x ) { mDecayTime = x; }
	inline void setDecayStep    ( uint16_t x ) { mDecayStep = x; }

  protected:
    uint8_t  mState;
    uint16_t mCounter;
    uint16_t mPeak;

    uint16_t mPeakHoldTime;
    uint16_t mDecayTime;
    uint16_t mDecayStep;

};


class MaximumHold : public MinOrMaxHold {
  public:
    MaximumHold(uint16_t pPeakHoldTime, uint16_t pDecayTime, uint16_t pDecayStep);

  public:
    void consume(uint16_t pVal);

};

class MinimumHold : public MinOrMaxHold {
  public:
    MinimumHold(uint16_t pPeakHoldTime, uint16_t pDecayTime, uint16_t pDecayStep);

  public:
    void consume(uint16_t pVal);

};


#endif

