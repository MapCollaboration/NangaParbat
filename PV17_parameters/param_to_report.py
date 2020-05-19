import pandas as pd
import glob
import os,sys
from shutil import copyfile
from pathlib import Path

fdir = '/Users/delcarro/HEPsoftware/NangaParbatPrivate/PV17_parameters'
os.chdir(fdir)
replfiles = glob.glob('unpolTMD*')

replp = {}
for fn in replfiles:
    replp[int(fn.strip('unpolTMD_parameters_*.h'))] =  {'path':fn}

for ir in replp.keys():
    with open(replp[ir]['path']) as f:
        fln = f.readlines()
        flna = [ln.replace('=','').split() for ln in fln]
        if int(flna[-1][2].strip(':')) != ir:
                print('number of replica not matching with filename: {}'.format(ir))
                break
        del flna[-2:]
        for el in flna:
            replp[ir][el[3]] = el[4]

replp.keys()


rdir = fdir+'/reports'
#os.mkdir(rdir)
Path(rdir).mkdir(parents=True, exist_ok=True)
os.chdir(rdir)
origfname = rdir + '/Report_orig.yaml'
copyfile('/Users/delcarro/HEPsoftware/NangaParbat/FitResults/TestFit_PV17_NLL/replica_0/Report.yaml',origfname)


with open(origfname) as file:
    data = file.read()
    for ir in replp.keys():
        string_to_sub = 'Parameters: {{$g_2$: {}, $N_1$: {}, $\\alpha$: {}, $\\sigma$: {}, $\\lambda$: {}, $N_3$: {}, $\\beta$: {}, $\\delta$: {}, $\\gamma$: {}, $\\lambda_F$: {}, $N_4$: {}}}\n'.format(*list(map(replp[ir].get, ['g2','N1d','al','si', 'lam', 'N3fv', 'be', 'de', 'ga', 'lamF','N4'])))
        at = data.replace('Parameters: {$g_2$: 0.128, $N_1$: 0.285, $\\alpha$: 2.98, $\\sigma$: 0.173, $\\lambda$: 0.39, $N_3$: 0.212, $\\beta$: 2.1, $\\delta$: 0.094, $\\gamma$: 2.52, $\\lambda_F$: 5.29, $N_4$: 0.033}\n',string_to_sub)
        fw = open(rdir+'/Report_{}.yaml'.format(ir),'w')
        fw.write(at)
        fw.close()
