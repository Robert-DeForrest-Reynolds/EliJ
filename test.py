# create a function that is a text editor using tkinter

import tkinter as tk
from tkinter import filedialog
from tkinter import messagebox
from tkinter import ttk
from tkinter import scrolledtext
import os
import sys
import time
import threading
import subprocess
import webbrowser
import re
import shutil
import platform


class TextEditor:
    def __init__(self, root):
        self.root = root
        self.root.title("Text Editor")
        self.root.geometry("1200x700+200+50")
        self.root.resizable(False, False)

        self.filename = None

        self.title = self.root.title("Untitled - Text Editor")
        self.menubar()
        self.toolbar()
        self.textarea()

    def menubar(self):
        self.menubar = tk.Menu(self.root, font=("times new roman", 14))
        self.root.config(menu=self.menubar)

        # file menu
        self.filemenu = tk.Menu(self.menubar, tearoff=0, font=("times new roman", 14))
        self.menubar.add_cascade(label="File", menu=self.filemenu)
        self.filemenu.add_separator()

        # edit menu
        self.editmenu = tk.Menu(self.menubar, tearoff=0, font=("times new roman", 14))
        self.menubar.add_cascade(label="Edit", menu=self.editmenu)

root = tk.Tk()
TextEditor(root)

