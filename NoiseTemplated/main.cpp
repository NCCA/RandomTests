#include <cstdlib>
#include "Noise.h"
#include <OpenImageIO/imageio.h>
#include <memory>
#include <cstdint>
OIIO_NAMESPACE_USING

int main()
{
  constexpr int xres = 1024, yres = 720;
  constexpr int channels = 1; // RGB
  int frame=0;

  std::unique_ptr<float []>pixels(new float[xres*yres*channels]);
  std::unique_ptr <ImageOutput> out( ImageOutput::create ("test.png"));
  ImageSpec spec (xres, yres, channels, TypeDesc::FLOAT);

  Noise<uint_fast8_t> n;

 // for(float no=0.001; no<1.0; no+=0.005)
  for(int f=0; f<200; ++f)
  {
    std::cout<<"frame "<<frame<<" "<<f<<"\n";
  int i=-1;
  n.setSeed(f);
  for(int y=0; y<yres; ++y)
  {
    for(int x=0; x<xres; ++x)
    {
//      pixels[++i]=n.complex(12,5.02,0.1,Point(x,y,0.0f));
      pixels[++i]=n.complex(13,3.02,0.1,Point(x,y,0.0f));
     // pixels[++i]=n.complex(8,8.02,no,Point(x,y,0.0f));
     //pixels[++i]=n.noise(0.55,Point(x,y,0.0f));
//     pixels[++i]=n.noise(0.2,Point(x,y,0.0f));
//     pixels[++i]=n.noise(0.3,Point(x,y,0.0f));
//    pixels[++i]=n.turbulance(0.9,Point(x,y,0.0f));
//    pixels[++i]=n.turbulance(1.09,Point(x,y,0.0f));
   // pixels[++i]=n.turbulance(no,Point(x,y,0.0f));
    }
  }
  char str[40];
  sprintf(str,"noiseSeed%03d.png",frame++);
  out->open (str, spec);
  out->write_image (TypeDesc::FLOAT, pixels.get());
  out->close();
  }
  return EXIT_SUCCESS;
}
