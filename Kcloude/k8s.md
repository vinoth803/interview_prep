### Kubernetes Components

---

#### Pods 📦
A **Pod** is the smallest and most fundamental unit of work in Kubernetes. It is an abstraction that represents a running process on a cluster. A pod can contain one or more containers (like Docker containers), which share storage, networking, and a specification for how to run.
* **Ephemeral Nature:** Pods are not persistent. If a pod fails, Kubernetes restarts it, but it's a new pod with a new IP address.
* **Shared Context:** All containers within a single pod share the same network namespace and can communicate with each other via `localhost`.

---

#### Services 🌐
A **Service** is an abstraction that provides a stable, permanent IP address and DNS name for a set of pods. Services ensure that even if pods are restarted with new IPs, other pods and external clients can always find them.
* **Load Balancing:** Services automatically distribute network traffic to the pods they manage.
* **Discovery:** Pods can discover and communicate with each other using the service's stable IP and name, decoupling them from the ephemeral pod IPs.

---

#### Ingress 🚪
**Ingress** is an API object that manages external access to services within a cluster, typically HTTP and HTTPS traffic. It provides a way to route traffic to different services based on the incoming request's host or path, offering a unified entry point to the cluster.

---

#### ConfigMap & Secrets 🔑
* **ConfigMap:** Used to store non-confidential configuration data as key-value pairs. This allows you to decouple application configurations from the application code itself, making it easy to change settings without rebuilding the container image.
* **Secrets:** Similar to ConfigMaps, but specifically designed to store sensitive data like passwords, API keys, and certificates. Kubernetes secrets are base64-encoded to prevent accidental display but are not encrypted by default.

---

#### Volumes 💾
**Volumes** are directories that can be accessed by containers in a pod. They provide persistent storage that survives container restarts.
* **Purpose:** The data in a volume is independent of the container's lifecycle. If a container crashes, the data in the volume is preserved.
* **Types:** Volumes can be provisioned in various ways, such as local storage, network-attached storage, or cloud provider-specific storage.

---

#### Deployments 🚀
A **Deployment** is a higher-level abstraction that defines the desired state for a set of pods, including the number of replicas and the container image to use.
* **Stateless Applications:** Deployments are ideal for managing stateless applications, ensuring that a specified number of identical pods are always running.
* **Updates and Rollbacks:** Deployments manage rolling updates, allowing you to update an application with zero downtime. They also enable easy rollbacks to a previous version if an update fails.

---

#### StatefulSets 🐘
**StatefulSets** are a specialized type of controller used for managing stateful applications, like databases. Unlike deployments, StatefulSets provide:
* **Stable Network IDs:** Each pod is given a persistent and unique network identifier.
* **Ordered Deployment/Scaling:** Pods are created and scaled up or down in a predictable, ordered manner.
* **Persistent Storage:** StatefulSets use PersistentVolumes to ensure that each pod's data is associated with its identity.

---

### Kubernetes Architecture

Kubernetes operates in a client-server model with a **Master Node** and several **Worker Nodes**. 

#### Master Node 🧠
The master node is the brain of the cluster, responsible for managing the state and control of all nodes and pods.
* **API Server:** The central component that exposes the Kubernetes API. It is the entry point for all administrative tasks and handles all communication between cluster components.
* **Scheduler:** Responsible for scheduling newly created pods onto a specific worker node based on resource requirements and constraints.
* **Controller Manager:** A set of controllers that regulate the state of the cluster. For example, if a pod dies, the Replication Controller notices this and asks the Scheduler to create a new pod to maintain the desired replica count.
* **Etcd:** A distributed key-value store that serves as the cluster's "single source of truth." It stores the entire cluster configuration, state, and metadata.

#### Worker Nodes 👷
Worker nodes are the machines that run the actual application containers.
* **Kubelet:** An agent that runs on each worker node. It communicates with the master node and ensures that containers are running in a pod as intended.
* **Kube-Proxy:** A network proxy that runs on each node. It manages network rules to enable communication between pods and from outside the cluster to pods.
* **Container Runtime:** The software responsible for running containers. Docker used to be the default, but now other runtimes like containerd or CRI-O are common.

---

### Kubectl Commands

**`kubectl`** is the command-line tool for interacting with a Kubernetes cluster.

#### Info Commands 📖
* `kubectl get nodes`: List all the nodes in the cluster.
* `kubectl get pods`: List all pods in the current namespace.
* `kubectl get services`: List all services.
* `kubectl get deployments`: List all deployments.
* `kubectl get pods -o wide`: Displays more information, including the node each pod is running on.
* `kubectl get deployment <deploy-name> -o yaml > new_file`: Retrieves the YAML configuration of a deployment and saves it to a file.

#### Create/Edit Commands ✏️
* `kubectl create deployment <NAME> --image=<image-name>`: Creates a new deployment.
* `kubectl apply -f <pod.yaml>`: Applies a configuration file (like a pod manifest) to the cluster.
* `kubectl edit deployment <name-of-deployment>`: Opens the live configuration of a deployment for editing.

#### Debug Commands 🐞
* `kubectl logs <pod-name>`: Displays the logs of a pod's container.
* `kubectl describe <pod-name>`: Shows detailed information about a pod, including its status, events, and container details.

#### Interactive Commands 💻
* `kubectl exec -it <pod-name> -- /bin/bash`: Executes a shell command inside a running container, allowing you to debug it interactively.

---

### Kubernetes Configuration Files 📝
Kubernetes configuration files (often in YAML format) have three main parts:
1.  **Metadata:** Data about the object, such as its name, labels, and annotations.
2.  **Specification (`spec`):** The desired state for the object, such as the container image to use, the number of replicas, or port mappings.
3.  **Status:** The current state of the object, which is managed and updated by Kubernetes itself. This field is not set by the user.

Pods are connected to services using **labels** and **selectors** defined in the specification. A service's selector matches the labels on a set of pods, automatically routing traffic to them.