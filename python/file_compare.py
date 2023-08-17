import csv_io
import sys
import numpy as np

def CompareResults(c_pred_file, python_pred_file):
    c_img = csv_io.ReadCSV(c_pred_file)
    python_img = csv_io.ReadCSV(python_pred_file)

    difference = (c_img - python_img)
    print(np.nonzero(difference))
    return (difference.std())

if __name__ == "__main__":
    n = len(sys.argv)

    if n == 3:
        print("______Comparing C and Python______")
        print("Error:", CompareResults(sys.argv[1], sys.argv[2]))
