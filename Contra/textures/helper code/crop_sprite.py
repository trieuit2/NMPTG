image_path=r'D:\ContraCE108\Contra\textures\font.png'
import cv2
import numpy as np

# Load the PNG image
_img = cv2.imread(image_path, cv2.IMREAD_UNCHANGED)
img=np.copy(_img)
height,width,_=img.shape
# Get the alpha channel of the image
alpha_channel = img[:,:,3]
unfinished_parts=[]
finished_parts=[]

cur_part=None
def isTransparent(y,x):
    return alpha_channel[y,x]==0
for y in range(height):
    x=0
    cur_line=[]
    while x<width:
        if(isTransparent(y,x)):
                if(cur_part==None):
                    pass
                else:
                    cur_line.append(cur_part)
                    cur_part=None         

        else:
            if(cur_part==None):
                cur_part=[(y,x)]
            else:
                cur_part.append((y,x))   
        x=x+1
    #check if there is stiff part left
    if(cur_part!=None):
        cur_line.append(cur_part)
        cur_part=None
    #link if linked and add if not
    for i in range(len(cur_line)):
        _,x_cur=cur_line[i][0]
        _,x_cur_end=cur_line[i][-1]
        flag=False
        for j in range(len(unfinished_parts)):
            _,x_start=unfinished_parts[j][-1][0]
            _,x_end=unfinished_parts[j][-1][-1]
            #print(x_start,x_end,_)
            if(x_start<=x_cur<=x_end)or (x_start<=x_cur_end<=x_end)or (x_cur<=x_start<=x_cur_end) or (x_cur<=x_end<=x_cur_end):
                flag=True
                unfinished_parts[j].append(cur_line[i])
                break
            
        if(flag==False):
            unfinished_parts.append([cur_line[i]])
    if y==height-1:
        for i in unfinished_parts:
            finished_parts.append(i)
    remove_list=[]
    for i in range(len(unfinished_parts)):
        flag=False
        for j in range(len(unfinished_parts[i][-1])):
            y,x=unfinished_parts[i][-1][j]
            if(isTransparent(y+1,x)==False):
                flag=True
                break
        if(flag==False):
            remove_list.append(i)
    for i in remove_list:
        finished_parts.append(unfinished_parts[i])
    unfinished_parts=[unfinished_parts[i] for i in range(len(unfinished_parts)) if i not in remove_list]
# Loop through each image in the array
images=[]
for cur_parr in range(len(finished_parts)):
    y_start,x_start=finished_parts[cur_parr][0][0]
    y_end,x_end=finished_parts[cur_parr][-1][0]
    for i in finished_parts[cur_parr]:
        _,x_temp_start=i[0]
        _,x_temp_end=i[-1]
        if(x_temp_start<x_start):
            x_start=x_temp_start
        if(x_temp_end>x_end):
            x_end=x_temp_end
    if(y_end-y_start>64):
        continue
    if(x_end-x_start>64):
        continue
    
    image=img[y_start:y_end+1,x_start:x_end+1]
    images.append(image)
import os

# Define constants
MAX_IMAGES_PER_ROW = 10
MAX_ROWS_PER_SPRITE = 10
IMAGE_SIZE = 65

# Define function to create a new sprite
def create_sprite(images, output_path, sprite_index):
    # Calculate the number of rows and columns needed to display the images
    num_images = len(images)
    num_rows = (num_images - 1) // MAX_IMAGES_PER_ROW + 1
    num_cols = min(num_images, MAX_IMAGES_PER_ROW)
    # Create a new transparent image to serve as the background for the sprite
    sprite_size = (num_cols * IMAGE_SIZE, num_rows * IMAGE_SIZE)
    sprite = np.zeros((sprite_size[1], sprite_size[0], 4), dtype=np.uint8)
    sprite[:, :, 3] = 0
    # Paste the images onto the sprite
    for i, image in enumerate(images):
        row_index = i // MAX_IMAGES_PER_ROW
        col_index = i % MAX_IMAGES_PER_ROW
        x = col_index * IMAGE_SIZE + (IMAGE_SIZE - image.shape[1]) // 2
        y = row_index * IMAGE_SIZE + (IMAGE_SIZE - image.shape[0]) // 2
        print(image.shape)
        sprite[y:y+image.shape[0], x:x+image.shape[1], :4] = image
        #sprite[y:y+image.shape[0], x:x+image.shape[1], 3] = 255
    # Save the sprite image to disk
    sprite_path = os.path.join(output_path, f"{sprite_index}.png")
    cv2.imwrite(sprite_path, sprite)


output_path = "D:/temp_sprite"
os.makedirs(output_path, exist_ok=True)
sprite_index = 0
sprite_images = []
for i, image in enumerate(images):
    if i > 0 and i % (MAX_IMAGES_PER_ROW * MAX_ROWS_PER_SPRITE) == 0:
        create_sprite(sprite_images, output_path, sprite_index)
        sprite_index += 1
        sprite_images = []
    sprite_images.append(image)
if len(sprite_images) > 0:
    create_sprite(sprite_images, output_path, sprite_index)

