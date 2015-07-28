#!/bin/bash


get_file_list.pl -onefile -delim / -keys path,filename -cond collision=auau15,production=P14ii,filetype=daq_reco_mudst,filename~st_physics,runnumber[]15053000-15071000 -limit 50000000 > fullList.lis