
import numpy as np
import matplotlib.pyplot as plt

X = ['0.1',
     '0.25',
     '0.50',
     '0.75',
     '0.90'
     ]
yData = [
    0.59049,
    0.2373046875,
    0.03125,
    0.0009765625,
    0.00001
]
zData = [
    0.5746536923,
    0.2423636519,
    0.03280416001,
    0.001515151515,
    0
]


X_axis = np.arange(len(X))

plt.bar(X_axis - 0.2, yData, 0.4, label='Analytical')
plt.bar(X_axis + 0.2, zData, 0.4, label='Simulation')

plt.xticks(X_axis, X)
plt.xlabel("Loss probability")
plt.ylabel("Average PDR")
plt.title("Comparing analytical with simulated PDR")
plt.legend()
plt.show()
