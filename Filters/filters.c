# include <math.h>

// Convert image to grayscale
// Calculate the avg of r,g,b values and put all values equal to avg
// **x/y returns an int. To get a float return value (float)x/y or x.0/y or x/y.0
// round() always rounds up
// nearbyint() rounds up in x.5 x is odd and rounds down when x is even. 
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int red = image[i][j].rgbtRed;
            int blue = image[i][j].rgbtBlue;
            int green = image[i][j].rgbtGreen;
            float f_avg = ((float)red + blue + green) / 3;
            int avg = (int)nearbyint(f_avg);
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
        }
    }
    return;
}
// Convert image to sepia
// Given formulas for conversions
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int originalRed = image[i][j].rgbtRed;
            int originalBlue = image[i][j].rgbtBlue;
            int originalGreen = image[i][j].rgbtGreen;
            int sepia_red = (int) round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            int sepia_green = (int) round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            int sepia_blue = (int) round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);
            //If return value is greater than 255 we restrict to 255
            if (sepia_red > 255)
            {
                sepia_red = 255;
            }
            if (sepia_green > 255)
            {
                sepia_green = 255;
            }
            if (sepia_blue > 255)
            {
                sepia_blue = 255;
            }
            image[i][j].rgbtRed = sepia_red;
            image[i][j].rgbtBlue = sepia_blue;
            image[i][j].rgbtGreen = sepia_green;
        }
    }
    return;
}

// Reflect image horizontally
// Replacing value of pixel in the front with the corresponding pixel at the end using a temporary variable
// If there is a middle row it needs to stay unchanged
// Middle row will exist in case of odd number of rows
// width/2 returns just the integer part of the quotient
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 1; j <= width / 2; j++)
        {
            int temp_red = image[i][j - 1].rgbtRed;
            int temp_blue = image[i][j - 1].rgbtBlue;
            int temp_green = image[i][j - 1].rgbtGreen;
            image[i][j - 1].rgbtRed = image[i][width - j].rgbtRed;
            image[i][j - 1].rgbtBlue = image[i][width - j].rgbtBlue;
            image[i][j - 1].rgbtGreen = image[i][width - j].rgbtGreen;
            image[i][width - j].rgbtRed = temp_red;
            image[i][width - j].rgbtBlue = temp_blue;
            image[i][width - j].rgbtGreen = temp_green;
        }
    }
    return;
}

// Blur image
// We take avg of r,g,b values in the respective array to be considered
// For corners: 2x2 array
// For edges: 2x3 /3x2 array
// For any other pixel: 3x3 array
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //Copying the picture into another 2-D array temp
    // The data type is of RGVTRIPLE
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sum_red = 0;
            int sum_blue = 0;
            int sum_green = 0;
            //In case of a corner 4 cases
            // 2x2 array array considered
            if ((i == 0 && j == 0) || (i == 0 && j == width - 1) || (i == height - 1 && j == 0) || (i == height - 1 && j == width - 1))
            {
                if (i == 0 && j == 0)
                {
                    for (int x = 0; x < 2; x++)
                    {
                        for (int y = 0; y < 2; y++)
                        {
                            sum_red += temp[x][y].rgbtRed;
                            sum_blue += temp[x][y].rgbtBlue;
                            sum_green += temp[x][y].rgbtGreen;
                            
                        }
                    }
                    image[i][j].rgbtRed = (int)(round(((float)sum_red) / 4));
                    image[i][j].rgbtBlue = (int)(round(((float)sum_blue) / 4));
                    image[i][j].rgbtGreen = (int)(round(((float)sum_green) / 4));
                }
                if ((i == 0 && j == width - 1))
                {
                    for (int x = 0; x < 2; x++)
                    {
                        for (int y = j - 1; y < j + 1; y++)
                        {
                            sum_red += temp[x][y].rgbtRed;
                            sum_blue += temp[x][y].rgbtBlue;
                            sum_green += temp[x][y].rgbtGreen;
                            
                        }
                    }
                    image[i][j].rgbtRed = (int)(round(((float)sum_red) / 4));
                    image[i][j].rgbtBlue = (int)(round(((float)sum_blue) / 4));
                    image[i][j].rgbtGreen = (int)(round(((float)sum_green) / 4));
                }
                if ((i == height - 1 && j == 0))
                {
                    for (int x = i - 1; x < i + 1; x++)
                    {
                        for (int y = 0; y < 2; y++)
                        {
                            sum_red += temp[x][y].rgbtRed;
                            sum_blue += temp[x][y].rgbtBlue;
                            sum_green += temp[x][y].rgbtGreen;
                            
                        }
                    }
                    image[i][j].rgbtRed = (int)(round(((float)sum_red) / 4));
                    image[i][j].rgbtBlue = (int)(round(((float)sum_blue) / 4));
                    image[i][j].rgbtGreen = (int)(round(((float)sum_green) / 4));
                }
                if ((i == height - 1 && j == width - 1))
                {
                    for (int x = i - 1; x < i + 1; x++)
                    {
                        for (int y = j - 1; y < j + 1; y++)
                        {
                            sum_red += temp[x][y].rgbtRed;
                            sum_blue += temp[x][y].rgbtBlue;
                            sum_green += temp[x][y].rgbtGreen;
                            
                        }
                    }
                    image[i][j].rgbtRed = (int)(round(((float)sum_red) / 4));
                    image[i][j].rgbtBlue = (int)(round(((float)sum_blue) / 4));
                    image[i][j].rgbtGreen = (int)(round(((float)sum_green) / 4));
                }
                
            }
            else if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
            {
                if (i == 0)
                {
                    for (int x = 0; x < 2; x++)
                    {
                        for (int y = j - 1; y < j + 2; y++)
                        {
                            sum_red += temp[x][y].rgbtRed;
                            sum_blue += temp[x][y].rgbtBlue;
                            sum_green += temp[x][y].rgbtGreen;
                        }
                    }
                    image[i][j].rgbtRed = (int)(round(((float)sum_red) / 6));
                    image[i][j].rgbtBlue = (int)(round(((float)sum_blue) / 6));
                    image[i][j].rgbtGreen = (int)(round(((float)sum_green) / 6));
                }
                if (i == height - 1)
                {
                    for (int x = i - 1; x < i + 1; x++)
                    {
                        for (int y = j - 1; y < j + 2; y++)
                        {
                            sum_red += temp[x][y].rgbtRed;
                            sum_blue += temp[x][y].rgbtBlue;
                            sum_green += temp[x][y].rgbtGreen;
                        }
                    }
                    image[i][j].rgbtRed = (int)(round(((float)sum_red) / 6));
                    image[i][j].rgbtBlue = (int)(round(((float)sum_blue) / 6));
                    image[i][j].rgbtGreen = (int)(round(((float)sum_green) / 6));
                }
                if (j == 0)
                {
                    for (int x = i - 1; x < i + 2; x++)
                    {
                        for (int y = 0; y < 2; y++)
                        {
                            sum_red += temp[x][y].rgbtRed;
                            sum_blue += temp[x][y].rgbtBlue;
                            sum_green += temp[x][y].rgbtGreen;
                        }
                    }
                    image[i][j].rgbtRed = (int)(round(((float)sum_red) / 6));
                    image[i][j].rgbtBlue = (int)(round(((float)sum_blue) / 6));
                    image[i][j].rgbtGreen = (int)(round(((float)sum_green) / 6));
                }
                if (j == width - 1)
                {
                    for (int x = i - 1; x < i + 2; x++)
                    {
                        for (int y = j - 1; y < j + 1; y++)
                        {
                            sum_red += temp[x][y].rgbtRed;
                            sum_blue += temp[x][y].rgbtBlue;
                            sum_green += temp[x][y].rgbtGreen;
                        }
                    }
                    image[i][j].rgbtRed = (int)(round(((float)sum_red) / 6));
                    image[i][j].rgbtBlue = (int)(round(((float)sum_blue) / 6));
                    image[i][j].rgbtGreen = (int)(round(((float)sum_green) / 6));
                }
            }
            else
            {
                for (int x = i - 1; x < i + 2; x++)
                {
                    for (int y = j - 1; y < j + 2; y++)
                    {
                        sum_red += temp[x][y].rgbtRed;
                        sum_blue += temp[x][y].rgbtBlue;
                        sum_green += temp[x][y].rgbtGreen;
                    }
                } 
                image[i][j].rgbtRed = (int)(round(((float)sum_red) / 9));
                image[i][j].rgbtBlue = (int)(round(((float)sum_blue) / 9));
                image[i][j].rgbtGreen = (int)(round(((float)sum_green) / 9));
            }
        }
    }
    return;
}
