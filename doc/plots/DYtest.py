import numpy as np
import matplotlib.pyplot as pl

pl.style.use('seaborn-talk')
pl.rc('axes', linewidth=2)
ax = pl.gca()

ax.get_yaxis().set_tick_params(which='both', direction='in', width=2, right='on')
ax.get_xaxis().set_tick_params(which='both', direction='in', width=2, top='on')
ax.get_yaxis().set_tick_params(which='major', size=10)
ax.get_xaxis().set_tick_params(which='major', size=10)
ax.get_yaxis().set_tick_params(which='minor', size=5)
ax.get_xaxis().set_tick_params(which='minor', size=5)

data = np.loadtxt('DYtest.dat')

pl.title(r"Drell-Yan production at CDF Run II, $\sqrt{s}=1.96$ TeV", fontsize=22)

pl.xlabel(r'$q_T$ [GeV]', fontsize=22)
pl.ylabel(r'$\frac{d\sigma}{dq_T} (1/GeV)$', fontsize=22)
pl.xlim(0, 20.)
pl.ylim(0.0001, 2.5)
#pl.xscale('log')
#pl.yscale('log')
pl.grid(linewidth=1)
pl.xticks(size=20)
pl.yticks(size=20)

pl.errorbar(data[:,2], data[:,3]/10, data[:,4]/10,
            elinewidth=2, capsize=3, capthick=2, label='Data', markersize=12,
            fmt='ko')

pl.step(data[:,0], data[:,5]/10, where='post', label=r'N$^3$LL (APFEL++/NangaParbat)')
#pl.step(data[:,0], data[:,6], where='post', label=r'NangaParbat $\times$ 2')
#pl.step(data[:,0], data[:,7], where='post', label=r'NangaParbat $\times$ 2')
#pl.step(data[:,0], data[:,8], where='post', label=r'NangaParbat $\times$ 2')

pl.legend(fontsize=22)

pl.savefig('DYtest.pdf')
pl.show()
