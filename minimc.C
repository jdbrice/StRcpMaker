

void loadlibs(){

	gROOT->Macro("loadMuDst.C");
    gROOT->LoadMacro("$STAR/StRoot/StMuDSTMaker/COMMON/macros/loadSharedLibraries.C");
    loadSharedLibraries();
    
    gSystem ->Load("StChain");
    gSystem ->Load("StMiniMcEvent");
    gSystem->Load( "StRefMultCorr" );
    gSystem->Load( "StRcpPicoMaker" );
}

// pi+ 	= 8
// pi- 	= 9
// k+ 	= 11
// k- 	= 12
// P 	= 14
// pbar = 15
void minimc( int gid = 8, string filelist = "./filelist.lis", string suffix = "_sample", string trackType = "mc", int maxFiles = -1 ){
	
	loadlibs();
	

	StRcpMiniMcPicoMaker * maker = new StRcpMiniMcPicoMaker( gid, filelist, suffix + "_" + trackType, trackType, maxFiles );

	maker->make( );

	delete maker;

}