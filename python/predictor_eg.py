import numpy as np
import compression as comp
#from sklearn.metrics import mean_squared_error
import csv
import sys

from csv_io import ReadCSV, SaveCSV
if __name__ == "__main__":
    print("_________PYTHON PREDICTOR_________")
    n = len(sys.argv)
    if(n > 1):
        data = ReadCSV(f"data/test-images/TEST{sys.argv[1]}.csv")
        Nx, Ny, Nz = data.shape

        python_predicted = comp.predictor(data)
        SaveCSV(python_predicted, f"data/results/PYTHONRESULT{sys.argv[1]}_predicted.csv")
    else:
        data = ReadCSV("data/test-images/TEST_100x100x100_0.csv")
        Nx, Ny, Nz = data.shape

        python_predicted = comp.predictor(data)
        SaveCSV(python_predicted, "data/results/PYTHONRESULT_100x100x100_0_predicted.csv")
    #data1 = ReadCSV("results/PYTHONRESULT_100x100x100_0_predicted.csv")
    #print(np.equal(data, data1).std())
    #SaveCSV(python_residuals, "./python_residuals.csv")

    #c_predicted = ReadCSV("../build/predictor.csv")
    #c_vs_python = c_predicted == python_predicted
    #SaveCSV(c_vs_python, "./c_vs_python.csv")