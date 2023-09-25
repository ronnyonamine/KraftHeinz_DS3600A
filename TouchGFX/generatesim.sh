#
# Add a pre-build step to run RegParamCollect.exe 
# 
echo "compiling simulator"
if [ -e ../RegParamCollect.exe ]
then 
    ../RegParamCollect.exe ../
else
    echo "Error: RegParamCollect not found"
    read -n 1 -s -r -p "Press any key to close this window"
fi
# check for return code
retVal=$?
if [ $retVal -eq 0 ]
then
    make -f simulator/gcc/Makefile assets -j8
else
    echo "Error RegParamCollect encountered errors"
    read -n 1 -s -r -p "Press any key to close this window"
fi

