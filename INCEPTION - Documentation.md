INCEPTION - Documentation
hopefully to help me understand what to

/*

Docker tutorial, goes over basic docker commands, terminology, images and dockefiles
https://docker-curriculum.com/

Containers vs VMs: What's the difference?
IBM Technology
	https://www.youtube.com/watch?v=cjXI-yxqGTI



*/



				     $$\                     $$\
				     $$ |                    $$ |
				$$$$$$$ | $$$$$$\   $$$$$$$\ $$ |  $$\  $$$$$$\   $$$$$$\
				$$  __$$ |$$  __$$\ $$  _____|$$ | $$  |$$  __$$\ $$  __$$\
				$$ /  $$ |$$ /  $$ |$$ /      $$$$$$  / $$$$$$$$ |$$ |  \__|
				$$ |  $$ |$$ |  $$ |$$ |      $$  _$$<  $$   ____|$$ |
				\$$$$$$$ |\$$$$$$  |\$$$$$$$\ $$ | \$$\ \$$$$$$$\ $$ |
				\_______| \______/  \_______|\__|  \__| \_______|\__|

Docker
	Supply containers  - an environment to run applications in, that is mostly isolated from the host and other containers.
	Containes the application and its dependencies only!


	|----VMS vs DOCKER:-----------------------------------------------------------------------------------------------------|
	|	VMS virtualize the OS Kernel, as well as the applications layer. meaning they boot their own OS with each instance.	|
	|	Docker containers only virtualize the Applications layer.															|
	|		this makes Docker more lightweight and faster to boot and run than a VM.										|
	|																														|
	|	VMS are completely isolated from eachother - HARDWARE ISOLATION.													|
	|	Docker containers are able to communicate and share resources.														|
	|	Compatibility:																										|
	|		VM of any OS can run on any OS host.																			|
	|		Docker is more limited - A Docker container may not be compatible with the Windows kernel.						|
	|-----------------------------------------------------------------------------------------------------------------------|

	namespaces:
		the isolation mechanism that allows multiple containers to run on the same host without interfering with each other.
	Cgroups:
		limtation and control of the resources each process is using

	Dockerfiles:
			basically a makefile for creating Docker Images.
			Dockerfile ref: https://docs.docker.com/engine/reference/builder/
	Docker Image:
		A Docker image is a pre-packaged, read-only template that contains everything needed to run an application, including the application code, dependencies, and any system libraries or configuration files. Images are created from a Dockerfile, which specifies the configuration and steps needed to build the image.
	Docker Container:
		A Docker container is a running instance of a Docker image. Containers are isolated environments that run an application and its dependencies, but with their own isolated file system, network, and resources. Containers are created from Docker images, and multiple containers can run from the same image.
	Docker Volume:
		A Docker volume is a persistent data storage area that can be used by one or more containers. Volumes are used to store data that needs to persist beyond the life of a container, such as application configuration files or user data. Volumes can be created and managed independently of containers and can be shared between containers.

										|----docker-compose.yml---------------------------------------------|
										|	A docker-compose.yml is a config file for Docker Compose.		|
										|	It allows to deploy, combine, and configure multiple docker		|
										|		containers at the same time. The Docker "rule" is to		|
										|		outsource every single process to its own Docker container.	|
										|	The advantage of Docker Compose is easy configuration.			|
										|		You don't have to write a big bunch of commands into Bash,	|
										|		You can predefine it in the docker-compose.yml.				|
										|	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!		|
										|	The key difference between the Dockerfile and docker-compose	|
										|	is that the Dockerfile describes how to build Docker images,	|
										|	while docker-compose is used to run Docker containers.			|
										|-------------------------------------------------------------------|


$$$$$$$$\ $$\                        $$$$$$\                       $$\               $$\
\__$$  __|$$ |                      $$  __$$\                      $$ |              \__|
   $$ |   $$$$$$$\   $$$$$$\        $$ /  \__| $$$$$$\  $$$$$$$\ $$$$$$\    $$$$$$\  $$\ $$$$$$$\   $$$$$$\   $$$$$$\   $$$$$$$\
   $$ |   $$  __$$\ $$  __$$\       $$ |      $$  __$$\ $$  __$$\\_$$  _|   \____$$\ $$ |$$  __$$\ $$  __$$\ $$  __$$\ $$  _____|
   $$ |   $$ |  $$ |$$$$$$$$ |      $$ |      $$ /  $$ |$$ |  $$ | $$ |     $$$$$$$ |$$ |$$ |  $$ |$$$$$$$$ |$$ |  \__|\$$$$$$\
   $$ |   $$ |  $$ |$$   ____|      $$ |  $$\ $$ |  $$ |$$ |  $$ | $$ |$$\ $$  __$$ |$$ |$$ |  $$ |$$   ____|$$ |       \____$$\
   $$ |   $$ |  $$ |\$$$$$$$\       \$$$$$$  |\$$$$$$  |$$ |  $$ | \$$$$  |\$$$$$$$ |$$ |$$ |  $$ |\$$$$$$$\ $$ |      $$$$$$$  |
   \__|   \__|  \__| \_______|       \______/  \______/ \__|  \__|  \____/  \_______|\__|\__|  \__| \_______|\__|      \_______/


• NGINX with TLSv1.2 or TLSv1.3 only.
	Nginx is a webserver which stores hmtl, js, images files and use http request to display a website. Nginx conf documents will be used to config our server and the right proxy connexion.
	TLS - Transport Layer Security protocol

• WordPress + php-fpm (it must be installed and configured) - without nginx.
 	php-fpm - (FastCGI Process Manager)
• MariaDB  -  without nginx.
• A volume that contains your WordPress database.
• A second volume that contains your WordPress website files.
• A docker-network that establishes the connection between your containers.
Your containers have to restart in case of a crash.

___________________________________________________________________________________________________________________________________________________________________________
___________________________________________________________________________________________________________________________________________________________________________

NOTES:
	-only users in the 'docker' user grouo have access to the Docker deamon socket. by default only sudo and docker are added, personal user might need to be added with [sudo usermod -aG docker $USER] then either reset ubuntu, or run [newgrp docker] which will open a new terminal, iin which the current user's primary grouo is the specified one. ie docker. (TEMP solution that will only last for the current terminal)
