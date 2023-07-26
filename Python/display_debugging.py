import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

CacheFiles = ["raw",
   "predictor", "local-sums"]

num_images = len(CacheFiles)
rows = 2 if num_images > 5 else 1
cols = (num_images + 1) // 2

fig, axes = plt.subplots(rows, cols, figsize=(10, 5))
fig.tight_layout()


images = []

def display_images(i):
    images = []
    
    for filename in CacheFiles:
        images.append(plt.imread(f'Python/images/{filename}{i}.png'))
    
    if num_images > 10:
        print("Error: Maximum 10 images can be displayed.")
        return


    for i, ax in enumerate(axes.flat):
        if i < num_images:
            ax.imshow(images[i])
            ax.axis('off')
        else:
            ax.axis('off')

    



if __name__ == "__main__":

    anim = FuncAnimation(fig, display_images, frames = 100, interval=1000)
    plt.show()