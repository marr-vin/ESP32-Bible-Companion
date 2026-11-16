import os
import gzip

SOURCE_FOLDER = "data"
OUTPUT_FOLDER = "data_gz"

os.makedirs(OUTPUT_FOLDER, exist_ok=True)

total_before = 0
total_after = 0

for filename in os.listdir(SOURCE_FOLDER):

    if not filename.endswith(".txt"):
        continue

    source_path = os.path.join(SOURCE_FOLDER, filename)
    output_name = filename[:-4] + ".gz"
    output_path = os.path.join(OUTPUT_FOLDER, output_name)

    with open(source_path, "rb") as source:
        data = source.read()

    with gzip.open(output_path, "wb", compresslevel=9) as output:
        output.write(data)

    before = os.path.getsize(source_path)
    after = os.path.getsize(output_path)

    total_before += before
    total_after += after

    print(f"{filename}: {before:,} -> {after:,} bytes")

print()
print(f"Original size:   {total_before / 1024 / 1024:.2f} MB")
print(f"Compressed size: {total_after / 1024 / 1024:.2f} MB")
print(f"Saved:           {(total_before-total_after) / 1024 / 1024:.2f} MB")