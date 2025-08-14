Here is a comprehensive guide to Docker, formatted in Markdown. It covers the core concepts and commands you've outlined, with added details and explanations to provide a solid foundation for your learning.

---

### Why Do We Need Docker?

Docker is a tool that packages an application and its dependencies into a single, isolated unit called a **container**. This solves the "it works on my machine" problem and streamlines the development workflow. 

The primary benefits are:
* **Portability:** A container runs the same way on any machine, from a developer's laptop to a production server, because it includes all necessary libraries and dependencies.
* **Consistency:** It ensures that every member of a team and every environment (development, testing, production) uses the exact same setup, which drastically reduces configuration time and errors.
* **Isolation:** Containers are lightweight, isolated environments that don't interfere with each other or the host system. This allows you to run multiple applications on the same server without conflicts.

---

### Docker Main Components

Understanding these components is key to grasping how Docker works:

* **Docker Image:** A read-only template that contains the application code, a runtime, libraries, and any other files needed to run the application. Images are the blueprint for containers.
* **Docker Container:** A running instance of a Docker image. It's an isolated, virtual environment where your application executes. Containers have their own virtual file system, and you can interact with them.
* **Docker Daemon (Engine):** The background service that manages Docker objects like images, containers, networks, and volumes.
* **Docker Registry (e.g., Docker Hub):** A repository for storing and sharing Docker images. Docker Hub is the default public registry, but you can also use private registries.

---

### Docker Commands

Here are some of the most common Docker commands, with explanations.

| Command                                      | Description                                                                                                                              |
| -------------------------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------- |
| `docker pull <image-name>`                   | Downloads a Docker image from a registry (like Docker Hub) to your local machine.                                                        |
| `docker images`                              | Lists all the Docker images stored in your local repository.                                                                             |
| `docker run <image-name>`                    | Creates a new container from a specified image and starts it.                                                                            |
| `docker ps`                                  | Lists all currently running containers.                                                                                                  |
| `docker ps -a`                               | Lists all containers, including those that have stopped.                                                                                 |
| `docker stop <container-id>`                 | Gracefully stops a running container.                                                                                                    |
| `docker start <container-id>`                | Starts a stopped container.                                                                                                              |
| `docker rm <container-id>`                   | Removes a stopped container. You must stop a container before you can remove it.                                                         |
| `docker rmi <image-id>`                      | Removes an image from your local machine. You must remove all containers based on an image before you can delete the image.                |
| `docker run -d <image-name>`                 | Runs a container in **detached mode**, meaning it runs in the background.                                                                |
| `docker run <image:4.0>`                     | Pulls and runs a container using a specific version (tag) of an image.                                                                   |
| `docker run -p 6000:6379`                    | **Port Mapping:** Maps port `6000` on the host machine to port `6379` inside the container, allowing external access to the application.   |
| `docker run --name "container_name"`         | Assigns a specific name to a container instead of a random hash.                                                                         |
| `docker logs <container-id>`                 | Fetches and displays the logs from a container, which is essential for debugging.                                                        |
| `docker exec -it <container-id> /bin/bash`   | Executes a command inside a running container. This is a common way to get a shell inside a container for debugging or inspection. `-i` keeps `STDIN` open, and `-t` allocates a pseudo-terminal. |

---

### Docker Networking

Containers need to communicate with each other and the outside world. Docker handles this through various network drivers.

* `docker network create <network-name>`: Creates a custom bridge network, which is the recommended way to enable communication between a group of containers. Containers on the same custom network can talk to each other using their container names as hostnames.
* **Default Network:** By default, containers are connected to the `bridge` network, but they can only communicate with each other via IP addresses, not container names.

---

### Docker Volumes

Containers are ephemeral; any data written to the container's writable layer is lost when the container is deleted. **Docker Volumes** are a way to persist data and share it with containers.

* **Host Volume (Bind Mount):**
    * `docker run -v <host-dir-path>:<container-dir-path> <image-name>`
    * Mounts a directory from the host machine directly into the container. This is useful for development, as changes on the host are instantly reflected in the container.
* **Named Volumes:**
    * `docker run -v my_volume:/app/data <image-name>`
    * Docker manages the physical location of the volume on the host. You reference it by a name (e.g., `my_volume`). This is the preferred method for production data persistence.
* **Anonymous Volumes:**
    * `docker run -v /app/data <image-name>`
    * Docker creates a new volume with a random hash name and manages it. It's similar to a named volume but harder to reference.

---

### Docker Compose

Docker Compose is a tool for defining and running multi-container Docker applications. It uses a **YAML file (`docker-compose.yml`)** to configure all the application's services.

* `docker-compose -f <yaml-file> up`: Reads the YAML file, builds images (if necessary), and creates and starts all the services in a single command. It also automatically creates a network for all the services to communicate.
* `docker-compose -f <yaml-file> down`: Stops and removes the containers, networks, and volumes created by `up`.

---

### Dockerfile

A **Dockerfile** is a text file that contains a series of instructions on how to build a Docker image. It's the standard way to create your own images.

* `docker build -t my-app:1.0 .`: Builds an image from the `Dockerfile` in the current directory (`.`). The `-t` flag tags the image with a name (`my-app`) and version (`1.0`).

---

### Pushing Images to a Registry

To share your custom images with others or deploy them, you need to push them to a registry like Docker Hub.

* `docker tag my-app:1.0 <repository-domain>/<username>/my-app:1.0`: This command **tags** your local image with a new name that includes the registry domain and your username, which is required before pushing.
* `docker push <repository-domain>/<username>/my-app:1.0`: Uploads the tagged image to the specified registry.

---

### Creating an Image from a Container

You can create a new image from a modified container using the `docker commit` command.

* `docker commit <container-id> my-app:2.0`: This command takes a running container and saves its current state (including any changes you made to it) as a new image with the tag `my-app:2.0`. This is generally discouraged for production use in favor of using a Dockerfile.