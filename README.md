CSGO.CLI
========

This repo is still under development. If you have any questions or feature request don't hesitate to get in touch with me.

WTF is this?
------------

Well, it's a CLI for CSGO.

The library ( \lib )
--------------------

Used as a folder for stuff that can and should be reused. Current features:

* Remote
	* Dto
		* Layouting a dto
		* Reading in one call from attached process
		* Subleveling
	* Function
		* Parsing a function in our process space
		* Copy a parsed function into the attached process
		* Executing the copied function
		* Getting the result of the executed function
	* Hook
		* Virtual Methods Table
			* Parsing the functions of a VirtualMethodsTable
			* Replacing the instance of the VirtualMethodsTable
			* Hooking individual VirtualMethods of the parsed functions
			* Calling a callback in our own process -> can modify params, return value...
		* ... in development
	* Process
		* Attaching to an external process via window or processname
		* Sharing handles between the attached process
		* Basic read / write
		* Allocating Data/Deallocating Data
		* Creating RemoteThreads
		* Thread resuming / suspending
		* Iterating modules

The source ( \src )
----------------

Divide into two subsections [CLI, CSGO]. Current features:

* CLI
	* Hooks
		* Client::CreateMove Virtual Method Table Hook -> Calling a callback in our own process
* CSGO
	* ClientClass
		* ClientClassService
			* GetRecvPropOffset by table with property name
	* Interfaces
		* Client
		* EngineClient
			* IsConnected
			* ClientCmdUnrestricted
