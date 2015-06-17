#include "StRcpQAMaker.h"

ClassImp(StRcpQAMaker);

void StRcpQAMaker::postTrackLoop( Int_t nPrimaryGood ){
	histos->nTrack_refMult->Fill( refmultCorrUtil->getRefMultCorr(), nPrimaryGood  );
}

void StRcpQAMaker::passEventCut( string name ){
	histos->eventCuts->Fill( name.c_str(), 1 );
}

void StRcpQAMaker::passTrackCut( string name ){
	histos->trackCuts->Fill( name.c_str(), 1 );
}

void StRcpQAMaker::preEventCuts(){
	StMuEvent *muEvent = muDst->event();

	histos->pre_vZ->Fill( pZ );
	histos->pre_vX_vY->Fill( pX, pY );
	histos->pre_vR->Fill( TMath::Sqrt( pX*pX + pY*pY ) );
	histos->pre_nTofMatchA->Fill( nTofMatchedTracks );
	histos->pre_refMult->Fill( muEvent->refMult() );

}

void StRcpQAMaker::postEventCuts(){
	StMuEvent *muEvent = muDst->event();

	histos->vZ->Fill( pZ );
	histos->vX_vY->Fill( pX, pY );
	histos->vR->Fill( TMath::Sqrt( pX*pX + pY*pY ) );
	histos->nTofMatchA->Fill( nTofMatchedTracks );
	histos->refMult->Fill( muEvent->refMult() );
	histos->corrRefMult->Fill( refmultCorrUtil->getRefMultCorr(), eventWeight );
	histos->refMultBins->Fill( cent9, eventWeight );
}

void StRcpQAMaker::preTrackCuts( StMuTrack *primaryTrack ){
	const StMuTrack *globalTrack = primaryTrack->globalTrack();
	StMuBTofPidTraits tofPid = globalTrack->btofPidTraits();

	StThreeVectorF pMom = primaryTrack->momentum();
	StThreeVectorF gMom = globalTrack->momentum();
	float ptRatio = gMom.perp() / pMom.perp();

	histos->pre_nHitsFit->Fill( globalTrack->nHitsFit(kTpcId) );
	histos->pre_nHitsFitOverPoss->Fill( (float)globalTrack->nHitsFit(kTpcId) / globalTrack->nHitsPoss() );
	histos->pre_nHitsDedx->Fill( globalTrack->nHitsDedx() );
	histos->pre_ptRatio->Fill( ptRatio );
	histos->pre_ptRatio2D->Fill( pMom.perp(), gMom.perp() );
	histos->pre_dca->Fill( primaryTrack->dcaGlobal().magnitude() );
	histos->pre_yLocal->Fill( tofPid.yLocal() );
	histos->pre_zLocal->Fill( tofPid.zLocal() );

	histos->trackBeta->Fill( pMom.mag(), 1.0 / tofPid.beta() );
}

void StRcpQAMaker::postTrackCuts( StMuTrack *primaryTrack ){

	const StMuTrack *globalTrack = primaryTrack->globalTrack();
	StMuBTofPidTraits tofPid = globalTrack->btofPidTraits();

	StThreeVectorF pMom = primaryTrack->momentum();
	StThreeVectorF gMom = globalTrack->momentum();
	float ptRatio = gMom.perp() / pMom.perp();

	histos->nHitsFit->Fill( globalTrack->nHitsFit(kTpcId) );
	histos->nHitsFitOverPoss->Fill( (float)globalTrack->nHitsFit(kTpcId) / globalTrack->nHitsPoss() );
	histos->nHitsDedx->Fill( globalTrack->nHitsDedx() );
	histos->ptRatio->Fill( ptRatio );
	histos->ptRatio2D->Fill( pMom.perp(), gMom.perp() );
	histos->dca->Fill( primaryTrack->dcaGlobal().magnitude() );
	histos->yLocal->Fill( tofPid.yLocal() );
	histos->zLocal->Fill( tofPid.zLocal() );	
}

//---------------------------------------------------------------------------
/// constructor sets default parameters
StRcpQAMaker::StRcpQAMaker( const Char_t *name="rcpQAMaker", const Char_t *outname="rcpQA.root") : StRcpSkimmer(name, outname) {
	
}

/// default empty destructor
StRcpQAMaker::~StRcpQAMaker( ){ 

}


Int_t StRcpQAMaker::Init( ){

	StRcpSkimmer::Init();

	mTupleFile = new TFile(mTupleFileName.c_str(), "RECREATE");
	histos = new StRcpQAHistos();

	return kStOK;
}


