INCEPTION - Documentation
hopefully to help me understand what to

/*
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

	DOCKER IMAGES: lightweight executable packages that include everything needed to run some software.
		built with DOCKER FILES - instructions for creating the image.
			Dockerfile ref: https://docs.docker.com/engine/reference/builder/


	|----docker-compose.yml---------------------------------------------|
	|	A docker-compose.yml is a config file for Docker Compose.		|
	|	It allows to deploy, combine, and configure multiple docker		|
	|		containers at the same time. The Docker "rule" is to		|
	|		outsource every single process to its own Docker container.	|
	|	The advantage of Docker Compose is easy configuration.			|
	|		You don't have to write a big bunch of commands into Bash,	|
	|		You can predefine it in the docker-compose.yml.				|
	|																	|
	|	Basically makefile for Docker containers						|
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
	TLS - Transport Layer Sec
• WordPress + php-fpm (it must be installed and configured) - without nginx.
• MariaDB  -  without nginx.
• A volume that contains your WordPress database.
• A second volume that contains your WordPress website files.
• A docker-network that establishes the connection between your containers.
Your containers have to restart in case of a crash.