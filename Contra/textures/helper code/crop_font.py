from PIL import Image

# Open the source image
source_image = Image.open(r"D:\ContraCE108\Contra\textures\font-2.png")



# Calculate the number of cropped images
crop_width = 16
crop_height = 16
num_crops = (source_image.width // crop_width) * (source_image.height // crop_height)

# Create a list to store the cropped images
cropped_images = []

# Loop through the image and crop each section
for y in range(0, source_image.height, crop_height):
    for x in range(0, source_image.width, crop_width):
        # Check if the remaining portion is smaller than the desired crop size
        if x + crop_width > source_image.width or y + crop_height > source_image.height:
            continue

        # Crop a portion of the source image
        crop = source_image.crop((x, y, x + crop_width, y + crop_height))

        # Create an empty transparent 65x65 image
        empty_image = Image.new("RGBA", (65, 65), (0, 0, 0, 0))

        # Calculate the position to paste the crop in the empty image
        paste_x = (empty_image.width - crop.width) // 2
        paste_y = (empty_image.height - crop.height) // 2

        # Paste the crop into the empty image
        empty_image.paste(crop, (paste_x, paste_y))

        # Add the cropped image to the list
        cropped_images.append(empty_image)

# Create a new image to store the final arrangement
images_per_row = 10
num_rows = (num_crops + images_per_row - 1) // images_per_row
final_width = images_per_row * cropped_images[0].width
final_height = num_rows * cropped_images[0].height
final_image = Image.new("RGBA", (final_width, final_height), (0, 0, 0, 0))

# Loop through the cropped images and arrange them in a grid style
for i, cropped_image in enumerate(cropped_images):
    # Calculate the position to paste the cropped image in the final image
    paste_x = (i % images_per_row) * cropped_image.width
    paste_y = (i // images_per_row) * cropped_image.height

    # Paste the cropped image into the final image
    final_image.paste(cropped_image, (paste_x, paste_y))

# Save the final image
final_image.save("D:/final_image.png")
