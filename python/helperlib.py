#Helper functions
import numpy
#Function required for weight update - not the same as numpy.sign so I had to quickly make it
def sign(x):
    if x >= 0:
        return 1
    else:
        return -1

#Conversion functions (borrowed from FPCNN)
def dec_to_bin(d, width):
    if (type(d) == numpy.float64):
        d = int(d)
    b = [int(x) for x in "{:0{size}b}".format(d, size=width)]

    return b

def bin_to_dec(b):
    d = int("".join(str(x) for x in b), 2)

    return d
