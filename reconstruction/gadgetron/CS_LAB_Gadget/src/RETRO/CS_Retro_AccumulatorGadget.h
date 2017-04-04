#ifndef CS_RETRO_ACCUMULATORGADGET_H
#define CS_RETRO_ACCUMULATORGADGET_H

#if __GADGETRON_VERSION_HIGHER_3_6__ == 1
	//#define GET_MACRO(_1,_2,_3,NAME,...) NAME
	//#define GDEBUG(...) GET_MACRO(__VA_ARGS__, GADGET_DEBUG1, GADGET_DEBUG2)(__VA_ARGS__)
	#define GADGET_DEBUG1(__VA_ARGS__) GDEBUG(__VA_ARGS__)
	#define GADGET_DEBUG2(x, ...) GDEBUG(x, ##__VA_ARGS__)
	#define GADGET_DEBUG_EXCEPTION(x,y) GEXCEPTION(x,y)
#endif

#pragma once
#include "Gadget.h"
#include "hoNDArray.h"
#include "CS_LAB_export.h"
#include <ismrmrd.h>
#include <complex>
#include "GlobalVar.h"
#include "SomeFunctions.h"
#include "hoNDArray_blas.h"
#include "hoNDArray_math_util.h"
#include "hoNDImage_util.h"
#include "hoNDBSpline.h"
#include <cmath>

#include "GadgetIsmrmrdReadWrite.h"

#if __GADGETRON_VERSION_HIGHER_3_6__ == 1
	#include "xml.h"
#else		
	#include "ismrmrd/xml.h"
#endif

namespace Gadgetron{
	
	class EXPORTCSLAB CS_Retro_AccumulatorGadget : public Gadget2< ISMRMRD::AcquisitionHeader, hoNDArray< std::complex<float> > >
    {
    public:      
		CS_Retro_AccumulatorGadget();
		~CS_Retro_AccumulatorGadget();
		int process_config(ACE_Message_Block* mb);
		int process(GadgetContainerMessage<ISMRMRD::AcquisitionHeader>*m1, GadgetContainerMessage<hoNDArray<std::complex<float>>>*m2);
		GADGET_DECLARE(CS_Retro_AccumulatorGadget);
	  
    public:
		
		hoNDArray< std::complex<float> >* bufferkSpace_;
		hoNDArray< std::complex<float> >* bufferNav_;

		std::vector<size_t> dimkSpace_;
		std::vector<size_t> dimNav_;

		// navigator signal interpolated to TRs
		std::vector<float> vNavInt_;

		// navigator signal
		std::vector<float> vNav_;
		long lCurrentScan_;
		std::vector<size_t> dimensionsIn_;
		std::vector<size_t> dimensionsOut_;
		std::vector<float> field_of_view_;
		size_t slices_;
		size_t repetitions_;
		long long image_counter_;
		long long image_series_;
		
		int iNoSamples_;
		long lNoScans_;
		int iNoChannels_;
		int iNoNav_;
		int iNoNavLine_;
		int iEchoLine_;
		int iEchoPartition_;

		// Gating mode (0: percentile, 1: kMeans)
		int iGatingMode_;

		// mode for k-space population (0: closes, 1: average, 2: collect)
		int iPopulationMode_;

		// vector containing the Gate positions
		std::vector<float> vGatePos_;

		// vector containing the tolerance values
		std::vector<float> vTolerance_;

		// CS_Retro variables
		int iBaseRes_;
		float fTR_;
		int iNavPeriod_;
		int iNavPERes_;
		int iMeasurementTime_;

		// number of phases
		int iNPhases_;

		// tolerance/blending factor
		float fTolerance_;

		// Compressed Sensing variables
		int iESPReSSoDirection_; 
		float fPartialFourierVal_;
		float fLESPReSSo_;
		float fLQ_;
		int iBodyRegion_; 
		int iVDMap_;
		int iSamplingType_;
		float fCSAcc_;
		float fFullySa_;
    };
}
#endif //CS_RETRO_ACCUMULATORGADGET_H
