import matplotlib.pyplot as plt
import numpy as np

y1 = np.array([
    0.5746536923,
    0.2423636519,
    0.03280416001,
    0.001515151515,
    0
])
y2 = np.array([
    0.59049,
    0.2373046875,
    0.03125,
    0.0009765625,
    0.00001
])

plt.plot(y1)
plt.plot(y2)

plt.show()