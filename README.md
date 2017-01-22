# CSGO-Extern
<strong>"dynamic" shell-code injection &amp; extrn stuff.</strong>

<strong>Features:</strong> <br />
-> Calling *any* naked function in an another process space <br />
-> obv. the targeted process needs to know the used functions <br />
 
<strong>Example ( in Main.cpp ):</strong> <br />
-> Loading CSGO-Interfaces <br />
-> Calling VMT-Methode 'gEngineClient->IsConnected()' and if connected > saying 'CSGO-Extern doing it' <br />
