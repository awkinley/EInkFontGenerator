#include <ft2build.h>
#include FT_FREETYPE_H
#include <iostream>

int main(){
  FT_Library library;

  FT_Error error = FT_Init_FreeType( &library );
   if ( error )
    {
      std::cout<<"an error occured during freetype init\n";
    }
   FT_Face face;
   error = FT_New_Face( library, "./fonts/Anonymous.ttf", 0, &face);
   if ( error == FT_Err_Unknown_File_Format )
     {
       std::cout<< "the font file could be opened and read, but it appears that its font format is unsupported";
     }
   else if ( error )
     {
       std::cout<< "another error code means that the font file could not be opened or read, or that it is broken...";
     }
   error = FT_Set_Pixel_Sizes(face, 0, 12);
   if ( error )
     {
       std::cout<< "there was an error setting char size" << std::endl;
     }
   std::cout<<"face has: " << face->num_glyphs <<" faces \n";
   FT_ULong glyph_index = FT_Get_Char_Index( face, 65); //should be 'A'
   std::cout<<"glyph index is " << glyph_index << std::endl;
   error = FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT);
   if(error)
     {
       std::cout<<"there was an error loading the glyph\n";
       std::cout<<"error is " << error << std::endl;
     }
   /*std::cout<<"glyph format is " << face->glyph->format << std::endl;
   std::cout<<"format bitmap " << FT_GLYPH_FORMAT_BITMAP << std::endl;
   std::cout<<"format outline " << FT_GLYPH_FORMAT_OUTLINE << std::endl;
   std::cout<<"format plotter " << FT_GLYPH_FORMAT_PLOTTER << std::endl;*/

   error = FT_Render_Glyph( face->glyph, FT_RENDER_MODE_MONO);
   std::cout<<"bitmap dimensions are (" << face->glyph->bitmap_left << ", " << face->glyph->bitmap_top << ")" << std::endl;
   FT_Bitmap* bitmap = &face->glyph->bitmap;
   std::cout<<bitmap->rows << std::endl;
   std::cout<<bitmap->width << std::endl;
   std::cout<<bitmap->pitch << std::endl;
   std::cout<<bitmap->buffer[0] <<std::endl;
   FT_Int x, y;
   x = 5;
   y = 5;
   FT_Int  i, j, p, q;
   FT_Int  x_max = x + bitmap->width;
   FT_Int  y_max = y + bitmap->rows;

   /* origin is the upper left corner */
   int HEIGHT = 50;
   int WIDTH = 50;
   unsigned char image[HEIGHT][WIDTH];


   /* for simplicity, we assume that `bitmap->pixel_mode' */
   /* is `FT_PIXEL_MODE_GRAY' (i.e., not a bitmap font)   */

   for ( i = x, p = 0; i < x_max; i++, p++ )
     {
       for ( j = y, q = 0; j < y_max; j++, q++ )
         {
           if ( i < 0      || j < 0       ||
                i >= WIDTH || j >= HEIGHT )
             continue;

           image[j][i] = bitmap->buffer[q * bitmap->width + p];
         }
     }

   for ( i = 0; i < HEIGHT; i++ )
     {
       for ( j = 0; j < WIDTH; j++ )
         std::cout<<( image[i][j] == 0 ? ' '
                  : image[i][j] < 128 ? '+'
                  : '*' );
       std::cout<<"|" << std::endl;
     }

}
