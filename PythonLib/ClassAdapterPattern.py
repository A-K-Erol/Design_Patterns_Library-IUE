import abc
# =============================================================================
# Name: ClassAdapterPattern.py
#
# The classes and/or objects participating in this pattern are:
# 1. Target (NASocket): Defines the domain specific interface Client uses
# 2. Adapter (ConnectorAdapterNAtoEUR) Adapts Adaptee to Target
# 3. Adaptee (EURSocket) Defines an existing interface that needs adapting
# 4. Client (VCR) Collaborates with objects conforming to the Target interface
# Using class, not object adapter
# =============================================================================

# This is the "Target" class, North American Socket. Our
# device is manufactured for use with a North American Socket.


class NASocket:
    @abc.abstractmethod
    def using_na_socket(self):
        pass


# This is the "Adaptee" class. Continental Europe Socket.
# The device will be used in Europe which has different sockets.

class EURSocket:
    def using_eur_socket(self):
        print("Giving you 220 Volt using Europe Connection")
        return 220


# This is the "Adapter" class, ConnectorAdapterNAtoEUR.
# We need a connector so our device works

class ConnectorAdapterNAtoEUR(EURSocket, NASocket):
    def using_na_socket(self):
        # Possibly do some other work and then call
        # using_eur_socket from the European socket
        voltage = self.using_eur_socket()
        return voltage


# Utility Class
class VCR:
    def power_up(self, voltage):
        print("Powered up")


# Client
def adapter_pattern_class():
    # Create the adapter.
    socket = ConnectorAdapterNAtoEUR()
    # socket is-a NA socket, so our NA
    # device can connect
    voltage = socket.using_na_socket()
    vcr = VCR()
    vcr.power_up(voltage)


if __name__ == "__main__":
    adapter_pattern_class()
