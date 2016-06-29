Selitcoin (SELIT)
=====================


 





Compile Linux 
 
 Selitcoin Daemon and QT Client

This tutorial is based on Debian based Linux distributions like Ubuntu.

Retrieve Dependency Packages

*	$ sudo apt-get update
*	$ sudo apt-get install git build-essential libssl-dev 
libboost-thread-dev libboost-filesystem-dev 
libboost-program-options-dev libdb++-dev libminiupnpc-dev 
libqrencode-dev qt4-qmake libqt4-dev




Clone the Selitcoin Github Repository

*	$ git clone https://github.com/proffilit/selitcoin.git



Note: If you run into an public key error while attempting to clone the 
repository, follow these steps to set up a valid RSA keypair. If you use Github, 
you can then add that pair to your account, for easier access in the future.
Compile the Selitcoin daemon (selitcoind)

*	$ cd ~/selitcoin/src
*	$ make -f makefile.unix

# daemon will be compiled, and can be started from the command line
Compile the Selitcoin Wallet Client

*	$ cd ~/selitcoin
*	$ qmake
*	$ make 

#qt wallet will be compiled, and can be run by double clicking selitcoin 
executable
Create Selitcoin configuration file (selitcoin.conf)

In any text editor (vi, vim, nano, etc.) open the file and insert the following 
content:


*	server=1
*	testnet=1
*	rpcuser=selitcoinrpc
*	rpcpassword=HNimrbN6ySQLqrFxzZWC8SNn7CGbZi4uVv
*	rpcport=55883
*	port=55884


Save the changes to the file.


Scrypt Hashcash PoW Template




 
 ============================
*	   Copyright (c) 2016 Selitcoin Developers
