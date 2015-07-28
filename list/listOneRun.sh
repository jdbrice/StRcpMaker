#!/bin/bash


get_file_list.pl -delim / -keys path,filename -cond collision=auau15,production=P14ii,filetype=daq_reco_mudst,filename~st_physics,runnumber[]15061001-15061001 -limit 50