counter=1

cd build

for i in {1..20}
do
    echo $counter
    /home/kevin/Kevin/Programming/C/CCSDS_Compression/CCSDS-Compression-C/build/CCSDS_Compressor
    ((counter++))
done

echo ALL DONE