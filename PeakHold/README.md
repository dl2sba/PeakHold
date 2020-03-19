Arduino Library for a peak hold implementation

Simple library to implement a peak hold variable. There are two implementations

Use getPeak() to get the highest/lowest value. 
The timing of the peak hold is based on the frequency, on which the consume() function is called.

MaximumHold
	Stores the highest value passed to the consume() function.
	
MinimumHold
	Stores the lowest value passed to the consume() function.

See further details in the header file PeakHold.h.

73

Dietmar, DL2SBA