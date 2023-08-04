from PIL import Image
import csv
import numpy as np
import math
import pandas as pd
import sys


def ReadCSV(filename):
        fulltxt = open(filename, 'r').read()
        data = []
        num = 0
        for i in range(len(fulltxt)):
            if str(fulltxt[i]).isnumeric():
                num *= 10
                num += int(fulltxt[i])
            else:
                data.append(num)
                num = 0
            if(i % (len(fulltxt) // 100) == 0):
                print(f"Reading... {int(i/len(fulltxt)*100)}%", end="\r")


        del fulltxt
        del num

        print("Finished Reading...")

        return data

def wavelength_to_rgb(wavelength, gamma=0.8):

    '''This converts a given wavelength of light to an 
    approximate RGB color value. The wavelength must be given
    in nanometers in the range from 380 nm through 750 nm
    (789 THz through 400 THz).
    Based on code by Dan Bruton
    http://www.physics.sfasu.edu/astro/color/spectra.html
    '''

    wavelength = float(wavelength)
    if wavelength >= 380 and wavelength <= 440:
        attenuation = 0.3 + 0.7 * (wavelength - 380) / (440 - 380)
        R = ((-(wavelength - 440) / (440 - 380)) * attenuation) ** gamma
        G = 0.0
        B = (1.0 * attenuation) ** gamma
    elif wavelength >= 440 and wavelength <= 490:
        R = 0.0
        G = ((wavelength - 440) / (490 - 440)) ** gamma
        B = 1.0
    elif wavelength >= 490 and wavelength <= 510:
        R = 0.0
        G = 1.0
        B = (-(wavelength - 510) / (510 - 490)) ** gamma
    elif wavelength >= 510 and wavelength <= 580:
        R = ((wavelength - 510) / (580 - 510)) ** gamma
        G = 1.0
        B = 0.0
    elif wavelength >= 580 and wavelength <= 645:
        R = 1.0
        G = (-(wavelength - 645) / (645 - 580)) ** gamma
        B = 0.0
    elif wavelength >= 645 and wavelength <= 750:
        attenuation = 0.3 + 0.7 * (750 - wavelength) / (750 - 645)
        R = (1.0 * attenuation) ** gamma
        G = 0.0
        B = 0.0
    else:
        R = 0.0
        G = 0.0
        B = 0.0
    R *= 255
    G *= 255
    B *= 255
    return (int(R), int(G), int(B))

# CacheFiles = ["raw",
#   "local-sums",
#    "sample-representatives",
#    "predicted_sample",
#    "central_local_difference",
#    "predicted_central_local_difference", 
#    "clipped_quanitzer_bin_center",
#    "predictor", "quantizer_index"]

CacheFiles = ["predictor"]

#file_index = 7

if __name__ == "__main__":
    for file_index in range(len(CacheFiles)):
        print("Starting Display Image..")   

        data = ReadCSV(f"build/{CacheFiles[file_index]}.csv")
        #print(data)

        Nx,Ny,Nz = data[0], data[1], data[2]

        del data[0]
        del data[0]
        del data[0]


        numbers = np.array(data, dtype=int)
        del data
        numbers.resize((Nx,Ny,Nz))


        print("Table Created")

        minimum = numbers.min()
        maximum = numbers.max()
        number_range = maximum - minimum + 1

        print(maximum)
        print(minimum)


        print("Prepared Data..")


        for z in range(0, Nz, 1):
            img = Image.new( 'RGB', (Nx,Ny), "black") # Create a new black image
            pixels = img.load() # Create the pixel map

            minimum = numbers[:,:,z].min()
            maximum = numbers[:,:,z].max()
            number_range = maximum - minimum
            for i in range(img.size[0]):    # For every pixel:
                for j in range(img.size[1]):
                    v = (numbers[i, j, z] - minimum) / number_range * 370 + 380
                    if(math.isnan(v)):
                        v = 0
                    d = wavelength_to_rgb(int(v))
                    pixels[i,j] = (d) # Set the colour accordingly
            img.save(f"Python/images/{CacheFiles[file_index]}{z}.png")
            del img
    

    