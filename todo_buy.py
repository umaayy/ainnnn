# to-do list sederhana berbasis tkinter
# dibuat untuk latihan GUI python
# by: (isi namamu kalau mau)
# -------------------------------

import tkinter as tk
from tkinter import ttk, messagebox, simpledialog, filedialog
import json, os
from datetime import datetime

FILE_TUGAS = "tasks.json"

# ====== Kelas Data Tugas ======
class Tugas:
    def __init__(self, judul, catatan="", due="", prioritas="Normal", selesai=False, dibuat=None):
        # internal storage private
        self.__judul = None
        self.__catatan = None
        self.__due = None
        self.__prioritas = None
        self.__selesai = None
        self.__dibuat = None

        # gunakan setter untuk validasi/normalisasi
        self.judul = judul
        self.catatan = catatan
        self.due = due
        self.prioritas = prioritas
        # selesai diset langsung lewat property
        self.selesai = bool(selesai)
        self.__dibuat = dibuat or datetime.now().isoformat()

    # ----- properties untuk kompatibilitas (bisa dipanggil t.judul / t.selesai) -----
    @property
    def judul(self):
        return self.__judul

    @judul.setter
    def judul(self, value):
        if value is None:
            value = ""
        v = str(value).strip()
        # jangan lempar error di setter supaya GUI tidak crash; biarkan validasi di FormTugas
        self.__judul = v or "(tanpa judul)"

    @property
    def catatan(self):
        return self.__catatan

    @catatan.setter
    def catatan(self, value):
        if value is None:
            value = ""
        self.__catatan = str(value)

    @property
    def due(self):
        return self.__due

    @due.setter
    def due(self, value):
        if value is None:
            value = ""
        # simpan apa adanya; validasi format dilakukan di FormTugas
        self.__due = str(value)

    @property
    def prioritas(self):
        return self.__prioritas

    @prioritas.setter
    def prioritas(self, value):
        if value is None:
            value = "Normal"
        p = str(value)
        # normalisasi: terima Low/Normal/High, fallback ke Normal
        self.__prioritas = p if p in ["Low", "Normal", "High"] else "Normal"

    @property
    def selesai(self):
        return self.__selesai

    @selesai.setter
    def selesai(self, value):
        self.__selesai = bool(value)

    @property
    def dibuat(self):
        return self.__dibuat

    # tidak ada setter untuk dibuat (read-only)

    # Konversi ke dictionary untuk simpan JSON
    def to_dict(self):
        return {
            "judul": self.judul,
            "catatan": self.catatan,
            "due": self.due,
            "prioritas": self.prioritas,
            "selesai": self.selesai,
            "dibuat": self.dibuat
        }

    @staticmethod
    def from_dict(d):
        return Tugas(
            d.get("judul", "(tanpa judul)"),
            d.get("catatan", ""),
            d.get("due", ""),
            d.get("prioritas", "Normal"),
            d.get("selesai", False),
            d.get("dibuat")
        )

# ====== Pengelola daftar tugas ======
class Pengelola:
    def __init__(self):
        self.daftar = []
        self.load()

    def tambah(self, t):
        self.daftar.append(t)
        self.save()

    def hapus(self, i):
        if 0 <= i < len(self.daftar):
            del self.daftar[i]
            self.save()

    def ubah(self, i, t):
        if 0 <= i < len(self.daftar):
            self.daftar[i] = t
            self.save()

    def tandai(self, i):
        if 0 <= i < len(self.daftar):
            self.daftar[i].selesai = not self.daftar[i].selesai
            self.save()

    def save(self, path=FILE_TUGAS):
        try:
            with open(path,"w",encoding="utf-8") as f:
                json.dump([x.to_dict() for x in self.daftar], f, indent=2, ensure_ascii=False)
        except Exception as e:
            print("gagal simpan:", e)

    def load(self, path=FILE_TUGAS):
        self.daftar = []
        if os.path.exists(path):
            try:
                with open(path,"r",encoding="utf-8") as f:
                    data = json.load(f)
                self.daftar = [Tugas.from_dict(x) for x in data]
            except:
                pass

# ====== Dialog Input/Edit ======
class FormTugas(simpledialog.Dialog):
    def __init__(self, parent, title, tugas=None):
        self.tugas = tugas
        super().__init__(parent, title)

    def body(self, master):
        tk.Label(master, text="Judul:").grid(row=0, column=0, sticky="w")
        self.e_judul = tk.Entry(master, width=40)
        self.e_judul.grid(row=0, column=1, pady=3)

        tk.Label(master, text="Due (YYYY-MM-DD):").grid(row=1, column=0, sticky="w")
        self.e_due = tk.Entry(master)
        self.e_due.grid(row=1, column=1, pady=3, sticky="w")

        tk.Label(master, text="Prioritas:").grid(row=2, column=0, sticky="w")
        self.var_pr = tk.StringVar(value="Normal")
        self.cb_pr = ttk.Combobox(master, textvariable=self.var_pr,
                                  values=["Low","Normal","High"], state="readonly", width=10)
        self.cb_pr.grid(row=2, column=1, sticky="w")

        tk.Label(master, text="Catatan:").grid(row=3, column=0, sticky="nw")
        self.txt_cat = tk.Text(master, width=40, height=5)
        self.txt_cat.grid(row=3, column=1, pady=3)

        if self.tugas:
            # gunakan property publik (kompatibel)
            self.e_judul.insert(0, self.tugas.judul)
            self.e_due.insert(0, self.tugas.due)
            self.var_pr.set(self.tugas.prioritas)
            self.txt_cat.insert("1.0", self.tugas.catatan)
        return self.e_judul

    def validate(self):
        j = self.e_judul.get().strip()
        if not j:
            messagebox.showwarning("Perhatian", "Judul tidak boleh kosong.")
            return False
        if self.e_due.get().strip():
            try:
                datetime.strptime(self.e_due.get().strip(), "%Y-%m-%d")
            except:
                messagebox.showwarning("Format Salah", "Gunakan format tanggal YYYY-MM-DD.")
                return False
        return True

    def apply(self):
        j = self.e_judul.get().strip()
        d = self.e_due.get().strip()
        p = self.var_pr.get()
        c = self.txt_cat.get("1.0","end").strip()
        if self.tugas:
            # update tugas yang ada (pakai property sehingga kompatibel)
            hasil = Tugas(j,c,d,p,self.tugas.selesai,self.tugas.dibuat)
        else:
            hasil = Tugas(j,c,d,p,False)
        self.result = hasil

# ====== GUI Utama ======
class Aplikasi:
    def __init__(self, root):
        self.root = root
        self.root.title("To-Do List GUI")
        self.root.geometry("750x480")

        self.mgr = Pengelola()

        # tombol atas
        bar = tk.Frame(root)
        bar.pack(fill="x", padx=8, pady=6)
        tk.Button(bar, text="Tambah", command=self.tambah).pack(side="left")
        tk.Button(bar, text="Edit", command=self.edit).pack(side="left", padx=4)
        tk.Button(bar, text="Hapus", command=self.hapus).pack(side="left")
        tk.Button(bar, text="Tandai", command=self.tandai).pack(side="left", padx=6)
        tk.Button(bar, text="Simpan Sebagai", command=self.simpan_sebagai).pack(side="left", padx=6)

        tk.Label(bar, text="Filter:").pack(side="left", padx=(12,4))
        self.var_filter = tk.StringVar(value="Semua")
        ttk.Combobox(bar, textvariable=self.var_filter,
                     values=["Semua","Selesai","Belum"], state="readonly", width=8).pack(side="left")

        tk.Label(bar, text="Cari:").pack(side="left", padx=(10,4))
        self.var_cari = tk.StringVar()
        e_cari = tk.Entry(bar, textvariable=self.var_cari)
        e_cari.pack(side="left")
        e_cari.bind("<KeyRelease>", lambda e: self.refresh())

        # tabel
        kolom = ("judul","due","prioritas","status")
        self.tree = ttk.Treeview(root, columns=kolom, show="headings")
        for c, t in zip(kolom, ["Judul","Due","Prioritas","Status"]):
            self.tree.heading(c, text=t)
        self.tree.column("judul", width=340)
        self.tree.column("due", width=100, anchor="center")
        self.tree.column("prioritas", width=80, anchor="center")
        self.tree.column("status", width=80, anchor="center")
        self.tree.pack(fill="both", expand=True, padx=8, pady=6)
        self.tree.bind("<Double-1>", lambda e: self.edit())
        self.tree.bind("<<TreeviewSelect>>", lambda e: self.tampil_detail())

        # area bawah
        bawah = tk.Frame(root)
        bawah.pack(fill="x", padx=8, pady=(0,8))
        tk.Label(bawah, text="Catatan / Detail:").pack(anchor="w")
        self.txt_det = tk.Text(bawah, height=5)
        self.txt_det.pack(fill="x")

        self.refresh()

    def get_sel(self):
        sel = self.tree.selection()
        return int(sel[0]) if sel else None

    def refresh(self):
        self.tree.delete(*self.tree.get_children())
        f = self.var_filter.get()
        q = self.var_cari.get().strip().lower()
        for i, t in enumerate(self.mgr.daftar):
            # gunakan property publik t.selesai (tetap kompatibel)
            if f == "Selesai" and not t.selesai: continue
            if f == "Belum" and t.selesai: continue
            if q and q not in (t.judul + t.catatan).lower(): continue
            status = "Selesai" if t.selesai else "Belum"
            self.tree.insert("", "end", iid=str(i), values=(t.judul, t.due, t.prioritas, status))
        self.tampil_detail()

    def tambah(self):
        f = FormTugas(self.root, "Tambah Tugas")
        if getattr(f, "result", None):
            self.mgr.tambah(f.result)
            self.refresh()

    def edit(self):
        i = self.get_sel()
        if i is None:
            messagebox.showinfo("Info", "Pilih tugas dulu.")
            return
        t = self.mgr.daftar[i]
        f = FormTugas(self.root, "Edit Tugas", t)
        if getattr(f, "result", None):
            self.mgr.ubah(i, f.result)
            self.refresh()

    def hapus(self):
        i = self.get_sel()
        if i is None: return
        if messagebox.askyesno("Hapus", "Yakin mau hapus tugas ini?"):
            self.mgr.hapus(i)
            self.refresh()

    def tandai(self):
        i = self.get_sel()
        if i is None: return
        # gunakan property publik (tetap kompatibel)
        t = self.mgr.daftar[i]
        t.selesai = not t.selesai
        self.mgr.save()
        self.refresh()

    def tampil_detail(self):
        self.txt_det.delete("1.0","end")
        i = self.get_sel()
        if i is None: return
        t = self.mgr.daftar[i]
        isi = f"Judul: {t.judul}\nDue: {t.due}\nPrioritas: {t.prioritas}\nStatus: {'Selesai' if t.selesai else 'Belum'}\nDibuat: {t.dibuat}\n\nCatatan:\n{t.catatan}"
        self.txt_det.insert("1.0", isi)

    def simpan_sebagai(self):
        p = filedialog.asksaveasfilename(defaultextension=".json", filetypes=[("JSON","*.json")])
        if p:
            try:
                # simpan seluruh daftar ke file baru
                with open(p, "w", encoding="utf-8") as f:
                    json.dump([x.to_dict() for x in self.mgr.daftar], f, indent=2, ensure_ascii=False)
                messagebox.showinfo("OK", "Berhasil disimpan.")
            except:
                messagebox.showerror("Error", "Gagal menyimpan.")

# ====== Jalankan ======
if __name__ == "__main__":
    root = tk.Tk()
    app = Aplikasi(root)
    root.mainloop()
