#include "StRcpSkimmer.h"

//// StRoot
// StMuDst
#include "StMuDSTMaker/COMMON/StMuDst.h"
#include "StMuDSTMaker/COMMON/StMuEvent.h"
#include "StMuDSTMaker/COMMON/StMuDstMaker.h"
#include "StMuDSTMaker/COMMON/StMuTrack.h"
#include "StMuDSTMaker/COMMON/StMuPrimaryVertex.h"

#include "StMemoryInfo.hh"
#include "StMessMgr.h"
#include "StTimer.hh"



/**
 * Processes the MuDst
 */
void StRcpSkimmer::processMuDst() {
	//LOG_INFO << "StRcpSkimmer::processMuDst()" << endm;

	StMuDstMaker *muDstMaker = (StMuDstMaker*) GetMaker( "MuDst" );

  	if( !muDstMaker ) {
		LOG_WARN << "WARNING: No MuDstMaker" << endm;
		return;
  	}
  	muDst = muDstMaker->muDst();
  	if(!muDst) {
		LOG_WARN << "WARNING: No MuDst" << endm;
		return;
  	}

	StTimer timer;

  	if (doPrintCpuInfo) 
  		timer.start();
  	if (doPrintMemoryInfo)
  		StMemoryInfo::instance()->snapshot();

 
 	// Event selection
  	if ( !keepEvent() )
  		return;

  	StMuEvent *muEvent = muDst->event();

  	// Primary vertex
	StThreeVectorD pVtx(-999., -999., -999.);  
	pVtx = muDst->primaryVertex()->position();        

	/**
	 * Loop over primary tracks
	 */
	UInt_t nPrimary = muDst->primaryTracks()->GetEntries();
	nPrimary = muDst->numberOfPrimaryTracks();
	
	Int_t nPrimaryGood = 0;
	for (int iNode = 0; iNode < nPrimary; iNode++ ){
		
		StMuTrack*	tPrimary 	= (StMuTrack*)muDst->primaryTracks(iNode);
		if ( !tPrimary ) continue;
		StMuTrack*	tGlobal 	= (StMuTrack*)tPrimary->globalTrack();

		if ( !keepTrack( iNode ) )
			continue;

		analyzeTrack( iNode, nPrimaryGood );

		nPrimaryGood++;
	}

	postTrackLoop( nPrimaryGood );


	//- debug info`
	if (doPrintMemoryInfo) {
		StMemoryInfo::instance()->snapshot();
		StMemoryInfo::instance()->print();
	}
	if (doPrintCpuInfo) {
		timer.stop();
		LOG_INFO << "CPU time for StEventMaker::Make(): " << timer.elapsedTime() << " sec\n" << endm;
	}

}

void StRcpSkimmer::postTrackLoop( Int_t nPrimaryGoodTracks ){


}


void StRcpSkimmer::analyzeTrack( Int_t iNode, Int_t iGoodTrack ){
	//LOG_INFO << "StRcpSkimmer::analyzeTrack" << endm;
}

Int_t StRcpSkimmer::nTofMatchedTracksA(){

	Int_t nPrimary 	= muDst->primaryTracks()->GetEntries();
	Int_t nTofMatched = 0;
	for (int iNode = 0; iNode < nPrimary; iNode++ ){
		StMuTrack*	tPrimary 	= (StMuTrack*)muDst->primaryTracks(iNode);
		StMuTrack*	tGlobal 	= (StMuTrack*)tPrimary->globalTrack();

		if ( !tPrimary ) continue;
		if ( tPrimary->vertexIndex() != 0 ) continue;

		/**
		 * Get Tof info
		 */
		StMuBTofPidTraits bTofPidTraits	= tPrimary->btofPidTraits();

		if ( bTofPidTraits.matchFlag() > 0 ) 
			nTofMatched++;
	}

	return nTofMatched;

}


/**
 * Called before main event cuts but after trigger selection
 */
void StRcpSkimmer::preEventCuts(){
	//LOG_INFO << "StRcpSkimmer::preEventCuts" << endm;

}

/**
 * Called after main event cuts
 */
void StRcpSkimmer::postEventCuts(){
	//LOG_INFO << "StRcpSkimmer::postEventCuts" << endm;


}

void StRcpSkimmer::passEventCut( string name ){
	
}

/**
 * Apply Event cuts
 * @return [description]
 */
Bool_t StRcpSkimmer::keepEvent(){
	//LOG_INFO << "StRcpSkimmer::keepEvent" << endm;

	passEventCut( "All");
	
	StMuEvent *muEvent = muDst->event();
	if ( !muEvent )
		return false;

	//-- read in TOF info
	StBTofHeader* tofHeader = muDst->btofHeader();

	//BBC_MB
	// 15GeV
	Bool_t isTrigger = 
			( 	muEvent->triggerIdCollection().nominal().isTrigger(440005) ||	// BBC_MB but not used
				muEvent->triggerIdCollection().nominal().isTrigger(440015) ||	// BBC_MB
				muEvent->triggerIdCollection().nominal().isTrigger(440001) || 	// VPD_MB
				muEvent->triggerIdCollection().nominal().isTrigger(440004) ); 	// ZDC_MB
	
	// MB
	// 11 GeV
	// Bool_t isTrigger = 
	// 		( 	muEvent->triggerIdCollection().nominal().isTrigger(310014) );
	
	// MB
	// 19 GeV
	// Bool_t isTrigger = 
	// 		( 	muEvent->triggerIdCollection().nominal().isTrigger(340011) || 
	//  			muEvent->triggerIdCollection().nominal().isTrigger(340021) || 
	//  			muEvent->triggerIdCollection().nominal().isTrigger(340001) ||
	//  			muEvent->triggerIdCollection().nominal().isTrigger(340002) ||
	//  			muEvent->triggerIdCollection().nominal().isTrigger(340061) ||
	//  			muEvent->triggerIdCollection().nominal().isTrigger(340060) );
	
	

	if ( !isTrigger )
		return false;
	passEventCut( "Trigger" );


	StThreeVectorD pVtx(-999., -999., -999.);  
	if( !muDst->primaryVertex() ) {
		//LOG_INFO << "No Primary Vertex" << endm;
		return false;
	}
	passEventCut( "VertexExists" );

	nTofMatchedTracks = nTofMatchedTracksA();
	pVtx = muDst->primaryVertex()->position();

	// Initialize the refMult Corr
	//refmultCorrUtil->init( muEvent->runId() );
	//refmultCorrUtil->initEvent( muEvent->refMult(), pVtx.z() );

	corrRefMult 	= (Float_t)0;//refmultCorrUtil->getRefMultCorr();
	cent9  			= 0;//refmultCorrUtil->getCentralityBin9();
	cent16  		= 0;//refmultCorrUtil->getCentralityBin16();
	eventWeight  	= 0;//refmultCorrUtil->getWeight();

	//LOG_WARN << "StRMCUtil Sanity : Run 15053029" << //refmultCorrUtil->isBadRun( 15053029 ) << endl;

	runId = muEvent->runId();
	//if ( //refmultCorrUtil->isBadRun( muEvent->runId() ) )
	//	return false;
	passEventCut( "BadRun" );

	// The Pre event cuts hook
	preEventCuts();

	

	// Initialize the vertex	
	// float xOffset = - 0.09797;		// 11GeV
	// float yOffset = 0.2274;			// 11GeV
	// float xOffset = - 0.3685;		// 19GeV
	// float yOffset = 0.03097;			// 19GeV
	float xOffset = 0.0;			// 15GeV
	float yOffset = 0.89;			// 15GeV

	pX = pVtx.x() + xOffset;
	pY = pVtx.y() + yOffset;
	pZ = pVtx.z();


	// dont need to keep the events in 80-100% centrality range
	if ( cent9 < 0 )
		return false;


	if ( TMath::Abs( pVtx.z() ) > 30 )
		return false;
	passEventCut( "vZ");

	

	if ( TMath::Sqrt( pX*pX + pY*pY ) > 1.0 )
		return false;
	passEventCut( "vR");

		
	if ( nTofMatchedTracks < 3 )
		return false;
	passEventCut( "nTofMatch");

	// The Post event cuts hook
	postEventCuts();

	return true;

}



void StRcpSkimmer::passTrackCut( string name ){

}

void StRcpSkimmer::preTrackCuts(StMuTrack *primaryTrack ){

}
void StRcpSkimmer::postTrackCuts(StMuTrack *primaryTrack ){
	//LOG_INFO << "StRcpSkimmer::postTrackCuts" << endm;
}

/**
 * Apply Track Cuts
 * @param  		iNode - Primary Track index
 * @return      true - keep track
 */
Bool_t StRcpSkimmer::keepTrack( Int_t iNode ){
	//LOG_INFO << "StRcpSkimmer::keepTrack( " << iNode << " )" << endm;

	StMuTrack*	tPrimary 	= (StMuTrack*)muDst->primaryTracks(iNode);
	passTrackCut("All");

	const StMuTrack *globalTrack = tPrimary->globalTrack();
	if (!globalTrack ) 
		return false;

	passTrackCut( "primaryWGlobal");

	StThreeVectorF pMom = tPrimary->momentum();
	StThreeVectorF gMom = globalTrack->momentum();
	float ptRatio = gMom.perp() / pMom.perp();

	

	/**
	 * Pre Cut Hook
	 */
	preTrackCuts( tPrimary );

	if ( 16 > globalTrack->nHitsFit(kTpcId) )
		return false;
	passTrackCut( "nHitsFit" );

	if ( (float)globalTrack->nHitsFit(kTpcId) / globalTrack->nHitsPoss() < 0.52 )
		return false;
	passTrackCut( "nHitsRatio" );

	if ( 11 > globalTrack->nHitsDedx() )
		return false;	
	passTrackCut( "nHitsDedx" );

	if ( ptRatio < 0.7 || ptRatio > 1.42857 )
		return false;
	passTrackCut( "ptRatio" );

	if ( pMom.perp() < 0.1 )
		return false;
	passTrackCut( "pmmtm" );

	if ( tPrimary->dcaGlobal().magnitude() > 1.0 )
		return false;
	passTrackCut( "DCA" );


	/**
	 * Post Cut Hook
	 */
	postTrackCuts( tPrimary );

	return true;

}






ClassImp(StRcpSkimmer)

/**
 * Creates the Maker
 */
StRcpSkimmer::StRcpSkimmer( const Char_t *name="rcpSkimmer", const Char_t *outname="rcp.skim.root") : StMaker(name) {
	// the output filename
	mTupleFileName = outname;

	// default debug options
	doPrintMemoryInfo = kFALSE;
	doPrintCpuInfo    = kFALSE;

}

/**
 * Destructor
 */
StRcpSkimmer::~StRcpSkimmer( ){ 

}

/**
 * Initialise the Maker
 */
Int_t StRcpSkimmer::Init( ){

	//refmultCorrUtil  = CentralityMaker::instance()->getRefMultCorr();

	return kStOK;
}


Int_t StRcpSkimmer::InitRun( int runnumber ) {

	return kStOK;
}

Int_t StRcpSkimmer::FinishRun( int runnumber ) {
  	return kStOK;
}

/// write and close the ntuple file
Int_t StRcpSkimmer::Finish() {

	if ( (string)"" != mTupleFileName && mTupleFile ){
		mTupleFile->Write();
		mTupleFile->Close();

		LOG_INFO  << "StRcpSkimmer::Finish() ntuple file " << mTupleFileName  << " closed." << endm;

	}

	return kStOK;
}


/**
 * Called for each event 
 */
Int_t StRcpSkimmer::Make(){

  processMuDst();

  return kStOK;
}

