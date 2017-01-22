# CSGO-Extern
"dynamic" shell-code injection &amp; extrn stuff.

Features:
-> Calling *any* naked function in an another process space
 -> obv. the targeted process needs to know the used functions
 
Example ( in Main.cpp ):

-> Loading CSGO-Interfaces
-> Calling VMT-Methode 'gEngineClient->IsConnected()'
