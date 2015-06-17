#ifndef ST_RCP_SKIMMER_H
#define ST_RCP_SKIMMER_H

#include "StMaker.h"
#include "StThreeVectorD.hh"
#include "StPhysicalHelixD.hh"
#include "StRcpTreeData.h"

#include "StMuDSTMaker/COMMON/StMuUtilities.h"
#include "StMuDSTMaker/COMMON/StMuPrimaryVertex.h"
#include "StMuDSTMaker/COMMON/StMuDst.h"
#include "StMuDSTMaker/COMMON/StMuEvent.h"
#include "StMuDSTMaker/COMMON/StMuDstMaker.h"
#include "StMuDSTMaker/COMMON/StMuTrack.h"

#include "StRcpSkimmer.h"
#include "StRefMultCorr/StRefMultCorr.h"
#include "StRefMultCorr/CentralityMaker.h"

#include <string>
#include <vector>

#ifndef ST_NO_NAMESPACES
	using std::string;
	using std::vector;
#endif

class StEvent;
class StTrack;
class StGlobalTrack;
class StHelix;
#include "StThreeVectorF.hh"
class StTrackGeometry;
class StBTofGeometry; 
class StBTofCollection;
class StBTofHitCollection;   
class StSPtrVecBTofHit;      
class StMuDst;

class TFile;
class TTree;

class StRcpSkimmer : public StMaker {
 public:
	StRcpSkimmer(const Char_t *name, const Char_t *outname);
	~StRcpSkimmer();

	Int_t  Init();
	Int_t  InitRun(int runnumber);
	Int_t  Make();
	Int_t  FinishRun(int runnumber);
	Int_t  Finish();

	
	



protected:

	Int_t nTofMatchedTracksA();

	/**
	 * Event Selection
	 */
	Bool_t keepEvent();
	virtual void passEventCut( string name );
	virtual void preEventCuts();
	virtual void postEventCuts();

	// Event variables to make available to children
	Int_t runId;
	Float_t eventWeight;
	Float_t corrRefMult;
	Int_t cent9;
	Int_t cent16;
	Int_t nTofMatchedTracks;
	Float_t pX, pY, pZ;


	virtual void postTrackLoop( Int_t nPrimaryGood );

	/**
	 * Track Selection
	 */
	Bool_t keepTrack( Int_t iNode );
	virtual void passTrackCut( string name );
	virtual void preTrackCuts( StMuTrack *primaryTrack );
	virtual void postTrackCuts( StMuTrack *primaryTrack );
	virtual void postTrackCuts( StMuTrack *primaryTrack );

	virtual void analyzeTrack( Int_t iNode, Int_t iGoodTrack );

	StRefMultCorr* refmultCorrUtil;

	void processMuDst();

	
	StMuDst *muDst;
	string mTupleFileName;
	TFile *mTupleFile;
	
	Bool_t  doPrintMemoryInfo; 		//! control debug memory data
	Bool_t  doPrintCpuInfo; 		//! control debug timing data

	virtual const char *GetCVS() const 
		{static const char cvs[]="Tag $Name:  $ $Id: StRcpSkimmer.h, $ built "__DATE__" "__TIME__ ; return cvs;}

	ClassDef(StRcpSkimmer,1)
};

#endif
