# Offline-Voice-Recognition-Hub-Based-on-ESPNOW
A smart offline module which acts like a hub and send commands to different slave devices, Based on ESPNOW protocol ESP8266.

![Image](https://github.com/user-attachments/assets/20939e3d-b144-45aa-a2ab-fb8b1cd7ed29)

An offline voice recognition hub, no internet connection, no wifi router. Just a pair of ESP8266 with ESPNOW protocol running on them. This is what I want in my room. The devices can either be controlled by pressing switches or by voice. A central hub like alexa is there to respond to your commands. And this is the article which explains how things work. The idea comes to mind when I am operating my lab lights with an IR remote, this can be seen in one of the very previous articles I have made. Then to switch a little bit towards smart home keeping every data personal at my end, I made a plan to keep it offline. As I already have a voice recognition module lane around from DF, Gravity: Offline Language Learning Voice Recognition. 

https://wiki.dfrobot.com/SKU_SEN0539-EN_Gravity_Voice_Recognition_Module_I2C_UART

![Image](https://github.com/user-attachments/assets/da8a47d7-6ede-4992-a357-7ae23e3972c4)


I also made a getting started tutorial on this module which can be seen from here. It explains types of commands and pre- programming required for the sensor. Although the current article provides all the required information. I made a solid state relay PCB to use this with AC mains, Big thanks to PCBWay for sponsoring the PCBs for this project! Their high-quality manufacturing and quick turnaround made this build possible.

https://www.hackster.io/electroboy001/intelligent-offline-voice-recognition-module-is-here-07bed9

![Image](https://github.com/user-attachments/assets/871a50dc-f915-4bb5-9131-30b56a5c662d)


https://www.pcbway.com/?from=circuitkicker

Offline Voice recognition module:

![Image](https://github.com/user-attachments/assets/f9b9c83c-579a-4b93-bfc8-78e652721214)

This offline speech recognition sensor is built around an offline voice recognition chip, which can be directly used without an internet connection. It comes with 121 built-in fixed command words and supports the addition of 17 custom command words.
This small sensor can be interfaced with any microcontroller board and then different actions can be performed over voice. It will be the same as Alexa but with much more restricted commands and answers. Because overall it is a small ML model working on a little microcontroller. Some popular applications are such as various smart home appliances, toys, lighting fixtures, and robotics projects, among others.

Types of commands:

I will try to keep it as simple as possible, I will divide all the words in 3 sections as per action. See the block diagram given below.

1)Wake-Up words: The wake-up word refers to the word that switches a product from standby mode to operational mode. It is the first command which is given to wake the module. It is similar to saying “Alexa”, “Hey Siri”, “OK Google”. Same as that here the default wake up word is “Hello Robot” and it is the default one. We can also add one more wake work which is demonstrated below as “JARVIS”.

![Image](https://github.com/user-attachments/assets/5df71825-46d6-4c89-85cd-598a70c6f2eb)

2)Command words: Fixed command words refers to the designated vocabulary used by users to issue specific instructions. Here these words are essential because, after all, this is an offline module and does not have external data/server from the internet to process. So these are the already processed, trained words which are stored in the memory of the module and whenever triggered produce the corresponding ID, which can be used to specify the different actions later on. There are a total of 121 words which are already defined for specific functions over different ID’s.

![Image](https://github.com/user-attachments/assets/41145746-7ada-47dd-bc9f-2860f32c654c)

Now whenever working on a project it is not always good luck that these commands work for you. Means sometimes we need some other commands. Which is possible to do here, known as a custom command word. And there are a total of 17 Custom command words you can train the model on. See all commands from here.

3)Learning Related Commands (Control Commands): These are the command words which are used to interact with the Machine learning model. These are the Controlling commands which initiates the learning and deleting of Wake-up words and command words.

![Image](https://github.com/user-attachments/assets/0de1dd4f-08fa-4f07-b293-f160e104398e)


What is ESP NOW?

ESP-NOW is a wireless communication protocol based on the data-link layer, which reduces the five layers of the OSI model to only one. This way, the data need not be transmitted through the network layer, the transport layer, the session layer, the presentation layer, and the application layer. Also, there is no need for packet headers or unpackers on each layer, which leads to a quick response reducing the delay caused by packet loss in congested networks. More details about the protocol can be found on the official website. 

System Integration, Local and wireless host:

![Image](https://github.com/user-attachments/assets/f8ad55f1-d39e-442f-b63a-d384526b6256)

The idea is to first connect the local host to an offline voice recognition module and connect the wireless host over ESPNOW. In this way multiple GPIOs can be used to control different appliances. In this way multiple wireless hosts can be connected to the network and the central local voice recognition hub sends commands to each of them in order to switch ON/OFF. But that is the topic for another day.

Transmitter ESP:

![Image](https://github.com/user-attachments/assets/fe0b3578-da5d-43d5-9f44-4db30195241d)

In the code given in repo, the transmitter (local host) has two control units, defined as CAMERA and SPEAKER. And four control units LIGHT OSCILLOSCOPE SOLDER POWER for wireless (receiver) hosts. The circuit diagram explaining the connection can be used for the reference.

Receiver ESP:

![Image](https://github.com/user-attachments/assets/a166f52b-0007-4ca8-85c7-bb71c6d49915)

PCB for Relay Switching AC application:

![Image](https://github.com/user-attachments/assets/19879b3c-138c-428f-8c40-ecec3200360d)

I have designed a solid state relay to connect the receiver esp, in order to control the AC mains. This is a simple and minimal design and designed in a small form factor to be fit in any housing. The main advantage of solid state relay, it will not make such noises. Overall small and control the applications in a better way.

![Image](https://github.com/user-attachments/assets/f8dc405d-92cf-4a7c-8652-1519476781b7)

https://www.pcbway.com/?from=circuitkicker

Special thanks to PCBWay for sponsoring the PCBs. Their quality and service are unmatched in the industry! Sign-up now and get free coupons on your next order. All the required files Gerber, BOM and CPL are uplaoded on GITHUB repo. 

![Image](https://github.com/user-attachments/assets/f0c8e59a-2e31-4006-9d42-6fc6245529ea)


Working:

The ESPNOW is good protocol to use wireless, but using it with ESP8266 gives some difficulties, if not properly written in the program it ruins everything. I tested my units many times and was happy to see that they are in working condition every time.

![Image](https://github.com/user-attachments/assets/d75badad-42ea-4520-afe4-e96cd5ae3326)

See Youtube Video : https://youtu.be/V6rI0z5z9Yw

I have tested the voice commands and they are working perfectly, the video for the same is attached here for your reference. The ESPNOW is easy to use just plug and power both ESPs and it will automatically make a connection, see the code for wifi MAC settings. After a successful connection serial prints the same information to validate the connection.
