#include <math.h>
#include "helpers.h"

// Convert image to grayscale (converte a imagem para escala de cinza)
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through every pixel (acessa todos os pixels)
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Get RGBTRIPLE values, get the round average and set all values to grayscale to rgb (pega os valores de RGBTRIPLE, faz a média e arredonda o valor e coloca o valor de grayscale para o rgb)
            float average = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0;
            int grayscale = round(average);

            image[i][j].rgbtBlue = grayscale;
            image[i][j].rgbtGreen = grayscale;
            image[i][j].rgbtRed = grayscale;
        }
    }
    return;

}

// Reflect image horizontally (reflete a imagem horizontalmente)
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through pixels and reflect the values (acessa os pixels e reflete os valores)
    for (int i = 0; i < height; i++)
    {
        for (int j = 0, n = round(width / 2); j < n; j++)
        {
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][(width -1) - j];
            image[i][(width -1) - j] = tmp;
        }
    }
    return;
}

// Blur image (imagem desfocada)
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a temporary array (cria uma array temporária)
    RGBTRIPLE tmp[height][width];

    // Loop through all pixels (acessa todos os pixels)
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float sum_red = 0;
            float sum_green = 0;
            float sum_blue = 0;
            int divider = 0;

            // For each pixel loop vertical and horizontal (para cada pixel faz uma iteração vertical e horizontal)
            for (int x = i - 1; x <= i + 1; x++)
            {
                for (int y = j - 1; y <= j + 1; y++)
                {
                    // Sum only the pixels that is inside the rows and columns (Soma apenas os valores que estão dentro das linhas e colunas)
                    if ((x >= 0 && y >= 0) && (x <= (height - 1) && y <= (width - 1)))
                    {
                        sum_red += image[x][y].rgbtRed;
                        sum_green += image[x][y].rgbtGreen;
                        sum_blue += image[x][y].rgbtBlue;
                        divider++;
                    }
                }
            }
            // Get the round average and set to the temporary array (pega a média aproximada e coloca na array temporária)
            tmp[i][j].rgbtRed = round(sum_red / divider);
            tmp[i][j].rgbtGreen = round(sum_green / divider);
            tmp[i][j].rgbtBlue = round(sum_blue / divider);
        }
    }

    // Set the values of the temporary array to the original array (coloca os valores da array temporária para a array original)
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = tmp[i][j];
        }
    }
    return;
}

// Detect edges (detecta bordas)
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int gx[3][3];
    int gy[3][3];

    RGBTRIPLE imagetmp[height][width];

    int gxRed, gyRed, gxGreen, gyGreen, gxBlue, gyBlue;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (i == 0 || i == 2)
            {
                gx[i][j] = -1 + j;
                gy[j][i] = gx[i][j];
            }
            else {
                gx[i][j] = (-1 + j) * 2;
                gy[j][i] = gx[i][j];
            }

        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            gxRed = gyRed = gxGreen = gyGreen = gxBlue = gyBlue = 0;

            for (int x = -1; x <= 1; x++)
            {
                for (int y = -1; y <= 1; y++)
                {
                    if (((x + i) >= 0 && (y + j) >= 0) && ((x + i) <= (height - 1) && (y + j) <= (width - 1)))
                    {
                        gxRed += image[x + i][y + j].rgbtRed * gx[x + 1][y+1];
                        gyRed += image[x + i][y + j].rgbtRed * gy[x + 1][y+1];

                        gxGreen += image[x + i][y + j].rgbtGreen * gx[x + 1][y+1];
                        gyGreen += image[x + i][y + j].rgbtGreen * gy[x + 1][y+1];

                        gxBlue += image[x + i][y + j].rgbtBlue * gx[x + 1][y+1];
                        gyBlue += image[x + i][y + j].rgbtBlue * gy[x + 1][y+1];
                    }
                }
            }

            int red = round(sqrt(pow(gxRed, 2) + pow(gyRed, 2)));
            int green = round(sqrt(pow(gxGreen, 2) + pow(gyGreen, 2)));
            int blue = round(sqrt(pow(gxBlue, 2) + pow(gyBlue, 2)));

            if (red > 255)
            {
                red = 255;
            }
            if (green > 255)
            {
                green = 255;
            }
            if (blue > 255)
            {
                blue = 255;
            }

            imagetmp[i][j].rgbtRed = red;
            imagetmp[i][j].rgbtGreen = green;
            imagetmp[i][j].rgbtBlue = blue;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = imagetmp[i][j];
        }
    }
    return;
}
