#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			float gray_value_float = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3;
			BYTE gray_value = round(gray_value_float);
			image[i][j].rgbtBlue = gray_value;
			image[i][j].rgbtGreen = gray_value;
			image[i][j].rgbtRed = gray_value;
		}
	}
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			tmp_image = image;
			image[i][j] = tmp_image[i][width - j];
		}
	}
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
	int red_sum = 0;
	int blue_sum = 0;
	int green_sum = 0;
	int grid_size = 0;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			for (int k = i - 1; k <= i + 1; k++)
			{
				if (k < 0 || k > height - 1)
				{
					continue;
				}

				for (int l = j - 1; l <= j; l++)
				{
					if (l < 0 || l > width - 1)
					{
						continue;
					}

					red_sum += image[k][l].rgbtRed;
					green_sum += image[k][l].rgbtGreen;
					blue_sum += image[k][l].rgbtBlue;
					grid_size++;
				}
			}

			image[i][j].rgbtRed = round((float) red_sum / grid_size);
			image[i][j].rgbtGreen = round((float) green_sum / grid_size);
			image[i][j].rgbtBlue = round((float) blue_sum / grid_size);
		}
	}
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
	int gx_red_sum = 0, gy_red_sum = 0;
	int gx_green_sum = 0, gy_green_sum = 0;
	int gx_blue_sum = 0, gy_blue_sum = 0;
	BYTE grid_size = 0;

	//loop for each pixel row in image
	for (int i = 0; i < height; i++)
	{
		//loop for each pixel column in image
		for (int j = 0; j < width; j++)
		{
			//loop for each row in 3x3 grid
			for (int k = i - 1; k <= i + 1; k++)
			{
				//checks to see if pixel is beyond border
				if (k < 0 || k > height)
				{
					continue;
				}

				//loop for each column in 3x3 grid
				for (int l = j - 1; l <= j + 1; l++)
				{
					//checks to see if pixel is beyond border
					if (l < 0 || l > width)
					{
						continue;
					}

					//if pixel isn't in middle
					if (l == j - 1 || l == j + 1)
					{
						//if pixel is on the left
						if (l == j - 1)
						{
							//if pixel is in top or bottom row
							if (k == i - 1 || k == i + 1)
							//compute for gx accordingly
							gx_red_sum += -1 * image[k][l].rgbtRed;
							gx_blue_sum += -1 * image[k][l].rgbtBlue;
							gx_green_sum += -1 * image[k][l].rgbtGreen;
						}

						//else pixel is on the right
						else
						{
							//compute for gx accordingly
							gx_red_sum += image[k][l].rgbtRed;
							gx_blue_sum += image[k][l].rgbtBlue;
							gx_green_sum += image[k][l].rgbtGreen;
						}

						//compute for gy accordingly
						gy_red_sum += -1 * image[k][l].rgbtRed;
						gy_green_sum += -1 * image[k][l].rgbtGreen;
						gy_blue_sum += -1 * image[k][l].rgbtBlue;

					//else if pixel is in middle
					else
					{
						//compute for gy ONLY
						gy_red_sum += -2 * image[k][l].rgbtRed;
						gy_green_sum += -2 * image[k][l].rgbtGreen;
						gy_blue_sum += -2 * image[k][l].rgbtBlue;
					}
				}
			}
		}
	}
    return;
}
