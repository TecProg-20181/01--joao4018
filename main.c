#include <stdio.h>

unsigned int counter = 0;
unsigned int counter_two = 0;

typedef struct _pixel {
    unsigned short int red;
    unsigned short int green;
    unsigned short int blue;
} Pixel;

typedef struct _image {
    unsigned short int pixel[512][512][3];
    unsigned int widht;
    unsigned int height;
} Image;
int calculate_average(unsigned short int pixel[512][512][3]){
  int media = (pixel[counter][counter_two][0] +
              pixel[counter][counter_two][1] +
              pixel[counter][counter_two][2])/3;
  return media;
}

void copy_data(unsigned short int pixel[512][512][3],int *media){
  pixel[counter][counter_two][0] = *media;
  pixel[counter][counter_two][1] = *media;
  pixel[counter][counter_two][2] = *media;
}

Image change_color_to_gray(Image image) {
    for (counter = 0; counter < image.height; ++counter) {
        for (counter_two = 0; counter_two < image.widht; ++counter_two) {
            int media = calculate_average(image.pixel);
            copy_data(image.pixel, &media);
        }
    }

    return image;
}
void blur(unsigned int height, unsigned short int pixel[512][512][3], int tamanho, unsigned int wight) {
    for (unsigned int i = 0; i < height; ++i) {
        for (unsigned int j = 0; j < wight; ++j) {
            Pixel media = {0, 0, 0};

            int menor_height = (height - 1 > i + tamanho/2) ? i + tamanho/2 : height - 1;
            int min_wight = (wight - 1 > j + tamanho/2) ? j + tamanho/2 : wight - 1;
            for(int x = (0 > i - tamanho/2 ? 0 : i - tamanho/2); x <= menor_height; ++x) {
                for(int y = (0 > j - tamanho/2 ? 0 : j - tamanho/2); y <= min_wight; ++y) {
                    media.red += pixel[x][y][0];
                    media.green += pixel[x][y][1];
                    media.blue += pixel[x][y][2];
                }
            }

            // printf("%u", media.r)
            media.red /= tamanho * tamanho;
            media.green /= tamanho * tamanho;
            media.blue /= tamanho * tamanho;

            pixel[i][j][0] = media.red;
            pixel[i][j][1] = media.green;
            pixel[i][j][2] = media.blue;
        }
    }
}

Image rotacionar90direita(Image image) {
    Image rotacionada;

    rotacionada.widht = image.height;
    rotacionada.height = image.widht;

    for (unsigned int i = 0, y = 0; i < rotacionada.height; ++i, ++y) {
        for (int j = rotacionada.widht - 1, x = 0; j >= 0; --j, ++x) {
            rotacionada.pixel[i][j][0] = image.pixel[x][y][0];
            rotacionada.pixel[i][j][1] = image.pixel[x][y][1];
            rotacionada.pixel[i][j][2] = image.pixel[x][y][2];
        }
    }

    return rotacionada;
}

void inverter_cores(unsigned short int pixel[512][512][3],
                    unsigned int w, unsigned int h) {
    for (unsigned int i = 0; i < h; ++i) {
        for (unsigned int j = 0; j < w; ++j) {
            pixel[i][j][0] = 255 - pixel[i][j][0];
            pixel[i][j][1] = 255 - pixel[i][j][1];
            pixel[i][j][2] = 255 - pixel[i][j][2];
        }
    }
}

Image cortar_imagem(Image img, int x, int y, int w, int h) {
    Image cortada;

    cortada.widht = w;
    cortada.height = h;

    for(int i = 0; i < h; ++i) {
        for(int j = 0; j < w; ++j) {
            cortada.pixel[i][j][0] = img.pixel[i + y][j + x][0];
            cortada.pixel[i][j][1] = img.pixel[i + y][j + x][1];
            cortada.pixel[i][j][2] = img.pixel[i + y][j + x][2];
        }
    }

    return cortada;
}

Image read_image()
{
  int max_color;
  char p3[4];
  Image image;

  scanf("%s",p3);
  scanf("%u %u", &image.widht, &image.height);
  scanf("%d",&max_color);

  for (counter = 0; counter < image.height; ++counter) {
    for (counter_two = 0; counter_two < image.widht; ++counter_two) {

      scanf("%hu", &image.pixel[counter][counter_two][0]);
      scanf("%hu",&image.pixel[counter][counter_two][1]);
      scanf("%hu",&image.pixel[counter][counter_two][2]);

    }
  }
return image;
}
void print_image(Image image){

      printf("P3\n");
      printf("%u %u\n255\n", image.widht, image.height);
      for (counter = 0; counter < image.height; ++counter) {
          for (counter_two = 0; counter_two < image.widht; ++counter_two) {
              printf("%hu %hu %hu ", image.pixel[counter][counter_two][0],
                                     image.pixel[counter][counter_two][1],
                                     image.pixel[counter][counter_two][2]);

          }
          printf("\n");
      }
}
Image filter_serpia(Image image){
  for (counter = 0; counter < image.height; ++counter) {
    for (counter_two = 0; counter_two < image.widht; ++counter_two) {
      unsigned short int pixel[3];
      pixel[0] = image.pixel[counter][counter_two][0];
      pixel[1] = image.pixel[counter][counter_two][1];
      pixel[2] = image.pixel[counter][counter_two][2];

      int p =  pixel[0] * .393 + pixel[1] * .769 + pixel[2] * .189;
      int menor_r = (255 >  p) ? p : 255;
      image.pixel[counter][counter_two][0] = menor_r;

      p =  pixel[0] * .349 + pixel[1] * .686 + pixel[2] * .168;
      menor_r = (255 >  p) ? p : 255;
      image.pixel[counter][counter_two][1] = menor_r;

      p =  pixel[0] * .272 + pixel[1] * .534 + pixel[2] * .131;
      menor_r = (255 >  p) ? p : 255;
      image.pixel[counter][counter_two][2] = menor_r;
    }
  }
  return image;
}
void options(Image image){
  int n_opcoes;
  scanf("%d", &n_opcoes);

  for(int i = 0; i < n_opcoes; ++i) {
      int opcao;
      scanf("%d", &opcao);

      switch(opcao) {
          case 1: { // Escala de Cinza
              image = change_color_to_gray(image);
              break;
          }
          case 2: { // Filtro Sepia
               image = filter_serpia(image);
              break;
          }
          case 3: { // Blur
              int tamanho = 0;
              scanf("%d", &tamanho);
              blur(image.height, image.pixel, tamanho, image.widht);
              break;
          }
          case 4: { // Rotacao
              int quantas_vezes = 0;
              scanf("%d", &quantas_vezes);
              quantas_vezes %= 4;
              for (int j = 0; j < quantas_vezes; ++j) {
                  image = rotacionar90direita(image);
              }
              break;
          }
          case 5: { // Espelhamento
              int horizontal = 0;
              scanf("%d", &horizontal);

              int w = image.widht, h = image.height;

              if (horizontal == 1) w /= 2;
              else h /= 2;

              for (int i2 = 0; i2 < h; ++i2) {
                  for (int j = 0; j < w; ++j) {
                      int x = i2, y = j;

                      if (horizontal == 1) y = image.widht - 1 - j;
                      else x = image.height - 1 - i2;

                      Pixel aux1;
                      aux1.red = image.pixel[i2][j][0];
                      aux1.green = image.pixel[i2][j][1];
                      aux1.blue = image.pixel[i2][j][2];

                      image.pixel[i2][j][0] = image.pixel[x][y][0];
                      image.pixel[i2][j][1] = image.pixel[x][y][1];
                      image.pixel[i2][j][2] = image.pixel[x][y][2];

                      image.pixel[x][y][0] = aux1.red;
                      image.pixel[x][y][1] = aux1.green;
                      image.pixel[x][y][2] = aux1.blue;
                  }
              }
              break;
          }
          case 6: { // Inversao de Cores
              inverter_cores(image.pixel, image.widht, image.height);
              break;
          }
          case 7: { // Cortar Imagem
              int x, y;
              scanf("%d %d", &x, &y);
              int w, h;
              scanf("%d %d", &w, &h);

              image = cortar_imagem(image, x, y, w, h);
              break;
          }
      }

  }
  print_image(image);
}
int main() {
    Image image;
    image = read_image();
    options(image);
    return 0;
}
