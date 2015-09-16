#!/bin/bash

starver SL14i
root4star -b -q 'minimc.C(12,"/star/u/jdb/work/StRcpMaker/list/mc/k_minus.lis","", "mc")' >& log_k_minus_mc.log
root4star -b -q 'minimc.C(12,"/star/u/jdb/work/StRcpMaker/list/mc/k_minus.lis","", "rc")' >& log_k_minus_rc.log

root4star -b -q 'minimc.C(11,"/star/u/jdb/work/StRcpMaker/list/mc/k_plus.lis","", "mc")' >& log_k_plus_mc.log
root4star -b -q 'minimc.C(11,"/star/u/jdb/work/StRcpMaker/list/mc/k_plus.lis","", "rc")' >& log_k_plus_rc.log

root4star -b -q 'minimc.C(15,"/star/u/jdb/work/StRcpMaker/list/mc/anti_p.lis","", "mc")' >& log_anti_p_mc.log
root4star -b -q 'minimc.C(15,"/star/u/jdb/work/StRcpMaker/list/mc/anti_p.lis","", "rc")' >& log_anti_p_rc.log

root4star -b -q 'minimc.C(9,"/star/u/jdb/work/StRcpMaker/list/mc/pi_minus.lis","", "rc")' >& log_pi_minus_rc.log
root4star -b -q 'minimc.C(9,"/star/u/jdb/work/StRcpMaker/list/mc/pi_minus.lis","", "mc")' >& log_pi_minus_mc.log

root4star -b -q 'minimc.C(8,"/star/u/jdb/work/StEffMaker/lists/pi_plus.lis","", "mc")' >& log_pi_plus_mc.log
root4star -b -q 'minimc.C(8,"/star/u/jdb/work/StEffMaker/lists/pi_plus.lis","", "rc")' >& log_pi_plus_rc.log

root4star -b -q 'minimc.C(14,"/star/u/jdb/work/StRcpMaker/list/mc/p.lis","", "mc")' >& log_p_mc.log
root4star -b -q 'minimc.C(14,"/star/u/jdb/work/StRcpMaker/list/mc/p.lis","", "rc")' >& log_p_rc.log