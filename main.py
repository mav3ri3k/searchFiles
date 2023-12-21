import sqlite3
import os
import hashlib

path = "."
absolutePath = os.path.abspath(path)

def database():
    con = sqlite3.connect("database.db")
    cur = con.cursor()

    return cur

def database_first_setup(cur: sqlite3.Cursor):
    cur.execute("CREATE TABLE files(filename, extension, path, date_created, last_modified, size, hash)")

def add_file(filename, extension, path, date_created, last_modeified, size, hash):
    cur.execute(f"""
                INSERT INTO files VALUES 
                ('{filename}', 
                '{extension}', 
                '{path}', 
                 {date_created}, 
                {last_modeified}, 
                 {size},
                '{hash}' )
                """)
    print("Added")


def read_all():
    for row in cur.execute("SELECT * FROM files"):
        print(row)

def clean(str):
    pattern = ""
    i = 0;
    for ch in str:
        if i >= 2:
            break
        pattern += ch
        i += 1 

    if (pattern == "./"):
        return str[2:]
    else:
        return str

def find_files():
    for root, _, f_names in os.walk(path):
        for file in f_names:
            filepath = f"{absolutePath}/{clean(root)}/{file}"
            extension = os.path.splitext('my_file.txt')[1][1:]
            size = os.path.getsize(filepath)
            date_created = os.path.getmtime(filepath)
            last_modeified = os.path.getctime(filepath)
            BUF_SIZE = 65536  #64kb chunks
            md5 = hashlib.md5()

            with open(filepath, 'rb') as f:
                while True:
                    data = f.read(BUF_SIZE)
                    if not data:
                        break
                    md5.update(data)

            add_file(file, extension, filepath, date_created, last_modeified, size, md5.hexdigest() )

cur = database()
database_first_setup(cur)
find_files()
read_all()


