import psutil
import subprocess
import tkinter as tk
from tkinter import filedialog

def open_folder(path):
    subprocess.run(('sudo','pcmanfm',format(path)))

def pathinputpage():
    tmp=psutil.disk_partitions()
    print(tmp)
    for index in range(len(tmp)):
        if 'media' in tmp[index].mountpoint:
            print(tmp[index].mountpoint)
    canvas1 = tk.Canvas( width=400, height=400)
    canvas1.place(x=0, y=0) 
    #入力欄の作成
    input_box = tk.Entry(width=40)
    input_box.place(x=10, y=100)
 
    #ボタンの作成
    button = tk.Button(text="参照",command=lambda:file_select(input_box,tmp[2]))
    button.place(x=10, y=130)

    widgechange = tk.Button(canvas1, text="遷移するボタン", command=lambda:transition_button(canvas1,input_box)) # 遷移ボタン                                                
    widgechange.place(x=70, y=200, anchor=tk.CENTER)
    
def file_select(input_box,devicepath):
    filetype = [("ALL","*")]
    file_path = tk.filedialog.askopenfilename(filetypes = filetype,initialdir =devicepath.mountpoint)
    print(file_path)
    input_box.insert(tk.END, file_path)
    
def transition_button(widget,input_box):
    if input_box.get():
        widget.place_forget()                        
        canvas = tk.Canvas(width=400, height=400)
        canvas.place(x=0, y=0)
        label = tk.Label(canvas, text=input_box.get())
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

#ウインドウの描画
root.mainloop()

