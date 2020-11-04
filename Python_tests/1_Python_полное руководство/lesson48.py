import zipfile
import os

folder_path = 'c:\\Python\\folder'
zip_path = 'c:\\Python\\folder\\test.zip'
zip_name = 'test.zip'

my_zip = zipfile.ZipFile(zip_path, 'w')

# my_zip.write('c:\\Python\\folder\\1.txt', 'new.txt', compress_type=zipfile.ZIP_DEFLATED)

for folder, subfolders, files in os.walk(folder_path):
    for file in files:
        if file == zip_name:
            continue
        my_zip.write(os.path.join(folder, file),
        os.path.relpath(os.path.join(folder, file), folder_path),
        compress_type=zipfile.ZIP_DEFLATED)


my_zip.close()
