#include <cstdlib>
#include "Noise.h"
#include <OpenImageIO/imageio.h>
#include <memory>
OIIO_NAMESPACE_USING

int main()
{
  const char *filename = "foo.tiff";
  constexpr int xres = 640, yres = 480;
  constexpr int channels = 1; // RGB
  int frame=0;

  std::unique_ptr<float []>pixels(new float[xres*yres*channels]);
  ImageOutput *out = ImageOutput::create (filename);
  if (! out)
  {
    return EXIT_FAILURE;
  }
  for(float no=0.001; no<1.0; no+=0.005)
  {
    std::cout<<"frame "<<frame<<" "<<no<<"\n";
  int i=-1;
  Noise n;

  for(int y=0; y<yres; ++y)
  {
    for(int x=0; x<xres; ++x)
    {
//      pixels[++i]=n.complex(12,5.02,0.1,Point(x,y,0.0f));
//      pixels[++i]=n.complex(13,3.02,0.1,Point(x,y,0.0f));
     // pixels[++i]=n.complex(8,8.02,no,Point(x,y,0.0f));
     pixels[++i]=n.noise(no,Point(x,y,0.0f));
//     pixels[++i]=n.noise(0.2,Point(x,y,0.0f));
//     pixels[++i]=n.noise(0.3,Point(x,y,0.0f));
//    pixels[++i]=n.turbulance(0.9,Point(x,y,0.0f));
//    pixels[++i]=n.turbulance(1.09,Point(x,y,0.0f));
   // pixels[++i]=n.turbulance(no,Point(x,y,0.0f));
    }
  }
  ImageSpec spec (xres, yres, channels, TypeDesc::FLOAT);
  char str[40];
  sprintf(str,"noise%03d.tiff",frame++);
  out->open (str, spec);
  out->write_image (TypeDesc::FLOAT, pixels.get());
  out->close ();
  }
  return EXIT_SUCCESS;
}
