# Set permissions recursively for all files and directories in the current directory
sudo chmod -R 777 ./*
# Start the Docker container named TPE_CONTAINER
sudo docker start TPE_CONTAINER
# Execute the 'make' command inside the Docker container at the specified path
sudo docker exec -it TPE_CONTAINER make -C/root/Toolchain
# Execute the 'make' command inside the Docker container at the specified path and redirect the output to a file named 'make_out.txt'
sudo docker exec -it TPE_CONTAINER make -C/root/ > make_out.txt
# Set permissions for the 'x64BareBonesImage.qcow2' file
sudo chmod 777 Image/x64BareBonesImage.qcow2
# Run the 'qemu-system-x86_64' command with the specified parameters
qemu-system-x86_64 -hda Image/x64BareBonesImage.qcow2 -m 512
qemu-system-x86_64 -hda Image/x64BareBonesImage.qcow2 -m 512 -audiodev pa,id=speaker -machine pcspk-audiodev=speaker
# Execute the 'make clean' command inside the Docker container at the specified path to clean up any previous build artifacts in the Toolchain directory
sudo docker exec -it TPE_CONTAINER make clean -C/root/Toolchain
# Execute the 'make clean' command inside the Docker container at the specified path to clean up any previous build artifacts in the root directory
sudo docker exec -it TPE_CONTAINER make clean -C/root/
# Stop the Docker container named TPE_CONTAINER
sudo docker stop TPE_CONTAINER                                             #stop