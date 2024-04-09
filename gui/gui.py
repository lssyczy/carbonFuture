import tkinter as tk
from tkinter import ttk

def on_button_click():
    result_label.config(text="" + selected_application.get() + ", " + selected_strength.get() + ", " + quantity_entry.get())

def on_application_select(event):
    if selected_application.get() == "完整生产碳核算申请":
        material_frame.pack_forget()
        quantity_frame.pack(pady=5)
    else:
        material_frame.pack(pady=5)
        quantity_frame.pack_forget()

root = tk.Tk()
root.title("碳排计算器")
root.geometry("400x300")

title_label = ttk.Label(root, text="水泥", font=("Helvetica", 16))
title_label.pack(pady=10)

application_frame = ttk.Frame(root)
application_frame.pack(pady=5)

application_label = ttk.Label(application_frame, text="选择计算方式:", font=("Helvetica", 12))
application_label.grid(row=0, column=0, padx=5)

applications = ["单一物质碳核算申请", "完整生产碳核算申请"]
selected_application = tk.StringVar(root)
selected_application.set(applications[0])
application_dropdown = ttk.Combobox(application_frame, textvariable=selected_application, values=applications, width=20, font=("Helvetica", 12))
application_dropdown.grid(row=0, column=1, padx=5)
application_dropdown.bind("<<ComboboxSelected>>", on_application_select)

material_frame = ttk.Frame(root)
material_frame.pack(pady=5)

material_label = ttk.Label(material_frame, text="选择原材料:", font=("Helvetica", 12))
material_label.grid(row=0, column=0, padx=5)

materials = ["石灰石", "粉煤灰", "石膏", "铁粉矿泥", "石英砂矿泥", "矿渣", "页岩", "建筑垃圾", "煤矸石", "乙炔污泥", "氨", "水", "电力", "煤炭", "二氧化碳"]
selected_material = tk.StringVar(root)
selected_material.set(materials[0])
material_dropdown = ttk.Combobox(material_frame, textvariable=selected_material, values=materials, width=20, font=("Helvetica", 12))
material_dropdown.grid(row=0, column=1, padx=5)

strength_frame = ttk.Frame(root)
strength_frame.pack(pady=5)

strength_label = ttk.Label(strength_frame, text="抗压强度:", font=("Helvetica", 12))
strength_label.grid(row=0, column=0, padx=5)

strengths = ["32.5 RMPa", "32.5 RMPa", "42.5 Mpa", "42.5 Mpa", "52.5 Mpa", "52.5 Mpa"]
selected_strength = tk.StringVar(root)
selected_strength.set(strengths[0])
strength_dropdown = ttk.Combobox(strength_frame, textvariable=selected_strength, values=strengths, width=20, font=("Helvetica", 12))
strength_dropdown.grid(row=0, column=1, padx=5)

quantity_frame = ttk.Frame(root)
quantity_label = ttk.Label(quantity_frame, text="数量:", font=("Helvetica", 12))
quantity_label.pack(side=tk.LEFT, padx=5)
quantity_entry = ttk.Entry(quantity_frame, font=("Helvetica", 12))
quantity_entry.pack(side=tk.LEFT)
quantity_frame.pack(pady=5)

button = ttk.Button(root, text="计算", command=on_button_click)
button.pack(pady=10)

result_label = ttk.Label(root, text="", font=("Helvetica", 12))
result_label.pack(pady=5)

root.mainloop()
