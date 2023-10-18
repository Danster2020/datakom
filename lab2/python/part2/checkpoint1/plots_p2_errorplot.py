import matplotlib.pyplot as plt
import numpy as np

pdr_standard_deviation_data = {
        '0.1': 0.017577595300111,
        '0.25': 0.020337674237231,
        '0.50': 0.0075604936466853,
        '0.75': 0.0030303030304,
        '0.90': 0
}


x = list(pdr_standard_deviation_data.keys())
y = np.array([0.5746536923, 0.2423636519, 0.03280416001, 0.001515151515, 0])
e = list(pdr_standard_deviation_data.values())

plt.errorbar(x, y, e, linestyle='None', marker='.', capsize=3)
plt.grid()
plt.xlabel("Loss probability")
plt.ylabel("Average PDR") 
plt.title("Standard deviation") 

plt.show()