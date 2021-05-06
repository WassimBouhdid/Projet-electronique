from tkinter import *
import serial


def send_input():
    input_limit = input_box.get()
    input_box.delete(0, END)
    if input_limit.isnumeric():
        octet = bytes(input_limit, 'ascii')
        serialport = serial.Serial(port='COM1')
        serialport.write(octet)
        error_label.destroy()
    else:
        error_label.pack()


window = Tk()

window.title("Interface Python")
window.geometry("400x150")

frame = Frame(window)

label_main = Label(frame, text="veuillez insérer la limite de personne admissible", font=("Arial", 12), fg='black')
label_main.pack()

input_box = Entry(frame, font=("Arial", 12), fg='black')
input_box.pack()

entry_button = Button(frame, text="set the limit", command=send_input)
entry_button.pack()

error_label = Label(frame, text="veuillez insérer un nombre !!", font=("Arial", 12), fg='red')

frame.pack(expand=YES)

window.mainloop()
