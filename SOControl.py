import pyautogui 
import time
import serial

ArduinoSerial = serial.Serial('COM3',9600)
while True:
    arduinoInput = ArduinoSerial.readline()
    strInput = str(arduinoInput.decode()).replace("\r","").replace("\n","") 
    if(strInput == "Next"):
        # print("Next")
        pyautogui.press('right')
    elif(strInput == "Back"):
        # print("Back")
        pyautogui.press('left')
    elif(strInput == "Play/Pause"):
        pyautogui.press('space')
    elif(strInput == "VUP"):
        pyautogui.hotkey("ctrl","up")
    elif(strInput == "VDN"):
        pyautogui.hotkey("ctrl","down")