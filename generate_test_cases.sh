ProjectName="CCSDS_Compression"

cd build
cmake ..
make
./${ProjectName} gentest
#sudo shutdown -h now
