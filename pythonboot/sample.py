import subprocess
import Tkinter as tk
import tkFileDialog
import rect
import ctypes
def open_folder(path):
    subprocess.run(('sudo','pcmanfm',format(path)))

def pathinputpage():

    canvas1 = tk.Canvas( width=400, height=400)
    canvas1.place(x=0, y=0) 
    input_box = tk.Entry(width=40)
    input_box.place(x=10, y=100)
    button = tk.Button(text="sannsyou",command=lambda:file_select(input_box))
    button.place(x=10, y=130)

    widgechange = tk.Button(canvas1, text="seni", command=lambda:transition_button(canvas1,input_box))                                               
    widgechange.place(x=70, y=200, anchor=tk.CENTER)
    
def file_select(input_box):
    filetype = [("ALL","*")]
    file_path = tkFileDialog.askopenfilename(filetypes = filetype,initialdir ='C:')
    input_box.insert(tk.END, file_path)
    
def transition_button(widget,input_box):
    a=input_box.get()

    if input_box.get():
        widget.place_forget()                        
        canvas = tk.Canvas(width=400, height=400)
        canvas.place(x=0, y=0)
        label = tk.Label(canvas, text=input_box.get())
        rect_obj = rect.PyRectangle()
        rect_obj.run(b"aaa")
        label.place(x=200, y=150, anchor=tk.CENTER)
        button = tk.Button(canvas,text="back",command=lambda:prayback(canvas))
        button.place(x=70, y=200, anchor=tk.CENTER)
        
def prayback(widget):
    widget.place_forget()
    pathinputpage()

root = tk.Tk()
root.title("Python GUI")
root.geometry("360x240")
pathinputpage()

root.mainloop()

