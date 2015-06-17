#include "iostream.h"

class     StChain;
StChain  *chain=0;
class     St_db_Maker;
St_db_Maker *dbMk =0;

Int_t iEvt=0,istat=0,nEvents=0;
void doMuDstEvents( const Char_t *fileList = "small.lis",
					const Char_t *ntuplename = "ntuple.root")
{
  	Int_t nEvents = 100000000; //1000000;
  	Int_t nfiles 	= 10000;

	//
	// First load some shared libraries we need
	if (gClassTable->GetID("TTable") < 0) {
	gSystem->Load("libStar");
	gSystem->Load("libPhysics");
	}  
	gROOT->LoadMacro("$STAR/StRoot/StMuDSTMaker/COMMON/macros/loadSharedLibraries.C");
	loadSharedLibraries();
	/*gSystem->Load("StarMagField");
	gSystem->Load("StMagF");
	gSystem->Load("StTpcDb");
	//  gSystem->Load("StDbUtilities");
	gSystem->Load("StDaqLib");
	gSystem->Load("StDbBroker");
	gSystem->Load("StDetectorDbMaker");
	gSystem->Load("StDbUtilities");
	gSystem->Load("St_db_Maker");

	gSystem->Load("StEvent");
	gSystem->Load("StEventMaker");
	gSystem->Load("StarMagField");

	gSystem->Load("libtpc_Tables");
	gSystem->Load("libGeom");
	gSystem->Load("St_g2t");
	gSystem->Load("geometry");
	gSystem->Load("St_geant_Maker");

	gSystem->Load("StBTofUtil");
	gSystem->Load("StBTofMatchMaker");*/
	
	gSystem->Load("StRcpPicoMaker");
	gSystem->Load("StRefMultCorr");

	// Handling depends on whether file is a ROOT file or XDF file
	chain  = new StChain("StChain");

	// create the StMuDstMaker
	StMuDstMaker *muDstMaker = new StMuDstMaker(  0,
	                                                0,
	                                                "",
	                                                fileList,
	                                                "MuDst.root",
	                                                nfiles
	                                              );

	//StRcpQAMaker *rcpQA = new StRcpQAMaker("rcpQA", ("qa_" + string(ntuplename) ).c_str() );
	StRcpPicoMaker *rcpPico = new StRcpPicoMaker("rcpPico", ntuplename);

	// Initialize chain
	Int_t iInit = chain->Init();
	if (iInit) chain->Fatal(iInit,"on init");
	chain->PrintInfo();


	// Event loop
	//
	int istat = 0, i = 1;
EventLoop: 
	
	if (i <= nEvents && istat != 2) {
   
   if ( i % 100 == 0 )
	   cout << endl << "============================ Event " << i << " start ============================" << endl;
   
   chain->Clear();
   istat = chain->Make(i);
   if (istat == 2) 
	 {cout << "Last  event processed. Status = " << istat << endl;}
   if (istat == 3) 
	 {cout << "Error event processed. Status = " << istat << endl;}
   
   //   gObjectTable->Print();
   i++;
   goto EventLoop;
 }
	
	i--;
	if ( i % 100 == 0 )
  		cout<<endl<<"============================ Event "<<i<<" finish ============================"<<endl;

  //
  // Chain Finish
  //
  if (nEvents > 1) {
	chain->Finish();
	delete chain;
  }

}



