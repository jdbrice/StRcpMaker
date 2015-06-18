#ifndef ST_RCP_TREE_DATA_H
#define ST_RCP_TREE_DATA_H

const Int_t kMaxTracks = 10000;

struct StRcpTreeData {
	
	Int_t       runId;
	Float_t     weight;						// event weight
	Float_t    	corrRefMult;                // Corrected
	UShort_t 	bin16;						// bin16
	UShort_t 	bin9;						// bin9
	Int_t    	nTracks;      				// These are what we are keeping!!
											// these are Primary TPC tracks

	/**
	 * Track variables
	 */
	Float_t     pPt[kMaxTracks],			// Primary Pt * charge
				pP[kMaxTracks],
				pEta[kMaxTracks];

	UShort_t    dedx[kMaxTracks];        	// dEdx * 1000
	UShort_t    beta[kMaxTracks];         	// beta * 20000

	UChar_t 	matchFlag[ kMaxTracks ];	// tofpid.matchflag
	Float_t 	yLocal[ kMaxTracks ];		// tofpid.yLocal
	Float_t 	zLocal[ kMaxTracks ];		// tofpid.zLocal


};  
#endif
