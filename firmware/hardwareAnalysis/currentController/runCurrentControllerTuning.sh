printf -v sessionFileName 'cellCurrent_%(%Y-%m-%d_%Hh_%Mm_%Ss)T.session' -1
lxterminal -e ../../IT_Client-0/env/bin/python3 PlotCellCurrent.py $sessionFileName
../../IT_Client-0/env/bin/python3 ../../IT_Client-0/Client.py -initFile cellCurrent_procedure.py -sessionFile $sessionFileName
