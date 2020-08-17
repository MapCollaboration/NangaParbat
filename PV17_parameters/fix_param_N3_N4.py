import pandas as pd
import glob
import os,sys
from shutil import copyfile
from pathlib import Path

fdir = '/Users/delcarro/HEPsoftware/NangaParbatPrivate/PV17_parameters/unpolTMD_parameters/'
os.chdir(fdir)
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

rdir = fdir+'/newpar' #name of destination directory
#os.mkdir(rdir)
Path(rdir).mkdir(parents=True, exist_ok=True) #create dest directory if not existing
os.chdir(rdir) #move to dest directory

for ir in replp.keys():
    with open(fdir+replp[ir]['path']) as file:
        replp[ir]['N4'] = '{:.5E}'.format(float(replp[ir]['N4'])/4)
        replp[ir]['N3fv'] = '{:.5E}'.format(float(replp[ir]['N3fv'])/4)
        data = file.readlines()
        data[5] = '   double precision :: N3fv= {}\n'.format(replp[ir]['N3fv'])
        data[6] = '   double precision :: N3unfv= {}\n'.format(replp[ir]['N3fv'])
        data[7] = '   double precision :: N3Ks= {}\n'.format(replp[ir]['N3fv'])
        data[8] = '   double precision :: N3Ku= {}\n'.format(replp[ir]['N3fv'])
        data[14] = '   double precision :: N4= {}\n'.format(replp[ir]['N4'])
        #save file using specific replica number
        fw = open(rdir+'/unpolTMD_parameters_{}.h'.format(ir),'w')
        fw.writelines(data)
        fw.close()
