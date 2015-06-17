#ifndef ST_RCP_QA_HISTOS_H
#define ST_RCP_QA_HISTOS_H


#include "TTree.h"
#include "TFile.h"
#include "TH1.h"
#include "TH1I.h"
#include "TH2.h"
#include <string>
#include <sstream>


class StRcpQAHistos
{
public:
	StRcpQAHistos(){


		/*
			Event Cuts
		 */
		eventCuts = new TH1I( "event_cuts", "Event Cuts", 10, 0, 10 );
		
		nTrack_refMult = new TH1I( "event_nTrack_refMult", "nTrack vs. RefMult", 401, -0.5, 400.5 );
		
		pre_refMult = new TH1I( "event_pre_refMult", "Pre Raw RefMult", 401, -0.5, 400.5 );
		refMult = new TH1I( "event_refMult", "Raw RefMult", 401, -0.5, 400.5 );
		corrRefMult = new TH1F( "event_corrRefMult", "Corr RefMult", 401, -0.5, 400.5 );
		refMultBins = new TH1F( "event_refMultBins", "Corr RefMult Bins", 11, -0.5, 10.5 );

		pre_vZ = new TH1F( "event_pre_vZ", "pre vZ", 400, -200, 200 );
		vZ = new TH1F( "event_vZ", "vZ", 100, -50, 50 );

		pre_vX_vY = new TH2F( "event_pre_vX_vY", "pre vX vY", 200, -1, 1, 200, -1, 1 );
		vX_vY = new TH2F( "event_vX_vY", "vX vY", 200, -1, 1, 200, -1, 1 );

		pre_vR = new TH1F( "event_pre_vR", "", 30, 0, 3 );
		vR = new TH1F( "event_vR", "", 22, 0, 1.1 );

		pre_nTofMatchA = new TH1F( "event_pre_nTofMatchA", "", 451, -0.5, 450.5 );
		nTofMatchA = new TH1F( "event_nTofMatchA", "", 401, -0.5, 400.5 );


		/**
		 * Track Histos
		 */
		trackCuts = new TH1I( "track_cuts", "Track Cuts", 20, 0, 20 );
		pre_nHitsFit = new TH1I( "track_pre_nHitsFit", "", 53, -0.5, 52.5 );
		nHitsFit = new TH1I( "track_nHitsFit", "", 53, -0.5, 52.5 );

		pre_nHitsDedx = new TH1I( "track_pre_nHitsDedx", "", 53, -0.5, 52.5 );
		nHitsDedx = new TH1I( "track_nHitsDedx", "", 53, -0.5, 52.5 );

		pre_nHitsFitOverPoss = new TH1I( "track_pre_nHitsFitOverPoss", "", 100, 0, 1.0 );
		nHitsFitOverPoss = new TH1I( "track_nHitsFitOverPoss", "", 100, 0, 1.0 );

		pre_ptRatio = new TH1I( "track_pre_ptRatio", "", 100, 0, 2.1  );
		ptRatio = new TH1I( "track_ptRatio", "", 100, 0, 2.1 );

		pre_ptRatio2D = new TH2F( "track_pre_ptRatio2D", "Global vs. Primary; Primary pT; Global pT", 30, 0, 6, 30, 0, 6  );
		ptRatio2D = new TH2F( "track_ptRatio2D", "Global vs. Primary; Primary pT; Global pT", 30, 0, 6, 30, 0, 6 );

		pre_dca = new TH1I( "track_pre_dca", "", 40, 0, 2.0  );
		dca = new TH1I( "track_dca", "", 40, 0, 2.0 );

		pre_yLocal = new TH1I( "track_pre_yLocal", "", 40, -2.0, 2.0  );
		yLocal = new TH1I( "track_yLocal", "", 40, -2.0, 2.0 );

		pre_zLocal = new TH1I( "track_pre_zLocal", "", 60, -3.0, 3.0  );
		zLocal = new TH1I( "track_zLocal", "", 60, -3.0, 3.0 );

		trackBeta = new TH2F( "trackBeta", "beta", 40, 0, 5, 100, -.5, 3 );

	}
	~StRcpQAHistos();


//protected:

	/**
	 * Event Histos
	 */
	TH1I *eventCuts, *nTrack_refMult, *refMult, *pre_refMult;
	TH1F *pre_vZ, *pre_vR, *pre_nTofMatchA;
	TH2F *pre_vX_vY, *vX_vY;
	TH1F *vZ, *vR, *nTofMatchA, *corrRefMult, *refMultBins;


	/**
	 * Track Histos
	 */
	TH1I *trackCuts;
	TH1I * pre_nHitsFit, *pre_nHitsDedx, *pre_nHitsFitOverPoss, *pre_ptRatio, *pre_dca;
	TH1I * nHitsFit, *nHitsDedx, *nHitsFitOverPoss, *ptRatio, *dca, *pre_yLocal, *pre_zLocal, *yLocal, *zLocal;
	TH2F * pre_ptRatio2D, *ptRatio2D;
	TH2F * trackBeta;

	/**
	 * Analysis 
	 */
	TH1F * ptSpectra[9];

	


};



#endif