import pandas as pd
import glob
import os,sys
from shutil import copyfile
from pathlib import Path

fdir = '/Users/delcarro/HEPsoftware/NangaParbatPrivate/PV17_parameters'
os.chdir(fdir+'/unpolTMD_parameters')
replfiles = glob.glob('unpolTMD*') #read all param filenames in the folder

replp = {} #initialize param dict
for fn in replfiles:
    replp[int(fn.strip('unpolTMD_parameters_*.h'))] =  {'path':fn} #save path of replica, number of repl is also main level key

for ir in replp.keys():  #iterate over repl number
    with open(replp[ir]['path']) as f:
        fln = f.readlines()
        flna = [ln.replace('=','').split() for ln in fln] #remove redundant parts in lines and split them in single strings
        if int(flna[-1][2].strip(':')) != ir: #check that replica filename and replica numbercontained  in the file actually match
                print('number of replica not matching with filename: {}'.format(ir))
                break
        del flna[-2:] #remove lines with replica number after check
        for el in flna:
            replp[ir][el[3]] = el[4] #assign param value [4], using param name [3] as key

rdir = fdir+'/reports' #name of destination directory
#os.mkdir(rdir)
Path(rdir).mkdir(parents=True, exist_ok=True) #create dest directory if not existing
os.chdir(rdir) #move to dest directory
origfname = rdir + '/Report_orig.yaml'
copyfile('/Users/delcarro/HEPsoftware/NangaParbat/FitResults/TestFit_PV17_NLL/replica_0/Report.yaml',origfname) #copy original report file in dest directory


with open(origfname) as file:
    data = file.read() #read copy of original report file
    for ir in replp.keys():
        #substitute string with parameters in original file with parameters from a specific replica
        #replp[ir]['N4'] = '{:.5E}'.format(float(replp[ir]['N4'])/4)
        #replp[ir]['N4'] = '{:.5E}'.format(float(replp[ir]['N4'])/4)
        string_to_sub = 'Parameters: {{$g_2$: {}, $N_1$: {}, $\\alpha$: {}, $\\sigma$: {}, $\\lambda$: {}, $N_3$: {}, $\\beta$: {}, $\\delta$: {}, $\\gamma$: {}, $\\lambda_F$: {}, $N_4$: {}}}\n'.format(*list(map(replp[ir].get, ['g2','N1d','al','si', 'lam', 'N3fv', 'be', 'de', 'ga', 'lamF','N4'])))
        at = data.replace('Parameters: {$g_2$: 0.128, $N_1$: 0.285, $\\alpha$: 2.98, $\\sigma$: 0.173, $\\lambda$: 0.39, $N_3$: 0.212, $\\beta$: 2.1, $\\delta$: 0.094, $\\gamma$: 2.52, $\\lambda_F$: 5.29, $N_4$: 0.033}\n',string_to_sub)
        #save file using specific replica number
        fw = open(rdir+'/Report_{}.yaml'.format(ir),'w')
        fw.write(at)
        fw.close()
