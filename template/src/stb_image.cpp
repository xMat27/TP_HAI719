#define STB_IMAGE_IMPLEMENTATION
#include "./stb_image.h"

// unsigned int texture ;
// glGenTextures(1, &texture) ;
// glBindTexture(GL_TEXTURE_2D, texture) ;
// // load and generate the texture
// int width , height , nrChannels ;
// unsigned char *data = stbi_load ( "TwoSidedPlane_BaseColor.png " , &width , &height , &nrChannels , 0);
// if(data){
// glTexImage2D ( GL_TEXTURE_2D , 0 , GL_RGB , width , height , 0 , GL_RGB , GL_UNSIGNED_BYTE , data ) ;
// glGenerateMipmap ( GL_TEXTURE_2D );
// } 
// else{
// std::cout<< " Failed to load texture "<<std::endl ;
// }
// stbi_image_free(data) ;