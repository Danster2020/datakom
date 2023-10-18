
import numpy as np  
import matplotlib.pyplot as plt  
  
X = ['Sim1','Sim2','Sim3','Sim4', 'Sim5'] 
yData = [
    1.481559683,
    1.482996856,
    1.482187667,
    1.490446547,
    1.484687831
    ] 
zData = [
    8.659695386,
    13.85819476,
    18.77449527,
    36.00272552,
    0,
    ] 
  
X_axis = np.arange(len(X)) 
  
plt.bar(X_axis - 0.2, yData, 0.4, label = 'IGG') 
plt.bar(X_axis + 0.2, zData, 0.4, label = 'IPG') 
  
plt.xticks(X_axis, X) 
plt.xlabel("Simulation groups")
plt.ylabel("Time") 
plt.title("Comparing IGG and IPG") 
plt.legend() 
plt.show() 
