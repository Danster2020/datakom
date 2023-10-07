
import numpy as np  
import matplotlib.pyplot as plt  
  
X = ['Sim1','Sim2','Sim3','Sim4', 'Sim5'] 
yData = [
    0.1512,
    0.1008,
    0.06048,
    0.0168,
    0.0072
    ] 
zData = [
    0.1651382175,
    0.09679219677,
    0.0655632577,
    0.02098800469,
    0.005904298459,
    ] 
  
X_axis = np.arange(len(X)) 
  
plt.bar(X_axis - 0.2, yData, 0.4, label = 'Analytical') 
plt.bar(X_axis + 0.2, zData, 0.4, label = 'Simulation') 
  
plt.xticks(X_axis, X) 
plt.xlabel("Simulation groups")
plt.ylabel("PDR") 
plt.title("Comparing analytical with simulated PDR") 
plt.legend() 
plt.show() 
