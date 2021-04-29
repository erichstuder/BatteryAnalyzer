from control import tf
from math import inf

class RcFilter:

	'''
	   ___       ___
	--|___|--+--|___|--+-- ...
	         |         |
	       -----     -----
	       -----     -----
	         |         |
	---------+---------+-- ...

	'''
	@staticmethod
	def getCoupled(R=1, C=1, nrOfStages=2):
		s = tf('s')
		xc = 1/(s*C)

		ua = 1
		ue = ua
		z = inf

		for n in range(nrOfStages):
			z = 1/(1/xc + 1/z)
			i = ue/z
			z += R
			ue = i * z
		
		return ua/ue
