
sudo chmod -R 777 ./*
sudo docker start TPE_CONTAINER                                                #start del docker

sudo docker exec -it TPE_CONTAINER   make -C/root/Toolchain                       #make
sudo docker exec -it TPE_CONTAINER   make -C/root/                                #make

sudo chmod 777 Image/x64BareBonesImage.qcow2                       #permisos
sudo chmod -R 777 ./*

qemu-system-x86_64 -s -S -hda Image/x64BareBonesImage.qcow2 -m 512       #run
sudo docker exec -it TPE_CONTAINER   make clean -C/root/Toolchain                 #borra lo que habia
sudo docker exec -it TPE_CONTAINER   make clean -C/root/                          #borra lo que habia
sudo docker stop TPE_CONTAINER                                                  #stop