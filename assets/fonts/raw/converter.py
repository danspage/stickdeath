from PIL import Image
from bitarray import bitarray

image_path = "default.png"
char_width = 3
char_height = 6
char_spacing_horizontal = 1
char_spacing_vertical = 0

output_filename = "default"

# FILE FORMAT:
# First 8 bits: character width integer
# Second 8 bits: character height integer
# Rest of the file: bits representing the pixels for the characters

try:
    img = Image.open(image_path)
    img = img.convert("RGB")

    img_width, img_height = img.size

    x = 0
    y = 0

    file_data = ""

    file_data += str(char_width) + "\n"
    file_data += str(char_height) + "\n"

    do_scanning = True

    while do_scanning:
        char_data = ""
        for py in range(y, y+char_height):
            for px in range(x, x+char_width):
                if img.getpixel((px, py)) == (255, 255, 255):
                    char_data += "1"
                else:
                    char_data += "0"
        x += char_width + char_spacing_horizontal
        if x + char_width-1 > img_width-1:
            x = 0
            y += char_height + char_spacing_vertical
        file_data += char_data
        if y + char_height-1 > img_height-1:
            do_scanning = False
        else:
            file_data += "\n"
            
    with open(f"{output_filename}.2df", 'w') as file:
        file.write(file_data)

except FileNotFoundError:
    print(f"Error: Image file not found at {image_path}")
except Exception as e:
    print(f"An error occurred: {e}")
