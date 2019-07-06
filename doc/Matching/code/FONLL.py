import numpy as np
import matplotlib.pyplot as pl

pl.style.use('seaborn-talk')
pl.rc('axes', linewidth=2)
ax = pl.gca()

ax.get_yaxis().set_tick_params(which='both', direction='in', width=2, right=True)
ax.get_xaxis().set_tick_params(which='both', direction='in', width=2, top=True)
ax.get_yaxis().set_tick_params(which='major', size=10)
ax.get_xaxis().set_tick_params(which='major', size=10)
ax.get_yaxis().set_tick_params(which='minor', size=5)
ax.get_xaxis().set_tick_params(which='minor', size=5)

data = np.loadtxt('FONLL.dat')
expdata = np.loadtxt('data.dat')

pl.title(r"SIDIS mult., $x = 0.157$, $Q^2 = 20$ GeV$^2$, $y = 0.439$, $z = 0.2$", fontsize=18)

pl.xlabel(r'$q_T$ [GeV]', fontsize=22, labelpad=-2)
pl.ylabel(r'$\frac{d\sigma}{dx dQ^2 dz dq_T^2}$ / $\frac{d\sigma}{dx dQ^2}$', fontsize=22, labelpad=-3)
pl.xlim(0, 10)
pl.ylim(0.001, 10)
pl.yscale('log')
#pl.xscale('log')
pl.xticks(size=20)
pl.yticks(size=20)

#ax.text(0.2, 0.02,  r'PDF set: CT14nlo', fontsize=22)
#ax.text(0.2, 0.0125, r'FF set: DSS07 ($h+\overline{h}$)', fontsize=22)

pl.plot(data[:,0], data[:,1], 'r-', label = r"Resummed at NLL'")
pl.plot(data[:,0], data[:,2], 'b-', label = r"Asymptotic $\mathcal{O}(\alpha_s)$ w/ NP")
pl.plot(data[:,0], data[:,3], 'g-', label = r"Asymptotic $\mathcal{O}(\alpha_s)$ w/o NP")
pl.plot(data[:,0], data[:,4], 'c-', label = r"Fixed-order $\mathcal{O}(\alpha_s)$")

pl.errorbar(np.sqrt(expdata[:,4] / expdata[:,3] / expdata[:,3]), expdata[:,5], np.sqrt(expdata[:,6]*expdata[:,6]),
            elinewidth=2, capsize=2, capthick=2, label='COMPASS', markersize=8,
            fmt='ko')

pl.legend(fontsize=18)

pl.savefig('FONLL.pdf')
pl.show()
