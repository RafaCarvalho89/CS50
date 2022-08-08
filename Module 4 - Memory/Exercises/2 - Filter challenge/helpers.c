#include "helpers.h"
#include <math.h>

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

// Convert image to sepia (converte a imagem para sépia)
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through every pixel (acessa todos os pixels)
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Get RGBTRIPLE values, get the round of the conversion formula
            //(pega os valores de RGBTRIPLE, pega a aproximação do resultado da fórmula de conversão)
            int sepiaRed = round((0.272 * image[i][j].rgbtRed) + (0.534 * image[i][j].rgbtGreen) + (0.131 * image[i][j].rgbtBlue));
            int sepiaGreen = round((0.349 * image[i][j].rgbtRed) + (0.686 * image[i][j].rgbtGreen) + (0.168 * image[i][j].rgbtBlue));
            int sepiaBlue = round((0.393 * image[i][j].rgbtRed) + (0.769 * image[i][j].rgbtGreen) + (0.189 * image[i][j].rgbtBlue));

            // Check for invalid values (checa valores inválidos)
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            // Set the sepia values to the original array (coloca os valores de sépia na array original)
            image[i][j].rgbtBlue = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaBlue;
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
