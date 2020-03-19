//================================================================
//
//  tbd
//
//  (c) Dietmar Krause, DL2SBA 2017
//
//  License see https://creativecommons.org/licenses/by/4.0/

#include <arduino.h>
#include "PeakHold.h"


MinOrMaxHold::MinOrMaxHold(uint16_t pPeakHoldTime, uint16_t pDecayTime, uint16_t pDecayStep) {
  mPeakHoldTime = pPeakHoldTime;
  mDecayTime = pDecayTime;
  mDecayStep = pDecayStep;
}

MaximumHold::MaximumHold(uint16_t pPeakHoldTime, uint16_t pDecayTime, uint16_t pDecayStep) : MinOrMaxHold(pPeakHoldTime, pDecayTime, pDecayStep) {
	mPeak = 0x0000;
	mState = 0;
}

void MaximumHold::consume(uint16_t pVal) {
	// new maximum value?
	if ( pVal > mPeak ) {
		//  yes
		//  store new peak
		mPeak = pVal;

		// switch to peak hold phase
		mState = 1;
	} else if ( mState == 1 ) {
		//  start peak hold counter
		mCounter = mPeakHoldTime;
		mState = 2;
	} else if ( mState == 2 ) {
		// in peak hold phase
		// time elapsed?
		if ( mCounter > 0 ) {
			// no
			// decrement
			--mCounter;
		} else {
			//	yes
			mState = 3;
		}
	} else if (mState == 3) {
		//  in decay phase
		mPeak -= mDecayStep;
		mCounter = mDecayTime;
		mState = 4;
	} else if (mState == 4 ) {
		// in decay phase
		// time elapsed?
		if ( mCounter > 0 ) {
			//	no
			// decrement
			--mCounter;
		} else {
			//	yes
			mState = 5;
		}
	} else if (mState == 5 ) {
		// decay time elapsed
		// at end of range?
		if ( mPeak > mDecayStep ) {
			// no
			// decay more
			mState = 3;
		} else {
			mState = 0;
		}
	}
}

MinimumHold::MinimumHold(uint16_t pPeakHoldTime, uint16_t pDecayTime, uint16_t pDecayStep) : MinOrMaxHold(pPeakHoldTime, pDecayTime, pDecayStep) {
	mPeak = 0xffff;
	mState = 0;
}

void MinimumHold::consume(uint16_t pVal) {
	// new minimum value?
	if ( pVal < mPeak ) {
		//  yes
		//  store new peak
		mPeak = pVal;

		// switch to peak hold phase
		mState = 1;
	} else if ( mState == 1 ) {
		//  start peak hold counter
		mCounter = mPeakHoldTime;
		mState = 2;
	} else if ( mState == 2 ) {
		// in peak hold phase
		// time elapsed?
		if ( mCounter > 0 ) {
			// no
			// decrement
			--mCounter;
		} else {
			//	yes
			mState = 3;
		}
	} else if (mState == 3) {
		//  in decay phase
		mPeak += mDecayStep;
		mCounter = mDecayTime;
		mState = 4;
	} else if (mState == 4 ) {
		// in decay phase
		// time elapsed?
		if ( mCounter > 0 ) {
			//	no
			// decrement
			--mCounter;
		} else {
			//	yes
			mState = 5;
		}
	} else if (mState == 5 ) {
		// decay time elapsed
		// at end of range?
		if ( mPeak < 0xffff - mDecayStep ) {
			// no
			// decay more
			mState = 3;
		} else {
			mState = 0;
		}
	}
}


