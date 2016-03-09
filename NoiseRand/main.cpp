#include <cstdlib>
#include "Noise.h"
#include <OpenImageIO/imageio.h>
#include <OpenImageIO/imagebuf.h>
#include <OpenImageIO/imagebufalgo.h>

#include <memory>
#include <cstdint>
OIIO_NAMESPACE_USING

int main()
{
  constexpr int xres = 1024, yres = 720;
  constexpr int channels = 3; // RGB
  int frame=0;

  ImageBuf buff ("myimage", ImageSpec(xres, yres, channels, TypeDesc::FLOAT));

  Noise<unsigned short> n;

  for(float no=0.001; no<1.0; no+=0.005)
  {
    std::cout<<"frame "<<frame<<" "<<no<<"\n";
  int i=-1;
//  n.setSeed(f);
  for(int y=0; y<yres; ++y)
  {
    for(int x=0; x<xres; ++x)
    {
//      pixels[++i]=n.complex(12,5.02,0.1,Point(x,y,0.0f));
 //     pixels[++i]=n.complex(13,3.02,0.1,Point(x,y,0.0f));
     // pixels[++i]=n.complex(8,8.02,no,Point(x,y,0.0f));
     //pixels[++i]=n.noise(0.55,Point(x,y,0.0f));
      float p=n.noise(no,Point(x,y,0.0f));
      float data[3]={0,
                     0,
                     p};
      buff.setpixel(++i,data,3);


//     pixels[++i]=n.noise(0.3,Point(x,y,0.0f));
//    pixels[++i]=n.turbulance(0.9,Point(x,y,0.0f));
//    pixels[++i]=n.turbulance(1.09,Point(x,y,0.0f));
   // pixels[++i]=n.turbulance(no,Point(x,y,0.0f));
    }
  }
  char str[40];
  sprintf(str,"noiseSeed%03d.png",frame++);
  float textColour[]={1,1,0,1};
  char data[50];
  sprintf(data,"noise with rand() seed 1 scale %f",no);
  ImageBufAlgo::render_text (buff,10,50,data, 40, "Arial",textColour );
  buff.write(str);
  }
  return EXIT_SUCCESS;
}
