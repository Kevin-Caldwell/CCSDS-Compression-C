from PIL import Image
import csv
import numpy as np
import math

def ReadCSV(filename):
    with open(filename) as f:
        reader = csv.reader(f)
        return list(reader)

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

CacheFiles = ["raw",
  "local-sums",
   "sample-representatives",
   "predicted_sample",
   "central_local_difference",
   "predicted_central_local_difference", 
   "clipped_quanitzer_bin_center",
   "predictor", "quantizer_index"]

#file_index = 7

if __name__ == "__main__":
    for file_index in range(len(CacheFiles)):
        print("Starting Display Image..")   

        data = ReadCSV(f"build/{CacheFiles[file_index]}.csv")
        #print(data)

        Nx,Ny,Nz = int(data[0][0]), int(data[0][1]), int(data[0][2])

        del data[0][0]
        del data[0][0]
        del data[0][0]


        numbers = np.array(data, dtype=int)
        numbers.resize((1, Nx * Ny * Nz))

        a = np.zeros((Nx,Ny,Nz))
        buf = 0

        for i in range(Nx):
            for j in range(Ny):
                for k in range(Nz):
                    buf = numbers[0,k * Nx * Ny + j * Nx + i]
                    if buf > 6553:
                        a[i,j,k] = 0
                    else:
                        a[i,j,k] = buf

        print("Table Created")

        del numbers

        #print(numbers)

        minimum = a.min()
        maximum = a.max()
        number_range = 999 #maximum - minimum + 1

        print(maximum)
        print(minimum)

        #numbers.resize((Nx,Ny,Nz), refcheck=False)

        print("Prepared Data..")

        #print(numbers)
        #z = 0

        for z in range(0, Nz, 1):
            img = Image.new( 'RGB', (Nx,Ny), "black") # Create a new black image
            pixels = img.load() # Create the pixel map

            minimum = a[:,:,z].min()
            maximum = a[:,:,z].max()
            number_range = maximum - minimum
            for i in range(img.size[0]):    # For every pixel:
                for j in range(img.size[1]):
                    v = (a[i, j, z] - minimum) / number_range * 370 + 380
                    if(math.isnan(v)):
                        v = 0
                    d = wavelength_to_rgb(int(v))
                    pixels[i,j] = (d) # Set the colour accordingly
            img.save(f"Python/images/{CacheFiles[file_index]}{z}.png")
            del img
    

    