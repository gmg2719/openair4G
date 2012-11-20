
import socket
import array
import pickle
from bzrlib.merge import ConfigurableFileMerger
from copy_reg import pickle

class Packet:
	@staticmethod
	def sendConfigurationRequest(serverAddress, serverPort, clientPort):
		# Build the packet
		configurationRequestPacket = array.array('B')
		configurationRequestPacket.append(0x40) # Validity=1, version=0
		configurationRequestPacket.append(0x00) # Priority=0
		configurationRequestPacket.append(0x03) # EventType=3
		configurationRequestPacket.append(0x01) # EventSubtype=1
		configurationRequestPacket.append(0xff) # ConfigurationId=0xFFFF (all)
		configurationRequestPacket.append(0xff)
		configurationRequestPacket.append(0x00) # TransmissionMode=0x0001 (bulk)
		configurationRequestPacket.append(0x01)

		# Create the socket to send to MGMT
		managementSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
		managementSocket.bind(('0.0.0.0', clientPort))
		sentByteCount = managementSocket.sendto(configurationRequestPacket, (serverAddress, serverPort))
		print sentByteCount, "bytes sent"

		receivedBytes, sourceAddress = managementSocket.recvfrom(1024)
		print receivedBytes.encode('hex'), "bytes received from", sourceAddress

		return True

	@staticmethod
	def sendCommunicationProfileRequest(serverAddress, serverPort, clientPort):
		# Build the packet
		communicationProfileRequestPacket = array.array('B')
		communicationProfileRequestPacket.append(0x40) # Validity=1, version=0
		communicationProfileRequestPacket.append(0x00) # Priority=0
		communicationProfileRequestPacket.append(0x03) # EventType=3
		communicationProfileRequestPacket.append(0x04) # EventSubtype=4
		communicationProfileRequestPacket.append(0xc0) # Transport
		communicationProfileRequestPacket.append(0xc0) # Network
		communicationProfileRequestPacket.append(0x80) # Access
		communicationProfileRequestPacket.append(0xF8) # Channel

		# Create the socket to send to MGMT
		managementSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
		managementSocket.bind(('0.0.0.0', clientPort))
		sentByteCount = managementSocket.sendto(communicationProfileRequestPacket, (serverAddress, serverPort))
		print sentByteCount, "bytes sent"

		receivedBytes, sourceAddress = managementSocket.recvfrom(1024)
		print receivedBytes.encode('hex'), "bytes received from", sourceAddress

		return True

	@staticmethod
	def sendNetworkState(serverAddress, serverPort, clientPort):
		# Build the packet
		networkStatePacket = array.array('B')
		networkStatePacket.append(0x40) # Validity=1, version=0
		networkStatePacket.append(0x00) # Priority=0
		networkStatePacket.append(0x03) # EventType=3
		networkStatePacket.append(0x01) # EventSubtype=1
		networkStatePacket.append(0x00) # RxPackets
		networkStatePacket.append(0x0D)
		networkStatePacket.append(0x00)
		networkStatePacket.append(0xF0)
		networkStatePacket.append(0x00) # RxBytes
		networkStatePacket.append(0xA1)
		networkStatePacket.append(0x12)
		networkStatePacket.append(0x02)
		networkStatePacket.append(0xDD) # TxPackets
		networkStatePacket.append(0x10)
		networkStatePacket.append(0x0A)
		networkStatePacket.append(0x56)
		networkStatePacket.append(0x10) # TxBytes
		networkStatePacket.append(0x22)
		networkStatePacket.append(0xBB)
		networkStatePacket.append(0x89)
		networkStatePacket.append(0x00) # ToUpperLayerPackets
		networkStatePacket.append(0x00)
		networkStatePacket.append(0x00)
		networkStatePacket.append(0x20)
		networkStatePacket.append(0x00) # DiscardedPackets
		networkStatePacket.append(0x00)
		networkStatePacket.append(0x00)
		networkStatePacket.append(0x0A)
		networkStatePacket.append(0x00) # DuplicatePackets
		networkStatePacket.append(0x00)
		networkStatePacket.append(0x00)
		networkStatePacket.append(0x0C)
		networkStatePacket.append(0x00) # ForwardedPackets
		networkStatePacket.append(0x01)
		networkStatePacket.append(0x30)
		networkStatePacket.append(0x00)

		# Create the socket to send to MGMT
		managementSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
		managementSocket.bind(('0.0.0.0', clientPort))
		sentByteCount = managementSocket.sendto(networkStatePacket, (serverAddress, serverPort))
		print sentByteCount, "bytes sent"

		return True

	@staticmethod
	def sendLocationUpdate(serverAddress, serverPort, clientPort):
		# Build the packet
		locationUpdatePacket = array.array('B')
		locationUpdatePacket.append(0x40) # Validity=1, version=0
		locationUpdatePacket.append(0x00) # Priority=0
		locationUpdatePacket.append(0x01) # EventType=1
		locationUpdatePacket.append(0x10) # EventSubtype=10
		locationUpdatePacket.append(0x01) # Timestamp (4-byte)
		locationUpdatePacket.append(0x02)
		locationUpdatePacket.append(0x03)
		locationUpdatePacket.append(0x04)
		locationUpdatePacket.append(0x01) # Latitude (4-byte)
		locationUpdatePacket.append(0x02)
		locationUpdatePacket.append(0x03)
		locationUpdatePacket.append(0x04)
		locationUpdatePacket.append(0x01) # Longitude (4-byte)
		locationUpdatePacket.append(0x02)
		locationUpdatePacket.append(0x03)
		locationUpdatePacket.append(0x04)
		locationUpdatePacket.append(0x01) # Speed (2-byte)
		locationUpdatePacket.append(0x02)
		locationUpdatePacket.append(0x01) # Heading (2-byte)
		locationUpdatePacket.append(0x02)
		locationUpdatePacket.append(0x01) # Altitude (2-byte)
		locationUpdatePacket.append(0x02)
		locationUpdatePacket.append(0x01) # TAcc, and PodAcc (1-byte)
		locationUpdatePacket.append(0x01) # SAcc, Hacc, and AltAcc (1-byte) 

		# Create the socket to send to MGMT
		managementSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
		managementSocket.bind(('0.0.0.0', clientPort))
		sentByteCount = managementSocket.sendto(locationUpdatePacket, (serverAddress, serverPort))
		print sentByteCount, "bytes sent"

		return True

	@staticmethod
	def sendConfigurationNotification(serverAddress, serverPort, clientPort):
		# Build the packet
		configurationNotificationPacket = array.array('B')
		configurationNotificationPacket.append(0x40) # Validity=1, version=0
		configurationNotificationPacket.append(0x00) # Priority=0
		configurationNotificationPacket.append(0x03) # EventType=3
		configurationNotificationPacket.append(0x14) # EventSubtype=14
		configurationNotificationPacket.append(0x0B) # Configuration ID (2-byte)
		configurationNotificationPacket.append(0xCC)   # Configuration ID = LDM Garbage Collection Interval
		configurationNotificationPacket.append(0x00) # Length (2-byte)
		configurationNotificationPacket.append(0x04)   # Length = 4-byte
		configurationNotificationPacket.append(0x00) # Configuration Value (variable-size)
		configurationNotificationPacket.append(0x00)   # configuration Value = 100 (ms)
		configurationNotificationPacket.append(0x00)
		configurationNotificationPacket.append(0x64)

		# Create the socket to send to MGMT
		managementSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
		managementSocket.bind(('0.0.0.0', clientPort))
		sentByteCount = managementSocket.sendto(configurationNotificationPacket, (serverAddress, serverPort))
		print sentByteCount, "bytes sent"

		return True

	@staticmethod
	def testConfigurationResponse(address):
		# Create the socket to receive from MGMT
		managementSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
#		managementSocket.bind(address)

		receivedBytes = managementSocket.recvfrom(1024)
		print receivedBytes, "bytes received"

		return True
