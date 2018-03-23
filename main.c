#include <stdio.h>

unsigned int count = 0;
unsigned int count_two = 0;

typedef struct _pixel {
  unsigned short int red;
  unsigned short int green;
  unsigned short int blue;
} Pixel;

typedef struct _image {
  Pixel pixel[512][512];
  unsigned int widht;
  unsigned int height;
} Image;

Image read_image();
void change_pixel_color(Image *image, Pixel *media, int *tamanho);
void change_pixel_image_color(Image *image, Pixel *media, int *tamanho);
int max(int a, int b);
int min(int a, int b);
int calculate_average(Image *image);
Pixel copy_pixel(Pixel pixel,Pixel image);
void copy_data(Image *image,int *media);
void print_image(Image image);
Image invert_colors(Image image);
void blur(Image *image);
Image change_color_to_gray(Image image);
Image cut_image(Image img);
Image rotate(Image image);
Image mirror(Image image);
Image filter_sepia(Image image);

int main(){
  Image image;
  image = read_image();

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
        image = filter_sepia(image);
        break;
      }
      case 3: { // Blur
        blur(&image);
        break;
      }
      case 4: { // Rotacao
        image = rotate(image);
        break;
      }
      case 5: { // Espelhamento
        image = mirror(image);
        break;
      }
      case 6: { // Inversao de Cores
        image = invert_colors(image);
        break;
      }
      case 7: { // Cortar Imagem
        image = cut_image(image);
        break;
        }
      }
    }

    print_image(image);
    return 0;
}

int min(int a, int b) {
  if (a > b)
    return b;
  return a;
}
int max(int a, int b) {
  if (a > b)
    return a;
  return b;
}

Pixel copy_pixel(Pixel pixel,Pixel image){
  pixel.red = image.red;
  pixel.green = image.green;
  pixel.blue = image.blue;

  return pixel;
}

int calculate_average(Image *image){
  int media = ((*image).pixel[count][count_two].red +
  (*image).pixel[count][count_two].green +
  (*image).pixel[count][count_two].blue)/3;
return media;
}

void copy_data(Image *image,int *media){
  (*image).pixel[count][count_two].red = *media;
  (*image).pixel[count][count_two].green = *media;
  (*image).pixel[count][count_two].blue = *media;
}

Image change_color_to_gray(Image image) {
  for (count = 0; count < image.height; ++count) {
    for (count_two = 0; count_two < image.widht; ++count_two) {
      int media = calculate_average(&image);
      copy_data(&image, &media);
    }
  }
    return image;
}

void change_pixel_color(Image *image, Pixel *media, int *tamanho){

  int menor_height = min(((*image).height - 1), (count + *tamanho/2));
  int min_widht = min(((*image).widht - 1), (count_two + *tamanho/2));

  for(int x = (max(0, (count - *tamanho/2))) ; x <= menor_height; ++x)  {
    for(int y = (max(0, (count_two - *tamanho/2))) ; y <= min_widht; ++y) {
      (*media).red += (*image).pixel[x][y].red;
      (*media).green += (*image).pixel[x][y].green;
      (*media).blue += (*image).pixel[x][y].blue;
    }
  }
}

void change_pixel_image_color(Image *image, Pixel *media, int *tamanho){
  (*media).red /= *tamanho * *tamanho;
  (*media).green /= *tamanho * *tamanho;
  (*media).blue /= *tamanho * *tamanho;

  (*image).pixel[count][count_two] = copy_pixel((*image).pixel[count][count_two],*media);
}

void blur(Image *image) {
  int tamanho = 0;
  scanf("%d", &tamanho);
  for (count = 0; count < (*image).height; ++count) {
    for (count_two = 0; count_two < (*image).widht; ++count_two) {
      Pixel media = {0, 0, 0};
      change_pixel_color(*(&image), &media, &tamanho);
      change_pixel_image_color(*(&image), &media, &tamanho);
    }
  }
}

int how_many_rotations(){
  scanf("%d", &count);
  count %= 4;
  return count;
}

Image rotate(Image image) {
  int quantas_vezes;
  quantas_vezes = how_many_rotations();
  Image rotacionada;
  for (int j = 0; j < quantas_vezes; ++j) {

    rotacionada.widht = image.height;
    rotacionada.height = image.widht;

    for (unsigned int i = 0, y = 0; i < rotacionada.height; ++i, ++y) {
      for (int j = rotacionada.widht - 1, x = 0; j >= 0; --j, ++x) {
        rotacionada.pixel[i][j] = copy_pixel(rotacionada.pixel[i][j], image.pixel[x][y]);
      }
    }
  }
  return rotacionada;
}

Image invert_colors(Image image) {
  for (unsigned counter = 0; counter < image.height; ++counter) {
    for (unsigned counter_two = 0; counter_two < image.widht; ++counter_two) {
      image.pixel[counter][counter_two].red = 255 - image.pixel[counter][counter_two].red;
      image.pixel[counter][counter_two].green = 255 - image.pixel[counter][counter_two].green;
      image.pixel[counter][counter_two].blue = 255 - image.pixel[counter][counter_two].blue;
    }
  }
  return image;
}

Image cut_image(Image img) {
  Image cortada;

  int x, y;
  scanf("%d %d", &x, &y);
  int w, h;
  scanf("%d %d", &w, &h);

  cortada.widht = w;
  cortada.height = h;

  for(unsigned counter = 0; counter < h; ++counter) {
    for(unsigned counter_two = 0; counter_two < w; ++counter_two) {
      cortada.pixel[counter][counter_two] = copy_pixel(cortada.pixel[counter][counter_two], img.pixel[counter + y][counter_two + x]);
    }
  }

  return cortada;
}

Image read_image() {
  int max_color;
  char p3[4];
  Image image;

  scanf("%s",p3);
  scanf("%u %u", &image.widht, &image.height);
  scanf("%d",&max_color);

  for (unsigned int counter = 0; counter < image.height; ++counter) {
    for (unsigned int counter_two = 0; counter_two < image.widht; ++counter_two) {

      scanf("%hu", &image.pixel[counter][counter_two].red);
      scanf("%hu",&image.pixel[counter][counter_two].green);
      scanf("%hu",&image.pixel[counter][counter_two].blue);
    }
  }
  return image;
}

void print_image(Image image){
  printf("P3\n");
  printf("%u %u\n255\n", image.widht, image.height);

  for (unsigned int counter = 0; counter < image.height; ++counter) {
    for (unsigned int counter_two = 0; counter_two < image.widht; ++counter_two) {
      printf("%hu %hu %hu ", image.pixel[counter][counter_two].red,
        image.pixel[counter][counter_two].green,
        image.pixel[counter][counter_two].blue);

      }
    printf("\n");
  }
}

Image mirror(Image image){
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
      aux1 = copy_pixel(aux1,image.pixel[i2][j]);
      image.pixel[i2][j] = copy_pixel(image.pixel[i2][j],image.pixel[x][y]);
      image.pixel[x][y] = copy_pixel(image.pixel[x][y],aux1);;

    }
  }
  return image;
}

Image filter_sepia(Image image){
  for (unsigned int counter = 0; counter < image.height; ++counter) {
    for (unsigned int counter_two = 0; counter_two < image.widht; ++counter_two) {
      Image pixel;

      pixel.pixel[counter][counter_two] = copy_pixel(pixel.pixel[counter][counter_two],image.pixel[counter][counter_two]);

      int p =  pixel.pixel[counter][counter_two].red * .393 + pixel.pixel[counter][counter_two].green * .769 + pixel.pixel[counter][counter_two].blue * .189;
      int menor_r = (255 >  p) ? p : 255;
      image.pixel[counter][counter_two].red = menor_r;

      p =  pixel.pixel[counter][counter_two].red * .349 + pixel.pixel[counter][counter_two].green * .686 + pixel.pixel[counter][counter_two].blue * .168;
      menor_r = (255 >  p) ? p : 255;
      image.pixel[counter][counter_two].green = menor_r;

      p =  pixel.pixel[counter][counter_two].red * .272 + pixel.pixel[counter][counter_two].green * .534 + pixel.pixel[counter][counter_two].blue * .131;
      menor_r = (255 >  p) ? p : 255;
      image.pixel[counter][counter_two].blue = menor_r;
    }
  }
return image;
}
