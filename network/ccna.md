### Introduction
network is digital telecommunciations which enables the nodes to share the resources.
 **router** - provide connectivity between 2 lans over internet (isr 1000, isr 900, )
 **switch** - provide connectivity to host within the lan
 **server** - device that provides functions or services to a client
 **client** - device that access the service that made available by the server
**firewall** - monitor and control network traffic based on configured rules

### Network Devices
**hub** --  Layer1 -- 1 collision domain -- half duplex 
**bridge** -- Layer2 -- Segments Lans -- 2 Collision domain -- Fewer ports
**switch** -- Layer2 -- has mac table -- Full duplex -- multiple collision domain
**router** -- layer3 -- has ip table
-- full duplex -- fewer ports

# OSI Model Layers and Associated Technologies

| Layer         | Protocols/Technologies           | Devices/Functions                  |
|---------------|----------------------------------|------------------------------------|
| Application   | HTTP, HTTPS, SNMP                | User-facing applications           |
| Presentation  | SSL/TLS, Encryption, Compression | Data formatting, encryption        |
| Session       | NetBIOS, RPC                     | Session management                 |
| Transport     | TCP, UDP                         | End-to-end communication           |
| Network       | IPv4, IPv6, ICMP                 | Routers                            |
| Data Link     | MAC, ARP, Ethernet               | Switches, NICs                     |
| Physical      | Copper wire, Optical cable       | Hubs, Repeaters, Cables            |
# TCP/IP 4-Layer Model Overview

| Layer      | Protocols/Technologies     | Devices/Functions         |
|------------|----------------------------|----------------------------|
| Application| HTTP, HTTPS, SNMP, FTP     | Browsers, Email clients    |
| Transport  | TCP, UDP                   | OS-level transport         |
| Internet   | IPv4, IPv6, ICMP           | Routers                    |
| Link       | MAC, ARP, Ethernet         | Switches, NICs             |

# PDUs (Protocol Data unit)
Application Data
   ↓
TCP Segment
   ↓
IP Packet
   ↓
Ethernet Frame

# TCP vs UDP

TCP - connection oriented , reliable. good for trusted transcations 
Uses - ACK, SEQ number, CHECKSUM

Estiables connection
PC1 ----SYN-----> PC2
PC1 <--SYNC-ACK-- PC2
Pc1 ---ACK------> PC2


### TCP Segment Header (32-bit Layout)

| 0 - 15              | 16 - 31             |
|---------------------|---------------------|
| Source Port         | Destination Port    |
| Sequence Number (32 bits)                |
| Acknowledgment Number (32 bits)          |
| Data Offset (4) + Reserved (3) + Flags (9) | Window Size        |
| Checksum            | Urgent Pointer      |
| Options (if any, variable length)        |
| Padding (if needed to align to 32-bit)   |
| Data (Payload, variable length)          |


UDP - connectionless, unreliable, audio, video streaming. 

### UDP Header (32-bit Layout)

| 0 - 15              | 16 - 31             |
|---------------------|---------------------|
| Source Port         | Destination Port    |
| Length              | Checksum            |
| Data (Payload, variable length)           |

### Port Number Categories

| Category        | Port Range       | Purpose / Usage                                      | Examples                          |
|----------------|------------------|------------------------------------------------------|-----------------------------------|
| Well-known      | 0 – 1023         | Reserved for core services and protocols             | HTTP (80), HTTPS (443), FTP (21), DNS (53), SSH (22) |
| Registered      | 1024 – 49151     | Used by user applications and services               | MySQL (3306), PostgreSQL (5432), RDP (3389), VNC (5900) |
| Ephemeral       | 49152 – 65535    | Temporary ports assigned to clients for connections  | Browser using port 51523 to connect to HTTPS (443) |

#### 🌐 Most Commonly Used Well-Known Ports (0–1023)

| Port | Protocol | Description                                      |
|------|----------|--------------------------------------------------|
| 20   | FTP Data | File Transfer Protocol (data channel)            |
| 21   | FTP      | File Transfer Protocol (control channel)         |
| 22   | SSH      | Secure Shell for encrypted remote login          |
| 23   | Telnet   | Unencrypted remote login (legacy protocol)       |
| 25   | SMTP     | Simple Mail Transfer Protocol (email sending)    |
| 53   | DNS      | Domain Name System (name resolution)             |
| 67   | DHCP     | Dynamic Host Configuration Protocol (server)     |
| 68   | DHCP     | DHCP (client)                                    |
| 69   | TFTP     | Trivial File Transfer Protocol                   |
| 80   | HTTP     | Hypertext Transfer Protocol (web browsing)       |
| 110  | POP3     | Post Office Protocol v3 (email retrieval)        |
| 119  | NNTP     | Network News Transfer Protocol                   |
| 123  | NTP      | Network Time Protocol (clock synchronization)    |
| 143  | IMAP     | Internet Message Access Protocol (email access)  |
| 161  | SNMP     | Simple Network Management Protocol               |
| 443  | HTTPS    | Secure HTTP (encrypted web browsing)             |
| 445  | SMB      | Server Message Block (Windows file sharing)      |
| 993  | IMAPS    | Secure IMAP (encrypted email access)             |
| 995  | POP3S    | Secure POP3 (encrypted email retrieval)          |

# IP Addrees
Unique identifier to identidy a network device in a network

### IPV4 vs IPV6
IPV4 -- 32 bits (192.168.10.1)
        needs subnet mask (255.255.255.0)
        whenever there is a '255'it is the network part of it.
        host part of the ip address.

# 🌐 IPv4 Address Classes

IP addresses are divided into five classes: **A, B, C, D, and E**, based on their leading bits and intended usage.

## 📊 IPV4 Classes Overview

| Class | Range (First Octet) | Default Subnet Mask     | Number of Hosts per Network | Usage                          |
|-------|----------------------|--------------------------|------------------------------|--------------------------------|
| A     | 1 – 126              | 255.0.0.0                | ~16 million                  | Large networks (e.g., ISPs)    |
| B     | 128 – 191            | 255.255.0.0              | ~65,000                      | Medium-sized networks          |
| C     | 192 – 223            | 255.255.255.0            | 254                          | Small networks (e.g., LANs)    |
| D     | 224 – 239            | N/A                      | N/A                          | Multicast groups               |
| E     | 240 – 255            | N/A                      | N/A                          | Reserved for experimental use  |

> Note: 127.x.x.x is reserved for loopback (localhost), so it's not used for Class A networks.

## 🧠 Key Concepts

- **Class A**: Supports a few networks with many hosts.
- **Class B**: Balances number of networks and hosts.
- **Class C**: Supports many networks with few hosts.
- **Class D**: Used for multicast (e.g., streaming).
- **Class E**: Reserved for future or experimental purposes.

## 🔒 Private IP Ranges

| Class | Private IP Range            |
|-------|-----------------------------|
| A     | 10.0.0.0 – 10.255.255.255   |
| B     | 172.16.0.0 – 172.31.255.255 |
| C     | 192.168.0.0 – 192.168.255.255 |

These private IPs are used within internal networks and are **not routable on the public internet**.

192.168.130.0/24 means all the 3 octets are for network
192.168.130.0 (network address)
192.168.130.255 (broadcast address)
so the range of the host in this example is 256-2=254 hosts

## IPV6

it is 128 bits it is hextets. It is hexadecimal
it is 64bits - network 

2001:0dab:0000:0000:a111:b222:c333:d444
2001:0dab::a111:b222:c333:d444

"::" means all zeros inbetween


# 🌐 IPv6 Addressing Overview

IPv6 (Internet Protocol version 6) is the successor to IPv4, designed to solve the problem of IP address exhaustion and improve routing efficiency, security, and scalability.

## 📊 IPv6 vs IPv4

| Feature              | IPv4                          | IPv6                                 |
|----------------------|-------------------------------|--------------------------------------|
| Address Length       | 32 bits                       | 128 bits                             |
| Address Format       | Decimal (e.g., 192.168.1.1)   | Hexadecimal (e.g., 2001:0db8::1)     |
| Total Addresses      | ~4.3 billion                  | ~340 undecillion (2¹²⁸)              |
| Header Complexity    | Complex                       | Simplified                           |
| NAT Required         | Yes                           | No (end-to-end connectivity)         |
| Built-in Security    | Optional                      | Mandatory (IPSec)                    |
| Broadcast Support    | Yes                           | No (uses multicast instead)          |

## 🧩 IPv6 Address Structure

An IPv6 address is written as **eight groups of four hexadecimal digits**, separated by colons:

2001:0db8:85a3:0000:0000:8a2e:0370:7334


### 🔧 Compression Rules:
- Leading zeros in each group can be omitted.
- Consecutive groups of zeros can be replaced with `::` (only once per address).

Example compressed:

2001:db8:85a3::8a2e:370:7334


## 🏷️ IPv6 Address Types

| Type            | Prefix         | Purpose                                  |
|-----------------|----------------|------------------------------------------|
| Unicast         | Various        | One-to-one communication                 |
| Multicast       | ff00::/8       | One-to-many communication                |
| Anycast         | Shared         | One-to-nearest (based on routing)        |
| Link-local      | fe80::/10      | Local network segment communication      |
| Unique-local    | fc00::/7       | Private addressing (similar to IPv4 private ranges) |
| Global Unicast  | 2000::/3       | Publicly routable addresses              |

## 🔒 IPv6 Highlights

- **No need for NAT**: Every device can have a globally unique address.
- **Built-in IPSec**: Security is integrated from the ground up.
- **Efficient routing**: Aggregated prefixes simplify routing tables.
- **Auto-configuration**: Devices can configure themselves using SLAAC (Stateless Address Auto Configuration).

# 🧠 Media Access Control (MAC) – Networking Essentials

Media Access Control (MAC) is a sublayer of the **Data Link Layer (Layer 2)** in the OSI model. It governs how devices access and transmit data over a shared communication medium, ensuring orderly and efficient communication.

---

## 📦 MAC Sublayer Responsibilities

- **Addressing**: Assigns unique MAC addresses to devices for identification.
- **Frame Delimiting**: Encapsulates data into frames for transmission.
- **Channel Access**: Controls when devices can transmit to avoid collisions.
- **Error Detection**: Adds checksums (Frame Check Sequence) to detect errors.
- **Collision Handling**: Uses protocols to manage or avoid data collisions.

---

## 🔗 MAC Address Format

A **MAC address** is a 48-bit identifier, typically shown as:
00:1A:2B:3C:4D:5E

- **First 24 bits**: Organizationally Unique Identifier (OUI) – identifies the manufacturer.
- **Last 24 bits**: Device-specific identifier – unique to each network interface.

MAC addresses are **burned into hardware** but can be spoofed or changed in software.

---

## 📡 MAC Protocols

| Protocol        | Used In         | Description |
|----------------|------------------|-------------|
| **CSMA/CD**     | Ethernet (wired) | Listens before transmitting; detects collisions and retries |
| **CSMA/CA**     | Wi-Fi (wireless) | Avoids collisions by waiting and acknowledging |
| **Token Passing** | Token Ring, FDDI | Devices transmit only when holding a token |
| **Polling**     | Master-slave setups | Central controller decides who transmits |

---

## 🛡️ MAC vs LLC

The Data Link Layer is split into two sublayers:

| Sublayer | Function |
|----------|----------|
| **MAC**  | Controls access to the physical medium |
| **LLC**  | Provides interface to the Network Layer and handles error checking |

---

## 🧭 Why MAC Matters

- Enables **device-level communication** on local networks
- Prevents **data collisions** and ensures fair access
- Supports **efficient transmission** in both wired and wireless environments
- Forms the foundation for **network security** features like MAC filtering

---

## 🔒 MAC Filtering (Security Feature)

MAC filtering is a method used in routers and switches to allow or deny network access based on MAC addresses.

- **Whitelist**: Only approved MAC addresses can connect
- **Blacklist**: Specific MAC addresses are blocked

Note: MAC filtering is **not foolproof** — MAC addresses can be spoofed.

---

 

