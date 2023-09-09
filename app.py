import bluetooth
import time
import threading
import socket
import tkinter as tk
from tkinter import messagebox

connected=0;
# Create a BluetoothSocket object to use for scanning
s = socket.socket(socket.AF_BLUETOOTH, socket.SOCK_STREAM, socket.BTPROTO_RFCOMM)
# Search for nearby Bluetooth devices
devices = bluetooth.discover_devices()
address="none"
# Print the name and address of each device
for addr in devices:
    name = bluetooth.lookup_name(addr)
    if name == "HC-05":
       address=addr
       print(address)
    print(f"Found device: {name} ({addr})")
class MyForm(tk.Frame):
    def __init__(self, master=None):
        super().__init__(master)
        self.master = master
        self.grid()
        self.create_widgets()
        self.master.geometry("500x500")
        icon_path = 'D:\Omar\\tkinter\icon.ico' #edit the path yourself
        root.iconbitmap(icon_path)
        self.master.title("IMT_GRAD")
        self.master.resizable(False, False)  # Make the form size fixed
       
    def create_custom_label(self):
        label_text = "Custom Label"
        label_font = ("Arial", 12, "bold")
        label_fg = "white"
        label_bg = None
        custom_label = tk.Label(self, text=label_text, font=label_font, fg=label_fg, bg=label_bg)
        custom_label.place(relx=0.15, rely=0.5, anchor=tk.W)
    
    def create_widgets(self):
        global spinbox
        global spinboy
        connect_button = tk.Button(text="Connect", font=("Arial", 24, "bold"),bg="white",command=self.connect_click)
        connect_button.place(relx=0.5, rely=0.0, anchor='n')
        labelx = tk.Label(root, text="Square:", font=("Arial", 10,"bold"), padx=10, pady=10)
        labelx.place(relx=0.4, rely=0.15, anchor='n')
        spinbox = tk.Spinbox(root, from_=0, to=8, font=("Arial", 12), width=5)
        spinbox.place(relx=0.53, rely=0.165, anchor='n')
        ack = tk.Button(text="Send Ack", font=("Arial", 15, "bold"), bg="white",command=self.ack_click)
        ack.place(relx=0.3, rely=0.25, anchor='n')
        xb = tk.Button(text="Send Square", font=("Arial", 15, "bold"), bg="white",command=self.x_click)
        xb.place(relx=0.6, rely=0.25, anchor='n')
        up = tk.Button(text="F", font=("Arial", 18, "bold"), bg="white",command=self.up_click)
        up.place(relx=0.5, rely=0.45, anchor='n')
        d = tk.Button(text="B", font=("Arial", 18, "bold"), bg="white",command=self.down_click)
        d.place(relx=0.5, rely=0.75, anchor='n')
        s = tk.Button(text="S", font=("Arial", 18, "bold"), bg="white",command=self.stop_click)
        s.place(relx=0.5, rely=0.6, anchor='n')
        r = tk.Button(text="R", font=("Arial", 18, "bold"), bg="white",command=self.right_click)
        r.place(relx=0.6, rely=0.6, anchor='n')
        l = tk.Button(text="L", font=("Arial", 18, "bold"), bg="white",command=self.left_click)
        l.place(relx=0.4, rely=0.6, anchor='n')
        slider = tk.Scale(root, from_=1, to=10, orient="horizontal", resolution=1, length =200,command=self.on_slider_change)
        slider.set(10)
        slider.place(relx=0.5, rely=0.9, anchor='n')
    def close_form(self):
        self.destroy()
    def connect_click(self):
        global connected
        if address== "none":
            connected=0
            messagebox.showerror("Error", "Can't find HC05")
        else:
            try:
               sock = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
               sock.settimeout(10)
               s.connect((address, 1))
               connected=1
               print("connected successfully")
            except socket.timeout:
               messagebox.showerror("Error", "Can't connect to HC05")
               connected=0

        print("Button 1 clicked!")
    def on_slider_change(event, value):
        global connected
        int_value = int(value)
        print(connected)
        if (connected):
           if(int_value!=10):
               int_value=int_value+48
               character_byte = chr(int_value)
               b=bytes(character_byte,'ascii')
               print(b)
               s.send(b)
           else:
               s.send(b'q')
            
        print(f"Slider value: {value}")


    def ack_click(self):
        global connected
        if (connected):
           s.send(b'A')    
    def up_click(self):
        global connected
        if (connected):
           s.send(b'F')    
    def down_click(self):
        global connected
        if (connected):
           s.send(b'B')    
    def right_click(self):
        global connected
        if (connected):
           s.send(b'R')    
    def left_click(self):
        global connected
        if (connected):
           s.send(b'L')    
    def stop_click(self):
        global connected
        if (connected):
           s.send(b'S')    
    def x_click(self):
        global connected
        value = spinbox.get()
        int_value = int(value)
        print(int_value)
        character_byte = chr(int_value).encode()
        if (connected):
           s.send(character_byte)    
root = tk.Tk()
form = MyForm(master=root)
root.eval('tk::PlaceWindow . center')

form.mainloop()