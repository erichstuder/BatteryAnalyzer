from RcFilter import RcFilter
from control import bode
from control import step_response
from control import freqresp
from scipy.optimize import root_scalar
import matplotlib.pyplot as plt
from math import pi
import numpy as np

def myFunc(R, C, nrOfStages):
	g = RcFilter.getCoupled(R=R, C=C, nrOfStages=nrOfStages)
	mag, phase, w = freqresp(g, 2*pi*980)
	return mag - 1e-3

g = []
for n in range(1, 5):
	R=68e3
	result = root_scalar(lambda C: myFunc(R=R, C=C, nrOfStages=n), bracket=[1e-10, 1e6], method='bisect')
	g += [RcFilter.getCoupled(R=R, C=result.root, nrOfStages=n)]
	print(result.root)



plt.ion()
plt.figure(1)
#plt.style.use('dark_background')
mag, phase, w = bode(g, dB=True, Hz=True)

plt.figure(2)
plt.grid()
for sys in g:
	t,y = step_response(sys, np.arange(0, 0.1, 1e-4))
	plt.plot(t, y)

input("press enter to exit ...")
