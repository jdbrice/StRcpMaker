#!/bin/bash

starver SL14i

root4star -b -q 'minimc.C(12,"/star/u/jdb/work/StRcpMaker/list/mc/k_minus.lis","", "rc")' >& MC/log_k_minus_rc.log
root4star -b -q 'minimc.C(11,"/star/u/jdb/work/StRcpMaker/list/mc/k_plus.lis","", "rc")' >& MC/log_k_plus_rc.log
root4star -b -q 'minimc.C(15,"/star/u/jdb/work/StRcpMaker/list/mc/anti_p.lis","", "rc")' >& MC/log_anti_p_rc.log
root4star -b -q 'minimc.C(9,"/star/u/jdb/work/StRcpMaker/list/mc/pi_minus.lis","", "rc")' >& MC/log_pi_minus_rc.log
root4star -b -q 'minimc.C(8,"/star/u/jdb/work/StEffMaker/lists/pi_plus.lis","", "rc")' >& MC/log_pi_plus_rc.log
root4star -b -q 'minimc.C(14,"/star/u/jdb/work/StRcpMaker/list/mc/p.lis","", "rc")' >& MC/log_p_rc.log