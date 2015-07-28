## StRcpMaker

First step in the PIDed R_CP analysis.  
- Skims MuDsts to extract only Primary TPC tracks that pass a loose set of analysis cuts. The skimmer is used to produce RcpPicoDst trees and to produce QA for the analysis.
- Skims MiniMC files from embedding or other simulated data souces. Produces RcpPicoDst Trees identical to those from skimming the MuDst. Can be used to produce trees with only MC tracks or trees with only RC tracks.


### Usage:

- Templates for submitting to the STAR condor pool are in /grid/
- List files for testing and for MC files are in /list/ ( data is read from the catalogue)
- Should be compiled with `make` not `cons` since it uses JDBlib for XML config file parsing
- Outputs to /star/institutions/rice/jdb/run14/auau15/rcp/rcpData for Data files
- Outputs to /star/institutions/rice/jdb/run14/auau15/embedding for MC 